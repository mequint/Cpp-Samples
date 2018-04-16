#include "Shader.h"

#include <fstream>
#include <iostream>
#include <sstream>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath)
{
	unsigned int vertex, fragment, geometry;
	vertex = compileShaderCode(vertexPath, GL_VERTEX_SHADER);
	fragment = compileShaderCode(fragmentPath, GL_FRAGMENT_SHADER);
	
	// Geometry shader is optional
	geometry = (geometryPath != "") ? geometry = compileShaderCode(geometryPath, GL_GEOMETRY_SHADER) : -1;

	linkShaders(vertex, fragment, geometry);

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	if (geometryPath != "") glDeleteShader(geometry);
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

void Shader::Set(const std::string& name, const glm::mat4& value) const
{
	glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

// ----------------------------------------
// Accesors / mutators
// ----------------------------------------

void Shader::ID(int id)			{ m_ID = id; }
unsigned int Shader::ID() const { return m_ID; }

// ----------------------------------------
// Helper methods
// ----------------------------------------

unsigned int Shader::compileShaderCode(const std::string& path, unsigned int shaderType)
{
	std::string type = shaderTypeToString(shaderType);

	// Load shader code
	std::string data;

	std::ifstream shaderFile;
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	// Some duplicate code here...
	try
	{
		shaderFile.open(path.c_str());

		std::stringstream shaderStream;
		shaderStream << shaderFile.rdbuf();
		shaderFile.close();

		data = shaderStream.str();
	}

	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR: Failed to read " << type << " file: " << path << std::endl;
	}

	const char* shaderCode = data.c_str();

	unsigned int shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderCode, nullptr);
	glCompileShader(shader);

	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		std::cout << "ERROR: Failed to compile " << type << " shader: " << path << "\n" << infoLog << std::endl;
	}

	return shader;
}

void Shader::linkShaders(unsigned int vertex, unsigned int fragment, unsigned int geometry)
{
	m_ID = glCreateProgram();
	glAttachShader(m_ID, vertex);
	glAttachShader(m_ID, fragment);

	if (geometry != -1)
	{
		glAttachShader(m_ID, geometry);
	}

	glLinkProgram(m_ID);

	int success;
	glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		char infoLog[1024];
		glGetProgramInfoLog(m_ID, 1024, nullptr, infoLog);
		std::cout << "ERROR: Failed to link shader program\n" << infoLog << std::endl;
	}
}

std::string Shader::shaderTypeToString(unsigned int shaderType)
{
	if (shaderType == GL_VERTEX_SHADER) return "vertex";
	if (shaderType == GL_FRAGMENT_SHADER) return "fragment";
	if (shaderType == GL_GEOMETRY_SHADER) return "geometry";

	return "<unsupported>";
}