#include "Camera.h"
#include "EasyBMP.hpp"

void Camera::render()
{
	Color c{ 255, 0.0, 0.0 };
	Vertex v1{ 0,0,0 };
	Vertex v2{ 0,0,0 };
	Ray ray{ v1,v2,c };

	//Changes all pixel colors to red
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			cameraplane[index(i, j)] = Pixel{ c,ray };
		}
	}


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
