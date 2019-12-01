#include "GUI_Scrollbar.h"

#include <sstream>

#include "GUI_Interface.h"
#include "GUI_Manager.h"
#include "SharedContext.h"
#include "Window.h"

GUI_Scrollbar::GUI_Scrollbar(const std::string & name, GUI_Interface * owner) :
	GUI_Element(name, GUI_ElementType::Scrollbar, owner) {
	m_isControl = true;
}

GUI_Scrollbar::~GUI_Scrollbar() = default;

void GUI_Scrollbar::SetPosition(const sf::Vector2f & pos) {
	GUI_Element::SetPosition(pos);

	if (m_sliderType == SliderType::Horizontal) {
		m_position.x = 0;
	}
	else {
		m_position.y = 0;
	}
}

void GUI_Scrollbar::ReadIn(std::stringstream& stream) {
	std::string type;
	stream >> type;

	if (type == "Horizontal") {
		m_sliderType = SliderType::Horizontal;
		m_slider.setPosition(0.0f, GetPosition().y);
	}
	else {
		m_sliderType = SliderType::Vertical;
		m_slider.setPosition(GetPosition().x, 0.0f);
	}
}

void GUI_Scrollbar::OnClick(const sf::Vector2f & mousePos) {
	if (!m_slider.getGlobalBounds().contains(mousePos - m_owner->GetPosition())) return;

	SetState(GUI_ElementState::Clicked);
	m_moveMouseLast = mousePos;
}

void GUI_Scrollbar::OnRelease() {
	SetState(GUI_ElementState::Neutral);
}

void GUI_Scrollbar::OnHover(const sf::Vector2f & mousePos) {
	SetState(GUI_ElementState::Focused);
}

void GUI_Scrollbar::OnLeave() {
	SetState(GUI_ElementState::Neutral);
}

void GUI_Scrollbar::ApplyStyle() {
	GUI_Element::ApplyStyle();

	m_slider.setFillColor(m_style[m_state].m_elementColor);

	bool horizontal = (m_sliderType == SliderType::Horizontal);

	auto& bgSolid = m_visual.m_backgroundSolid;

	SetPosition(horizontal ? 
		sf::Vector2f(0.0f, m_owner->GetSize().y - bgSolid.getSize().y) :
		sf::Vector2f(m_owner->GetSize().x - bgSolid.getSize().x, 0.0f));
	bgSolid.setSize(horizontal ?
		sf::Vector2f(m_owner->GetSize().x, m_style[m_state].m_size.y) :
		sf::Vector2f(m_style[m_state].m_size.x, m_owner->GetSize().y));
	m_slider.setPosition(
		(horizontal ? m_slider.getPosition().x : GetPosition().x),
		(horizontal ? GetPosition().y : m_slider.getPosition().y));

	float sizeFactor = (horizontal ?
		m_owner->GetContentSize().x / m_owner->GetSize().x :
		m_owner->GetContentSize().y / m_owner->GetSize().y);

	if (sizeFactor < 1.0f) {
		sizeFactor = 1.0f;
	}

	float sliderSize = (horizontal ? m_owner->GetSize().x : m_owner->GetSize().y) / sizeFactor;

	m_slider.setSize(horizontal ?
		sf::Vector2f(sliderSize, bgSolid.getSize().y) :
		sf::Vector2f(bgSolid.getSize().x, sliderSize));
	bgSolid.setPosition(GetPosition());
}

void GUI_Scrollbar::UpdateStyle(const GUI_ElementState & state, const GUI_Style & style) {
	GUI_Element::UpdateStyle(state, style);

	if (m_sliderType == SliderType::Horizontal) {
		m_style[state].m_size.x = m_owner->GetSize().x;
	}
	else {
		m_style[state].m_size.y = m_owner->GetSize().y;
	}
}

void GUI_Scrollbar::Update(float dt) {
	if (GetState() != GUI_ElementState::Clicked) return;

	SharedContext* context = m_owner->GetManager()->GetContext();
	sf::Vector2f mousePos = sf::Vector2f(context->m_eventManager->GetMousePos(
		context->m_window->GetRenderWindow()));

	if (m_moveMouseLast == mousePos) return;

	sf::Vector2f difference = mousePos - m_moveMouseLast;
	m_moveMouseLast = mousePos;

	bool horizontal = (m_sliderType == SliderType::Horizontal);
	m_slider.move(
		horizontal ? difference.x : 0.0f, 
		horizontal ? 0.0f : difference.y);

	if (horizontal && m_slider.getPosition().x < 0.0f) {
		m_slider.setPosition(0.0f, m_slider.getPosition().y);
	}
	else if (m_slider.getPosition().y < 0.0f) {
		m_slider.setPosition(m_slider.getPosition().x, 0.0f);
	}

	if (horizontal && (m_slider.getPosition().x + m_slider.getSize().x > m_owner->GetSize().x)) {
		m_slider.setPosition(0.0f, m_slider.getPosition().y);
	}
	else if (m_slider.getPosition().y + m_slider.getSize().y > m_owner->GetSize().y) {
		m_slider.setPosition(m_slider.getPosition().x, m_owner->GetSize().y - m_slider.getSize().y);
	}

	float workArea = (horizontal ? m_owner->GetSize().x - m_slider.getSize().x :
		m_owner->GetSize().y - m_slider.getSize().y);

	int percentage = static_cast<int>(((horizontal ? m_slider.getPosition().x : m_slider.getPosition().y) / 
		workArea) * 100.0f);

	if (horizontal) {
		m_owner->UpdateScrollHorizontal(percentage);
	}
	else {
		m_owner->UpdateScrollVertical(percentage);
	}

	SetRedraw(true);
}

void GUI_Scrollbar::Draw(sf::RenderTarget * target) {
	target->draw(m_visual.m_backgroundSolid);
	target->draw(m_slider);
}
