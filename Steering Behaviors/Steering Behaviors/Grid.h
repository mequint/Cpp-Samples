#pragma once

#include "IDrawable.h"
#include "Shader.h"
#include "Vertex.h"

class Grid : public IDrawable
{
	public:
		Grid(Shader shader, int rows, int columns);

		void Initialize();
		void Draw();

	private:
		unsigned int VAO, VBO;	// Might need to use indices for this one...

		int m_rows, m_columns;

		Shader m_shader;
		Vertices m_vertices;
};