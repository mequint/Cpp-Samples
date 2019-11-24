#pragma once

#define N_COMPONENT_TYPES 32

using ComponentType = unsigned int;

enum class Component {
	Position = 0, SpriteSheet, State, Movable, Controller, Collidable, SoundEmitter, SoundListener
};

enum class System {
	Renderer = 0, Movement, Collision, Control, State, SheetAnimation, Sound
};