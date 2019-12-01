#pragma once

#include <unordered_map>

#include "Communicator.h"
#include "EntityMessages.h"

using Subscriptions = std::unordered_map<EntityMessage, Communicator>;

class MessageHandler {
public:
	bool Subscribe(const EntityMessage& type, Observer* observer) {
		return m_communicators[type].AddObserver(observer);
	}

	bool Unsubscribe(const EntityMessage& type, Observer* observer) {
		return m_communicators[type].RemoveObserver(observer);
	}

	void Dispatch(const Message& message) {
		auto iter = m_communicators.find(static_cast<EntityMessage>(message.m_type));
		if (iter == m_communicators.end()) return;

		iter->second.Broadcast(message);
	}
private:
	Subscriptions m_communicators;
};