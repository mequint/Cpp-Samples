#pragma once

#include "qe/Window/EventManager.h"

namespace qe {
	class EventLoader {
		public:
			EventLoader(EventManager* eventManager);

			void loadFromJsonFile(const std::string& filepath);

		private:
			qe::EventManager* m_eventManager;
	};
}