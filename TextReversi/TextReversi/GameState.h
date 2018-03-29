#pragma once

class GameState
{
	public:
		virtual ~GameState() {}

		virtual void GetInput() = 0;
		virtual void Update() = 0;
		virtual void Display() = 0;
};