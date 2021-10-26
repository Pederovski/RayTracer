#include "Utilities.h"

std::pair<float, float> computeRandomAngles() {
	float rho = 0.0f, theta = 0.0f;
	//intervals rho [0, 2 * pi], theta [0, pi / 2]
	//y_i & x_i random numbers betweeen 0-1
	float x = ((double)rand() / (RAND_MAX));
	float y = ((double)rand() / (RAND_MAX));

	//std::cout << "x: " << x << " y:" << y << '\n';

	rho = 2.0f * M_PI * x;
	theta = M_PI * y / 2.0f;

	return { rho, theta };
}

glm::vec3 sphericalToCartesianCoordinates(float rho, float theta) {
	float x = std::sin(theta) * std::cos(rho);
	float y = std::sin(theta) * std::sin(rho);
	float z = std::cos(theta);

	return glm::vec3{ x,y,z };
}


//local to world
glm::mat4x4 worldToLocalMatrix(const Ray& incommingRay) {
	//ray and position need to be given in homogeneous coords
	//Z normal at ray surface intersection point
	glm::vec3 Z = incommingRay.intersectionNormal;
	//I = incomming ray 
	glm::vec3 I = incommingRay.intersectionPoint - incommingRay.startPoint.position;
	//X = normalize( I - dot(I,Z) * Z
	glm::vec3 X = glm::normalize(I - glm::dot(I, Z) * Z);
	//Y = cross(-X, Z)
	glm::vec3 Y = glm::normalize(glm::cross(-X, Z));

	//Translate4x4( - incommingray.intersectionpoint)
	glm::mat4x4 identity = glm::imat4x4();
	//glm::mat4x4 translate = glm::translate(identity, -incommingRay.intersectionPoint);
	glm::mat4x4 translate = glm::mat4x4(
		1.0, 0.0, 0.0, -incommingRay.intersectionPoint.x,
		0.0, 1.0, 0.0, -incommingRay.intersectionPoint.y,
		0.0, 0.0, 1.0, -incommingRay.intersectionPoint.z,
		0.0, 0.0, 0.0, 1.0);

	//rotational4x4( X, Y, Z ) 
	glm::mat4x4 rotation = glm::mat4x4(
		X.x, Y.x, Z.x, 0,
		X.y, Y.y, Z.y, 0,
		X.z, Y.z, Z.z, 0,
		0, 0, 0, 1);

	glm::mat4x4 WorldToLocal = rotation * translate;
	//glm::mat4x4 LocalToWorld = glm::inverse(WorldToLocal);


	//std::cout << glm::to_string(rotation) << '\n';
	//std::cout << glm::to_string(translate) << std::endl;

	//Local to world = R * T
	//World to local = invert(local to world)

	//return vec3 position in the new coordinate system? 

	return WorldToLocal;
}

glm::mat4x4 localToWorldMatrix(const Ray& inRay) {
	return glm::inverse(worldToLocalMatrix(inRay));
}