#pragma once

#include <glm/glm.hpp>
#include <vector>

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Color;
};

using Vertices = std::vector<Vertex>;