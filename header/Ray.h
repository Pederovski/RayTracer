#pragma once
#include "Vertex.h"
#include "Color.h"

class Triangle;  //forward that declaration yo

class Ray {
public:
	
	Ray(const Vertex& start, const Vertex& end/*,const Triangle* _loc = nullptr */, const Color& c = Color{}) :
		startPoint{ start }, endPoint{ end }, rayColor{ c } {
		/*endPointLocation = _loc ? new Triangle{*_loc} : nullptr ; */
	}
	Ray() = default;

	//copy constructor
	Ray(const Ray& r);

	~Ray() {
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
	//ref to triangle on which endpoint is located
	glm::vec3 intersectionPoint;

	Triangle* intersectionTriangle = nullptr;
	//eventuellt inkludera importance i ray obj

private:

};