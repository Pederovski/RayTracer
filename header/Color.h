#pragma once
#include <glm/vec3.hpp>


class Color {
	Color(glm::dvec3& color) : color{ color } {}
		Color(double r, double g, double b) : color{ glm::dvec3{r,g,b} } {}
	     
	glm::dvec3 color;
};