#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

class Shader
{
	public:
		Shader(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath="");


		void Use();
		void Set(const std::string& name, bool value) const;
		void Set(const std::string& name, int value) const;
		void Set(const std::string& name, float value) const;
		void Set(const std::string& name, const glm::mat4& value) const;

		void ID(int id);
		unsigned int ID() const;

	private:
		unsigned int compileShaderCode(const std::string& path, unsigned int shaderType);
		void linkShaders(unsigned int vertex, unsigned int fragment, unsigned int geometry = -1);

		std::string shaderTypeToString(unsigned int shaderType);

		unsigned int m_ID;
};