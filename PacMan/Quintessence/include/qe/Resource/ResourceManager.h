#pragma once

#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>
#include <SFML/System/Lock.hpp>
#include <SFML/System/Mutex.hpp>
#include <string>
#include <unordered_map>

namespace qe {
	template <typename T>
	using ResourcePair = std::pair<std::unique_ptr<T>, unsigned int>;

	template <typename T>
	using ResourceContainer = std::unordered_map<std::string, ResourcePair<T>>;

	using PathContainer = std::unordered_map<std::string, std::string>;

	template <class Derived, typename T>
	class ResourceManager {
	public:
		ResourceManager() {}

		virtual ~ResourceManager() {
			cleanup();
		}

		bool loadResource(const std::string& resourceName, const std::string& resourcePath) {
			m_paths.emplace(resourceName, resourcePath);

			return loadResource(resourceName);
		}

		void loadResourcesFromJson(const std::string& filename) {
			sf::Lock lock(m_mutex);
			std::ifstream jsonFile(filename);

			nlohmann::json json;
			jsonFile >> json;

			jsonFile.close();

			for (auto const& resource : json) {
				if (resource.contains("name") && resource["name"].is_string() && 
					resource.contains("path") && resource["path"].is_string()) {
					auto name = resource["name"].get<std::string>();
					auto path = resource["path"].get<std::string>();

					loadResource(name, path);
				}
			}
		}

		bool loadResource(const std::string& id) {
			sf::Lock lock(m_mutex);

			auto resourcePair = _find(id);

			if (resourcePair) {
				++(resourcePair->second);
				return true;
			}

			auto path = m_paths.find(id);
			if (path == m_paths.end()) return false;

			std::unique_ptr<T> resource = std::make_unique<T>();
			if (!_load(resource.get(), path->second)) return false;

			m_resources.emplace(id, std::make_pair(std::move(resource), 1));

			return true;
		}

		T* getResource(const std::string& id) {
			sf::Lock lock(m_mutex);
			
			auto resourcePair = _find(id);
			return resourcePair ? resourcePair->first.get() : nullptr;
		}

		bool releaseResource(const std::string& id) {
			sf::Lock lock(m_mutex);

			auto resourcePair = _find(id);
			if (!resourcePair) return false;

			--(resourcePair->second);
			if (!resourcePair->second) {
				auto iter = m_resources.find(id);
				if (iter == m_resources.end()) return true;

				m_resources.erase(iter);
			}

			return true;
		}

		void cleanup() {
			sf::Lock lock(m_mutex);

			while (m_resources.begin() != m_resources.end()) {
				m_resources.erase(m_resources.begin());
			}
		}

	protected:
		bool _load(T* resource, const std::string& path) {
			return static_cast<Derived*>(this)->load(resource, path);
		}

	private:
		ResourcePair<T>* _find(const std::string& id) {
			auto iter = m_resources.find(id);
			return iter != m_resources.end() ? &iter->second : nullptr;
		}

		ResourceContainer<T> m_resources;
		PathContainer m_paths;

		sf::Mutex m_mutex;
	};
}