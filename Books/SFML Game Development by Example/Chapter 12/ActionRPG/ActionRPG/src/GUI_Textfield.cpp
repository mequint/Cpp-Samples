#include "GUI_Textfield.h"

#include "Utilities.h"

GUI_Textfield::GUI_Textfield(const std::string & name, GUI_Interface * owner) :
	GUI_Element(name, GUI_ElementType::Textfield, owner) {}

GUI_Textfield::~GUI_Textfield() = default;

void GUI_Textfield::ReadIn(std::stringstream & stream) {
	std::string content;
	Utils::ReadQuotedString(stream, content);
	m_visual.m_text.setString(content);
}

void GUI_Textfield::OnClick(const sf::Vector2f & mousePos) {
	SetState(GUI_ElementState::Clicked);
}

void GUI_Textfield::OnRelease() {}

void GUI_Textfield::OnHover(const sf::Vector2f & mousePos) {
	SetState(GUI_ElementState::Focused);
}

void GUI_Textfield::OnLeave() {
	SetState(GUI_ElementState::Neutral);
}

void GUI_Textfield::Update(float dt) {}

void GUI_Textfield::Draw(sf::RenderTarget* target) {
	target->draw(m_visual.m_backgroundSolid);
	if (m_style[m_state].m_glyph != "") {
		target->draw(m_visual.m_glyph);
	}

	target->draw(m_visual.m_text);
}