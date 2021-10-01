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

	bool first = false;
	if (first) {
		//find max color value
		double maxColorValue = std::numeric_limits<double>::min();
		for (int i = 0; i < SIZE * SIZE; i++) {
			double max = std::max(std::max(cameraplane[i].c.color.r, cameraplane[i].c.color.g), cameraplane[i].c.color.b);
			if (maxColorValue < max)
				maxColorValue = max;
		}
		//normalize color values between 0 -> 1
		for (int i = 0; i < SIZE * SIZE; i++) {
			cameraplane[i].c.color.r /= maxColorValue;
			cameraplane[i].c.color.g /= maxColorValue;
			cameraplane[i].c.color.b /= maxColorValue;
		}
	}
	else { //Square the color values before finding the maximum r,g,b value and then do the scaling between 0-1 
		std::vector<Color> squezedColor;
		squezedColor.reserve(SIZE * SIZE);
		for (int i = 0; i < SIZE * SIZE; i++) {
			double rs = std::sqrt(cameraplane[i].c.color.r);
			double gs = std::sqrt(cameraplane[i].c.color.g);
			double bs = std::sqrt(cameraplane[i].c.color.b);
			squezedColor.push_back(Color(rs, gs, bs));
		}
		//find max
		double maxColorValue = std::numeric_limits<double>::min();
		for (int i = 0; i < SIZE * SIZE; i++) {
			double max = std::max(std::max(squezedColor[i].color.r, squezedColor[i].color.g), squezedColor[i].color.b);
			if (maxColorValue < max)
				maxColorValue = max;
		}
		//normalize color values between 0 -> 1
		for (int i = 0; i < SIZE * SIZE; i++) {
			cameraplane[i].c.color.r = squezedColor[i].color.r / maxColorValue;
			cameraplane[i].c.color.g = squezedColor[i].color.g / maxColorValue; 
			cameraplane[i].c.color.b = squezedColor[i].color.b / maxColorValue;
		}
	}

	//transfer pixel data from cameraplane to image output
	EasyBMP::Image img(SIZE, SIZE);
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			Color c = cameraplane[index(i,j)].c;
			img.SetPixel(i, j, EasyBMP::RGBColor(c.color.r * 255, c.color.g * 255, c.color.b * 255));
		}
	}
	//easy write image to file
	img.Write("scene.bmp");
}

int Camera::index(int c, int r)
{
	return c + SIZE * r;
}
