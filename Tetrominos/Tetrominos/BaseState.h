#pragma once

#include <SFML/Graphics.hpp>

class BaseState
{
	public:
		BaseState() {}
		virtual ~BaseState() {}

		virtual void Create() = 0;
		virtual void Destroy() = 0;

		virtual void Activate() = 0;
		virtual void Deactivate() = 0;

		virtual void Update(const sf::Time& time) = 0; 
		virtual void Draw(sf::RenderWindow& window) = 0;
		virtual void HandleEvent(sf::Event& event) = 0;
};