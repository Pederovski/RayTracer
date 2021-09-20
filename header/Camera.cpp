#include "Camera.h"
#include "EasyBMP.hpp"


void Camera::render(Scene &_scene)
{
	Color c{ 255, 0.0, 0.0 };
	//Vertex v1{ 0,0,0 };
	//Vertex v2{ 0,0,0 };
	//Ray ray{ v1,v2,c };

	//Changes all pixel colors to red
	//for (int i = 0; i < SIZE; i++) {
	//	for (int j = 0; j < SIZE; j++) {
	//		cameraplane[index(i, j)].c.color = c.color;
	//	}
	//}
	
	//
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			//std::cout << cameraplane[index(0, 0)].c.color.r << " " << cameraplane[index(0, 0)].c.color.g << " " << cameraplane[index(0, 0)].c.color.b << "\n";
			Color C = _scene.triangleIntersection(cameraplane[(index(i, j))].r);
			cameraplane[index(i, j)].c = C;

			//std::cout << "After: " << cameraplane[index(0, 0)].c.color.r << " " << cameraplane[index(0, 0)].c.color.g << " " << cameraplane[index(0, 0)].c.color.b << "\n";

		}
	}

	

	//cameraplane[index(400, 400)].r
	//transfer pixel data from cameraplane to 
	EasyBMP::Image img(SIZE, SIZE);
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			Color c = cameraplane[index(i, j)].c;
			img.SetPixel(i, j, EasyBMP::RGBColor(c.color.r, c.color.g, c.color.b));

		}
	}
	//easy write pic
	img.Write("test.bmp");
}

int Camera::index(int c, int r)
{
	return c + SIZE * r;
}
