#pragma once
#include <glm/glm.hpp>

class Lightsrc {
public:
	Lightsrc() = default;
	Lightsrc(float _crossSection, const glm::dvec3& _radiance, const glm::vec3& _position) :
		crossSection{_crossSection}, radiance{_radiance}, position{_position} {}

	glm::vec3 position;
	float crossSection;
	glm::dvec3 radiance;
private:
	
};