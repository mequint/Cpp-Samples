#include "qe/Animation/SpriteAnimation.h"

qe::SpriteAnimation::SpriteAnimation(TextureManager* textureManager) :
	m_textureManager(textureManager)
{
}

qe::SpriteAnimation::~SpriteAnimation() = default;

void qe::SpriteAnimation::setTexture(const std::string& textureName) {
	auto texture = m_textureManager->getResource(textureName);
	if (texture != nullptr) {
		m_textureName = textureName;

		sf::IntRect frame(0, 0, static_cast<int>(m_frameSize.x), static_cast<int>(m_frameSize.y));

		m_sprite.setTexture(*texture);
		m_sprite.setTextureRect(frame);
	}
}

void qe::SpriteAnimation::setFrameSize(unsigned int width, unsigned int height) {
	m_frameSize.x = width;
	m_frameSize.y = height;
}

void qe::SpriteAnimation::setPosition(const sf::Vector2f & position) {
	m_sprite.setPosition(position);
}

void qe::SpriteAnimation::setPosition(float x, float y) {
	m_sprite.setPosition(sf::Vector2f(x, y));
}

bool qe::SpriteAnimation::addAnimation(std::unique_ptr<AnimationControl> animation) {
	
	auto iter = m_animations.find(animation->getName());
	if (iter != m_animations.end()) {
		return false;
	}

	m_animations.emplace(std::make_pair(animation->getName(), std::move(animation)));
	return true;
}

qe::AnimationControl* qe::SpriteAnimation::getCurrentAnimation() {
	return m_currentAnimation;
}

bool qe::SpriteAnimation::changeAnimation(const std::string & action, bool play) {
	auto iter = m_animations.find(action);
	if (iter == m_animations.end()) return false;

	if (iter->second.get() == m_currentAnimation) return false;

	if (m_currentAnimation) {
		m_currentAnimation->stop();
	}

	m_currentAnimation = iter->second.get();

	if (play) {
		m_currentAnimation->start();
	}

	return true;
}

void qe::SpriteAnimation::update(float dt) {
	if (m_currentAnimation != nullptr) {
		m_currentAnimation->update(dt);
	}
}

void qe::SpriteAnimation::draw(sf::RenderTarget* renderTarget) {
	if (m_currentAnimation != nullptr) {
 		sf::IntRect frame(
			static_cast<int>(m_frameSize.x * m_currentAnimation->getCurrentFrame()),
			static_cast<int>(m_frameSize.y * m_currentAnimation->getFrameRow()),
			static_cast<int>(m_frameSize.x),
			static_cast<int>(m_frameSize.y)
		); 
		
		m_sprite.setTextureRect(frame);
		renderTarget->draw(m_sprite);
	}
}