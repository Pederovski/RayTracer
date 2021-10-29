#include "Btree.h"

void Btree::createTree(Node* ptr, Ray& ray, int depthcounter)
{
	scene.triangleIntersection(ray);

	int maxdepth = 20;
	if (depthcounter > maxdepth)
		return;


	bool terminateRay = checkRayTermination(ray);
	if (terminateRay)
		return;

	//check if ray intersected with triangle or sphere
	//intersected triangle
	if (ray.intersectionTriangle != nullptr) {
		//calculated reflected ray
		//Ray reflectedRay = scene.calculateReflection(ray, ray.intersectionNormal);
		Ray reflectedRay = ray.intersectionTriangle->material->computeReflectionRay(ray);
		//lambertian -> random direction + russian roulette 
		//transparent obj -> få två rays 


		//lowering importance should be done with brdf? 
		//reflectedRay.importance = ptr->ray.importance * 0.8f;
		//if (glm::length(reflectedRay.importance) > 1e-2f) {
			int c = ++depthcounter;
			//insert the reflected ray into tree
			//Node* child = insert(ptr, ptr->reflection, reflectedRay);
			insertReflection(ptr, reflectedRay);
			//call create tree with child node and reflected ray

			createTree(ptr->reflection, ptr->reflection->ray, c);
		//}
	}
	//intersected sphere
	else {
		//do same shit as above 
		//Ray reflectedRay = scene.calculateReflection(ray, ray.intersectionNormal);
		Ray reflectedRay = scene.sceneSphere.material->computeReflectionRay(ray);

		//reflectedRay.importance = ptr->ray.importance * 0.8f;
		//if (glm::length(reflectedRay.importance) > 1e-2f ) {
			int c = ++depthcounter;
			//insert the reflected ray into tree
			//Node* child = insert(ptr, ptr->reflection, reflectedRay);
			insertReflection(ptr, reflectedRay);
			//call create tree with child node and reflected ray

			createTree(ptr->reflection, ptr->reflection->ray, c);
		//}
	}
}

bool Btree::checkRayTermination(const Ray& ray) {

	//ray intersect light src -> terminate
	if (scene.sceneLight.lightsrcIntersection(ray))
		return true;
	
	//ray hit triangle
	if (ray.intersectionTriangle != nullptr) {
		MaterialType material = ray.intersectionTriangle->material->materialType;
		if (material == MaterialType::Mirror)
			return false;
		
		if (material == MaterialType::Lambertian) { //russian roulette
			float alpha = 1 - ray.intersectionTriangle->material->sigma;
			float randomValue = ((double)std::rand() / RAND_MAX);

			return randomValue < alpha;
		}
		//transparent material 
	}
	else {
		MaterialType material = scene.sceneSphere.material->materialType;
		if (material == MaterialType::Mirror)
			return false;

		if (material == MaterialType::Lambertian) //russian roulette
		{
			float alpha = 1 - scene.sceneSphere.material->sigma;
			float randomValue = ((double)std::rand() / RAND_MAX);

			return randomValue < alpha;
		}
		//transparent material
	}

	return false;
}

Color Btree::computeColor(Node* node)
{	
	Color radianceleftchild{ 0,0,0 }, radiancerightchild{ 0,0,0 };
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
	
	//Color Lr = scene.computeDirectIllumination(node->ray);


	MaterialType material =  MaterialType::None;

	Color surfaceColor{0,0,0};
	if (node->ray.intersectionTriangle != nullptr) {
		surfaceColor = node->ray.intersectionTriangle->color;
		material = node->ray.intersectionTriangle->material->materialType;
	}
	else {
		surfaceColor = scene.sceneSphere.color;
		material = scene.sceneSphere.material->materialType;
	}

	if (scene.sceneLight.lightsrcIntersection(node->ray)) {
		double len = glm::length(node->ray.intersectionPoint - node->ray.startPoint.position);
		if (len < 1)
			std::cout << "len: " << len << '\n';
		return scene.sceneLight.radiance / (len * len);
	}

	Color Lr = Color{ 0,0,0 };

	if(material == MaterialType::Lambertian)
		Lr = scene.computeDirectIllumination(node->ray);


	//multiply radiance with surface color
	surfaceColor.color = glm::vec3(surfaceColor.color.r * Lr.color.r,
		surfaceColor.color.g * Lr.color.g, surfaceColor.color.b * Lr.color.b);
	//how impactful shadow ray color is 
	double D = 1.0f; 

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