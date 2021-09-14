#pragma once

#include "Color.h"
#include "Ray.h"

class Pixel {
public:
	Pixel(const Color&  color, const Ray& ray) :
		c{ color }, r{ ray } {}

	Color c;
	Ray r;
};