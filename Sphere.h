#pragma once
#include "header/Vertex.h"
#include "header/Ray.h"
#include "header/Color.h"
#include "header/Triangle.h"

class Sphere {
public:
	Sphere() = default;

	Sphere(const glm::vec3& c, float r, const Color& clr, const BRDF& _brdf) :
		center{ c }, radius{ r }, color{ clr }, brdf{ _brdf }  {}


	float rayIntersection(const Ray& ray){
		glm::vec3 dir = ray.endPoint.position - ray.startPoint.position;
		dir = glm::normalize(dir); //l i lecture notes

		float b = 2 * glm::dot(dir, ray.startPoint.position - center);
		float c = glm::dot(ray.startPoint.position - center, ray.startPoint.position - center) - (radius * radius);

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
	BRDF brdf;
};