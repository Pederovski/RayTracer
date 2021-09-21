#pragma once
#include "Triangle.h"
#include "Sphere.h"
#include "Ray.h"
#include <vector>
#include "Tetrahedron.h"
#include "lightsrc.h"

class Scene {
public:
	Scene() {
		createScene();
	}

	Color triangleIntersection(Ray& ray); //return ref or ptr instead to save copying time


	void AddTriangle(const Triangle t) {
		triangleList.push_back(t);
	}

	Lightsrc sceneLight;

private:

	void createScene();

	std::vector<Triangle> triangleList;
	Sphere sceneSphere;
};