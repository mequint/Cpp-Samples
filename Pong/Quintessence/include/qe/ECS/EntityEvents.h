#pragma once

// TODO: These will be game specific...don't like having this engine code...how do I separate this out?
namespace qe {
	enum class EntityEvent {
		Spawned, Despawned, Collision_X, Collision_Y, Began_Moving, Moving, Moving_Up, Moving_Down, Stop, Became_Idle, Selected
	};
}