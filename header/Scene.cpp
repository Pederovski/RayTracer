#include "Scene.h"

void Scene::triangleIntersection(const Ray& ray)
{
	
}

void Scene::createScene()
{
	//golv
	Triangle t1 = Triangle(Vertex{ 0 ,-6,-5 }, Vertex{ 0 ,6,-5 }, Vertex{ -3,0,-5 }, Color{ 255, 255,255 }); //left
	Triangle t2 = Triangle(Vertex{ 10,-6,-5 }, Vertex{ 13,0,-5 }, Vertex{ 10,6,-5 }, Color{ 255, 255,255 }); //right 
	Triangle t3 = Triangle(Vertex{ 10,-6,-5 }, Vertex{ 0 ,6,-5 }, Vertex{ 0,-6,-5 }, Color{ 255, 255,255 }); //bottomleft
	Triangle t4 = Triangle(Vertex{ 10,-6,-5 }, Vertex{ 10,6,-5 }, Vertex{ 0 ,6,-5 }, Color{ 255, 255,255 }); //topright

	//Tak
	Triangle t5 = Triangle(Vertex{ 0 ,-6,5 }, Vertex{ -3,0,5 }, Vertex{ 0 ,6,5 }, Color{ 255, 255,255 }); //left
	Triangle t6 = Triangle(Vertex{ 10,-6,5 }, Vertex{ 10,6,5 }, Vertex{ 13,0,5 }, Color{ 255, 255,255 }); //right 
	Triangle t7 = Triangle(Vertex{ 10,-6,5 }, Vertex{ 0,-6,5 }, Vertex{ 0 ,6,5 }, Color{ 255, 255,255 }); //bottomleft
	Triangle t8 = Triangle(Vertex{ 10,-6,5 }, Vertex{ 0 ,6,5 }, Vertex{ 10,6,5 }, Color{ 255, 255,255 }); //topright

	//bottom wall
	Triangle t9  = Triangle(Vertex{ 0,-6,-5 }, Vertex{ 10,-6,5 }, Vertex{ 10,-6,-5 }, Color{ 0, 255, 0 }); 
	Triangle t10 = Triangle(Vertex{ 0,-6,-5 }, Vertex{ 0 ,-6,5 }, Vertex{ 10,-6, 5 }, Color{ 0, 255, 0 }); 

	//Bottom right diagonal
	Triangle t11 = Triangle(Vertex{ 10,-6,-5 }, Vertex{ 13,0,-5 }, Vertex{ 13,-6,-5 }, Color{ 255, 0, 0 }); 
	Triangle t12 = Triangle(Vertex{ 10,-6,-5 }, Vertex{ 10,-6,5 }, Vertex{ 13, 0, 5 }, Color{ 255, 0, 0}); 

	//Bottom left diagonal
	Triangle t13 = Triangle(Vertex{ 0 ,-6,-5 }, Vertex{ -3,0,-5 }, Vertex{ 0, -6, 5 }, Color{ 0, 0, 255 }); 
	Triangle t14 = Triangle(Vertex{ -3, 0,-5 }, Vertex{ -3,0, 5 }, Vertex{ 0, -6, 5 }, Color{ 0, 0, 255 }); 

	//Top wall
	Triangle t15 = Triangle(Vertex{ 0, 6,-5 }, Vertex{ 10,6,-5 }, Vertex{ 10, 6, 5 }, Color{ 255, 255, 0 });
	Triangle t16 = Triangle(Vertex{ 0, 6,-5 }, Vertex{ 10,6, 5 }, Vertex{ 0 , 6, 5 }, Color{ 255, 255, 0 });

	//Top right diagona
	Triangle t17 = Triangle(Vertex{ 10, 6,-5 }, Vertex{ 13,0,-5 }, Vertex{ 13, 0, 5 }, Color{ 255, 0, 255});
	Triangle t18 = Triangle(Vertex{ 10, 6,-5 }, Vertex{ 13,0,-5 }, Vertex{ 10, 6, 5 }, Color{ 255, 0, 255});

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
}