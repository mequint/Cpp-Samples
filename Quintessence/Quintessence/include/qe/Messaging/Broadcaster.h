#pragma once

#include <algorithm>
#include <vector>

#include "Subscriber.h"

namespace qe {
	using SubscriberContainer = std::vector<Subscriber*>;

	class Broadcaster {
	public:
		virtual ~Broadcaster() {
			m_subscribers.clear();
		}

		bool addSubscriber(Subscriber* subscriber) {
			if (hasSubscriber(subscriber)) return false;

			m_subscribers.emplace_back(subscriber);
			return true;
		}

		bool removeSubscriber(Subscriber* subscriber) {
			auto subIter = std::find_if(m_subscribers.begin(), m_subscribers.end(), [&subscriber](Subscriber* s) {
				return s == subscriber;
			});

			if (subIter == m_subscribers.end()) return false;
			m_subscribers.erase(subIter);

			return true;
		}

		bool hasSubscriber(const Subscriber* subscriber) const {
			return (std::find_if(m_subscribers.begin(), m_subscribers.end(), [&subscriber](Subscriber* s) {
				return s == subscriber;
			}) != m_subscribers.end());
		}

		void broadcast(const Message& message) {
			for (auto& iter : m_subscribers) {
				iter->notify(message);
			}
		}

	private:
		SubscriberContainer m_subscribers;
	};
}