#include "Camera.h"
#include "EasyBMP.hpp"


void Camera::render(Scene &_scene)
{
	//Shot a ray through each pixel 
	//Currently saves the first interaction with a triangle as that pixelcolor
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			//std::cout << cameraplane[index(0, 0)].c.color.r << " " << cameraplane[index(0, 0)].c.color.g << " " << cameraplane[index(0, 0)].c.color.b << "\n";
			Color C = _scene.triangleIntersection(cameraplane[(index(i, j))].r);
			cameraplane[index(i, j)].c = C;
			//std::cout << "After: " << cameraplane[index(0, 0)].c.color.r << " " << cameraplane[index(0, 0)].c.color.g << " " << cameraplane[index(0, 0)].c.color.b << "\n";
		}
	}

	//transfer pixel data from cameraplane to image output
	EasyBMP::Image img(SIZE, SIZE);
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			Color c = cameraplane[index(i,j)].c;
			img.SetPixel(i, j, EasyBMP::RGBColor(c.color.r, c.color.g, c.color.b));
		}
	}
	//easy write image to file
	img.Write("scene.bmp");
}

int Camera::index(int c, int r)
{
	return c + SIZE * r;
}
