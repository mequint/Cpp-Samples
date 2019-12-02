#pragma once

#include <string>
#include <vector>
#include "EventDetails.h"
#include "EventInfo.h"
#include "EventTypes.h"

namespace qe {
	using Events = std::vector<std::pair<EventType, EventInfo>>;

	struct EventBinding {
		EventBinding(const std::string& name) :
			m_name(name),
			m_details(name),
			count(0) {}

		void bindEvent(EventType type, EventInfo info = EventInfo()) {
			m_events.emplace_back(type, std::move(info));
		}

		Events m_events;
		std::string m_name;
		int count;

		EventDetails m_details;
	};
}