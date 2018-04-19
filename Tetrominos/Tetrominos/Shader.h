#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

class Shader
{
	friend class ShaderManager;

	public:
		Shader();
		Shader(const char* vertexSource, const char* fragmentSource, const char* geometrySource = nullptr);

		void Use();

		void Set(const std::string& name, bool value) const;
		void Set(const std::string& name, int value) const;
		void Set(const std::string& name, float value) const;
		void Set(const std::string& name, const glm::vec4& value) const;
		void Set(const std::string& name, const glm::mat4& value) const;

		unsigned int GetID() const;

	private:
		unsigned int m_ID;

		#pragma region "Helper methods"
		unsigned int compileShaderCode(const char* code, unsigned int shaderType);

		void linkShaderCode(unsigned int vertex, unsigned int fragment, unsigned int geometry);
		
		std::string shaderTypeToString(unsigned int shaderType);

		#pragma endregion
};