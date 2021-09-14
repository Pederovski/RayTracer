#pragma once

#include "Color.h"
#include "Ray.h"

class Pixel {
public:
	Pixel(Color color, Ray& ray) :
		c{ color }, r{ ray } {}

	Color c;
	Ray r;
private:

};