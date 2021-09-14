#pragma once
#include "Vertex.h"
#include "Pixel.h"
#include <vector>

const int SIZE = 800;
class Camera {
public:

	void render();


	int index(int x, int y);

private:
	bool useEye1 = true; //change to false to use eye2

	Vertex eye1, eye2;
	std::vector<Pixel> viewplane = std::vector<Pixel>(SIZE * SIZE);
};