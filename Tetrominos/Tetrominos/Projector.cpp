#include "Projector.h"

OrthoProjector::OrthoProjector(int width, int height, bool isOriginOnTop)
{
	if (isOriginOnTop)
	{
		m_projectionMatrix = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height), -1.0f, 1.0f);
	}
	else
	{
		m_projectionMatrix = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f);
	}
}

glm::mat4 OrthoProjector::GetProjection()
{
	return m_projectionMatrix;
}
