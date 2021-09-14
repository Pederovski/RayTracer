#pragma once
#include <glm/vec3.hpp>


class Color {   
public:
	Color(const glm::dvec3& color) : color{ color } {}
	Color(double r, double g, double b) : color{ glm::dvec3{r,g,b} } {}
	Color() : color{ glm::dvec3{255, 255, 255} } {}; //default white
	     
	glm::dvec3 color;
};