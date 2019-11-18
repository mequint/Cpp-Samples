#pragma once

#include <SFML/Graphics.hpp>

class StateManager;

class BaseState {
	friend class StateManager;
public:
	BaseState(StateManager* stateManager) :
		m_stateManager(stateManager),
		m_transparent(false),
		m_transcendent(false) {}

	virtual ~BaseState() = default;

	virtual void OnCreate() = 0;
	virtual void OnDestroy() = 0;

	virtual void Activate() = 0;
	virtual void Deactivate() = 0;

	virtual void Update(const sf::Time& time) = 0;
	virtual void Draw() = 0;

	void SetTransparent(bool transparent) { m_transparent = transparent; }
	void SetTranscendent(bool transcendent) { m_transcendent = transcendent; }
	bool IsTransparent() const { return m_transparent; }
	bool IsTranscendent() const { return m_transcendent; }

	sf::View& GetView() { return m_view; }
	StateManager* GetStateManager() { return m_stateManager; }

protected:
	StateManager* m_stateManager;
	bool m_transparent;
	bool m_transcendent;

	sf::View m_view;
};