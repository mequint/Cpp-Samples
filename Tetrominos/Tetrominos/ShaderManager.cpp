#include "ShaderManager.h"

#include <fstream>
#include <iostream>
#include <sstream>

ShaderManager::ShaderManager() {}
ShaderManager::~ShaderManager() {}

Shader& ShaderManager::GetShader(const std::string & name)
{
	auto iter = m_shaders.find(name);
	if (iter == m_shaders.end())
	{
		std::cout << "<ShaderManager>: Unable to find shader " << name << std::endl;
		// TODO: throw an error...or an empty shader...or something
	}

	return iter->second;
}

Shader& ShaderManager::BuildShader(const std::string& name, const std::string& vertexFile, const std::string& fragmentFile, const std::string& geometryFile)
{
	// Compile the shader code
	unsigned int vertex, fragment, geometry;
	vertex = compileShaderCode(vertexFile, GL_VERTEX_SHADER);
	fragment = compileShaderCode(fragmentFile, GL_FRAGMENT_SHADER);
	geometry = (geometryFile != "") ? compileShaderCode(geometryFile, GL_GEOMETRY_SHADER) : -1;

	// Link the shader code
	Shader shader = linkShaders(vertex, fragment, geometry);


	// Cleanup
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	if (geometryFile != "") glDeleteShader(geometry);

	// Store shader in the shader dictionary
	m_shaders[name] = shader;

	return m_shaders[name];
}


#pragma region "Helper methods"
unsigned int ShaderManager::compileShaderCode(const std::string& filename, unsigned int shaderType)
{
	std::string type = shaderTypeToString(shaderType);

	std::string data;
	std::ifstream file(filename.c_str());

	if (file.is_open())
	{
		std::stringstream ss;
		ss << file.rdbuf();
		file.close();

		data = ss.str();
	}
	else
	{
		std::cout << "<ShaderManager>::Failed to read " << type << " file: " << filename << std::endl;
		return -1;
	}

	const char* code = data.c_str();

	unsigned int shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &code, nullptr);
	glCompileShader(shader);

	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		std::cout << "<ShaderManager>::Failed to compile " << type << " shader: " << filename << "\n" << infoLog << std::endl;
	}

	return shader;
}

Shader ShaderManager::linkShaders(unsigned int vertex, unsigned int fragment, unsigned int geometry)
{
	unsigned int id = glCreateProgram();
	glAttachShader(id, vertex);
	glAttachShader(id, fragment);
	if (geometry != -1) glAttachShader(id, geometry);

	glLinkProgram(id);

	int success;
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success)
	{
		char infoLog[1024];
		glGetProgramInfoLog(id, 1024, nullptr, infoLog);
		std::cout << "<ShaderManager>::Failed to link shader program\n" << infoLog << std::endl;
	}

	return Shader(id);
}

std::string ShaderManager::shaderTypeToString(unsigned int shaderType)
{
	if (shaderType == GL_VERTEX_SHADER) return "vertex";
	if (shaderType == GL_FRAGMENT_SHADER) return "fragment";
	if (shaderType == GL_GEOMETRY_SHADER) return "geometry";

	return "<ShaderManager>::Unsupported shader type\n";
}

#pragma endregion