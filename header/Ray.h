#pragma once
#include "Vertex.h"
#include "Color.h"

class Triangle;  //forward that declaration yo

class Ray {
public:
	
	Ray(const Vertex& start, const Vertex& end/*,const Triangle* _loc = nullptr */, const Color& c = Color{}) :
		startPoint{ start }, endPoint{ end }, rayColor{ c }, intersectionNormal{ 0,0,0 }, intersectionPoint{ 0,0,0 },
		importance{ 1, 1, 1 }, intersectionTriangle{ nullptr } {
		/*endPointLocation = _loc ? new Triangle{*_loc} : nullptr ; */
	}
	Ray() = default;

	//copy constructor
	Ray(const Ray& r);

	~Ray() {
		//delete intersectionTriangle;
		intersectionTriangle = nullptr; //is this memory leak? 
	}

	//copy swap idiom
	Ray& operator=(Ray rhs) {
		std::swap(intersectionTriangle, rhs.intersectionTriangle);
		std::swap(startPoint, rhs.startPoint);
		std::swap(endPoint, rhs.endPoint);
		std::swap(rayColor, rhs.rayColor);
		std::swap(intersectionPoint, rhs.intersectionPoint);
		return *this;
	}

	Vertex startPoint, endPoint;
	Color rayColor; // is this the radiance
	glm::vec3 intersectionPoint;
	glm::vec3 intersectionNormal;

	//ref to triangle on which endpoint is located
	Triangle* intersectionTriangle = nullptr;
	//eventuellt inkludera importance i ray obj
	glm::vec3 importance;

private:

};