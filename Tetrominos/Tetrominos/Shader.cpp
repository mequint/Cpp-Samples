#include "Shader.h"

#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Shader::Shader() 
{
}

Shader::Shader(const char * vertexSource, const char * fragmentSource, const char * geometrySource)
{
	unsigned int vertShader, fragShader, geomShader;
	vertShader = compileShaderCode(vertexSource, GL_VERTEX_SHADER);
	fragShader = compileShaderCode(fragmentSource, GL_FRAGMENT_SHADER);
	if (geometrySource != nullptr) geomShader = compileShaderCode(geometrySource, GL_GEOMETRY_SHADER);

	m_ID = glCreateProgram();
	glAttachShader(m_ID, vertShader);
	glAttachShader(m_ID, fragShader);
	if (geometrySource != nullptr) glAttachShader(m_ID, geomShader);

	glLinkProgram(m_ID);

	int success;
	glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		char infoLog[1024];
		glGetProgramInfoLog(m_ID, 1024, nullptr, infoLog);
		std::cout << "<Shader>::Failed to link shader program\n" << infoLog << std::endl;
	}
}

void Shader::Use()
{
	glUseProgram(m_ID);
}

void Shader::Set(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(m_ID, name.c_str()), (int)value);
}

void Shader::Set(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
}

void Shader::Set(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
}

void Shader::Set(const std::string & name, const glm::vec3 & value) const
{
	glUniform3fv(glGetUniformLocation(m_ID, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::Set(const std::string & name, const glm::vec4 & value) const
{
	glUniform4fv(glGetUniformLocation(m_ID, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::Set(const std::string& name, const glm::mat4& value) const
{
	glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

#pragma region "Accessors/Mutators"

unsigned int Shader::GetID() const { return m_ID; }

#pragma endregion

#pragma region "Helper methods"

unsigned int Shader::compileShaderCode(const char * code, unsigned int shaderType)
{
	std::string type = shaderTypeToString(shaderType);

	unsigned int shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &code, nullptr);
	glCompileShader(shader);

	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		std::cout << "<Shader>::Failed to compile " << type << " shader\n" << infoLog << std::endl;
	}

	return shader;
}

void Shader::linkShaderCode(unsigned int vertex, unsigned int fragment, unsigned int geometry)
{
	m_ID = glCreateProgram();
	glAttachShader(m_ID, vertex);
	glAttachShader(m_ID, fragment);
	if (geometry != -1) glAttachShader(m_ID, geometry);

	glLinkProgram(m_ID);

	int success;
	glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		char infoLog[1024];
		glGetProgramInfoLog(m_ID, 1024, nullptr, infoLog);
		std::cout << "<ShaderManager>::Failed to link shader program\n" << infoLog << std::endl;
	}
}

std::string Shader::shaderTypeToString(unsigned int shaderType)
{
	if (shaderType == GL_VERTEX_SHADER) return "vertex";
	if (shaderType == GL_FRAGMENT_SHADER) return "fragment";
	if (shaderType == GL_GEOMETRY_SHADER) return "geometry";

	return "<ShaderManager>::Unsupported shader type\n";
}

#pragma endregion