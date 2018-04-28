#pragma once

#include <glm/gtc/matrix_transform.hpp>

enum class ProjectorType
{
	Orthographic,
	Perspective,
};

class IProjector
{
	public:
		virtual ~IProjector() {}
		virtual glm::mat4 GetProjection() = 0;

	protected:
		glm::mat4 m_projectionMatrix;
};

class OrthoProjector : public IProjector
{
	public:
		OrthoProjector(int width, int height, bool isOriginOnTop = false);

		virtual glm::mat4 GetProjection();
};