#include "Grid.h"

Grid::Grid(Shader shader, int rows, int columns) :
	m_shader(shader),
	m_rows(rows),
	m_columns(columns)
{
	Initialize();
}

void Grid::Initialize()
{
	glm::vec3 color = { 0.0f, 0.5f, 1.0f };

	for (int i = 0; i < m_rows; ++i)
	{
		float x = 1.0f - (2.0f / m_rows) * (i + 1);
		for (int j = 0; j < m_columns; ++j)
		{
			float y = 1.0f - (2.0f / m_columns) * (j + 1);

			Vertex v = { { x, y, 0.0f }, color };
			m_vertices.emplace_back(v);
		}
	}

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), m_vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));
	//glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

void Grid::Draw()
{
	m_shader.Use();

	glBindVertexArray(VAO);
	glDrawArrays(GL_POINTS, 0, m_vertices.size());
	glBindVertexArray(0);
}