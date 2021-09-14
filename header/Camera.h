#pragma once
#include "Vertex.h"
#include "Pixel.h"
#include <vector>
#include <iostream>


const int SIZE = 800;
class Camera {
public:
	Camera(Vertex& e1, Vertex& e2) : eye1{ e1 }, eye2{ e2 } {
		std::cout << SIZE << "\n";
		cameraplane.reserve(SIZE * SIZE);
		float offset = 2 / SIZE; //pixel size width, height

		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				//Calculate direction vector from eyepoint to the pixel
				Vertex cameraplaneEndPoint = Vertex{ 0, i * offset - (1 - offset ), j * offset - (1 - offset) };
				Ray dir = Ray{ useEye1 ? eye1 : eye2, cameraplaneEndPoint };
				cameraplane.push_back(Pixel{ Color{}, dir });
			}
		}
	}
	void render();


	int index(int x, int y);

private:
	bool useEye1 = true; //change to false to use eye2

	Vertex eye1, eye2;
	std::vector<Pixel> cameraplane;
};