#pragma once

#include "GUI_Element.h"

enum class SliderType { Horizontal, Vertical };

class GUI_Scrollbar : public GUI_Element {
public:
	GUI_Scrollbar(const std::string& name, GUI_Interface* owner);
	~GUI_Scrollbar();

	void SetPosition(const sf::Vector2f& pos);

	void ReadIn(std::stringstream& stream);
	
	void OnClick(const sf::Vector2f& mousePos);
	void OnRelease();
	void OnHover(const sf::Vector2f& mousePos);
	void OnLeave();

	void ApplyStyle();
	void UpdateStyle(const GUI_ElementState& state, const GUI_Style& style);

	void Update(float dt);
	void Draw(sf::RenderTarget* target);

private:
	SliderType m_sliderType;
	sf::RectangleShape m_slider;
	sf::Vector2f m_moveMouseLast;

	int m_percentage;
};