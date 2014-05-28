/*! \file colours.h
    \brief Utility for handling colours in OpenGL
    \author Y1400261
    \copyright Copyright Y1400261 2013 - 2014

    This file contains a structure that defines a colour and functions for
    generating them and setting the current OpenGL colour using one.

    (University of York C Programming Labs assessment)
*/

#ifndef COLOURS_INCLUDE
#define COLOURS_INCLUDE

#include <stdio.h>

///A structure that defines a colour
typedef struct {
	unsigned char r,g,b,a;
} colour_t;

/**
 * Generates a colour_t structure from raw RGBA Byte values
 * @param r	The red component of colour
 * @param g The green component of colour
 * @param b The blue component of colour
 * @param a The alpha component of colour
 * @return	The desired colour within a colour_t structure
 */
colour_t colourRGBAByte(unsigned char r, unsigned char g, unsigned char b,
		unsigned char a);

/**
 * Generates a colour_t structure from raw RGBA float values in the range 0.0 to 1.0
 * @param r	The red component of colour
 * @param g The green component of colour
 * @param b The blue component of colour
 * @param a The alpha component of colour
 * @return	The desired colour within a colour_t structure
 */
colour_t colourRGBA(float r, float g, float b, float a);

/**
 * Generates a colour_t structure from raw RGB float values in the range 0.0 to 1.0
 * @param r	The red component of colour
 * @param g The green component of colour
 * @param b The blue component of colour
 * @param a The alpha component of colour
 * @return	The desired colour within a colour_t structure
 */
colour_t colourRGB(float r, float g, float b);

/**
 * Generates a colour_t structure from raw RGB Byte values
 * @param r	The red component of colour
 * @param g The green component of colour
 * @param b The blue component of colour
 * @param a The alpha component of colour
 * @return	The desired colour within a colour_t structure
 */
colour_t colourRGBByte(unsigned char r, unsigned char g, unsigned char b);

/**
 * Sets the current OpenGL colour based on the info in a colour_t instance
 * @param c	The desired colour
 */
void colourEnable(colour_t c);

#endif //COLOURS_INCLUDE
