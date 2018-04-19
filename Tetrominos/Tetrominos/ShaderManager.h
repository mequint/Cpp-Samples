#pragma once

#include <string>
#include <unordered_map>

#include "Shader.h"

using Shaders = std::unordered_map<std::string, Shader>;

class ShaderManager
{
	public:
		ShaderManager();
		~ShaderManager();

		Shader& LoadShader(const std::string& name, const std::string& vertexFile, const std::string& fragmentFile, const std::string& geometryFile = "");
		Shader& GetShader(const std::string& name);

	private:

		Shaders m_shaders;

		#pragma region "Helper methods"

		std::string loadShaderCode(const std::string& filename);

		#pragma endregion
};