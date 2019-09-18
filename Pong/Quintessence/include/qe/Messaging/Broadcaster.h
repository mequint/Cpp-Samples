#pragma once

#include <vector>
#include "qe/Messaging/Observer.h"

namespace qe {
	using ObserverContainer = std::vector<Observer*>;

	class Broadcaster {
	public:
		virtual ~Broadcaster() {
			m_observers.clear();
		}

		bool AddObserver(Observer* observer) {
			if (HasObserver(observer)) return false;

			m_observers.emplace_back(observer);
			return true;
		}

		bool RemoveObserver(Observer* observer) {
			auto observerIter = std::find_if(m_observers.begin(), m_observers.end(), 
				[&observer](Observer* o) {
				return o == observer;
			});

			if (observerIter == m_observers.end()) return false;
			m_observers.erase(observerIter);

			return true;
		}

		bool HasObserver(const Observer* observer) const {
			return (std::find_if(m_observers.begin(), m_observers.end(), 
				[&observer](Observer* o) {
				return o == observer;
			}) != m_observers.end());
		}

		void Broadcast(const Message& message) {
			for (auto& iter : m_observers) {
				iter->Notify(message);
			}
		}

	private:
		ObserverContainer m_observers;
	};
}