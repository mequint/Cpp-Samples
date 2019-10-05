#pragma once

// TODO: These will be game specific...don't like having this engine code...how do I separate this out?

using ComponentType = unsigned int;

enum class Component {
	AIController = 0, Collider, Controller, Drawble, Health, Motion, Position, SoundEmitter, SpecialAbility, Sprite, State, Text, View, COUNT
};

enum class System {
	Collision = 0, Control, GameData, HUD, Movement, PaddleAI, Renderer, Sound, State, COUNT
};