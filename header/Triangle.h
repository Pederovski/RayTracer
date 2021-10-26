#pragma once
#include "glm\glm.hpp";
#include "Direction.h"
#include "Vertex.h"
#include "Color.h"
#include "Ray.h"
#include <iostream>
#include "Material.h"

const float NOT_FOUND = std::numeric_limits<float>::max();

struct BRDF {
	BRDF(bool w = true) : wall{ w } {}

	bool isWall() {
		return wall;
	}

	//parameters for the brdf
	bool wall;
};

class Triangle {
public:
	Triangle() = default; // : color{}, normal{}, brdf{}, v1{}, v2{}, v3{} {}

	Triangle(const Vertex& vertex1, const Vertex& vertex2, const Vertex& vertex3, const Color& color, const Material* _material) :
		v1{ vertex1 }, v2{ vertex2 }, v3{ vertex3 }, color{ color } {
		material = _material->clone();
		//Calculate normal direction by cross product of the triangle sides
		auto p1 = v1.position;
		auto p2 = v2.position;
		auto p3 = v3.position;
		glm::vec3 u = p2 - p1;
		glm::vec3 v = p3 - p1;

		normal.direction = glm::cross(u, v);

		normal.direction = glm::normalize(normal.direction);
		//print();
	}

	~Triangle() {
		delete material;
		material = nullptr;
	}

	Triangle(const Triangle& r) : v1{ r.v1 }, v2{ r.v2 }, v3{ r.v3 }, normal{ r.normal }, color{ r.color } {
		material = r.material->clone();
	}

	//copy swap idiom
	Triangle& operator=(Triangle rhs) {
		std::swap(material, rhs.material);
		std::swap(v1, rhs.v1);
		std::swap(v2, rhs.v2);
		std::swap(v3, rhs.v3);
		std::swap(normal, rhs.normal);
		std::swap(color, rhs.color);

		return *this;
	}

	/// <summary>
	/// Returns t value if there is an intersection between this triangle and the ray 
	/// Müller trumbone algorithm
	/// </summary>
	float rayIntersection(const Ray& ray) const;

	void print() {
		std::cout <<
			"V1 = ( " << v1.position.x << ", " << v1.position.y << ", " << v1.position.z << ")" << "\n" <<
			"V2 = ( " << v2.position.x << ", " << v2.position.y << ", " << v2.position.z << ")" << "\n" <<
			"V3 = ( " << v3.position.x << ", " << v3.position.y << ", " << v3.position.z << ")" << "\n" <<
			"Normal = (" << normal.direction.x << ", " << normal.direction.y << ", " << normal.direction.z << ")" << "\n" <<
			"Color = (" << color.color.r << ", " << color.color.g << ", " << color.color.b << ")\n" << std::endl;
	}
	
	Color color;
	Direction normal;
	//Material lambertian;
	Material* material;
	Vertex v1, v2, v3;


private:
	
};