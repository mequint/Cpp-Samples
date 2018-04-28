#include "Text.h"

#include "ShaderManager.h"

Text::Text(const Shader& shader, const Font& font, const std::string & text) :
	m_shader(shader),
	m_font(font),
	m_text(text),
	m_x(0.0f), m_y(0.0f),
	m_scale(1.0f),
	m_color(1.0f, 1.0f, 1.0f)
{
	m_shader.Set("text", 0);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Text::Draw()
{
	m_shader.Use();
	m_shader.Set("textColor", m_color);

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);

	int hBearingY = m_font.GetGlyph('H').BearingY;
	float currentX = m_x;

	std::string::const_iterator c;
	for (c = m_text.begin(); c != m_text.end(); ++c)
	{
		Glyph g = m_font.GetGlyph(*c);

		float xPos = currentX + g.BearingX * m_scale;
		float yPos = m_y + (hBearingY - g.BearingY) * m_scale;

		float width = g.Width * m_scale;
		float height = g.Height * m_scale;

		GLfloat vertices[6][4] =
		{
			{ xPos, yPos + height,			0.0f, 1.0f },
		{ xPos + width, yPos,			1.0f, 0.0f },
		{ xPos, yPos,					0.0f, 0.0f },
		{ xPos, yPos + height,			0.0f, 1.0f },
		{ xPos + width, yPos + height,	1.0f, 1.0f },
		{ xPos + width, yPos,			1.0f, 0.0f }
		};

		glBindTexture(GL_TEXTURE_2D, g.TextureID);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		currentX += (g.Advance >> 6) * m_scale;
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Text::SetPosition(float x, float y)
{
	m_x = x;
	m_y = y;
}

void Text::SetText(const std::string text)
{
	m_text = text;
}