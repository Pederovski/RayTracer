#pragma once
#include <glm/glm.hpp>
#include "Triangle.h"

class Lightsrc {
public:
	//Lightsrc() = default;
	/*
	Lightsrc(float _crossSection, const glm::dvec3& _radiance, const glm::vec3& _position) :
		crossSection{_crossSection}, radiance{_radiance}, position{_position} {	}*/

	Lightsrc(const glm::vec3& _position) 
	{
		Vertex v1 = Vertex(_position.x - sideLength / 2.0f, _position.y - sideLength / 2.0f, _position.z);
		Vertex v2 = Vertex(_position.x - sideLength / 2.0f, _position.y + sideLength / 2.0f, _position.z);
		Vertex v3 = Vertex(_position.x + sideLength / 2.0f, _position.y + sideLength / 2.0f, _position.z);
		Vertex v4 = Vertex(_position.x + sideLength / 2.0f, _position.y - sideLength / 2.0f, _position.z);

		Material* dummy = new PerfectReflectorMaterial{ 0.0f };
		t1 = Triangle(v1, v3, v4, radiance, dummy);
		t2 = Triangle(v1, v2, v3, radiance, dummy);
		normal = t1.normal.direction;
		delete dummy;

		//t1.print();
		//t2.print();
	}

	glm::vec3 randomPosition() const
	{
		//random value between 0-1
		double randomValue = (double)std::rand() / (RAND_MAX);
		//Generate random x coord in area light
		float randX = t1.v1.position.x + randomValue * (t1.v3.position.x - t1.v1.position.x);
		//Generate random y coord in area light
		float randY = t1.v1.position.y + randomValue * (t2.v2.position.y - t1.v1.position.y);

		glm::vec3 randomPosition = { randX, randY, t1.v1.position.z };

		return randomPosition;
	}

	/// <summary>
	///Check intersection with the lightsrc returns the smallest t value on either triangle 1 or triangle  
	/// </summary>
	/// <param name="ray"></param>
	/// <returns></returns>
	float lightsrcIntersection(Ray& ray) {
		float val1 = t1.rayIntersection(ray);
		float val2 = t2.rayIntersection(ray);

		return val1 < val2 ? val1 : val2;
	}



	//glm::vec3 position;
	//float crossSection;

	//Light src emit radiance L0 ( white light )
	double L0 = 1.0;
	glm::dvec3 radiance{ L0, L0, L0 };
	glm::vec3 normal;

private:
	float sideLength = 3.0f;
	Triangle t1, t2;
};