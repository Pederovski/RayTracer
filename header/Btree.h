#pragma once
#include "Ray.h"



class Btree {
	class Node {
		Node(const Ray& _ray, Node* _parent = nullptr, Node* l = nullptr, Node* r = nullptr) :
			parent{ _parent }, reflection{ l }, refraction{ r }, ray{ _ray } {}

		Node* parent;
		Node* reflection; //left
		Node* refraction; //right

		Ray ray;

		//should node or btree delete ptrs?
	};
public:
	Btree() {}
	~Btree() {}

	void insertReflection(Node* parent, Ray ray);
	void insertRefraction(Node* parent, Ray ray);

private:
	Node* root = nullptr;

};