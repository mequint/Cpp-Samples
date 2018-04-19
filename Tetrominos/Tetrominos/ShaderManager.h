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

		Shader& BuildShader(const std::string& name, const std::string& vertexFile, const std::string& fragmentFile, const std::string& geometryFile = "");
		Shader& GetShader(const std::string& name);

	private:

		Shaders m_shaders;

		#pragma region "Helper methods"
		unsigned int compileShaderCode(const std::string& filename, unsigned int shaderType);
		Shader linkShaders(unsigned int vertex, unsigned int fragment, unsigned int geometry);
		std::string shaderTypeToString(unsigned int shaderType);
		#pragma endregion
};