#include "Ray.h"
#include "Triangle.h"

Ray::Ray(const Ray&r) : startPoint{ r.startPoint }, endPoint{ r.endPoint },
	rayColor{ r.rayColor }, intersectionPoint{ r.intersectionPoint }, intersectionNormal{ r.intersectionNormal }, importance{ r.importance } {

	intersectionTriangle = r.intersectionTriangle ? new Triangle{ *r.intersectionTriangle } : nullptr;
}