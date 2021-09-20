#pragma once
#include "glm\glm.hpp";
#include "Direction.h"
#include "Vertex.h"
#include "Color.h"
#include "Ray.h"
#include <iostream>
const float NOT_FOUND = 100000000;

class Triangle {
public:
	Triangle() = default;

	Triangle(const Vertex&  vertex1, const Vertex& vertex2, const Vertex&  vertex3, const Color& color) :
		v1{ vertex1 }, v2{ vertex2 }, v3{ vertex3 }, color{ color } {
		//Calculate normal direction by cross product of the triangle sides
		glm::vec3 p1 = glm::vec3(v1.position.x, v1.position.y, v1.position.z);
		glm::vec3 p2 = glm::vec3(v2.position.x, v2.position.y, v2.position.z);
		glm::vec3 p3 = glm::vec3(v3.position.x, v3.position.y, v3.position.z);
		glm::vec3 u = p2 - p1;
		glm::vec3 v = p3 - p1;
		
		normal.direction = glm::cross(u, v);

		normal.direction = glm::normalize(normal.direction);
		print();
	}

	/// <summary>
	/// Returns t value if there is an intersection between this triangle and the ray 
	/// Müller trumbone algorithm
	/// </summary>
	float rayIntersection(const Ray& ray);

	void print() {
		std::cout <<
			"V1 = ( " << v1.position.x << ", " << v1.position.y << ", " << v1.position.z << ")" << "\n" <<
			"V2 = ( " << v2.position.x << ", " << v2.position.y << ", " << v2.position.z << ")" << "\n" <<
			"V3 = ( " << v3.position.x << ", " << v3.position.y << ", " << v3.position.z << ")" << "\n" <<
			"Normal = (" << normal.direction.x << ", " << normal.direction.y << ", " << normal.direction.z << ")" << "\n" <<
			"Color = (" << color.color.r << ", " << color.color.g << ", " << color.color.b << ")\n" << std::endl;
	}
	
	Color color;

private:
	Vertex v1, v2, v3;
	Direction normal;
};