#pragma once

#include "GUI_Element.h"

class GUI_Label : public GUI_Element {
public:
	GUI_Label(const std::string& name, GUI_Interface* owner);
	~GUI_Label();

	void ReadIn(std::stringstream& stream);
	void OnClick(const sf::Vector2f& mousePos);
	void OnRelease();
	void OnHover(const sf::Vector2f& mousePos);
	void OnLeave();
	void Update(float dt);
	void Draw(sf::RenderTarget* target);
};