/*
 *  Copyright Y1400261 2013 - 2014
 *  See colours.h for function documentation
 *  (University of York C Programming Labs assessment)
 */

#include "colours.h"

//This function generates a colour, in a structure, ready to go.
//It requires the values in unsigned byte form and uses alpha.
colour_t colourRGBAByte(unsigned char r, unsigned char g, unsigned char b,
		unsigned char a) {
	colour_t output;
	output.r = r;
	output.g = g;
	output.b = b;
	output.a = a;
	return output;
}

//This next function and the following two simply call the colourRGBAByte
//function with different values to make it easy to define a colour using
//either floats or unsigned bytes, with or without alpha.
colour_t colourRGBA(float r, float g, float b, float a) {
	return colourRGBAByte(255 * r, 255 * g, 255 * b, 255 * a);
}

colour_t colourRGB(float r, float g, float b) {
	return colourRGBA(r, g, b, 1.0f);
}

colour_t colourRGBByte(unsigned char r, unsigned char g, unsigned char b) {
	return colourRGBAByte(r, g, b, 255);
}

void colourEnable(colour_t c) {
	glColor4ub(c.r, c.g, c.b, c.a);
}
