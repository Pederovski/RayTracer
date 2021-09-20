#pragma once
#include "Vertex.h"
#include "Color.h"

class Ray {
public:
	
	Ray(const Vertex& start, const Vertex& end/*,const Triangle* _loc = nullptr */, const Color& c = Color{}) :
		startPoint{ start }, endPoint{ end }, rayColor{ c } {
		/*endPointLocation = _loc ? new Triangle{*_loc} : nullptr ; */
	}
	Ray() : startPoint{ 0,0,0,0 }, endPoint{ 0,0,0,0 }, rayColor{ 0,0,0 }, intersectionPoint{ 0,0,0 } {}

	//Ray(const Ray& r) : startPoint{ r.startPoint }, endPoint{ r.endPoint }, rayColor{ r.rayColor } {
	//	endPointLocation = r.endPointLocation ? new Triangle{ *r.endPointLocation } : nullptr;
	//}

	//~Ray() {
	//	delete endPointLocation;
	//}

	////copy swap idiom
	//Ray& operator=(Ray rhs) {
	//	std::swap(endPointLocation, rhs.endPointLocation);
	//	std::swap(startPoint, rhs.startPoint);
	//	std::swap(endPoint, rhs.endPoint);
	//	std::swap(rayColor, rhs.rayColor);
	//	return *this;
	//}

	Vertex startPoint, endPoint;
	Color rayColor; // is this the radiance
	//ref to triangle on which endpoint is located
	glm::vec3 intersectionPoint;
	//eventuellt inkludera importance i ray obj

private:

};