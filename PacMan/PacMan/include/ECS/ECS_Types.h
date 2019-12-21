#pragma once

enum class Component {
	Controller, Motion, Position, Sprite, State
};

enum class System {
	Control, Movement, Renderer, State
};

enum class EntityEvent {
	Moving_Up, Moving_Down, Moving_Left, Moving_Right, Stop
};

enum class EntityMessage {
	Move, Stop
};