#pragma once

#include <queue>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "Tweener.h"

class MessageAnimator
{
	public:
		MessageAnimator();

		void AddMessage(std::string& message);

		void Update(float dt);
		void Draw(sf::RenderWindow& window);

		void Start();

		bool IsAnimationComplete();

	private:
		
		sf::Font m_font;
		std::queue<std::string> m_messages;

		FloatTweener m_scaleTweener;
		FloatTweener m_alphaTweener;
		FloatTweener m_waitTweener;
};