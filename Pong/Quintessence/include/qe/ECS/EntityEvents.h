#pragma once

// TODO: These will be game specific...don't like having this engine code...how do I separate this out?
namespace qe {
	enum class EntityEvent {
		Collision_X, Collision_Y, Despawned, Moving, Moving_Up, Moving_Down, Spawned, Stop
	};
}