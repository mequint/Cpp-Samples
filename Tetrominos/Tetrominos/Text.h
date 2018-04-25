#pragma once

#include <glm/glm.hpp>
#include <string>

#include "Font.h"
#include "IDrawable.h"
#include "Shader.h"

class Text : public IDrawable
{
	public:
		Text(const Shader& shader, const Font& font, const std::string& text);

		void Draw();
		void SetPosition(float x, float y);

	private:
		unsigned int VAO, VBO;
		Font m_font;
		std::string m_text;
		Shader m_shader;

		float m_x, m_y;
		float m_scale;
		glm::vec3 m_color;
};