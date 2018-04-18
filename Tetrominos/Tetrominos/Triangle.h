#pragma once

#include "IDrawable.h"
#include "Shader.h"
#include "Vertex.h"

class Triangle : public IDrawable
{
	public:
		Triangle(Shader shader);

		void Initialize();
		void Draw();

	private:
		unsigned int VAO, VBO;
		Vertices m_vertices;
		Shader m_shader;
};