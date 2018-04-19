#include "Shader.h"

#include <glm/gtc/type_ptr.hpp>

Shader::Shader() : m_ID(0)
{}

Shader::Shader(unsigned int id) : m_ID(id)
{
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

void Shader::Set(const std::string & name, const glm::vec4 & value) const
{
	glUniform4fv(glGetUniformLocation(m_ID, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::Set(const std::string& name, const glm::mat4& value) const
{
	glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

// ----------------------------------------
// Accesors / mutators
// ----------------------------------------

unsigned int Shader::GetID() const { return m_ID; }