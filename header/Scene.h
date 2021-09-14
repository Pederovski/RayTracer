#pragma once
#include "Triangle.h"
#include "Ray.h"
#include <list>
class Scene {
public:
	Scene() {
		createScene();
	}

	Triangle triangleIntersection(const Ray& ray); //return ref or ptr instead to save copying time

private:

	void createScene();

	std::list<Triangle> triangleList;

};