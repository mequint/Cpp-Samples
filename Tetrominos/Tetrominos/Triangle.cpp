#include "Triangle.h"

Triangle::Triangle(Shader shader) :
	m_shader(shader)
{
	Initialize();
}

void Triangle::Initialize()
{
	Vertex v1, v2, v3;
	v1 = { { -0.5f, -0.5f, 0.0f },{ 1.0f, 0.0f, 0.0f } };
	v2 = { { 0.5f, -0.5f, 0.0f },{ 0.0f, 1.0f, 0.0f } };
	v3 = { { 0.0f,  0.5f, 0.0f },{ 0.0f, 0.0f, 1.0f } };

	m_vertices.emplace_back(v1);
	m_vertices.emplace_back(v2);
	m_vertices.emplace_back(v3);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), m_vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

void Triangle::Draw()
{
	m_shader.Use();
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(0);
}