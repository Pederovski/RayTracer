#include "Triangle.h"

float Triangle::rayIntersection(Ray& ray)
{
	glm::vec3 T = ray.startPoint.position - v1.position;
	glm::vec3 E1 = v2.position - v1.position;
	glm::vec3 E2 = v3.position - v1.position;
	glm::vec3 D = ray.endPoint.position - ray.startPoint.position;

	D = glm::normalize(D); //normalize or nah ? 

	float dotproduct = glm::dot(normal.direction, D);
	if (dotproduct > 0) //larger or equals than 0? 
		return NOT_FOUND;


	auto P = glm::cross(D, E2);
	auto Q = glm::cross(T, E1);
	auto PE1 = glm::dot(P, E1);

	auto t = glm::dot(Q, E2) / PE1;
	auto u = glm::dot(P, T) / PE1;
	auto v = glm::dot(Q, D) / PE1;

	if (u >= 0 && v >= 0 && (u + v) <= 1) {
		//auto res = ray.startPoint.position + t * (ray.endPoint.position - ray.startPoint.position);
		return t;
	}
	else
		return NOT_FOUND; //the function caller has to delete the allocated memory
}
