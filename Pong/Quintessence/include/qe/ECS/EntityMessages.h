#pragma once

// TODO: These will be game specific...don't like having this engine code...how do I separate this out?

enum class EntityMessage {
	Health_Depleted, Move, Out_Of_Bounds, Stop_Moving
};