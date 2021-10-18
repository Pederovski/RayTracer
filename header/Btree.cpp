#include "Btree.h"

void Btree::createTree(Node* ptr, Ray& ray, int depthcounter)
{
	if (depthcounter > 10) //max 10 reflections
		return;

	scene.triangleIntersection(ray);

	//check if ray intersected with mirror
	//intersected triangle
	if (ray.intersectionTriangle != nullptr) {
		 
		//calculated reflected ray
		//Ray reflectedRay = scene.calculateReflection(ray, ray.intersectionNormal);
		//Ray r = ray->intersectiontriangle.material.getreflectedRay();
		Ray reflectedRay = ray.intersectionTriangle->material->computeReflectionRay(ray);
		//lambertian -> random direction + russian roulette 
		//transparent obj -> f� tv� rays 

		//lowering importance should be done with brdf? 
		//reflectedRay.importance = ptr->ray.importance * 0.8f;
		if (glm::length(reflectedRay.importance) > 1e-2f) {
			int c = ++depthcounter;
			//insert the reflected ray into tree
			//Node* child = insert(ptr, ptr->reflection, reflectedRay);
			insertReflection(ptr, reflectedRay);
			//call create tree with child node and reflected ray

			createTree(ptr->reflection, ptr->reflection->ray, c);
		}
		
	}
	//intersected sphere
	else {
		//do same shit as above 
		//Ray reflectedRay = scene.calculateReflection(ray, ray.intersectionNormal);
		Ray reflectedRay = scene.sceneSphere.material->computeReflectionRay(ray);

		//reflectedRay.importance = ptr->ray.importance * 0.8f;
		if (glm::length(reflectedRay.importance) > 1e-2f ) {
			int c = ++depthcounter;
			//insert the reflected ray into tree
			//Node* child = insert(ptr, ptr->reflection, reflectedRay);
			insertReflection(ptr, reflectedRay);
			//call create tree with child node and reflected ray

			createTree(ptr->reflection, ptr->reflection->ray, c);
		}
	}
}

Color Btree::computeColor(Node* node)
{	
	Color radianceleftchild, radiancerightchild;
	glm::dvec3 leftimportance = glm::dvec3(0.0), rightimportance = glm::dvec3(0.0);
	//parent radiance = left importance * radiance  + right importance * radiance / parent importance + scalar * shadowray contribution
	if (node->reflection != nullptr) {
		radianceleftchild = computeColor(node->reflection);
		leftimportance = node->reflection->ray.importance;
	}
	if(node->refraction != nullptr) {
		radiancerightchild = computeColor(node->refraction);
		rightimportance = node->refraction->ray.importance;
	}
	//shoot shadow ray to introduce extra radiance
	//Color Lr = scene.shootShadowRay(node->ray.intersectionPoint, scene.sceneLight, node->ray.intersectionNormal);
	Color Lr = scene.computeDirectIllumination(node->ray);
	
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

	Color radiance = Color{ glm::vec3(
		((leftimportance.x * radianceleftchild.color.x + rightimportance.x * radiancerightchild.color.x) /
			node->ray.importance.x + D * surfaceColor.color.x),
		((leftimportance.y * radianceleftchild.color.y + rightimportance.y * radiancerightchild.color.y) /
			node->ray.importance.y + D * surfaceColor.color.y),
		((leftimportance.z * radianceleftchild.color.z + rightimportance.z * radiancerightchild.color.z) /
			node->ray.importance.z + D * surfaceColor.color.z)) };
	
	return radiance;
}

void Btree::insertReflection(Node* parent, Ray& ray)
{
	Node* child = new Node(ray, parent);
	parent->reflection = child;

}