#pragma once
#include <glm/vec3.hpp>
class Direction {
public:
	Direction() : direction{ glm::vec3{0 ,0 ,0} } {}
	Direction(const glm::vec3& _dir) : direction{ _dir } {}

	glm::vec3 direction;
};