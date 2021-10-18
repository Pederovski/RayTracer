#pragma once
#include <glm/glm.hpp>
#include "Ray.h"
#define _USE_MATH_DEFINES 
#include <math.h>
#include "Utilities.h"
#include <glm/gtc/matrix_transform.hpp>

class Material {
public:
	Material(float reflectivityConstant) : sigma{ reflectivityConstant } {}
	//get brdf ->
	//compute reflectionray
	virtual Ray computeReflectionRay(const Ray& inRay) = 0;
	virtual float getBRDF() = 0;

	virtual ~Material() = default;

	virtual Material* clone() const = 0;

protected:
	/// <summary>
	/// Reflectivity consant, 0 -> piece of coal, 1 -> white plastic ball
	/// </summary>
	float sigma;
};

class LambertianMaterial : public Material {
public:
	LambertianMaterial(float reflectionconstant) : Material{ reflectionconstant } {}

	virtual Ray computeReflectionRay(const Ray& inRay) override {
		//random direction azimute and inclination angle --> change to local coordinate system
		auto [rho, theta] = computeRandomAngles();

		glm::mat4x4 LTW = localToWorldMatrix(inRay);
		//might need to offset the endposition 
		glm::vec3 startPos = glm::vec3(inRay.intersectionPoint.x, inRay.intersectionPoint.y, inRay.intersectionPoint.z);
		glm::vec3 endP = sphericalToCartesianCoordinates(rho, theta);

		glm::vec4 endPos = glm::vec4(endP, 1); //given in local coordinates

		glm::vec4 endPosWorldCoords = LTW * endPos;
		Ray outRandomRay = Ray{ startPos, {endPosWorldCoords.x, endPosWorldCoords.y, endPosWorldCoords.z} };
		//outgoing ray = F * incommingRay given in 
		float F = M_PI * M_PI * getBRDF() * std::cos(theta) * std::sin(theta);
		outRandomRay.importance = F * inRay.importance;

		return outRandomRay;
	}
	~LambertianMaterial() = default;
	virtual float getBRDF() override {
		return sigma / M_PI;
	}

	virtual LambertianMaterial* clone() const override {
		return new LambertianMaterial{ *this };
	}
};

class PerfectReflectorMaterial : public Material {
public:
	PerfectReflectorMaterial(float reflectionconstant) : Material{ reflectionconstant } {}

	virtual Ray computeReflectionRay(const Ray& inRay) override {
		//perfect reflection model
		//calc new ray dir with reflection law
		glm::vec3 startp = inRay.startPoint.position;
		glm::vec3 endp = inRay.intersectionPoint;
		float offset = 1e-4;
		glm::vec3 correctedIntersectionEndPoint = endp + offset * (startp - endp); //calc offset end point in the other direction

		glm::vec3 inRayDir = correctedIntersectionEndPoint - startp;
		inRayDir = glm::normalize(inRayDir);

		//same as glm::reflect(inRayDir, intersectionNormal.direction)
		glm::vec3 reflectedRay = inRayDir - 2 * (glm::dot(inRayDir, inRay.intersectionNormal)) * inRay.intersectionNormal;
		reflectedRay = glm::normalize(reflectedRay);

		glm::vec3 rayEndPoint = correctedIntersectionEndPoint + 2.0f * reflectedRay;
		glm::vec3 rayStartPoint = correctedIntersectionEndPoint;

		Ray outReflectedRay = Ray{ rayStartPoint, rayEndPoint };
		outReflectedRay.importance = inRay.importance;

		return outReflectedRay;
	}
	~PerfectReflectorMaterial() = default;
	virtual float getBRDF() override {
		return 1.0f;
	}

	virtual PerfectReflectorMaterial* clone() const override {
		return new PerfectReflectorMaterial{ *this };
	}
};

class TransparentMaterial : Material {

};