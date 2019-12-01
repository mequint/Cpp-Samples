#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

#include "Utilities.h"

template <typename Derived, typename T>
class ResourceManager {
public:
	ResourceManager(const std::string& pathFile) {
		LoadPaths(pathFile);
	}

	virtual ~ResourceManager() { PurgeResources(); }

	T* GetResource(const std::string& id) {
		auto res = Find(id);
		return (res ? res->first : nullptr);
	}

	std::string GetPath(const std::string& id) {
		auto path = m_paths.find(id);

		return (path != m_paths.end() ? path->second : "");
	}

	bool RequireResource(const std::string& id) {
		auto res = Find(id);
		if (res) {
			++res->second;
			return true;
		}

		auto path = m_paths.find(id);
		if (path == m_paths.end()) return false;

		T* resource = Load(path->second);
		if (!resource) { return false; }

		m_resources.emplace(id, std::make_pair(resource, 1));

		return true;
	}

	bool ReleaseResource(const std::string& id) {
		auto res = Find(id);
		if (!res) return false;

		--res->second;
		if (!res->second) {
			Unload(id);
		}

		return true;
	}

	void PurgeResources() {
		std::cout << "Purging all resources" << std::endl;
		while (m_resources.begin() != m_resources.end()) {
			std::cout << "\tRemoving: " << m_resources.begin()->first << std::endl;
			delete m_resources.begin()->second.first;
			m_resources.erase(m_resources.begin());
		}

		std::cout << "Purging complete" << std::endl;
	}

protected:
	T* Load(const std::string& path) {
		return static_cast<Derived*>(this)->Load(path);
	}

private:
	std::pair<T*, unsigned int>* Find(const std::string& id) {
		auto iter = m_resources.find(id);
		return (iter != m_resources.end() ? &iter->second : nullptr);
	}

	bool Unload(const std::string& id) {
		auto iter = m_resources.find(id);
		if (iter == m_resources.end()) return false;

		delete iter->second.first;
		m_resources.erase(iter);

		return true;
	}

	void LoadPaths(const std::string& pathFile) {
		std::ifstream paths;
		paths.open(Utils::GetWorkingDirectory() + pathFile);

		if (paths.is_open()) {
			std::string line;
			while (std::getline(paths, line)) {
				std::stringstream keystream(line);
				std::string pathName;
				std::string path;

				keystream >> pathName >> path;
				m_paths.emplace(pathName, path);
			}

			paths.close();
		}
		else {
			std::cerr << "! Failed to load the path file: " << pathFile << std::endl;
		}
	}

	std::unordered_map<std::string, std::pair<T*, unsigned int>> m_resources;
	std::unordered_map<std::string, std::string> m_paths;
};