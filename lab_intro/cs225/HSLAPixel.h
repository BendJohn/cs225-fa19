/**
 * @file HSLAPixel.h
 *
 * @author CS 225: Data Structures
 * @version 2018r1-lab1
 */

#pragma once

#include <iostream>
#include <sstream>

namespace cs225 {
class HSLAPixel {
	public:
	// These are hue, saturation, luminance, and alpha respectively.
	double h;
	double s;
	double l;
	double a;

	// A default pixel is completely opaque (non-transparent) and white.
	HSLAPixel();
	// Constructs an opaque pixel with the given values.
	HSLAPixel(double hue, double saturation, double luminance);
	// Constructs a pixel with the given values.
	HSLAPixel(double hue, double saturation, double luminance, double alpha);
};	
}
