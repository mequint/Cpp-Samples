#pragma once

#include <queue>		// TODO: Update to a priority queue for delayed events

#include "EntityEventType.h"

namespace qe {
	class EntityEventQueue {
	public:
		void addEvent(const EntityEventType& event) {
			m_queue.push(event);
		}

		bool processEvents(EntityEventType& type) {
			if (m_queue.empty()) return false;

			type = m_queue.front();
			m_queue.pop();

			return true;
		}

		void clear() {
			while (!m_queue.empty()) m_queue.pop();
		}

	private:
		std::queue<EntityEventType> m_queue;
	};
}