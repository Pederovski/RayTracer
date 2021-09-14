#pragma once
#include "glm\glm.hpp";
#include "Direction.h"
#include "Vertex.h"
#include "Color.h"
#include "Ray.h"

class Triangle {
public:
	Triangle() = default;

	Triangle(const Vertex&  vertex1, const Vertex& vertex2, const Vertex&  vertex3, const Color& color) :
		v1{ vertex1 }, v2{ vertex2 }, v3{ vertex3 }, color{ color } {
		//Calculate normal direction by cross product of the triangle sides
		glm::vec3 p1 = glm::vec3(v1.position.x, v1.position.y, v1.position.z);
		glm::vec3 p2 = glm::vec3(v2.position.x, v2.position.y, v2.position.z);
		glm::vec3 p3 = glm::vec3(v3.position.x, v3.position.y, v3.position.z);
		glm::vec3 u = p1 - p2;
		glm::vec3 v = p1 - p3;
		
		normal.direction = glm::cross(u, v);
	}

	Vertex* rayIntersection(Ray ray);
	

private:
	Vertex v1, v2, v3;
	Color color;
	Direction normal;
};