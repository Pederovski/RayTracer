#pragma once
#include "header/Vertex.h"
#include "header/Triangle.h"
#include "header/Color.h"
#include <vector>

class Tetrahedron {
public:
	Tetrahedron(const Color& c, const BRDF& brdf = BRDF{}) {
		Vertex v1{ 5, 1.5, -2 };
		Vertex v2{ 7, 4.0, -2 };
		Vertex v3{ 7, 0, -2 };
		Vertex v4{ 6.5, 2, 2 };

		Triangle t1{ v1, v2, v3, c, brdf.wall };
		Triangle t2{ v1, v3, v4, c, brdf.wall };
		Triangle t3{ v1, v4, v2, c, brdf.wall };
		Triangle t4{ v2, v4, v3, c, brdf.wall };

		sides.push_back(t1);
		sides.push_back(t2);
		sides.push_back(t3);
		sides.push_back(t4);

		t1.print();
		t2.print();
		t3.print();
		t4.print();
	}

	std::vector<Triangle> sides;
};