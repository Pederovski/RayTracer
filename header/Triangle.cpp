#include "Triangle.h"

float Triangle::rayIntersection(Ray& ray)
{
	
	auto t1 = ray.startPoint.position - v1.position;
	auto e1 = v2.position - v1.position;
	auto e2 = v3.position - v1.position;
	auto d = ray.endPoint.position - ray.startPoint.position;


	glm::vec3 T = glm::vec3{ t1.x ,t1.y, t1.z };
	glm::vec3 E1 = glm::vec3{ e1.x, e1.y, e1.z }; 
	glm::vec3 E2 = glm::vec3{ e2.x, e2.y, e2.z };
	glm::vec3 D = glm::vec3{ d.x, d.y, d.z };

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
