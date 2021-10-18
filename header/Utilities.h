#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include "Ray.h"
#include <iostream>
#define _USE_MATH_DEFINES 
#include <math.h>

std::pair<float, float> computeRandomAngles();

glm::vec3 sphericalToCartesianCoordinates(float rho, float theta);

//local to world
glm::mat4x4 worldToLocalMatrix(const Ray& incommingRay);

glm::mat4x4 localToWorldMatrix(const Ray& inRay);