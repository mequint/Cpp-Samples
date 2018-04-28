#pragma once

#include <SFML/Graphics.hpp>
#include <string>

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

	WindowSettings(const std::string& title, int width, int height, int BitsPerPixel = 32, bool fullscreen = false) :
		Title(title), Width(width), Height(height), Fullscreen(fullscreen), Focused(true)
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

		IProjector* GetProjector();
		sf::RenderWindow* GetRenderWindow();
		int GetWidth() const;
		int GetHeight() const;

	private:
		void toggleFullscreen();

		void create();

		WindowSettings m_windowSettings;
		bool m_isDone;

		sf::RenderWindow m_window;
		IProjector* m_pProjector;
};