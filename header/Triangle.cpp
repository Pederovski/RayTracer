#include "Triangle.h"

float Triangle::rayIntersection(Ray& ray)
{
	glm::vec3 T = ray.startPoint.position - v1.position;
	glm::vec3 E1 = v2.position - v1.position;
	glm::vec3 E2 = v3.position - v1.position;
	glm::vec3 D = ray.endPoint.position - ray.startPoint.position;

	//D = glm::normalize(D); //normalize or nah ? 
	
	auto dotproduct = glm::dot(normal.direction, glm::normalize(D));
	if (dotproduct >= 0) //larger or equals than 0? 
		return NOT_FOUND;


	auto P = glm::cross(D, E2);
	auto Q = glm::cross(T, E1);
	auto PE1 = glm::dot(P, E1);

	float t = glm::dot(Q, E2) / PE1;
	float u = glm::dot(P, T) / PE1;
	float v = glm::dot(Q, D) / PE1;

	float epsilon = 1e-5;

	if (u > -epsilon && v > -epsilon && t > -epsilon && (u + v) < 1 + epsilon) {
		//auto res = ray.startPoint.position + t * (ray.endPoint.position - ray.startPoint.position);
		//glm::vec3 point = (1 - u - v) * v1.position + u * v2.position + v * v3.position;
		//std::cout << "Point from triangle intersect " << point.x << " " << point.y << " " << point.z << '\n';
		return t;
	}
	else {
		return NOT_FOUND; //the function caller has to delete the allocated memory
	}
}
