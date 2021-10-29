#pragma once
#include "Vertex.h"
#include "Pixel.h"
#include <vector>
#include <iostream>
#include "Scene.h"


const int SIZE = 800;
const int NRAYS = 16;
class Camera {
public:
	Camera(Vertex& e1, Vertex& e2, bool useEye1 = true) : eye1{ e1 }, eye2{ e2 } {

		cameraplane.reserve(SIZE * SIZE);
		float delta = 2.0f / SIZE; //pixel size width, height

		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				std::vector<Ray> rays; 
				for (int k = 0; k < NRAYS; ++k) {
					//Calculate direction vector from eyepoint to the pixel
					float x = (double)rand() / RAND_MAX;
					float y = (double)rand() / RAND_MAX;

					x = x * delta - (delta / 2.0f);
					y = y * delta - (delta / 2.0f);

					Vertex cameraplaneEndPoint = Vertex{ 0, j * delta - (1 - delta / 2.0f) + x, i * delta - (1 - delta / 2.0f) + y };
					Ray ray = Ray{ useEye1 ? eye1 : eye2, cameraplaneEndPoint };

					rays.push_back(ray);
				}
				cameraplane.push_back(Pixel{ Color{0,0,0}, rays });
			}
		}
	}
	void render(Scene& scene);


	int index(int x, int y);

private:
	Vertex eye1, eye2;
	std::vector<Pixel> cameraplane;
};