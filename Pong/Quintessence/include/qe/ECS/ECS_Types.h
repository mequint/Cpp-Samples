#pragma once

// TODO: These will be game specific...don't like having this engine code...how do I separate this out?

using ComponentType = unsigned int;

enum class Component {
	AIController = 0, BoxCollider, CircleCollider, Collider, Controller, Drawble, Motion, Position, SoundEmitter, Sprite, State, Text, COUNT
};

enum class System {
	Collision = 0, Control, GameData, Movement, PaddleAI, Renderer, Sound, State, COUNT
};