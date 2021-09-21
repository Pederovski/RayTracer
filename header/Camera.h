#pragma once
#include "Vertex.h"
#include "Pixel.h"
#include <vector>
#include <iostream>
#include "Scene.h"


const int SIZE = 800;
class Camera {
public:
	Camera(Vertex& e1, Vertex& e2, bool useEye1 = true) : eye1{ e1 }, eye2{ e2 } {
		//std::cout << SIZE << "\n";
		cameraplane.reserve(SIZE * SIZE);
		float delta = 2.0f / SIZE; //pixel size width, height

		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				//Calculate direction vector from eyepoint to the pixel
				Vertex cameraplaneEndPoint = Vertex{ 0, j * delta - (1 - delta ), i * delta - (1 - delta) };
				Ray dir = Ray{ useEye1 ? eye1 : eye2, cameraplaneEndPoint };
				cameraplane.push_back(Pixel{ Color{}, dir });
			}
		}
	}
	void render(Scene& scene);


	int index(int x, int y);

private:
	Vertex eye1, eye2;
	std::vector<Pixel> cameraplane;
};