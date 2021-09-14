#pragma once
#include "Triangle.h"
#include "Ray.h"
#include <vector>

class Scene {
public:
	Scene() {
		createScene();
	}

	void triangleIntersection(const Ray& ray); //return ref or ptr instead to save copying time

private:

	void createScene();

	std::vector<Triangle> triangleList;

};