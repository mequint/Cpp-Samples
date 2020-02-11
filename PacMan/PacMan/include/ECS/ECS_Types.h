#pragma once

enum class Component {
	Consumable, Collider, Controller, EntityType, Motion, Points, Position, Score, Sprite, State
};

enum class System {
	AppState, Collision, Consumption, Control, GameUI, Movement, Renderer, Scoring, State
};

enum class EntityEvent {
	Moving_Up, Moving_Down, Moving_Left, Moving_Right, Remove, Stop
};

enum class EntityMessage {
	Collide, NextLevel, RequestMove, Stop, UpdateScore
};