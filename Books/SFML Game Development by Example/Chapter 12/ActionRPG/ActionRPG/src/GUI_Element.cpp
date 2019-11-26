#include "GUI_Element.h"

#include "FontManager.h"
#include "GUI_Interface.h"
#include "GUI_Manager.h"
#include "TextureManager.h"

GUI_Element::GUI_Element(const std::string & name, const GUI_ElementType & type, GUI_Interface * owner) :
	m_name(name),
	m_type(type),
	m_state(GUI_ElementState::Neutral),
	m_owner(owner),
	m_needsRedraw(false),
	m_active(true),
	m_isControl(false) {}

GUI_Element::~GUI_Element() {
	ReleaseResources();
}

void GUI_Element::UpdateStyle(const GUI_ElementState & state, const GUI_Style & style) {
	if (style.m_backgroundImage != m_style[state].m_backgroundImage) {
		ReleaseTexture(m_style[state].m_backgroundImage);
		RequireTexture(style.m_backgroundImage);
	}

	if (style.m_glyph != m_style[state].m_glyph) {
		ReleaseTexture(m_style[state].m_glyph);
		RequireTexture(style.m_glyph);
	}

	if (style.m_textFont != m_style[state].m_textFont) {
		ReleaseFont(m_style[state].m_textFont);
		RequireFont(style.m_textFont);
	}

	m_style[state] = style;
	if (state == m_state) {
		SetRedraw(true);
		ApplyStyle();
	}
}

void GUI_Element::ApplyStyle() {
	ApplyTextStyle();
	ApplyBgStyle();
	ApplyGlyphStyle();

	if (m_owner != this && !IsControl()) {
		m_owner->AdjustContentSize(this);
	}
}

GUI_ElementType GUI_Element::GetType() { return m_type; }

const std::string & GUI_Element::GetName() const { return m_name; }
void GUI_Element::SetName(const std::string & name) { m_name = name; }

const sf::Vector2f & GUI_Element::GetPosition() const { return m_position; }
void GUI_Element::SetPosition(const sf::Vector2f & pos) { 
	m_position = pos; 
	if (m_owner == nullptr || m_owner == this) return;

	const auto& padding = m_owner->GetPadding();
	if (m_position.x < padding.x) { m_position.x = padding.x; }
	if (m_position.y < padding.y) { m_position.y = padding.y; }
}

const sf::Vector2f & GUI_Element::GetSize() const {
	return m_style.at(m_state).m_size;
}

GUI_ElementState GUI_Element::GetState() const { return m_state; }
void GUI_Element::SetState(const GUI_ElementState & state) {
	if (m_state == state) return;

	m_state = state;
	SetRedraw(true);
}

void GUI_Element::SetRedraw(bool redraw) { m_needsRedraw = redraw; }
bool GUI_Element::NeedsRedraw() const { return m_needsRedraw; }

void GUI_Element::SetOwner(GUI_Interface * owner) { m_owner = owner; }
GUI_Interface * GUI_Element::GetOwner() const { return m_owner; }
bool GUI_Element::HasOwner() const { return m_owner != nullptr; }

bool GUI_Element::IsActive() const { return m_active; }
void GUI_Element::SetActive(bool active) { m_active = active; }

bool GUI_Element::IsInside(const sf::Vector2f & point) const {
	sf::Vector2f position = GetGlobalPosition();

	return (point.x >= position.x &&
		point.y >= position.y &&
		point.x <= position.x + m_style.at(m_state).m_size.x &&
		point.y <= position.y + m_style.at(m_state).m_size.y);
}

sf::Vector2f GUI_Element::GetGlobalPosition() const {
	sf::Vector2f position = GetPosition();
	if (m_owner == nullptr || m_owner == this) return position;

	position += m_owner->GetGlobalPosition();

	if (IsControl()) return position;

	position.x -= m_owner->m_scrollHorizontal;
	position.y -= m_owner->m_scrollVertical;

	return position;
}

bool GUI_Element::IsControl() const { return m_isControl; }

std::string GUI_Element::GetText() const { return m_visual.m_text.getString(); }
void GUI_Element::SetText(const std::string & text) {
	m_visual.m_text.setString(text);
	SetRedraw(true);
}

void GUI_Element::ApplyTextStyle() {
	FontManager* fonts = m_owner->GetManager()->GetContext()->m_fontManager;
	const GUI_Style& currentStyle = m_style[m_state];

	if (currentStyle.m_textFont != "") {
		m_visual.m_text.setFont(*fonts->GetResource(currentStyle.m_textFont));
		m_visual.m_text.setFillColor(currentStyle.m_textColor);
		m_visual.m_text.setCharacterSize(currentStyle.m_textSize);

		if (currentStyle.m_textCenterOrigin) {
			sf::FloatRect rect = m_visual.m_text.getLocalBounds();
			m_visual.m_text.setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
		}
		else {
			m_visual.m_text.setOrigin(0.0f, 0.0f);
		}
	}

	m_visual.m_text.setPosition(m_position + currentStyle.m_textPadding);
}

void GUI_Element::ApplyBgStyle() {
	TextureManager* textures = m_owner->GetManager()->GetContext()->m_textureManager;
	const GUI_Style& currentStyle = m_style[m_state];

	if (currentStyle.m_backgroundImage != "") {
		m_visual.m_backgroundImage.setTexture(*textures->GetResource(currentStyle.m_backgroundImage));
		m_visual.m_backgroundImage.setColor(currentStyle.m_backgroundImageColor);
	}

	m_visual.m_backgroundImage.setPosition(m_position);
	m_visual.m_backgroundSolid.setSize(sf::Vector2f(currentStyle.m_size));
	m_visual.m_backgroundSolid.setFillColor(currentStyle.m_backgroundColor);
	m_visual.m_backgroundSolid.setPosition(m_position);
}

void GUI_Element::ApplyGlyphStyle() {
	const GUI_Style& currentStyle = m_style[m_state];

	TextureManager* textures = m_owner->GetManager()->GetContext()->m_textureManager;
	if (currentStyle.m_glyph != "") {
		m_visual.m_glyph.setTexture(*textures->GetResource(currentStyle.m_glyph));
	}

	m_visual.m_glyph.setPosition(m_position + currentStyle.m_glyphPadding);
}

void GUI_Element::RequireTexture(const std::string & name) {
	if (name == "") return;
	m_owner->GetManager()->GetContext()->m_textureManager->RequireResource(name);
}

void GUI_Element::RequireFont(const std::string & name) {
	if (name == "") return;
	m_owner->GetManager()->GetContext()->m_fontManager->RequireResource(name);
}

void GUI_Element::ReleaseTexture(const std::string & name) {
	if (name == "") return;
	m_owner->GetManager()->GetContext()->m_textureManager->ReleaseResource(name);
	
}

void GUI_Element::ReleaseFont(const std::string & name) {
	if (name == "") return;
	m_owner->GetManager()->GetContext()->m_fontManager->ReleaseResource(name);
}

void GUI_Element::ReleaseResources() {
	for (auto& iter : m_style) {
		ReleaseTexture(iter.second.m_backgroundImage);
		ReleaseTexture(iter.second.m_glyph);
		ReleaseFont(iter.second.m_textFont);
	}
}