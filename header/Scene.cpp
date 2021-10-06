#include "Scene.h"
#define _USE_MATH_DEFINES 
#include <math.h>

Color Scene::triangleIntersection(Ray& ray, int depthcounter)
{
	float minimumT = NOT_FOUND; //minimum t value found => closest triangle intersection
	Color pointSurfaceColor;
	Direction intersectionNormal;

	//Loopar alla trianglar i listan och kallar på rayintersection(ray)
	for (int i = 0; i < triangleList.size(); i++) {
		float t = triangleList[i].rayIntersection(ray); //här får vi ut massa tvärden
		if (t < minimumT) {
			minimumT = t;
			ray.intersectionTriangle = &triangleList[i];
			pointSurfaceColor = ray.intersectionTriangle->color.color;
			intersectionNormal.direction = ray.intersectionTriangle->normal.direction;
			//pointSurfaceColor = triangleList[i].color.color;
			//intersectionNormal.direction = triangleList[i].normal.direction;
		}
	}
	//save intersection point between ray and first triangle surface hit
	ray.intersectionPoint = ray.startPoint.position + minimumT * glm::normalize(ray.endPoint.position - ray.startPoint.position);

	//loopa igenom alla spheres (en atm sphere)
	float d = sceneSphere.rayIntersection(ray);
	if (d < minimumT) {
		minimumT = d;
		pointSurfaceColor = sceneSphere.color;
		ray.intersectionTriangle = nullptr;
		ray.intersectionPoint = ray.startPoint.position + minimumT * glm::normalize(ray.endPoint.position - ray.startPoint.position);
		intersectionNormal.direction = glm::normalize(ray.intersectionPoint - sceneSphere.center);
	}

	if (minimumT == NOT_FOUND) {
		std::cout << "No intersection with triangle or sphere \n";
	//	Direction intersectDir{ ray.intersectionPoint - ray.startPoint.position };
	//	Direction eyeToplane{ glm::normalize(ray.endPoint.position - ray.startPoint.position) };
	//	intersectDir.print();
	//	eyeToplane.print();
	//	std::cout << '\n';
	//	//glm::vec3 dir = ray.endPoint.position - ray.startPoint.position;
	//	//std::cout << " ray startpoint " << ray.startPoint.position.x << " " <<
	//	//	ray.startPoint.position.y<< " " << ray.startPoint.position.z << " ";
	//	//std::cout << " ray endpoint " << ray.endPoint.position.x << " " <<
	//	//	ray.endPoint.position.y << " " << ray.endPoint.position.z << " ";
	//	//std::cout << "ray direction " << dir.x << " " << dir.y << " " << dir.z << "\n\n";
	//	//return Color{ 255,255,255 };
	}



	////if we intersected the sphere, calc normal in that position.

	//color reflected color
	Color reflectedColor = calculateReflection(1, depthcounter, ray, intersectionNormal);

	//calc reflection ray if obj
	//btree.insertreflection(currentNode, reflectionray);
	//scene.triangleIntersection(reflectionray, currnode = currenode->reflection)

	//calc refraction ray if transparent
	//btree.insertrefractionray(currentNode, refractionray);
	//scene.triangleIntersection(refractionray);

	//Shoot shadow ray 
	glm::dvec3 Lr = shootShadowRay(ray.intersectionPoint, sceneLight, intersectionNormal.direction);

	//multiply surface color with emitted radiosity
	pointSurfaceColor.color = glm::vec3(pointSurfaceColor.color.r * Lr.r, pointSurfaceColor.color.g * Lr.g, pointSurfaceColor.color.b * Lr.b);
	
	//add shadowray color with reflected color
	return pointSurfaceColor.color + reflectedColor.color;
}

glm::dvec3 Scene::shootShadowRay(const glm::vec3 &start, const Lightsrc &lightsrc, const glm::vec3 &intersectionNormal) {
	glm::vec3 direction = lightsrc.position - start; //direction from intersectionpoint to light src
	float r = glm::length(direction); //length of shadowray 
	//inclination angle, negative values are clamped to 0
	double cosTheta = std::max((double)glm::dot(direction, intersectionNormal) / r, 0.0);
	double solidAngle = lightsrc.crossSection / (r * r);

	glm::dvec3 irradiance = solidAngle * lightsrc.radiance * cosTheta;
	double rho = 1.0; //reflectivity constant? - perhaps should come from bdrf
	//Emitted radiosity
	glm::dvec3 Lr = rho * irradiance / M_PI;

	return Lr;
}

Color Scene::calculateReflection(int nrofIterations, int depth, const Ray& ray, const Direction& intersectionNormal) {
	bool spheremirror = sceneSphere.brdf.isWall();
	if (depth < nrofIterations) {
		//intersecteded triangle or sphere that is not a wall
		if ((ray.intersectionTriangle != nullptr && !ray.intersectionTriangle->brdf.isWall()) ||
			(spheremirror && ray.intersectionTriangle == nullptr)) { //obj hit is perfect reflector surface
			//calculate new ray dir with reflection law
			glm::vec3 startp = ray.startPoint.position;
			glm::vec3 endp = ray.intersectionPoint;
			float offset = 0.25f;
			glm::vec3 correctedIntersectionEndPoint = endp + offset * (startp - endp);  //going in the opposite direction

			glm::vec3 incomingRayDir = correctedIntersectionEndPoint - ray.startPoint.position;
			incomingRayDir = glm::normalize(incomingRayDir);
			glm::vec3 ReflectedRay = incomingRayDir - 2 * (glm::dot(incomingRayDir, intersectionNormal.direction)) * intersectionNormal.direction;
			ReflectedRay = glm::normalize(ReflectedRay);

			glm::vec3 rayEndPoint = correctedIntersectionEndPoint + 2.0f * ReflectedRay;
			glm::vec3 rayStartPoint = correctedIntersectionEndPoint;
			Ray R{ rayStartPoint, rayEndPoint };

			//shoot ray into scene with recursion
			++depth;
			Color reflectiveColor = triangleIntersection(R, depth);

			return reflectiveColor;
		}
	}
	return Color{ 0,0,0 };
}


void Scene::createScene()
{
	//golv
	Triangle t1 = Triangle(Vertex{ 0 ,-6,-5 }, Vertex{ 0 ,6,-5 }, Vertex{ -3,0,-5 }, Color{ 255, 255, 255 }); //left
	Triangle t2 = Triangle(Vertex{ 10,-6,-5 }, Vertex{ 13,0,-5 }, Vertex{ 10,6,-5 }, Color{ 255, 255, 255 }); //right 
	Triangle t3 = Triangle(Vertex{ 10,-6,-5 }, Vertex{ 0 ,6,-5 }, Vertex{ 0,-6,-5 }, Color{ 255, 255, 255 }); //bottomleft
	Triangle t4 = Triangle(Vertex{ 10,-6,-5 }, Vertex{ 10,6,-5 }, Vertex{ 0 ,6,-5 }, Color{ 255, 255, 255 }); //topright

	//Tak
	Triangle t5 = Triangle(Vertex{ 0 ,-6,5 }, Vertex{ -3,0,5 }, Vertex{ 0 ,6,5 }, Color{ 240, 151, 17 }); //left
	Triangle t6 = Triangle(Vertex{ 10,-6,5 }, Vertex{ 10,6,5 }, Vertex{ 13,0,5 }, Color{ 240, 151, 17 }); //right 
	Triangle t7 = Triangle(Vertex{ 10,-6,5 }, Vertex{ 0,-6,5 }, Vertex{ 0 ,6,5 }, Color{ 240, 151, 17 }); //bottomleft
	Triangle t8 = Triangle(Vertex{ 10,-6,5 }, Vertex{ 0 ,6,5 }, Vertex{ 10,6,5 }, Color{ 240, 151, 17 }); //topright

	//bottom wall
	Triangle t9  = Triangle(Vertex{ 0,-6,-5 }, Vertex{ 10,-6,5 }, Vertex{ 10,-6,-5 }, Color{ 0, 255, 0 }); //green
	Triangle t10 = Triangle(Vertex{ 0,-6,-5 }, Vertex{ 0 ,-6,5 }, Vertex{ 10,-6, 5 }, Color{ 0, 255, 0 }); //green

	//Bottom right diagonal
	Triangle t11 = Triangle(Vertex{ 10,-6,-5 }, Vertex{ 13,0, 5 }, Vertex{ 13, 0,-5 }, Color{ 255, 0, 0 }); //red
	Triangle t12 = Triangle(Vertex{ 10,-6,-5 }, Vertex{ 10,-6,5 }, Vertex{ 13, 0, 5 }, Color{ 255, 0, 0 }); //red

	//Bottom left diagonal
	Triangle t13 = Triangle(Vertex{ 0 ,-6,-5 }, Vertex{ -3,0,-5 }, Vertex{ 0, -6, 5 }, Color{ 0, 0, 255 }); //blue
	Triangle t14 = Triangle(Vertex{ -3, 0,-5 }, Vertex{ -3,0, 5 }, Vertex{ 0, -6, 5 }, Color{ 0, 0, 255 }); //blue

	//Top wall
	Triangle t15 = Triangle(Vertex{ 0, 6,-5 }, Vertex{ 10,6,-5 }, Vertex{ 10, 6, 5 }, Color{ 255, 255, 0 }); //yellow
	Triangle t16 = Triangle(Vertex{ 0, 6,-5 }, Vertex{ 10,6, 5 }, Vertex{ 0 , 6, 5 }, Color{ 255, 255, 0 }); //yelllw

	//Top right diagona
	Triangle t17 = Triangle(Vertex{ 10, 6,-5 }, Vertex{ 13,0,-5 }, Vertex{ 13, 0, 5 }, Color{ 255, 0, 255}); //purple
	Triangle t18 = Triangle(Vertex{ 10, 6,-5 }, Vertex{ 13,0, 5 }, Vertex{ 10, 6, 5 }, Color{ 255, 0, 255}); //purple

	//Top left diagonal
	Triangle t19 = Triangle(Vertex{ -3, 0,-5 }, Vertex{ 0, 6,-5 }, Vertex{ 0,6,5 }, Color{ 0, 255, 255 }); //cyan
	Triangle t20 = Triangle(Vertex{ -3, 0,-5 }, Vertex{ 0, 6, 5 }, Vertex{-3,0,5 }, Color{ 0, 255, 255 }); //cyan

	triangleList.push_back(t1);
	triangleList.push_back(t2);
	triangleList.push_back(t3);
	triangleList.push_back(t4);
	triangleList.push_back(t5);
	triangleList.push_back(t6);
	triangleList.push_back(t7);
	triangleList.push_back(t8);
	triangleList.push_back(t9);
	triangleList.push_back(t10);
	triangleList.push_back(t11);
	triangleList.push_back(t12);
	triangleList.push_back(t13);
	triangleList.push_back(t14);
	triangleList.push_back(t15);
	triangleList.push_back(t16);
	triangleList.push_back(t17);
	triangleList.push_back(t18);
	triangleList.push_back(t19);
	triangleList.push_back(t20);

	sceneSphere = Sphere(glm::vec3{ 6, -3, 0 }, 2, Color{ 0, 150, 200 }, true);

	Tetrahedron T{ Color{ 253, 127, 249 }, false };
	for (const Triangle& t : T.sides)
	{
		triangleList.push_back(t);
	}
	
	sceneLight = Lightsrc{ 0.2, glm::dvec3{1, 1, 1}, glm::vec3{5, 0, 5} };
}