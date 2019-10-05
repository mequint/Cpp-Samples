#include "ECS/Systems/Sys_Collision.h"

#include "qe/ECS/Core/SystemManager.h"
#include "qe/Utilities/MathHelpers.h"

#include "ECS/Components/Comp_Motion.h"

Sys_Collision::Sys_Collision(qe::SystemManager * systemManager) :
	Sys_Base(System::Collision, systemManager) {

	qe::Bitmask req;
	req.set(static_cast<size_t>(Component::Position));
	req.set(static_cast<size_t>(Component::Collider));
	req.set(static_cast<size_t>(Component::Motion));

	m_requiredComponents.push_back(req);
}

Sys_Collision::~Sys_Collision() = default;

void Sys_Collision::Update(float dt) {
	auto entityManager = m_systemManager->GetEntityManager();

	for (auto& entity : m_entities) {
		auto position = entityManager->GetComponent<Comp_Position>(entity, Component::Position);
		auto collidable = entityManager->GetComponent<Comp_Collider>(entity, Component::Collider);

		collidable->SetPosition(position->GetPosition());
		collidable->ResetCollisionFlags();

		CheckOutOfBounds(entity, position, collidable);
	}

	for (auto iterA = m_entities.begin(); iterA != m_entities.end(); ++iterA) {
		for (auto iterB = std::next(iterA); iterB != m_entities.end(); ++iterB) {
			auto colA = entityManager->GetComponent<Comp_Collider>(*iterA, Component::Collider);
			auto colB = entityManager->GetComponent<Comp_Collider>(*iterB, Component::Collider);

			sf::FloatRect intersection;

			if (colA->GetAABB().intersects(colB->GetAABB(), intersection)) {
				auto boxA = colA->GetAABB();
				auto boxB = colB->GetAABB();

				// Determine the direction of the collision
				// 1. Get the center of the left AABB box
				sf::Vector2f centerA(boxA.left + boxA.width / 2.0f, boxA.top + boxA.height / 2.0f);

				// 2. Get the center of the right AABB box
				sf::Vector2f centerB(boxB.left + boxB.width / 2.0f, boxB.top + boxB.height / 2.0f);

				// 3. Get the difference between both center points
				auto difference = centerA - centerB;

				// 4. Clamp
				sf::Vector2f clamped;
				if (difference.x < -boxB.width / 2.0f) { 
					clamped.x = -boxB.width / 2.0f;
				}
				else if (difference.x > boxB.width / 2.0f) {
					clamped.x = boxB.width / 2.0f;
				}
				else {
					clamped.x = difference.x;
				}

				if (difference.y < -boxB.height / 2.0f) {
					clamped.y = -boxB.height / 2.0f;
				}
				else if (difference.y > boxB.height / 2.0f) {
					clamped.y = boxB.height / 2.0f;
				}
				else {
					clamped.y = difference.y;
				}

				auto closest = centerB + clamped;
				difference = closest - centerA;

				sf::Vector2f compass[] = {
					sf::Vector2f(0.0f, -1.0f),	// up
					sf::Vector2f(1.0f, 0.0f),	// right
					sf::Vector2f(0.0f, 1.0f),	// down
					sf::Vector2f(-1.0f, 0.0f)	// left
				};

				float max = 0.0f;
				int bestMatch = -1;
				for (int i = 0; i < 4; ++i) {
					auto normal = qe::math::GetNormal(difference);

					float dot = qe::math::Dot(normal, compass[i]);
					if (dot > max) {
						max = dot;
						bestMatch = i;
					}
				}

				Direction dir = static_cast<Direction>(bestMatch);

				auto penetration = sf::Vector2f(boxA.width / 2.0f - difference.x, boxA.height / 2.0f - difference.y);
				auto position = entityManager->GetComponent<Comp_Position>(*iterA, Component::Position);
				auto motion = entityManager->GetComponent<Comp_Motion>(*iterA, Component::Motion);
 
				if (dir == Direction::Left) {
					m_systemManager->AddEvent(*iterA, static_cast<qe::EventId>(qe::EntityEvent::Collision_X));
					m_systemManager->AddEvent(*iterB, static_cast<qe::EventId>(qe::EntityEvent::Collision_X));
					position->Move(penetration.x, 0.0f);

				}
				else if (dir == Direction::Right) {
					m_systemManager->AddEvent(*iterA, static_cast<qe::EventId>(qe::EntityEvent::Collision_X));
					m_systemManager->AddEvent(*iterB, static_cast<qe::EventId>(qe::EntityEvent::Collision_X));
					position->Move(-penetration.x, 0.0f);
				}
				else if (dir == Direction::Up) {
					m_systemManager->AddEvent(*iterA, static_cast<qe::EventId>(qe::EntityEvent::Collision_Y));
					m_systemManager->AddEvent(*iterB, static_cast<qe::EventId>(qe::EntityEvent::Collision_Y));
					position->Move(0.0f, -penetration.y);
				}
				else if (dir == Direction::Down) {
					m_systemManager->AddEvent(*iterA, static_cast<qe::EventId>(qe::EntityEvent::Collision_Y));
					m_systemManager->AddEvent(*iterB, static_cast<qe::EventId>(qe::EntityEvent::Collision_Y));
					position->Move(0.0f, penetration.y);
				}

				// We only have 3 colliders but we should just generalize
				float centerBoard = boxB.top + boxB.height / 2.0f;
				float distanceY = boxA.top + boxA.height / 2.0f - centerBoard;
				float percentage = distanceY / (boxB.height / 2.0f);

				float strength = 0.5f;
				auto oldVelocity = motion->GetVelocity();
				sf::Vector2f ballVelocity;
				ballVelocity.x = oldVelocity.x;
				ballVelocity.y = 800.0f / 3.0f * percentage * strength;

				auto normalizedBallVelocity = qe::math::GetNormal(ballVelocity);
				sf::Vector2f newVelocity = normalizedBallVelocity * qe::math::GetMagnitude(oldVelocity);

				motion->SetVelocity(newVelocity);
			}
		}
	}
}

void Sys_Collision::HandleEvent(const qe::EntityId & id, const qe::EntityEvent & event) {}
void Sys_Collision::Notify(const qe::Message & message) {}

void Sys_Collision::SetBoundary(const sf::FloatRect & rect) {
	m_boundary = rect;
}

void Sys_Collision::CheckOutOfBounds(const qe::EntityId& entity, Comp_Position * pos, Comp_Collider * collidable) {
	if (pos->GetPosition().x < m_boundary.left) {
		pos->SetPosition(m_boundary.left, pos->GetPosition().y);
		collidable->SetPosition(pos->GetPosition());

		m_systemManager->AddEvent(entity, static_cast<qe::EventId>(qe::EntityEvent::Collision_X));

		qe::Message message(static_cast<qe::MessageType>(EntityMessage::Out_Of_Bounds));
		message.m_int = static_cast<int>(Direction::Left);
		m_systemManager->GetMessageDispatcher()->Dispatch(message);
	}
	else if (pos->GetPosition().x > m_boundary.left + m_boundary.width - collidable->GetAABB().width) {
		pos->SetPosition(m_boundary.left + m_boundary.width - collidable->GetAABB().width, pos->GetPosition().y);
		collidable->SetPosition(pos->GetPosition());

		m_systemManager->AddEvent(entity, static_cast<qe::EventId>(qe::EntityEvent::Collision_X));

		qe::Message message(static_cast<qe::MessageType>(EntityMessage::Out_Of_Bounds));
		message.m_int = static_cast<int>(Direction::Right);
		m_systemManager->GetMessageDispatcher()->Dispatch(message);
	}

	if (pos->GetPosition().y < m_boundary.top) {
		pos->SetPosition(pos->GetPosition().x, m_boundary.top);
		collidable->SetPosition(pos->GetPosition());

		m_systemManager->AddEvent(entity, static_cast<qe::EventId>(qe::EntityEvent::Collision_Y));
	}
	else if (pos->GetPosition().y > m_boundary.top + m_boundary.height - collidable->GetAABB().height) {
		pos->SetPosition(pos->GetPosition().x, m_boundary.top + m_boundary.height - collidable->GetAABB().height);
		collidable->SetPosition(pos->GetPosition());

		m_systemManager->AddEvent(entity, static_cast<qe::EventId>(qe::EntityEvent::Collision_Y));
	}
}