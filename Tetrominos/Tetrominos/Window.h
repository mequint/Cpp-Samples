#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "EventManager.h"
#include "Projector.h"

struct WindowSettings
{
	std::string Title;
	int Width, Height;
	int BitsPerPixel;
	bool Fullscreen;
	bool Focused;

	WindowSettings() : 
		WindowSettings("Test Program", 800, 600)
	{
	}

	WindowSettings(const std::string& title, int width, int height, int bitsPerPixel = 32, bool fullscreen = false) :
		Title(title), Width(width), Height(height), BitsPerPixel(bitsPerPixel), Fullscreen(fullscreen), Focused(true)
	{

	}
};

class Window
{
	public:
		Window();
		Window(const WindowSettings& windowSettings, ProjectorType projectorType = ProjectorType::Orthographic);
		~Window();

		void BeginDraw();
		void EndDraw();

		void Update();
		
		bool IsDone() const;
		bool IsFullscreen() const;
		bool HasFocus() const;

		IProjector* GetProjector();
		sf::RenderWindow* GetRenderWindow();
		EventManager* GetEventManager();
		int GetWidth() const;
		int GetHeight() const;

	private:
		// Callback functions
		void close(EventDetails* details);
		void toggleFullscreen(EventDetails* details);

		void create();

		WindowSettings m_windowSettings;
		bool m_isDone;

		sf::RenderWindow m_window;
		EventManager m_eventManager;
		IProjector* m_pProjector;
};