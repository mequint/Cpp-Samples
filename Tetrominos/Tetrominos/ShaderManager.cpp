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
		std::cout << "<ShaderManager>: Unable to find shader \'" << name << "\'" << std::endl;
		// TODO: throw an error...or an empty shader...or something
	}

	return iter->second;
}

Shader& ShaderManager::LoadShader(const std::string& name, const std::string& vertexFile, const std::string& fragmentFile, const std::string& geometryFile)
{
	// Load the shader code
	std::string vertexCode, fragmentCode, geometryCode;
	vertexCode = loadShaderCode(vertexFile);
	fragmentCode = loadShaderCode(fragmentFile);
	geometryCode = (geometryFile != "") ? loadShaderCode(geometryFile) : "";

	// Create a shader using the shader code
	Shader shader(vertexCode.c_str(), fragmentCode.c_str(), (geometryCode == "") ? nullptr : geometryCode.c_str());

	// Store shader in the shader dictionary
	m_shaders[name] = shader;
	return m_shaders[name];
}


#pragma region "Helper methods"

std::string ShaderManager::loadShaderCode(const std::string & filename)
{
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
		std::cout << "<ShaderManager>::Failed to read \'" << filename << "\'" << std::endl;
		return "";
	}

	return data;
}

#pragma endregion