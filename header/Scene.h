#pragma once
#include "Triangle.h"
#include "Sphere.h"
#include "Ray.h"
#include <vector>
#include "Tetrahedron.h"
#include "lightsrc.h"
#include <glm/vec3.hpp>


class Scene {
public:
	Scene() {
		createScene();
	}

	Color triangleIntersection(Ray& ray, int c = 0); //return ref or ptr instead to save copying time

	glm::dvec3 shootShadowRay(const glm::vec3 &start, const Lightsrc &lightsrc, const glm::vec3 &intersectionNormal);

	/// <summary>
	/// Compute the reflection ray at the intersection point in ray
	/// </summary>
	/// <param name="nrofIterations"> how many reflections to compute </param>
	/// <param name="depth">current depth of reflections</param>
	/// <param name="ray">ray being launched in the scene</param>
	/// <param name="intersectionNormal">normal at intersection point</param>
	/// <returns></returns>
	Color calculateReflection(int nrofIterations, int depth, const Ray& ray, const Direction& intersectionNormal);

	void AddTriangle(const Triangle t) {
		triangleList.push_back(t);
	}

	Lightsrc sceneLight;

private:

	void createScene();

	std::vector<Triangle> triangleList;
	Sphere sceneSphere;
};