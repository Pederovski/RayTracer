#pragma once
#include "Vertex.h"
#include "Color.h"

class Ray {
public:
	Ray(Vertex& start, Vertex& end, Color& color) : startPoint{ start }, endPoint{ end }, rayColor{ color } {}
	Ray(Vertex& start, Vertex& end) : startPoint{ start }, endPoint{ end }, rayColor{} {}
	
	Vertex startPoint, endPoint;
	Color rayColor;
	//ref to triangle on which endpoint is located

private:

};