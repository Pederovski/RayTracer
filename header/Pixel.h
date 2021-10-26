#pragma once

#include "Color.h"
#include "Ray.h"
#include <vector>

class Pixel {
public:
	Pixel(const Color&  color, const std::vector<Ray>& rays) :
		c{ color }, r{ rays } {}

	Color c;
	std::vector<Ray> r;
};