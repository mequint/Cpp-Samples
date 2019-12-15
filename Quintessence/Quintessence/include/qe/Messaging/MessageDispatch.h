#pragma once

#include <unordered_map>

#include "Broadcaster.h"

namespace qe {
	using MessageType = unsigned int;

	using Broadcasters = std::unordered_map<MessageType, Broadcaster>;

	class MessageDispatch {
	public:
		bool subscribe(const MessageType& type, Subscriber* subscriber) {
			return m_broadcasters[type].addSubscriber(subscriber);
		}

		bool unsubscribe(const MessageType& type, Subscriber* subscriber) {
			return m_broadcasters[type].removeSubscriber(subscriber);
		}

		void dispatch(const Message& message) {
			auto iter = m_broadcasters.find(message.m_type);
			if (iter == m_broadcasters.end()) return;

			iter->second.broadcast(message);
		}
	
	private:
		Broadcasters m_broadcasters;
	};
}