#pragma once

#include <SFML/Graphics.hpp>

#include "Tweener.h"

class Anim_DestroyBlock
{
	public:
		Anim_DestroyBlock(sf::RectangleShape& rectangle);

		void Update(float dt);
		void Draw(sf::RenderWindow& window);

		void Play();
		bool IsPlaying();

		bool IsComplete();

	private:
		sf::RectangleShape& m_rectShape;

		Tweener<float> m_scaleTweener;
		Tweener<int> m_alphaTweener;

		bool m_isComplete;
};