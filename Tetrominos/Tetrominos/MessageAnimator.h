#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "Tweener.h"

class MessageAnimator
{
	public:
		MessageAnimator(int sreenWidth, int screenHeight);

		void SetMessage(std::string& message);

		void Update(float dt);
		void Draw(sf::RenderWindow& window);

		void Start();

		bool IsAnimationComplete();

	private:
		
		bool m_playing;

		sf::Font m_font;
		std::string m_message;

		int m_screenWidth, m_screenHeight;

		FloatTweener m_scaleTweener;
		FloatTweener m_alphaTweener;
		FloatTweener m_waitTweener;
};