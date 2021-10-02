#include "Ray.h"
#include "Triangle.h"

Ray::Ray(const Ray&r) : startPoint{ r.startPoint }, endPoint{ r.endPoint },
rayColor{ r.rayColor }, intersectionPoint{ r.intersectionPoint } {
	intersectionTriangle = r.intersectionTriangle ? new Triangle{ *r.intersectionTriangle } : nullptr;
}