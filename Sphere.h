#pragma once
#include "header/Vertex.h"
#include "header/Ray.h"
#include "header/Color.h"
#include "header/Triangle.h"

class Sphere {
public:
	Sphere() : center{ glm::vec3{0.0f} }, radius{ 1.0f }, color{ glm::vec3{0.0f} }, material{ nullptr } {}

	Sphere(const glm::vec3& c, float r, const Color& clr, const Material* _material) :
		center{ c }, radius{ r }, color{ clr } {
		material = _material->clone();
	}

	float rayIntersection(const Ray& ray){
		glm::vec3 dir = ray.endPoint.position - ray.startPoint.position;
		dir = glm::normalize(dir); //l i lecture notes

		float a = glm::dot(dir, dir);
		float b = 2 * glm::dot(dir, ray.startPoint.position - center);
		float c = glm::dot(ray.startPoint.position - center, ray.startPoint.position - center) - (radius * radius);

		float underroot = (b / 2) * (b / 2) - a * c;
		if (underroot < 0) //imaginary root 
			return std::numeric_limits<float>::max();

		float d1 = -b / 2 + std::sqrt(underroot);
		float d2 = -b / 2 - std::sqrt(underroot);

		////take the smalle of d1, d2
		float smallest = (d1 < d2) ? d1 : d2;
		float biggest = (d1 > d2) ? d1 : d2;

		//if d1 and d2 is negative -> invalid d value return NOT_FOUND
		if (smallest < 0 && biggest < 0)
			return std::numeric_limits<float>::max();
		else if (smallest < 0) //if d1 is negative -> d2 smallest positive value
			return biggest;
		else
			return smallest; //d1 is smallest positive nr

		////if (smallest < 0)
		////	return std::numeric_limits<float>::max();
		////else
		//	return smallest;
	}

	~Sphere() {
		//delete material;
	}

	glm::vec3 center;
	float radius;
	Color color;
	Material* material;
};