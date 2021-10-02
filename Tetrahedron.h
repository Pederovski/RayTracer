#pragma once
#include "header/Vertex.h"
#include "header/Triangle.h"
#include "header/Color.h"
#include <list>

class Tetrahedron {
public:
	Tetrahedron(const Color& c) {
		Vertex v1{ 5, 1.5, -2 };
		Vertex v2{ 7, 4.0, -2 };
		Vertex v3{ 7, 0, -2 };
		Vertex v4{ 6.5, 2, 2 };

		Triangle t1{ v1, v2, v3, c, false};
		Triangle t2{ v1, v3, v4, c, false};
		Triangle t3{ v1, v4, v2, c, false};
		Triangle t4{ v2, v4, v3, c, false};

		sides.push_back(t1);
		sides.push_back(t2);
		sides.push_back(t3);
		sides.push_back(t4);


	}
	std::list<Triangle> sides;
};