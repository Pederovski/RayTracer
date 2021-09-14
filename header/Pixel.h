#pragma once

#include "Color.h"
#include "Ray.h"

class Pixel {
public:

	Pixel(Color color, Ray& ray) :
		c{ color }, r{ ray } {}

private:
	Color c;
	Ray& r;
};