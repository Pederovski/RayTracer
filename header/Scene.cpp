#include "Scene.h"
#define _USE_MATH_DEFINES 
#include <math.h>
#include "Material.h"

/// <summary>
/// Computes the intersection between a ray and scene objects, ie triangles and speheres. 
/// Stores there intersection point and intersection normal in the ray
/// </summary>
/// <param name="ray"></param>
/// <param name="depthcounter"></param>s
float Scene::triangleIntersection(Ray& ray)
{
	float minimumT = NOT_FOUND; //minimum t value found => closest triangle intersection

	//Loopar alla trianglar i listan och kallar på rayintersection(ray)
	for (int i = 0; i < triangleList.size(); i++) {
		float t = triangleList[i].rayIntersection(ray); //här får vi ut massa t-värden
		if (t < minimumT) {
			minimumT = t;
			ray.intersectionTriangle = &triangleList[i];
			ray.intersectionNormal = ray.intersectionTriangle->normal.direction;
		}
	}
	//save intersection point between ray and first triangle surface hit
	ray.intersectionPoint = ray.startPoint.position + minimumT * (ray.endPoint.position - ray.startPoint.position);

	//loopa igenom alla spheres (en atm sphere)
	float d = sceneSphere.rayIntersection(ray);
	if (d < minimumT) {
		minimumT = d;
		ray.intersectionTriangle = nullptr;
		ray.intersectionPoint = ray.startPoint.position + minimumT * glm::normalize(ray.endPoint.position - ray.startPoint.position);
		ray.intersectionNormal = glm::normalize(ray.intersectionPoint - sceneSphere.center);
	}

	return minimumT;
}

/// <summary>
/// Checks if shadow ray is blocked by another object
/// </summary>
/// <param name="shadowray"></param>
/// <returns></returns>
float Scene::visibilityTest(Ray& shadowray) {

	glm::vec3 p = shadowray.startPoint.position;
	//if (p.x < 7.1f && p.x > 6.0f && p.y < -5.0f && p.z < -4.8f) {
	//	//std::cout << "there should be a intersection with sphere here and we should be in shadow\n";
	//}
	float t = triangleIntersection(shadowray);

	//A litle cheat to cast shadows from a sphere, if we intersect the sphere the point is in shadow, 
	//the triangle intersection 't' value will always be between 0-1 and
	//the 'd' value from sphere intersection is not mapped to the same intervall ->
	//the condition for sphere will never be take into account and we get no shadows from the sphere
	float d = sceneSphere.rayIntersection(shadowray);
	if (d < std::numeric_limits<float>::max()) {
		return 0.0f;
	}

	float epsilon = 1e-5;

	if (t < 0 + epsilon || t > 1 + epsilon)
		return 0.0f;

	//intresserade av om vi får en intersection mellan start punkt till ljuskällan som är mindre än 1
	//då blir vår shadowaray blockerad av ett annat object.
	//om t är mindre än 1 -> blockerad -> return 0 annars return 1
	if (1 - t < epsilon)
		return 1.0f;
	
	return 0.0f;
}

glm::dvec3 Scene::computeDirectIllumination(const Ray& ray) {

	//Number of shadow rays
	int N = 10;
	double sum = 0.0f;

	for (int i = 0; i < N; ++i) {

		//Compute shadow ray
		glm::vec3 endpointshadowray = sceneLight.randomPosition();
		glm::vec3 startpointshadowray = ray.intersectionPoint;
		glm::vec3 shadowray = endpointshadowray - startpointshadowray;
		Ray sray{ startpointshadowray, endpointshadowray };

		//Compute geometric term
		float slen = glm::length(shadowray);

		if (slen < 1)
			slen = 1.0f;

		float costhetain = glm::dot(shadowray, ray.intersectionNormal) / slen; //should shadowray be normalized here?

		float costhetaL = glm::dot(-shadowray, sceneLight.normal) / slen; //should -shadowray be normalized here?

		if (costhetain < 0)
			costhetain = 0.0f;

		if (costhetaL < 0)
			costhetaL = 0.0f;

		double G = costhetain * costhetaL / glm::dot(shadowray, shadowray);
		//Compute Visibility
		double V = visibilityTest(sray);

		//if (costhetain < 0 || costhetaL < 0) {
		//	std::cout << "costhetain = " << costhetain << " costhetaL = " << costhetaL << " G = " << G << " V = " << V << '\n';
		//}
		
		sum += V * G * 9.0; // / (1.0f / 9.0f); //multiply with area of lightsrc
	}

	double sigmaOverPi = 0.0f;
	if (ray.intersectionTriangle != nullptr) {
		sigmaOverPi = ray.intersectionTriangle->material->getBRDF();
	}
	else {
		sigmaOverPi = sceneSphere.material->getBRDF();
	}
	//glm::dvec3 sigma = glm::dvec3{ s, s, s };
	// sigma / pi is the brdf of the lambertian surface
	glm::dvec3 estimator = sigmaOverPi * (sceneLight.radiance * (1.0 / N)) * sum;

	//std::cout << "radiance: " << sceneLight.radiance.r << " " << sceneLight.radiance.g << " " << sceneLight.radiance.b << '\n';
	//std::cout << " estimator: " << estimator.r << " " << estimator.g << " " << estimator.b << '\n';

	return estimator;
}

glm::dvec3 Scene::shootShadowRay(const glm::vec3 &start, const Lightsrc &lightsrc, const glm::vec3 &intersectionNormal) {

	glm::vec3 endpointOnLightsrc = lightsrc.randomPosition();
	glm::vec3 direction = endpointOnLightsrc - start; //direction from intersectionpoint to light src
	float r = glm::length(direction); //length of shadowray 
	//inclination angle, negative values are clamped to 0
	double cosTheta = std::max((double)glm::dot(direction, intersectionNormal) / r, 0.0);
	//double solidAngle = lightsrc.crossSection / (r * r);

	glm::dvec3 irradiance = /*solidAngle * */ lightsrc.radiance * cosTheta;
	double rho = 1.0; //reflectivity constant? - perhaps should come from bdrf
	//Emitted radiosity
	glm::dvec3 Lr = rho * irradiance / M_PI;

	return Lr;
}

//Ray Scene::calculateReflection(const Ray& inRay, const Direction& intersectionNormal) {
	////calc new ray dir with reflection law
	//glm::vec3 startp = inRay.startPoint.position;
	//glm::vec3 endp = inRay.intersectionPoint;
	//float offset = 1e-4;
	//glm::vec3 correctedIntersectionEndPoint = endp + offset * (startp - endp); //calc offset end point in the other direction

	//glm::vec3 inRayDir = correctedIntersectionEndPoint - startp;
	//inRayDir = glm::normalize(inRayDir);
	////same as glm::reflect(inRayDir, intersectionNormal.direction)
	//glm::vec3 reflectedRay = inRayDir - 2 * (glm::dot(inRayDir, inRay.intersectionNormal)) * inRay.intersectionNormal;
	//reflectedRay = glm::normalize(reflectedRay);

	//glm::vec3 rayEndPoint = correctedIntersectionEndPoint + 2.0f * reflectedRay;
	//glm::vec3 rayStartPoint = correctedIntersectionEndPoint;
	//return Ray{ rayStartPoint, rayEndPoint };
//}

//Color Scene::calculateReflection(int nrofIterations, int depth, const Ray& ray, const Direction& intersectionNormal) {
	//std::cout << " Should not be called \n";
	//bool spheremirror = sceneSphere.brdf.isWall();
	//if (depth < nrofIterations) {
	//	//intersecteded triangle or sphere that is not a wall
	//	if ((ray.intersectionTriangle != nullptr && !ray.intersectionTriangle->brdf.isWall()) ||
	//		(spheremirror && ray.intersectionTriangle == nullptr)) { //obj hit is perfect reflector surface
	//		//calculate new ray dir with reflection law
	//		glm::vec3 startp = ray.startPoint.position;
	//		glm::vec3 endp = ray.intersectionPoint;
	//		float offset = 0.1f;
	//		glm::vec3 correctedIntersectionEndPoint = endp + offset * (startp - endp);  //going in the opposite direction

	//		glm::vec3 incomingRayDir = correctedIntersectionEndPoint - ray.startPoint.position;
	//		incomingRayDir = glm::normalize(incomingRayDir);
	//		glm::vec3 ReflectedRay = incomingRayDir - 2 * (glm::dot(incomingRayDir, intersectionNormal.direction)) * intersectionNormal.direction;
	//		ReflectedRay = glm::normalize(ReflectedRay);
	//		
	//		
	//		glm::vec3 rayEndPoint = correctedIntersectionEndPoint + 2.0f * ReflectedRay;
	//		glm::vec3 rayStartPoint = correctedIntersectionEndPoint;
	//		Ray R{ rayStartPoint, rayEndPoint };

	//		//shoot ray into scene with recursion
	//		++depth;
	//		Color reflectiveColor; // triangleIntersection(R, depth);

	//		return reflectiveColor;
	//	}
	//}
	//return Color{ 0,0,0 };
//}


void Scene::createScene()
{
	Material* diffuseWall = new LambertianMaterial{ 0.8f };
	//golv
	Triangle t1 = Triangle(Vertex{ 0 ,-6,-5 }, Vertex{ 0 ,6,-5 }, Vertex{ -3,0,-5 }, Color{ 1.0, 1.0, 1.0 }, diffuseWall); //left
	Triangle t2 = Triangle(Vertex{ 10,-6,-5 }, Vertex{ 13,0,-5 }, Vertex{ 10,6,-5 }, Color{ 1.0, 1.0, 1.0 }, diffuseWall); //right 
	Triangle t3 = Triangle(Vertex{ 10,-6,-5 }, Vertex{ 0 ,6,-5 }, Vertex{ 0,-6,-5 }, Color{ 1.0, 1.0, 1.0 }, diffuseWall); //bottomleft
	Triangle t4 = Triangle(Vertex{ 10,-6,-5 }, Vertex{ 10,6,-5 }, Vertex{ 0 ,6,-5 }, Color{ 1.0, 1.0, 1.0 }, diffuseWall); //topright

	//Tak
	Triangle t5 = Triangle(Vertex{ 0 ,-6,5 }, Vertex{ -3,0,5 }, Vertex{ 0 ,6,5 }, Color{ 0.94, 0.59, 0.06 }, diffuseWall); //left
	Triangle t6 = Triangle(Vertex{ 10,-6,5 }, Vertex{ 10,6,5 }, Vertex{ 13,0,5 }, Color{ 0.94, 0.59, 0.06 }, diffuseWall); //right 
	Triangle t7 = Triangle(Vertex{ 10,-6,5 }, Vertex{ 0,-6,5 }, Vertex{ 0 ,6,5 }, Color{ 0.94, 0.59, 0.06 }, diffuseWall); //bottomleft
	Triangle t8 = Triangle(Vertex{ 10,-6,5 }, Vertex{ 0 ,6,5 }, Vertex{ 10,6,5 }, Color{ 0.94, 0.59, 0.06 }, diffuseWall); //topright

	//bottom wall
	Triangle t9  = Triangle(Vertex{ 0,-6,-5 }, Vertex{ 10,-6,5 }, Vertex{ 10,-6,-5 }, Color{ 0, 1.0, 0 }, diffuseWall); //green
	Triangle t10 = Triangle(Vertex{ 0,-6,-5 }, Vertex{ 0 ,-6,5 }, Vertex{ 10,-6, 5 }, Color{ 0, 1.0, 0 }, diffuseWall); //green

	//Bottom right diagonal
	Triangle t11 = Triangle(Vertex{ 10,-6,-5 }, Vertex{ 13,0, 5 }, Vertex{ 13, 0,-5 }, Color{ 1.0, 0, 0 }, diffuseWall); //red
	Triangle t12 = Triangle(Vertex{ 10,-6,-5 }, Vertex{ 10,-6,5 }, Vertex{ 13, 0, 5 }, Color{ 1.0, 0, 0 }, diffuseWall); //red

	//Bottom left diagonal
	Triangle t13 = Triangle(Vertex{ 0 ,-6,-5 }, Vertex{ -3,0,-5 }, Vertex{ 0, -6, 5 }, Color{ 0, 0, 1.0 }, diffuseWall); //blue
	Triangle t14 = Triangle(Vertex{ -3, 0,-5 }, Vertex{ -3,0, 5 }, Vertex{ 0, -6, 5 }, Color{ 0, 0, 1.0 }, diffuseWall); //blue

	//Top wall
	Triangle t15 = Triangle(Vertex{ 0, 6,-5 }, Vertex{ 10,6,-5 }, Vertex{ 10, 6, 5 }, Color{ 1.0, 1.0, 0 }, diffuseWall); //yellow
	Triangle t16 = Triangle(Vertex{ 0, 6,-5 }, Vertex{ 10,6, 5 }, Vertex{ 0 , 6, 5 }, Color{ 1.0, 1.0, 0 }, diffuseWall); //yelllw

	//Top right diagona
	Triangle t17 = Triangle(Vertex{ 10, 6,-5 }, Vertex{ 13,0,-5 }, Vertex{ 13, 0, 5 }, Color{ 1.0, 0, 1.0 }, diffuseWall); //purple
	Triangle t18 = Triangle(Vertex{ 10, 6,-5 }, Vertex{ 13,0, 5 }, Vertex{ 10, 6, 5 }, Color{ 1.0, 0, 1.0 }, diffuseWall); //purple

	//Top left diagonal
	Triangle t19 = Triangle(Vertex{ -3, 0,-5 }, Vertex{ 0, 6,-5 }, Vertex{ 0,6,5 }, Color{ 0, 1.0, 1.0 }, diffuseWall); //cyan
	Triangle t20 = Triangle(Vertex{ -3, 0,-5 }, Vertex{ 0, 6, 5 }, Vertex{-3,0,5 }, Color{ 0, 1.0, 1.0 }, diffuseWall); //cyan

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

	Material* mirror = new PerfectReflectorMaterial{ 1.0f };
	sceneSphere = Sphere(glm::vec3{ 6, -3, 0 }, 2.0f, Color{ 0, 0, 0 }, mirror);

	Tetrahedron T{ Color{ 0.99, 0.49, 0.97 }, mirror };
	for (const Triangle& t : T.sides)
	{
		triangleList.push_back(t);
	}
	

	//sceneLight = Lightsrc{ 0.2, glm::dvec3{1, 1, 1}, glm::vec3{5, 0, 5} };
	delete diffuseWall;
	delete mirror;
}