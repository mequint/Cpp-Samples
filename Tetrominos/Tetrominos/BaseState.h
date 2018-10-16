#pragma once

#include <SFML/Graphics.hpp>

class StateManager;

class BaseState
{
	friend class StateManager;

	public:
		BaseState(StateManager* stateManager) : m_stateManager(stateManager) {}
		virtual ~BaseState() {}

		virtual void Create() = 0;
		virtual void Destroy() = 0;

		virtual void Activate() = 0;
		virtual void Deactivate() = 0;

		virtual void HandleEvents() = 0;
		virtual void Update(const sf::Time& time) = 0; 
		virtual void Draw() = 0;

	protected:
		StateManager * m_stateManager;
};