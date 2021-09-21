#include "Scene.h"

Color Scene::triangleIntersection(Ray& ray)
{
	float minT = NOT_FOUND;
	Color outcolor;
	Direction intersectionNormal;

	//Loopar alla trianglar i listan och kallar på rayintersection(ray)
	for (int i = 0; i < triangleList.size(); i++) {
		float t = triangleList[i].rayIntersection(ray); //här får vi ut massa tvärden
		if (t != NOT_FOUND && t < minT) {
			minT = t;
			outcolor = triangleList[i].color.color;
			intersectionNormal.direction = triangleList[i].normal.direction;
		}
	}
	//loopa igenom alla spheres (en atm sphere)
	float d = sceneSphere.rayIntersection(ray);
	if (d != NOT_FOUND && d < minT) {
		minT = d;
		outcolor = sceneSphere.color;
	}

	//save intersection point between ray and first surface hit
	glm::vec4 intersectionPoint = ray.startPoint.position + minT * (ray.endPoint.position - ray.startPoint.position);
	ray.intersectionPoint = glm::vec3(intersectionPoint.x, intersectionPoint.y, intersectionPoint.z);

	//if we intersected the sphere, calc normal in that position.
	if (d == minT)
		intersectionNormal.direction = glm::normalize(ray.intersectionPoint - sceneSphere.center);

	//Shoot shadow ray 
	//Ray shadowRay{ glm::vec4{ray.intersectionPoint,1.0}, glm::vec4{sceneLight.position, 1.0} };
	
	//här har vi då ett t värde och vi kan räkna ut en endpoint -> färgvärde på den pixeln från triangeln
	return outcolor;
}

void Scene::createScene()
{
	//golv
	Triangle t1 = Triangle(Vertex{ 0 ,-6,-5 }, Vertex{ 0 ,6,-5 }, Vertex{ -3,0,-5 }, Color{ 255, 255,255 }); //left
	Triangle t2 = Triangle(Vertex{ 10,-6,-5 }, Vertex{ 13,0,-5 }, Vertex{ 10,6,-5 }, Color{ 255, 255,255 }); //right 
	Triangle t3 = Triangle(Vertex{ 10,-6,-5 }, Vertex{ 0 ,6,-5 }, Vertex{ 0,-6,-5 }, Color{ 255, 255,255 }); //bottomleft
	Triangle t4 = Triangle(Vertex{ 10,-6,-5 }, Vertex{ 10,6,-5 }, Vertex{ 0 ,6,-5 }, Color{ 255, 255,255 }); //topright

	//Tak
	Triangle t5 = Triangle(Vertex{ 0 ,-6,5 }, Vertex{ -3,0,5 }, Vertex{ 0 ,6,5 }, Color{ 155, 155,155 }); //left
	Triangle t6 = Triangle(Vertex{ 10,-6,5 }, Vertex{ 10,6,5 }, Vertex{ 13,0,5 }, Color{ 155, 155,155 }); //right 
	Triangle t7 = Triangle(Vertex{ 10,-6,5 }, Vertex{ 0,-6,5 }, Vertex{ 0 ,6,5 }, Color{ 155, 155,155 }); //bottomleft
	Triangle t8 = Triangle(Vertex{ 10,-6,5 }, Vertex{ 0 ,6,5 }, Vertex{ 10,6,5 }, Color{ 155, 155,155 }); //topright

	//bottom wall
	Triangle t9  = Triangle(Vertex{ 0,-6,-5 }, Vertex{ 10,-6,5 }, Vertex{ 10,-6,-5 }, Color{ 0, 255, 0 }); 
	Triangle t10 = Triangle(Vertex{ 0,-6,-5 }, Vertex{ 0 ,-6,5 }, Vertex{ 10,-6, 5 }, Color{ 0, 255, 0 }); 

	//Bottom right diagonal
	Triangle t11 = Triangle(Vertex{ 10,-6,-5 }, Vertex{ 13,0, 5 }, Vertex{ 13, 0,-5 }, Color{ 255, 0, 0 }); 
	Triangle t12 = Triangle(Vertex{ 10,-6,-5 }, Vertex{ 10,-6,5 }, Vertex{ 13, 0, 5 }, Color{ 255, 0, 0}); 

	//Bottom left diagonal
	Triangle t13 = Triangle(Vertex{ 0 ,-6,-5 }, Vertex{ -3,0,-5 }, Vertex{ 0, -6, 5 }, Color{ 0, 0, 255 }); 
	Triangle t14 = Triangle(Vertex{ -3, 0,-5 }, Vertex{ -3,0, 5 }, Vertex{ 0, -6, 5 }, Color{ 0, 0, 255 }); 

	//Top wall
	Triangle t15 = Triangle(Vertex{ 0, 6,-5 }, Vertex{ 10,6,-5 }, Vertex{ 10, 6, 5 }, Color{ 255, 255, 0 });
	Triangle t16 = Triangle(Vertex{ 0, 6,-5 }, Vertex{ 10,6, 5 }, Vertex{ 0 , 6, 5 }, Color{ 255, 255, 0 });

	//Top right diagona
	Triangle t17 = Triangle(Vertex{ 10, 6,-5 }, Vertex{ 13,0,-5 }, Vertex{ 13, 0, 5 }, Color{ 255, 0, 255});
	Triangle t18 = Triangle(Vertex{ 10, 6,-5 }, Vertex{ 13,0, 5 }, Vertex{ 10, 6, 5 }, Color{ 255, 0, 255});

	//Top left diagonal
	Triangle t19 = Triangle(Vertex{ -3, 0,-5 }, Vertex{ 0, 6,-5 }, Vertex{ 0,6,5 }, Color{ 0, 255, 255 });
	Triangle t20 = Triangle(Vertex{ -3, 0,-5 }, Vertex{ 0, 6,-5 }, Vertex{-3,0,5 }, Color{ 0, 255, 255 });

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

	sceneSphere = Sphere(glm::vec3{ 6, -3, 0 }, 2, Color{ 0, 150, 200 });

	Tetrahedron T{ Color{ 130.0,30.0,150.0 } };
	for (const Triangle& t : T.sides)
	{
		triangleList.push_back(t);
	}
	
	sceneLight = Lightsrc{ 1, glm::dvec3{1, 1, 1}, glm::vec3{5, 0, 5} };
}