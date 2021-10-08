#include "Btree.h"

void Btree::createTree(Node* ptr, Ray& ray)
{
	scene.triangleIntersection(ray);
	//check if ray intersected with mirror
	//intersected triangle
	if (ray.intersectionTriangle != nullptr) {
		if (!ray.intersectionTriangle->brdf.isWall()) { 
			//calculated reflected ray
			Ray reflectedRay = scene.calculateReflection(ray, ray.intersectionTriangle->normal);
			//insert the reflected ray into tree
			//Node* child = insert(ptr, ptr->reflection, reflectedRay);
			insertReflection(ptr, reflectedRay);
			ptr->reflection->ray.importance = ptr->ray.importance * 0.8f;
			//call create tree with child node and reflected ray
			createTree(ptr->reflection, reflectedRay);
		}
	}
	//intersected sphere
	else {
		//do same shit as above 
		Direction normal{ glm::normalize(ray.intersectionPoint - scene.sceneSphere.center) };
		//calculated reflected ray
		Ray reflectedRay = scene.calculateReflection(ray, ray.intersectionNormal);
		//insert the reflected ray into tree
		insertReflection(ptr, reflectedRay);
		ptr->reflection->ray.importance = ptr->ray.importance * 0.8f;
		//call create tree with child node and reflected ray
		createTree(ptr->reflection, reflectedRay);
	}
}

Color Btree::computeColor(Node* node)
{	
	Color radianceleftchild, radiancerightchild;
	double leftimportance = 0.0, rightimportance = 0.0;
	//parent radiance = left importance * radiance  +     * radiance / parent importance + scalar * shadowray contribution
	if (node->reflection != nullptr) {
		radianceleftchild = computeColor(node->reflection);
		leftimportance = node->reflection->ray.importance;
	}
	if(node->refraction != nullptr) {
		radiancerightchild = computeColor(node->refraction);
		rightimportance = node->refraction->ray.importance;
	}
	//shoot shadow ray to introduce extra radiance
	Color Lr = scene.shootShadowRay(node->ray.intersectionPoint, scene.sceneLight, node->ray.intersectionNormal);
	Color surfaceColor{};
	if (node->ray.intersectionTriangle != nullptr) {
		surfaceColor = node->ray.intersectionTriangle->color;
	}
	else {
		surfaceColor = scene.sceneSphere.color;
	}
	//multiply radiance with surface color
	surfaceColor.color = glm::vec3(surfaceColor.color.r * Lr.color.r,
		surfaceColor.color.g * Lr.color.g, surfaceColor.color.b * Lr.color.b);
	//how impactful shadow ray color is 
	double D = 0.1f; 
	Color radiance = (leftimportance * radianceleftchild.color + rightimportance * radiancerightchild.color) * (1.0 / node->ray.importance) + D * surfaceColor.color;
	
	return radiance;
}

void Btree::insertReflection(Node* parent, Ray& ray)
{
	Node* child = new Node(ray, parent);
	parent->reflection = child;

}