#pragma once
#include "glm\glm.hpp";
#include "Vertex.h"
#include "Color.h"
#include "Direction.h"
#include "Ray.h"

class Triangle{
public:

	Triangle(Vertex vertex1, Vertex vertex2, Vertex vertex3, Color color, Direction normal) :
		v1{vertex1}, v2{vertex2}, v3{vertex3}, c{color}, n{normal} {}

	Vertex rayIntersection(Ray arg) 
	{
		//m�ller-trumbore algorithm

		return Vertex(0,0,0);
	}

private:
	Vertex v1, v2, v3;
	Color c;
	Direction n;
};