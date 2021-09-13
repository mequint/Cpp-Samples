#include "qe/Window/EventLoader.h"

#include <fstream>
#include <iostream>
#include <mutex>
#include "nlohmann/json.hpp"

qe::EventLoader::EventLoader(qe::EventManager* eventManager) :
	m_eventManager(eventManager) {
}

void qe::EventLoader::loadFromJsonFile(const std::string & filepath) {
	std::mutex lock;
	lock.lock();

	std::ifstream jsonFile(filepath);
	
	nlohmann::json json;
	jsonFile >> json;

	jsonFile.close();
	lock.unlock();

	if (json.contains("events") && json["events"].is_array()) {
		auto jsonEventArray = json["events"];

		for (auto const& jsonEvent : jsonEventArray) {
			if (jsonEvent.contains("name") && jsonEvent["name"].is_string() &&
				jsonEvent.contains("eventType") && jsonEvent["eventType"].is_number_integer() &&
				jsonEvent.contains("eventCode") && jsonEvent["eventCode"].is_number_integer()) {

				auto name = jsonEvent["name"].get<std::string>();
				auto eventType = jsonEvent["eventType"].get<int>();
				auto eventCode = jsonEvent["eventCode"].get<int>();

				m_eventManager->addBinding(name, eventType, eventCode);
			}
		}
	}
}