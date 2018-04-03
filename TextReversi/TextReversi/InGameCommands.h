#pragma once

enum class InGameCommands
{
	Move,
	Save,
	Load,
	Quit,
	PrintBoard,
	Options
};

struct Move
{
	InGameCommands Command;
	int Row;
	int Col;
};
