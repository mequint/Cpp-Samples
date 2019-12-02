#include "qe/Window/Window.h"

#include <iostream>						// TODO: Replace with a logger...
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

qe::Window::Window(const std::string& title, unsigned int width, unsigned int height) {
	Window(title, sf::Vector2u(width, height));
}

qe::Window::Window(const std::string& title, const sf::Vector2u& windowSize) : 
	m_title(title),
	m_windowSize(windowSize),
	m_backgroundColor(sf::Color::Black),
	m_isDone(false),
	m_isFullscreen(false),
	m_hasFocus(true) {

	_create();
}

qe::Window::~Window() {
	m_window.close();
}

void qe::Window::setBackgroundColor(const sf::Color& color) {
	m_backgroundColor = color;
}

void qe::Window::setCursor(const std::string& filename, const sf::Vector2u& hotspot) {
	sf::Image image;
	if (image.loadFromFile(filename)) {
		sf::Cursor cursor;
		if (cursor.loadFromPixels(image.getPixelsPtr(), image.getSize(), hotspot)) {
			m_window.setMouseCursor(cursor);
		}
	}
}

// Loads a System pre-defined cursor
void qe::Window::setCursor(const CursorType & type) {
	sf::Cursor cursor;
	if (cursor.loadFromSystem(static_cast<sf::Cursor::Type>(type))) {
		m_window.setMouseCursor(cursor);
	}
}

void qe::Window::beginDraw() {
	m_window.clear(m_backgroundColor);
}

void qe::Window::endDraw() {
	m_window.display();
}

void qe::Window::update() {
	sf::Event event;
	while (m_window.pollEvent(event)) {
		if (event.type == sf::Event::LostFocus) {
			m_hasFocus = false;
		}
		else if (event.type == sf::Event::GainedFocus) {
			m_hasFocus = true;
		}

		// Create an event manager class to handle other events
		if (event.type == sf::Event::Closed) {
			m_isDone = true;
		}
	}

	// Have the event manager perform updates
}

bool qe::Window::isDone() { return m_isDone; }

sf::RenderWindow * qe::Window::getRenderWindow() { return &m_window; }

void qe::Window::close() { m_isDone = true; }

void qe::Window::_create() {
	auto style = m_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default;

	m_window.create(sf::VideoMode(m_windowSize.x, m_windowSize.y), m_title, style);
}