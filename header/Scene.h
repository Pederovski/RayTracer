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
	Scene() : sceneLight{ Lightsrc{ glm::vec3{5, 0, 5} } } {
		createScene();
	}

	float triangleIntersection(Ray& ray); //return ref or ptr instead to save copying time

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
	Ray calculateReflection(const Ray& inRay, const Direction& intersectionNormal);
	glm::dvec3 computeDirectIllumination(const Ray& ray);
	
	float visibilityTest(Ray& shadowray);

	void AddTriangle(const Triangle t) {
		triangleList.push_back(t);
	}

	Lightsrc sceneLight;
	Sphere sceneSphere;

private:

	void createScene();

	std::vector<Triangle> triangleList;
};