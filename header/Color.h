#pragma once
#include <glm/vec3.hpp>
#include <iostream>

class Color {   
public:
	Color(const glm::dvec3& color) : color{ color } {}
	Color(double r, double g, double b) : color{ glm::dvec3{r,g,b} } {}
	Color() : color{ glm::dvec3{0, 0, 0} } {}; //default color


	void Print() {
		std::cout << color.r << " " << color.g << " " << color.b << '\n';
	}
	     
	glm::dvec3 color;
};