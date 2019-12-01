#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class DebugOverlay {
public:
	DebugOverlay() {
		m_debug = false;
	}

	~DebugOverlay() {
		while (m_drawables.begin() != m_drawables.end()) {
			delete m_drawables.back();
			m_drawables.pop_back();
		}
	}

	void Add(sf::Drawable* drawable) {
		m_drawables.push_back(drawable);
	}

	void Draw(sf::RenderWindow* window) {
		while (m_drawables.begin() != m_drawables.end()) {
			window->draw(*m_drawables.back());
			delete m_drawables.back();
			m_drawables.pop_back();
		}
	}

	bool Debug() { return m_debug; }
	void SetDebug(bool debug) { m_debug = debug; }

private:
	std::vector<sf::Drawable*> m_drawables;
	bool m_debug;
};