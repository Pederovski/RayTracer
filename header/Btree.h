#pragma once
#include "Ray.h"
#include "Scene.h"


class Btree {
	class Node {
	public:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="_ray">ray to insert into tree</param>
		/// <param name="_parent">parent node</param>
		/// <param name="l">reflection node</param>
		/// <param name="r">refraction node</param>
		Node(Ray& _ray, Node* _parent = nullptr, Node* l = nullptr, Node* r = nullptr) :
			parent{ _parent }, reflection{ l }, refraction{ r }, ray{ _ray } {}

		~Node() {
			delete reflection;
			delete refraction;
		}

		Node* parent;
		Node* reflection; //left
		Node* refraction; //right

		Ray ray;
	};

public:
	Btree(Scene& _scene, Ray& _ray) :  scene{_scene}, root{ new Node{_ray} } { 
		createTree(root, root->ray);
	}
	~Btree() {
		delete root;
	}

	void insertRefraction(Node* parent, Ray& ray);
	void insertReflection(Node* parent, Ray& ray);
	void createTree(Node* ptr, Ray& ray, int c = 0);
	Color computeColor(Node* node);
	/// <summary>
	/// Returns true if ray should be terminated
	/// </summary>
	/// <param name="ray"></param>
	/// <returns></returns>
	bool checkRayTermination(const Ray& ray);
	Node* root;

private:
	Scene& scene;

};