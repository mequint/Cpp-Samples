#pragma once

#include <string>

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
}