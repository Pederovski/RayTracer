#pragma once
#include "Ray.h"

struct Node {
	Node* parent;
	Node* reflection;
	Node* refraction;

	Ray* ray;

	//should node or btree delete ptrs?
};

class Btree {
public:
	Btree() {}
	~Btree() {}

	void insertReflection(Node* parent, Ray value);
	void insertRefraction(Node* parent, Ray value);

private:
	Node* root = nullptr;

};