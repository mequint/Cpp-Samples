#include "GUI_Label.h"

#include "Utilities.h"

GUI_Label::GUI_Label(const std::string & name, GUI_Interface * owner) :
	GUI_Element(name, GUI_ElementType::Label, owner) {}

GUI_Label::~GUI_Label() = default;

void GUI_Label::ReadIn(std::stringstream & stream) {
	std::string content;
	Utils::ReadQuotedString(stream, content);
	m_visual.m_text.setString(content);
}

void GUI_Label::OnClick(const sf::Vector2f & mousePos) {
	SetState(GUI_ElementState::Clicked);
}

void GUI_Label::OnRelease() {
	SetState(GUI_ElementState::Neutral);
}

void GUI_Label::OnHover(const sf::Vector2f & mousePos) {
	SetState(GUI_ElementState::Focused);
}

void GUI_Label::OnLeave() {
	SetState(GUI_ElementState::Neutral);
}

void GUI_Label::Update(float dt) {}

void GUI_Label::Draw(sf::RenderTarget * target) {
	target->draw(m_visual.m_backgroundSolid);
	if (m_style[m_state].m_glyph != "") {
		target->draw(m_visual.m_glyph);
	}

	target->draw(m_visual.m_text);
}