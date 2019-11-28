#include "State_Intro.h"

#include "FontManager.h"
#include "StateManager.h"
#include "SoundManager.h"
#include "Window.h"

State_Intro::State_Intro(StateManager* stateManager) : BaseState(stateManager) {}
State_Intro::~State_Intro() = default;

void State_Intro::OnCreate() {
	sf::Vector2u windowSize = m_stateManager->GetContext()->m_window->GetRenderWindow()->getSize();

	TextureManager* textureManager = m_stateManager->GetContext()->m_textureManager;
	textureManager->RequireResource("Intro");

	auto texture = textureManager->GetResource("Intro");
	m_introSprite.setTexture(*texture);
	m_introSprite.setOrigin(texture->getSize().x / 2.0f, texture->getSize().y / 2.0f);
	m_introSprite.setPosition(static_cast<float>(windowSize.x) / 2.0f, static_cast<float>(windowSize.y) / 2.0f);

	auto fontManager = m_stateManager->GetContext()->m_fontManager;

	m_text.setFont(*fontManager->GetResource("Main"));
	m_text.setString(sf::String("Press SPACE to continue"));
	m_text.setCharacterSize(15);

	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	m_text.setPosition(m_introSprite.getPosition().x, m_introSprite.getPosition().y + texture->getSize().y / 1.5f);

	EventManager* eventManager = m_stateManager->GetContext()->m_eventManager;
	eventManager->AddCallback(StateType::Intro, "Intro_Continue", &State_Intro::Continue, this);

	m_stateManager->GetContext()->m_soundManager->PlayMusic("Electrix", 100.0f, true);
}

void State_Intro::OnDestroy() {
	TextureManager* textureManager = m_stateManager->GetContext()->m_textureManager;
	textureManager->ReleaseResource("Intro");

	FontManager* fontManager = m_stateManager->GetContext()->m_fontManager;
	fontManager->ReleaseResource("Main");

	EventManager* eventManager = m_stateManager->GetContext()->m_eventManager;
	eventManager->RemoveCallback(StateType::Intro, "Intro_Continue");
}

void State_Intro::Activate() {}
void State_Intro::Deactivate() {}
void State_Intro::Update(const sf::Time& time) {}

void State_Intro::Draw() {
	sf::RenderWindow* window = m_stateManager->GetContext()->m_window->GetRenderWindow();

	window->draw(m_introSprite);
	window->draw(m_text);
}

void State_Intro::Continue(EventDetails * details) {
	m_stateManager->SwitchTo(StateType::MainMenu);
	m_stateManager->Remove(StateType::Intro);
}