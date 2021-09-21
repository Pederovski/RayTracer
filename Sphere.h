#pragma once
#include "header/Vertex.h"
#include "header/Ray.h"
#include "header/Color.h"

class Sphere {
public:
	Sphere() = default;

	Sphere(const glm::vec3& c, float r, const Color& clr) :
		center{ c }, radius{ r }, color{ clr } {}

	float rayIntersection(const Ray& ray){
		glm::vec3 startpoint{ ray.startPoint.position.x, ray.startPoint.position.y, ray.startPoint.position.z };
		glm::vec4 direction = ray.endPoint.position - ray.startPoint.position;
		glm::vec3 dir{ direction.x, direction.y, direction.z };
		dir = glm::normalize(dir); //l i lecture notes

		float b = 2 * glm::dot(dir, startpoint - center);
		float c = glm::dot(startpoint - center, startpoint - center) - radius * radius;

		float underroot = (b / 2) * (b / 2) - c;
		if (underroot < 0) //imaginary root 
			return std::numeric_limits<float>::max();

		float d1 = -b / 2 + std::sqrt(underroot);
		float d2 = -b / 2 - std::sqrt(underroot);

		//take the smalle of d1, d2
		return (d1 < d2) ? d1 : d2;
	}

	glm::vec3 center;
	float radius;
	Color color;
};