#pragma once

#include <unordered_map>

#include "Broadcaster.h"
#include "qe/ECS/EntityMessages.h"

namespace qe {
	using Subscriptions = std::unordered_map<EntityMessage, Broadcaster>;

	class MessageDispatcher {
	public:
		bool Subscribe(const EntityMessage& type, Observer* observer) {
			return m_broadcasters[type].AddObserver(observer);
		}

		bool Unsubscribe(const EntityMessage& type, Observer* observer) {
			return m_broadcasters[type].RemoveObserver(observer);
		}

		void Dispatch(const Message& message) {
			auto iter = m_broadcasters.find(static_cast<EntityMessage>(message.m_type));
			if (iter == m_broadcasters.end()) return;

			iter->second.Broadcast(message);
		}

	private:
		Subscriptions m_broadcasters;
	};
}