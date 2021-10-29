#include "Camera.h"
#include "EasyBMP.hpp"
#include "Btree.h"


void Camera::render(Scene &_scene)
{
	//Shot a ray through each pixel 
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			Color colorSum{ 0,0,0 };
			for (int k = 0; k < NRAYS; ++k) {
				Ray ray = cameraplane[index(i, j)].r[k];

				//if first ray from camera intersect light src, do not create a tree and give that pixel the value of light src
				if (_scene.sceneLight.lightsrcIntersection(ray)) {
					colorSum.color += _scene.sceneLight.radiance;
				}
				else {
					//std::cout << cameraplane[index(0, 0)].c.color.r << " " << cameraplane[index(0, 0)].c.color.g << " " << cameraplane[index(0, 0)].c.color.b << "\n";
					Btree rayTree{ _scene, ray };

					//rayTree.createTree(rayTree.root, rayTree.root->ray);
					//Color C = _scene.triangleIntersection(rayTree, rayTree.root, cameraplane[(index(i, j))].r);
					//_scene.triangleIntersection(ray);

					//if (_scene.sceneLight.lightsrcIntersection(ray)) {
					//	cameraplane[index(i, j)].c = _scene.sceneLight.radiance;
					//}
					//else {
					//}
					colorSum.color += rayTree.computeColor(rayTree.root).color;
					//std::cout << "After: " << cameraplane[index(0, 0)].c.color.r << " " << cameraplane[index(0, 0)].c.color.g << " " << cameraplane[index(0, 0)].c.color.b << "\n";
				}
			}
			colorSum.color /= (double)NRAYS;
			cameraplane[index(i, j)].c = colorSum;

		}
		std::cout << i << " rows finished" << '\n';
	}

	//Square the color values before finding the maximum r,g,b value and then do the scaling between 0-1 
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

		double min = std::min(std::min(cameraplane[i].c.color.r, cameraplane[i].c.color.g), cameraplane[i].c.color.b);
		if (min < 0)
			cameraplane[i].c.Print();
	}
	//normalize color values between 0 -> 1
	for (int i = 0; i < SIZE * SIZE; i++) {
		cameraplane[i].c.color.r = squezedColor[i].color.r / maxColorValue;
		cameraplane[i].c.color.g = squezedColor[i].color.g / maxColorValue; 
		cameraplane[i].c.color.b = squezedColor[i].color.b / maxColorValue;
	}
	

	//transfer pixel data from cameraplane to image output
	EasyBMP::Image img(SIZE, SIZE);
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			Color c = cameraplane[index(i,j)].c;
			img.SetPixel(i, j, EasyBMP::RGBColor(c.color.r * 255.99, c.color.g * 255.99, c.color.b * 255.99));
		}
	}
	//easy write image to file
	img.Write("scene.bmp");
}

int Camera::index(int c, int r)
{
	return c + SIZE * r;
}
