#pragma once

enum class Component {
	Collider, Controller, Motion, Position, Sprite, State
};

enum class System {
	Collision, Control, Movement, Renderer, State
};

enum class EntityEvent {
	Colliding_X, Colliding_Y, Moving_Up, Moving_Down, Moving_Left, Moving_Right, Stop
};

enum class EntityMessage {
	Move, Stop
};