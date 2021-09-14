#pragma once
#include <glm/vec4.hpp>

class Vertex {
public:
	Vertex(glm::vec4& _pos) : position{ _pos } {}
	Vertex(float x, float y, float z, float w = 1.0f) : position{ glm::vec4{x,y,z,w} } {}

	glm::vec4 position;
private:

};