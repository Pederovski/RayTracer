#pragma once
#include <glm/vec3.hpp>

class Vertex {
public:
	Vertex() = default;
	Vertex(glm::vec3& _pos, float _w = 1.0) : position{ _pos }, w{ _w } {}
	Vertex(float x, float y, float z, float _w = 1.0f) : position{ glm::vec3{x,y,z} }, w{ _w } {}

	glm::vec3 position;
	float w; //homogenus coordinate
private:

};