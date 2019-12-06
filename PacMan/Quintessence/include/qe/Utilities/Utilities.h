#pragma once

#define RUNNING_WINDOWS

#include <string>

namespace qe {
	namespace Utils {
		#ifdef RUNNING_WINDOWS
		#pragma comment(lib, "shlwapi.lib")
		#define WIN32_LEAN_AND_MEAN
	
		#include <Windows.h>
		#include <Shlwapi.h>

		inline std::string getWorkingDirectory() {
			HMODULE hModule = GetModuleHandle(nullptr);

			if (!hModule) return "";

			char path[256];
			GetModuleFileName(hModule, path, sizeof(path));
			PathRemoveFileSpec(path);

			return std::string(path) + "\\";
		}
		#elif defined RUNNING_LINUX
	
		#include <unistd.h>
		#include <dirent.h>

		inline std::string getWorkingDirectory() {
			char cwd[1024];
			if (!getcwd(cwd, sizeof(cwd))) return;

			return std::string(cwd) + std::string("/");
		}
		#endif
	}
}