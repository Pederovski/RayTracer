#pragma once
#include <glm/vec3.hpp>
class Direction {
public:
	explicit Direction(glm::vec3& _dir) : direction{ _dir } {}

	glm::vec3 direction;
};