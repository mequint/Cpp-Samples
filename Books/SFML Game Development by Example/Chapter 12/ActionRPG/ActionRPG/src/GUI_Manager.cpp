#include "GUI_Manager.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "SharedContext.h"
#include "Utilities.h"
#include "Window.h"

GUI_Manager::GUI_Manager(EventManager* eventManager, SharedContext* context) :
	m_eventManager(eventManager),
	m_context(context),
	m_currentState(StateType(0)) {

	RegisterElement<GUI_Label>(GUI_ElementType::Label);
	RegisterElement<GUI_Scrollbar>(GUI_ElementType::Scrollbar);
	RegisterElement<GUI_Textfield>(GUI_ElementType::Textfield);

	m_elemTypes.emplace("Label", GUI_ElementType::Label);
	m_elemTypes.emplace("Button", GUI_ElementType::Button);
	m_elemTypes.emplace("Scrollbar", GUI_ElementType::Scrollbar);
	m_elemTypes.emplace("TextField", GUI_ElementType::Textfield);
	m_elemTypes.emplace("Interface", GUI_ElementType::Window);

	m_eventManager->AddCallback(StateType(0), "Mouse_Left", &GUI_Manager::HandleClick, this);
	m_eventManager->AddCallback(StateType(0), "Mouse_Left_Release", &GUI_Manager::HandleRelease, this);
	m_eventManager->AddCallback(StateType(0), "Text_Entered", &GUI_Manager::HandleTextEntered, this);
}

GUI_Manager::~GUI_Manager() {
	m_eventManager->RemoveCallback(StateType(0), "Mouse_Left");
	m_eventManager->RemoveCallback(StateType(0), "Mouse_Left_Release");
	m_eventManager->RemoveCallback(StateType(0), "Text_Entered");

	for (auto& iter : m_interfaces) {
		for (auto& iter2 : iter.second) {
			delete iter2.second;
		}
	}
}

bool GUI_Manager::AddInterface(const StateType& state, const std::string& name) {
	auto s = m_interfaces.emplace(state, GUI_Interfaces()).first;

	GUI_Interface* temp = new GUI_Interface(name, this);
	if (s->second.emplace(name, temp).second) return true;

	delete temp;
	return false;
}

GUI_Interface* GUI_Manager::GetInterface(const StateType& state, const std::string& name) {
	auto s = m_interfaces.find(state);
	if (s == m_interfaces.end()) return nullptr;
	
	auto i = s->second.find(name);

	return (i != s->second.end() ? i->second : nullptr);
}

bool GUI_Manager::RemoveInterface(const StateType& state, const std::string& name) {
	auto s = m_interfaces.find(state);
	if (s == m_interfaces.end()) return false;

	auto i = s->second.find(name);
	if (i == s->second.end()) return false;

	delete i->second;

	return s->second.erase(name);
}

bool GUI_Manager::LoadInterface(const StateType& state, const std::string& interfaceFile, const std::string& name) {
	std::ifstream file;
	file.open(Utils::GetWorkingDirectory() + "media/GUI_Interfaces/" + interfaceFile);
	
	if (!file.is_open()) {
		std::cout << "! Failed to load: " << interfaceFile << std::endl;
		return false;
	}

	std::string line;
	std::string interfaceName;
	
	while (std::getline(file, line)) {
		if (line[0] == '|') continue;

		std::stringstream keystream(line);
		std::string key;
		keystream >> key;

		if (key == "Interface") {
			std::string style;
			keystream >> interfaceName >> style;

			if (!AddInterface(state, name)) {
				std::cout << "Failed adding interface: " << name << std::endl;
				return false;
			}

			GUI_Interface* i = GetInterface(state, name);
			keystream >> *i;

			if (!LoadStyle(style, i)) {
				std::cout << "Failed loading style file: " << style << " for interface " << name << std::endl;
			}

			i->SetContentSize(i->GetSize());
		}
		else if (key == "Element") {
			if (interfaceName == "") {
				std::cout << "Error: 'Element' outside or before declaration of 'Interface'!" << std::endl;
				continue;
			}

			std::string type;
			std::string elementName;
			sf::Vector2f position;
			std::string style;
			keystream >> type >> elementName >> position.x >> position.y >> style;

			GUI_ElementType eType = StringToType(type);
			if (eType == GUI_ElementType::None) {
				std::cout << "Unknown element('" << elementName << "') type: '" << type << "'" << std::endl;
				continue;
			}

			GUI_Interface* i = GetInterface(state, name);
			if (!i) continue;
			if (!i->AddElement(eType, elementName)) continue;

			GUI_Element* e = i->GetElement(elementName);
			keystream >> *e;

			e->SetPosition(position);

			if (!LoadStyle(style, e)) {
				std::cout << "Failed loading style file: " << style << " for element " << elementName << std::endl;
				continue;
			}
		}
	}

	file.close();
	return true;
}

void GUI_Manager::SetCurrentState(const StateType& state) {
	if (m_currentState == state) return;

	HandleRelease(nullptr);
	m_currentState = state;
}

SharedContext * GUI_Manager::GetContext() { return m_context; }

void GUI_Manager::DefocusAllInterfaces() {
	auto state = m_interfaces.find(m_currentState);
	if (state == m_interfaces.end()) return;

	for (auto& iter : state->second) {
		iter.second->Defocus();
	}
}

void GUI_Manager::HandleClick(EventDetails* details) {
	auto state = m_interfaces.find(m_currentState);
	if (state == m_interfaces.end()) return;

	sf::Vector2i mousePos = m_eventManager->GetMousePos(m_context->m_window->GetRenderWindow());

	for (auto iter = state->second.rbegin(); iter != state->second.rend(); ++iter) {
		if (!iter->second->IsInside(sf::Vector2f(mousePos))) continue;
		if (!iter->second->IsActive()) return;

		iter->second->OnClick(sf::Vector2f(mousePos));
		iter->second->Focus();

		if (iter->second->IsBeingMoved()) {
			iter->second->BeginMoving();
		}

		return;
	}
}

void GUI_Manager::HandleRelease(EventDetails* details) {
	auto state = m_interfaces.find(m_currentState);
	if (state == m_interfaces.end()) return;

	for (auto& iter : state->second) {
		GUI_Interface* i = iter.second;

		if (!i->IsActive()) continue;
		if (i->GetState() == GUI_ElementState::Clicked) {
			i->OnRelease();
		}

		if (i->IsBeingMoved()) {
			i->StopMoving();
		}
	}
}

void GUI_Manager::HandleTextEntered(EventDetails* details) {
	auto state = m_interfaces.find(m_currentState);
	if (state == m_interfaces.end()) return;

	for (auto& iter : state->second) {
		if (!iter.second->IsActive()) continue;
		if (!iter.second->IsFocused()) continue;

		iter.second->OnTextEntered(details->m_textEntered);
		return;
	}
}

void GUI_Manager::AddEvent(GUI_Event& event) {
	m_events[m_currentState].push_back(event);
}

bool GUI_Manager::PollEvent(GUI_Event& event) {
	if (m_events[m_currentState].empty()) return false;

	event = m_events[m_currentState].back();
	m_events[m_currentState].pop_back();

	return true;
}

void GUI_Manager::Update(float dt) {
	sf::Vector2f mousePos = static_cast<sf::Vector2f>(m_eventManager->GetMousePos(m_context->m_window->GetRenderWindow()));

	auto state = m_interfaces.find(m_currentState);
	if (state == m_interfaces.end()) return;

	for (auto iter = state->second.rbegin(); iter != state->second.rend(); ++iter) {
		GUI_Interface* i = iter->second;
		if (!i->IsActive()) continue;

		i->Update(dt);

		if (i->IsBeingMoved()) continue;
		if (i->IsInside(sf::Vector2f(mousePos))) {
			if (i->GetState() == GUI_ElementState::Neutral) {
				i->OnHover(sf::Vector2f(mousePos));
			}

			return;
		}
		else if (i->GetState() == GUI_ElementState::Focused) {
			i->OnLeave();
		}
	}
}

void GUI_Manager::Render(sf::RenderWindow * window) {
	auto state = m_interfaces.find(m_currentState);
	if (state == m_interfaces.end()) return;

	for (auto& iter : state->second) {
		GUI_Interface* i = iter.second;

		if (!i->IsActive()) continue;

		if (i->NeedsRedraw()) { i->Redraw(); }
		if (i->NeedsContentRedraw()) { i->RedrawContent(); }
		if (i->NeedsControlRedraw()) { i->RedrawControls(); }

		i->Draw(window);
	}
}

GUI_Element * GUI_Manager::CreateElement(const GUI_ElementType & id, GUI_Interface * owner) {
	if (id == GUI_ElementType::Window) {
		return new GUI_Interface("", this);
	}

	auto f = m_factory.find(id);
	return (f != m_factory.end() ? f->second(owner) : nullptr);
}

GUI_ElementType GUI_Manager::StringToType(const std::string & str) {
	auto t = m_elemTypes.find(str);

	return (t != m_elemTypes.end() ? t->second : GUI_ElementType::None);
}

bool GUI_Manager::LoadStyle(const std::string & filename, GUI_Element * element) {
	std::ifstream file;
	file.open(Utils::GetWorkingDirectory() + "media/GUI_Styles/" + filename);

	std::string currentState;
	GUI_Style parentStyle;
	GUI_Style temporaryStyle;

	if (!file.is_open()) {
		std::cout << "! Failed to load: " << filename << std::endl;
		return false;
	}

	std::string line;
	while (std::getline(file, line)) {
		if (line[0] == '|') continue;

		std::stringstream keystream(line);
		std::string type;
		keystream >> type;

		if (type == "") continue;

		if (type == "State") {
			if (currentState != "") {
				std::cout << "Error: 'State' keyword found inside another state!" << std::endl;
				continue;
			}

			keystream >> currentState;
		}
		else if (type == "/State") {
			if (currentState == "") {
				std::cout << "Error: '/State' keyword found prior to 'State'!" << std::endl;
				continue;
			}

			GUI_ElementState state = GUI_ElementState::Neutral;
			if (currentState == "Hover") {
				state = GUI_ElementState::Focused;
			}
			else if (currentState == "Clicked") {
				state = GUI_ElementState::Clicked;
			}

			if (state == GUI_ElementState::Neutral) {
				parentStyle = temporaryStyle;
				element->UpdateStyle(GUI_ElementState::Neutral, temporaryStyle);
				element->UpdateStyle(GUI_ElementState::Focused, temporaryStyle);
				element->UpdateStyle(GUI_ElementState::Clicked, temporaryStyle);
			}
			else {
				element->UpdateStyle(state, temporaryStyle);
			}

			temporaryStyle = parentStyle;
			currentState = "";
		}
		else {
			if (currentState == "") {
				std::cout << "Error: '" << type << "' keyword found outside of a state!" << std::endl;
				continue;
			}

			if (type == "Size") {
				keystream >> temporaryStyle.m_size.x >> temporaryStyle.m_size.y;
			}
			else if (type == "BgColor") {
				int r, g, b, a = 0;
				keystream >> r >> g >> b >> a;
				temporaryStyle.m_backgroundColor = sf::Color(r, g, b, a);
			}
			else if (type == "BgImage") {
				keystream >> temporaryStyle.m_backgroundImage;
			}
			else if (type == "BgImageColor") {
				int r, g, b, a = 0;
				keystream >> r >> g >> b >> a;
				temporaryStyle.m_backgroundImageColor = sf::Color(r, g, b, a);
			}
			else if (type == "TextColor") {
				int r, g, b, a = 0;
				keystream >> r >> g >> b >> a;
				temporaryStyle.m_textColor = sf::Color(r, g, b, a);
			}
			else if (type == "TextSize") {
				keystream >> temporaryStyle.m_textSize;
			}
			else if (type == "TextOriginCenter") {
				temporaryStyle.m_textCenterOrigin = true;
			}
			else if (type == "Font") {
				keystream >> temporaryStyle.m_textFont;
			}
			else if (type == "TextPadding") {
				keystream >> temporaryStyle.m_textPadding.x >> temporaryStyle.m_textPadding.y;
			}
			else if (type == "ElementColor") {
				int r, g, b, a = 0;
				keystream >> r >> g >> b >> a;
				temporaryStyle.m_elementColor = sf::Color(r, g, b, a);
			}
			else if (type == "Glyph") {
				keystream >> temporaryStyle.m_glyph;
			}
			else if (type == "GlyphPadding") {
				keystream >> temporaryStyle.m_glyphPadding.x >> temporaryStyle.m_glyphPadding.y;
			}
			else {
				std::cout << "Error: Style tag '" << type << "' is unknown!" << std::endl;
			}
		}
	}

	file.close();
	return true;
}