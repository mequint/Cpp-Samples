#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>

#include "Anim_Directional.h"
#include "TextureManager.h"

using Animations = std::unordered_map<std::string, Anim_Base*>;

class SpriteSheet {
public:
	SpriteSheet(TextureManager* textureManager);
	~SpriteSheet();

	void CropSprite(const sf::IntRect& rect);
	
	const sf::Vector2u& GetSpriteSize() const;
	const sf::Vector2f& GetSpritePosition() const;
	void SetSpriteSize(const sf::Vector2u& size);
	void SetSpritePosition(const sf::Vector2f& position);

	void SetDirection(const Direction& dir);
	Direction GetDirection();
	void SetSheetPadding(const sf::Vector2f& padding);
	void SetSpriteSpacing(const sf::Vector2f& spacing);
	const sf::Vector2f& GetSheetPadding() const;
	const sf::Vector2f& GetSpriteSpacing() const;

	bool LoadSheet(const std::string& file);
	void ReleaseSheet();

	Anim_Base* GetCurrentAnim();
	bool SetAnimation(const std::string& name, bool play = false, bool loop = false);

	void Update(float dt);
	void Draw(sf::RenderWindow* window);

private:
	std::string m_texture;
	sf::Sprite m_sprite;
	sf::Vector2u m_spriteSize;
	sf::Vector2f m_spriteScale;
	Direction m_direction;

	sf::Vector2f m_sheetPadding;
	sf::Vector2f m_spriteSpacing;

	std::string m_animType;
	Animations m_animations;
	Anim_Base* m_animationCurrent;

	TextureManager* m_textureManager;
};