#include "ECS/Systems/Sys_HUD.h"

#include "qe/ECS/Core/SystemManager.h"

#include "ECS/Components/Comp_Health.h"
#include "ECS/Components/Comp_SpecialAbility.h"
#include "Utilities/Directions.h"

Sys_HUD::Sys_HUD(qe::SystemManager * systemManager) : 
	Sys_Base(System::HUD, systemManager) {
	qe::Bitmask req;
	req.set(static_cast<size_t>(Component::Health));
	m_requiredComponents.push_back(req);

	req.reset(static_cast<size_t>(Component::Health));
	req.set(static_cast<size_t>(Component::SpecialAbility));
	m_requiredComponents.push_back(req);

	m_systemManager->GetMessageDispatcher()->Subscribe(EntityMessage::Out_Of_Bounds, this);
}

Sys_HUD::~Sys_HUD() = default;

void Sys_HUD::Setup(const int width, const int height) {
	float healthBarWidth = static_cast<float>(width / 2 - 20);
	float healthBarHeight = 15.0f;
	float specialBarWidth = static_cast<float>((width / 2 - 20) / 10);
	float specialBarHeight = 10.0f;

	m_leftHealthBar.SetPosition(sf::Vector2f(10.0f, 10.0f));
	m_leftHealthBar.SetBarSize(healthBarWidth, healthBarHeight);
	m_leftHealthBar.SetProgressColor(sf::Color(0x66, 0xff, 0x00, 0xff));
	m_leftHealthBar.SetEmptyColor(sf::Color(0x4c, 0xbf, 0x00, 0xff));
	m_leftHealthBar.SetCurrentValue(100);
	m_leftHealthBar.SetMaxValue(100);

	m_leftSpecialBar.SetPosition(sf::Vector2f(10.0f, 10.0f + healthBarHeight));
	m_leftSpecialBar.SetBarSize(specialBarWidth, specialBarHeight);
	m_leftSpecialBar.SetProgressColor(sf::Color(0x87, 0xce, 0xfa, 0xff));
	m_leftSpecialBar.SetEmptyColor(sf::Color(0x46, 0x82, 0xb4, 0xff));
	m_leftSpecialBar.SetCurrentValue(0);
	m_leftSpecialBar.SetMaxValue(20);

	m_rightHealthBar.SetPosition(sf::Vector2f(static_cast<float>(width / 2) + 10.0f, 10.0f));
	m_rightHealthBar.SetBarSize(healthBarWidth, healthBarHeight);
	m_rightHealthBar.SetProgressColor(sf::Color(0x66, 0xff, 0x00, 0xff));
	m_rightHealthBar.SetEmptyColor(sf::Color(0x4c, 0xbf, 0x00, 0xff));
	m_rightHealthBar.SetCurrentValue(100);
	m_rightHealthBar.SetMaxValue(100);

	m_rightSpecialBar.SetPosition(sf::Vector2f(static_cast<float>(width - 10) - specialBarWidth, 10.0f + healthBarHeight));
	m_rightSpecialBar.SetBarSize(specialBarWidth, specialBarHeight);
	m_rightSpecialBar.SetProgressColor(sf::Color(0x87, 0xce, 0xfa, 0xff));
	m_rightSpecialBar.SetEmptyColor(sf::Color(0x46, 0x82, 0xb4, 0xff));
	m_rightSpecialBar.SetCurrentValue(0);
	m_rightSpecialBar.SetMaxValue(20);
}

void Sys_HUD::SetLeftPlayer(const qe::EntityId & entityId) {
	m_leftPlayer = entityId;
}

void Sys_HUD::SetRightPlayer(const qe::EntityId & entityId) {
	m_rightPlayer = entityId;
}

void Sys_HUD::Update(float dt) {
}

void Sys_HUD::HandleEvent(const qe::EntityId & entityId, const qe::EntityEvent & event) {

}

void Sys_HUD::Notify(const qe::Message & message) {
	EntityMessage m = static_cast<EntityMessage>(message.m_type);
	auto entities = m_systemManager->GetEntityManager();

	switch (m) {
		case EntityMessage::Out_Of_Bounds: {
			Direction dir = static_cast<Direction>(message.m_int);
			
			if (dir == Direction::Left) {
				Comp_Health* health = entities->GetComponent<Comp_Health>(m_leftPlayer, Component::Health);
				
				auto currentHealth = health->GetHealth();
				currentHealth -= 25;
				if (currentHealth < 0) return;
				
				health->SetHealth(currentHealth);
				m_leftHealthBar.SetCurrentValue(currentHealth);

				// Game is over...send a message
				if (currentHealth <= 0) {
					qe::Message message(static_cast<qe::MessageType>(EntityMessage::Health_Depleted));
					message.m_int = static_cast<int>(Direction::Left);
					m_systemManager->GetMessageDispatcher()->Dispatch(message);
				}
			}
			else if (dir == Direction::Right) {
				Comp_Health* health = entities->GetComponent<Comp_Health>(m_rightPlayer, Component::Health);

				auto currentHealth = health->GetHealth();
				currentHealth -= 25;
				if (currentHealth < 0) return;

				health->SetHealth(currentHealth);
				m_rightHealthBar.SetCurrentValue(currentHealth);

				// Game is over...send a message
				if (currentHealth <= 0) {
					qe::Message message(static_cast<qe::MessageType>(EntityMessage::Health_Depleted));
					message.m_int = static_cast<int>(Direction::Right);
					m_systemManager->GetMessageDispatcher()->Dispatch(message);
				}
			}
		}
	}
}

void Sys_HUD::Render(qe::Window * window, unsigned int layer) {
	m_leftHealthBar.Draw(window->GetRenderWindow());
	m_leftSpecialBar.Draw(window->GetRenderWindow());
	m_rightHealthBar.Draw(window->GetRenderWindow());
	m_rightSpecialBar.Draw(window->GetRenderWindow());
}