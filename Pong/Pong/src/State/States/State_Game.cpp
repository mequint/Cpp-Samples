#include "State/States//State_Game.h"

#include "qe/ECS/Core/EntityManager.h"
#include "qe/Utilities/RandomGenerator.h"
#include "qe/State/StateManager.h"
#include "qe/ECS/Core/SystemManager.h"
#include "qe/Window/Window.h"

#include "ECS/Components/Components.h"
#include "ECS/Systems/Sys_GameData.h"
#include "ECS/Systems/Sys_PaddleAI.h"
#include "Utilities/Directions.h"

State_Game::State_Game(qe::StateManager* stateManager) : BaseState(stateManager), m_playerId(-1) {
}

State_Game::~State_Game() = default;

void State_Game::Create() {
	auto eventManager = m_stateManager->GetContext()->m_eventManager;
	eventManager->AddCallback(qe::StateType::Game, "Key_P", &State_Game::Pause, this);

	eventManager->AddCallback(qe::StateType::Game, "Key_W", &State_Game::MovePlayer, this);
	eventManager->AddCallback(qe::StateType::Game, "Key_W_Released", &State_Game::StopPlayer, this);
	eventManager->AddCallback(qe::StateType::Game, "Key_Up", &State_Game::MovePlayer, this);
	eventManager->AddCallback(qe::StateType::Game, "Key_Up_Released", &State_Game::StopPlayer, this);
	eventManager->AddCallback(qe::StateType::Game, "Key_S", &State_Game::MovePlayer, this);
	eventManager->AddCallback(qe::StateType::Game, "Key_S_Released", &State_Game::StopPlayer, this);
	eventManager->AddCallback(qe::StateType::Game, "Key_Down", &State_Game::MovePlayer, this);
	eventManager->AddCallback(qe::StateType::Game, "Key_Down_Released", &State_Game::StopPlayer, this);

	SetupViews();
	CreateEntities();
}

void State_Game::Destroy() {
	qe::EventManager* eventManager = m_stateManager->GetContext()->m_eventManager;
	eventManager->RemoveCallback(qe::StateType::Game, "Key_P");
}

void State_Game::Activate() {}
void State_Game::Deactivate() {}

void State_Game::Update(const sf::Time& time)  {
	auto context = m_stateManager->GetContext();
	context->m_systemManager->Update(time.asSeconds());
}

void State_Game::Draw() {
	auto context = m_stateManager->GetContext();
	m_leftHealthView.Draw(context->m_window->GetRenderWindow());
	m_rightHealthView.Draw(context->m_window->GetRenderWindow());

	context->m_systemManager->Draw(context->m_window, 0);
}

void State_Game::Pause(qe::EventDetails * details) {
	m_stateManager->ChangeState(qe::StateType::Paused);
}

void State_Game::MovePlayer(qe::EventDetails* details) {
	qe::Message msg(static_cast<qe::MessageType>(EntityMessage::Move));

	if (details->m_name == "Key_W" || details->m_name == "Key_Up") {
		msg.m_int = static_cast<int>(Direction::Up);
	}
	else if (details->m_name == "Key_S" || details->m_name == "Key_Down") {
		msg.m_int = static_cast<int>(Direction::Down);
	}

	msg.m_receiver = m_playerId;
	m_stateManager->GetContext()->m_systemManager->GetMessageDispatcher()->Dispatch(msg);
}

void State_Game::StopPlayer(qe::EventDetails* details) {
	qe::Message msg(static_cast<qe::MessageType>(EntityMessage::Stop_Moving));

	msg.m_receiver = m_playerId;
	m_stateManager->GetContext()->m_systemManager->GetMessageDispatcher()->Dispatch(msg);
}

void State_Game::CreateEntities() {
	auto entityManager = m_stateManager->GetContext()->m_entityManager;
	auto windowSize = m_stateManager->GetContext()->m_window->GetRenderWindow()->getSize();

	auto paddleAiSystem = m_stateManager->GetContext()->m_systemManager->GetSystem<Sys_PaddleAI>(System::PaddleAI);
	// Create the ball
	qe::Bitmask ballBits;
	ballBits.set(static_cast<size_t>(Component::Position));
	ballBits.set(static_cast<size_t>(Component::Sprite));
	ballBits.set(static_cast<size_t>(Component::Motion));
	ballBits.set(static_cast<size_t>(Component::Collider));

	auto id = entityManager->AddEntity(ballBits);

	auto sprite = entityManager->GetComponent<Comp_Sprite>(id, Component::Sprite);
	sprite->Create(m_stateManager->GetContext()->m_textureManager, "Ball");

	auto position = entityManager->GetComponent<Comp_Position>(id, Component::Position);
	
	position->SetPosition(static_cast<float>(windowSize.x) / 2.0f - static_cast<float>(sprite->GetSize().x) / 2.0f, 
		static_cast<float>(windowSize.y) / 2.0f - static_cast<float>(sprite->GetSize().x) / 2.0f);

	auto motion = entityManager->GetComponent<Comp_Motion>(id, Component::Motion);
	motion->SetVelocity(sf::Vector2f(static_cast<float>(windowSize.x) / 3.0f, 0.0f));
	motion->SetIsBouncy(true);

	auto collidable = entityManager->GetComponent<Comp_Collider>(id, Component::Collider);
	collidable->SetPosition(position->GetPosition());
	collidable->SetSize(static_cast<sf::Vector2f>(sprite->GetSize()));
	collidable->SetIsBouncy(true);

	paddleAiSystem->SetBall(id);

	// Create paddle 1
	qe::Bitmask paddle1Bits;
	paddle1Bits.set(static_cast<size_t>(Component::Position));
	paddle1Bits.set(static_cast<size_t>(Component::Sprite));
	paddle1Bits.set(static_cast<size_t>(Component::Motion));
	paddle1Bits.set(static_cast<size_t>(Component::Collider));
	paddle1Bits.set(static_cast<size_t>(Component::Controller));
	paddle1Bits.set(static_cast<size_t>(Component::SoundEmitter));

	id = entityManager->AddEntity(paddle1Bits);
	m_playerId = id;

	sprite = entityManager->GetComponent<Comp_Sprite>(id, Component::Sprite);
	sprite->Create(m_stateManager->GetContext()->m_textureManager, "RedPaddle");
	
	position = entityManager->GetComponent<Comp_Position>(id, Component::Position);
	position->SetPosition(0.0f, static_cast<float>(windowSize.y) / 2.0f - static_cast<float>(sprite->GetSize().y) / 2.0f);

	motion = entityManager->GetComponent<Comp_Motion>(id, Component::Motion);
	motion->SetIsBouncy(false);

	collidable = entityManager->GetComponent<Comp_Collider>(id, Component::Collider);
	collidable->SetPosition(position->GetPosition());
	collidable->SetSize(static_cast<sf::Vector2f>(sprite->GetSize()));
	collidable->SetIsBouncy(false);

	auto sound = entityManager->GetComponent<Comp_SoundEmitter>(id, Component::SoundEmitter);
	sound->SetSound(EntitySound::Collision, "Bleep");
	
	// Create paddle 2
	qe::Bitmask paddle2Bits;
	paddle2Bits.set(static_cast<size_t>(Component::Position));
	paddle2Bits.set(static_cast<size_t>(Component::Sprite));
	paddle2Bits.set(static_cast<size_t>(Component::Motion));
	paddle2Bits.set(static_cast<size_t>(Component::Collider));
	paddle2Bits.set(static_cast<size_t>(Component::SoundEmitter));

	id = entityManager->AddEntity(paddle2Bits);

	sprite = entityManager->GetComponent<Comp_Sprite>(id, Component::Sprite);
	sprite->Create(m_stateManager->GetContext()->m_textureManager, "BluePaddle");

	position = entityManager->GetComponent<Comp_Position>(id, Component::Position);
	position->SetPosition(static_cast<float>(windowSize.x) - static_cast<float>(sprite->GetSize().x), static_cast<float>(windowSize.y) / 2.0f - static_cast<float>(sprite->GetSize().y) / 2.0f);

	motion = entityManager->GetComponent<Comp_Motion>(id, Component::Motion);
	motion->SetIsBouncy(false);

	collidable = entityManager->GetComponent<Comp_Collider>(id, Component::Collider);
	collidable->SetPosition(position->GetPosition());
	collidable->SetSize(static_cast<sf::Vector2f>(sprite->GetSize()));
	collidable->SetIsBouncy(false);

	sound = entityManager->GetComponent<Comp_SoundEmitter>(id, Component::SoundEmitter);
	sound->SetSound(EntitySound::Collision, "Bloop");

	paddleAiSystem->SetPaddle(id);

	// Get the scoring system
	auto scoreSystem = m_stateManager->GetContext()->m_systemManager->GetSystem<Sys_GameData>(System::GameData);

	// Create Left Side Score
	qe::Bitmask leftScore;
	leftScore.set(static_cast<size_t>(Component::Position));
	leftScore.set(static_cast<size_t>(Component::Text));

	id = entityManager->AddEntity(leftScore);

	auto text = entityManager->GetComponent<Comp_Text>(id, Component::Text);
	text->Create(m_stateManager->GetContext()->m_fontManager, "Game");
	text->SetFontSize(24);
	text->SetText("0");

	position = entityManager->GetComponent<Comp_Position>(id, Component::Position);
	position->SetPosition(static_cast<float>(windowSize.x / 4.0f), static_cast<float>(windowSize.y / 10.0f));

	scoreSystem->SetLeftEntity(id);

	// Create Left Side Score
	qe::Bitmask rightScore;
	rightScore.set(static_cast<size_t>(Component::Position));
	rightScore.set(static_cast<size_t>(Component::Text));

	id = entityManager->AddEntity(rightScore);

	position = entityManager->GetComponent<Comp_Position>(id, Component::Position);
	position->SetPosition(static_cast<float>(3 * windowSize.x / 4.0f), static_cast<float>(windowSize.y / 10.0f));

	text = entityManager->GetComponent<Comp_Text>(id, Component::Text);
	text->Create(m_stateManager->GetContext()->m_fontManager, "Game");
	text->SetFontSize(24);
	text->SetText("0");

	scoreSystem->SetRightEntity(id);
}

void State_Game::SetupViews() {
	auto windowSize = m_stateManager->GetContext()->m_window->GetRenderWindow()->getSize();

	m_leftHealthView.SetPosition(sf::Vector2f(10.0f, 10.0f));
	m_leftHealthView.SetBarSize(static_cast<float>(windowSize.x / 2 - 20), 30.0f);

	m_rightHealthView.SetPosition(sf::Vector2f(static_cast<float>(windowSize.x / 2) + 10.0f, 10.0f));
	m_rightHealthView.SetBarSize(static_cast<float>(windowSize.x / 2 - 20), 30.0f);
}