#pragma once

#include <glm/glm.hpp>

// 
class Camera
{
	public:
		glm::mat4 GetViewMatrix();

	private:
		glm::vec3 m_position;
		glm::vec3 m_front;
		glm::vec3 m_up;
		glm::vec3 m_right;
		glm::vec3 m_worldUp;

		float m_yaw;
		float m_pitch;

		float m_movementSpeed;
		float m_mouseSensitivity;
		float m_zoom;

		void updateCameraVectors();
};