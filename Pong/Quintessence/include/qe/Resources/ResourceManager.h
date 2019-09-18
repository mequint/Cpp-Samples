#pragma once

#include <memory>
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

	template <typename Derived, typename T>
	class ResourceManager {
	public:
		ResourceManager() {}

		virtual ~ResourceManager() {
			Cleanup();
		}
		
		void AddResourcePath(const std::string& resourceName, const std::string& resourcePath) {
			m_paths.emplace(resourceName, resourcePath);
		}

		bool LoadResource(const std::string& id) {
			sf::Lock lock(m_mutex);
			auto resourcePair = Find(id);

			if (resourcePair) {
				++resourcePair->second;
				return true;
			}

			auto path = m_paths.find(id);
			if (path == m_paths.end()) return false;

			std::unique_ptr<T> resource = std::make_unique<T>();
			if (!Load(resource.get(), path->second)) return false;
			m_resources.emplace(id, std::make_pair(std::move(resource), 1));

			return true;
		}

		T* GetResource(const std::string& id) {
			sf::Lock lock(m_mutex);
			auto resourcePair = Find(id);

			return (resourcePair ? resourcePair->first.get() : nullptr);
		}

		bool ReleaseResource(const std::string& id) {
			sf::Lock lock(m_mutex);

			auto resourcePair = Find(id);
			if (!resourcePair) return false;

			--resourcePair->second;
			if (!resourcePair->second) {
				auto iter = m_resources.find(id);
				if (iter == m_resources.end()) return true;		// Don't need to do anything else here...

				m_resources.erase(iter);
			}

			return true;
		}

		void Cleanup() {
			sf::Lock lock(m_mutex);

			while (m_resources.begin() != m_resources.end()) {
				m_resources.erase(m_resources.begin());
			}
		}

	protected:
		bool Load(T* resource, const std::string& path) {
			return static_cast<Derived*>(this)->Load(resource, path);
		}

	private:
		ResourcePair<T>* Find(const std::string& id) {
			auto iter = m_resources.find(id);
			return (iter != m_resources.end() ? &iter->second : nullptr);
		}

		ResourceContainer<T> m_resources;
		PathContainer m_paths;

		sf::Mutex m_mutex;
	};
}