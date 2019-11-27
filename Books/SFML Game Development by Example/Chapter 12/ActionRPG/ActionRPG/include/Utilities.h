#pragma once

#include <string>
#include <sstream>

#define RUNNING_WINDOWS

namespace Utils {
	#ifdef RUNNING_WINDOWS
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
	#include <shlwapi.h>

	#pragma comment(lib, "shlwapi.lib")

	inline std::string GetWorkingDirectory() {
		HMODULE hModule = GetModuleHandle(nullptr);
		if (!hModule)  return "";

		char path[256];
		GetModuleFileName(hModule, path, sizeof(path));
		PathRemoveFileSpecA(path);

		return std::string(path) + "\\";
	}
	#elif defined RUNNING_LINUX
	#include <unistd.h>
	inline std::string GetWorkingDirectory() {
		char cwd[1024];
		if (getcwd(cwd, sizeof(cwd)) != nullptr) {
			return std::string(cwd) + std::string("/");
		}

		return "";
	}

	#endif

	inline void ReadQuotedString(std::stringstream& stream, std::string& string) {
		stream >> string;

		if (string.at(0) == '"') {
			while (string.at(string.length() - 1) != '"' || !stream.eof()) {
				std::string str;
				stream >> str;
				string.append(" " + str);
			}
		}

		string.erase(std::remove(string.begin(), string.end(), '"'), string.end());
	}
}