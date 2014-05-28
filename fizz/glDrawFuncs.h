/*! \file glDrawFuncs.h
    \brief Provides many useful OpenGL drawing functions for basic shapes.
    \author Y1400261
    \copyright Copyright Y1400261 2013 - 2014

    This file contains functions for drawing Lines, Triangles, Rectangles, Circles and Arcs.

    (University of York C Programming Labs assessment)
*/

#ifndef GLDRAWFUNCS_INCLUDE
#define GLDRAWFUNCS_INCLUDE

#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <stdio.h>
#include "vector3.h"
#include "boolean.h"

#include "glDrawFuncs.h"

/**
 * This functions calls the OpenGL function glVertex (variant 3f for three floating point values) to add a vertex to an OpenGL primitive
 * @param v The vertex to add
 */
void drawFuncAddVertex(vector3 v);

/**
 * This functions calls the OpenGL function glNormal (variant 3f for three floating point values) to add a normal to an OpenGL primitive
 * @param v The normal to add
 */
void drawFuncAddNormal(vector3 v);

/**
 * Draws a line between two points
 * @param P1
 * @param P2
 */
void drawFuncLine(vector3 P1, vector3 P2);

/**
 * Draws a triangle
 * @param P1
 * @param P2
 * @param P3
 */
void drawFuncTriangle(vector3 P1, vector3 P2, vector3 P3);

/**
 * Draws a rectangle given two corners and a rotation
 * @param TopLeft		The top left corner of the desired rectangle
 * @param BottomRight	The bottom right corner of the desired rectangle
 * @param rotation		The angle (in degrees) to rotate the desired rectangle
 */
void drawFuncRectangle(vector3 TopLeft, vector3 BottomRight, float rotation);

/**
 * Draws a filled or hollow circle
 * @param centre		The centre of the desired circle
 * @param radius		The radius of the desired circle
 * @param resolution	The number of lines used to draw the outside of the circle
 * @param filled		True for a solid, filled in circle. False for a hollow 'ring'
 */
void drawFuncCircleF(vector3 centre, float radius, int resolution, bool filled);

/**
 * Draws a hollow circle or 'ring'
 * @param centre		The centre of the desired circle
 * @param radius		The radius of the desired circle
 * @param resolution	The number of lines used to draw the outside of the circle
 */
void drawFuncCircle(vector3 centre, float radius, int resolution);

/**
 * Draws a filled circle or 'disc'
 * @param centre		The centre of the desired circle
 * @param radius		The radius of the desired circle
 * @param resolution	The number of lines used to draw the outside of the circle
 */
void drawFuncDisc(vector3 centre, float radius, int resolution);

/**
 * Draws an arc and returns the end points of the arc
 * @param centre		The centre of the circle that the arc lies on
 * @param radius		The radius of the circle that the arc lies on
 * @param resolution	The number of lines used to draw the arc
 * @param startAngle	The angle (in degrees) relative to the vertical axis at which the arc starts
 * @param stopAngle		The angle (in degrees) relative to the vertical axis at which the arc stops
 * @param startPos		A pointer to a vector3 where the start point should be returned
 * @param endPos		A pointer to a vector3 where the end point should be returned
 */
void drawFuncArcResult(vector3 centre, float radius, int resolution, float startAngle, float stopAngle, vector3 *startPos, vector3 *endPos);

/**
 * Draws an arc
 * @param centre		The centre of the circle that the arc lies on
 * @param radius		The radius of the circle that the arc lies on
 * @param resolution	The number of lines used to draw the arc
 * @param startAngle	The angle (in degrees) relative to the vertical axis at which the arc starts
 * @param stopAngle		The angle (in degrees) relative to the vertical axis at which the arc stops

 */
void drawFuncArc(vector3 centre, float radius, int resolution, float startAngle, float stopAngle);

/**
 * Applies a translation to the current OpenGL matrix
 * @param v	The translation
 */
void drawFuncApplyTranslation(vector3 v);

#endif //GLDRAWFUNCS_INCLUDE
