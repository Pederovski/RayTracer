#pragma once
#include <glm/vec3.hpp>


class Color {   
public:
	Color(glm::dvec3& color) : color{ color } {}
		Color(double r, double g, double b) : color{ glm::dvec3{r,g,b} } {}

		Color() : color{ glm::dvec3{1,1,1} } {};
	     
	glm::dvec3 color;
};