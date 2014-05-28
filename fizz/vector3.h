/*! \file vector3.h
    \brief Structures and functions for handling vectors
    \author Y1400261
    \copyright Copyright Y1400261 2013 - 2014

    This is a small library that provides a type for a 3D vector (vector3) and functions for performing operations with them.

    (University of York C Programming Labs assessment)
*/

#ifndef VECTOR3_INCLUDE
#define VECTOR3_INCLUDE

#include <math.h>

///A quick method for converting from degrees to radians, eg: float rightAngleRad = (90 IN_RADIANS);
#define IN_RADIANS /57.2957795
///A quick method for converting from radians to degrees, eg: float rightAngleDeg = ((3.141f/2.0f) IN_DEGREES);
#define IN_DEGREES *57.2957795

///Enumerated type for specifying an axis; x, y or z.
typedef enum {x_axis, y_axis, z_axis} axis_t;

///The 3D vector type
typedef struct {
	float x,y,z;
} vector3;

/**
 * Get the value of an axis from a 3D vector
 * @param v		Pointer to the vector to read
 * @param axis	The axis for which you want the value
 * @return	The value for the specified axis
 */
float vector3GetAxisValue(vector3 *v, axis_t axis);

/**
 * Set the value of an axis from a 3D vector
 * @param v		Pointer to the vector to set
 * @param axis	The axis to set
 * @param value The new value for the specified axis
 */
void  vector3SetAxisValue(vector3 *v, axis_t axis, float value);

/**
 * Translate a vector by another vector (add them together)
 * @param input			The initial vector
 * @param translation	The translation to make (the vector to add)
 * @return	The sum of the two vectors
 */
vector3 vector3Translate(vector3 input, vector3 translation);

/**
 * Invert a vector, making it point in the opposite direction.
 * @param input	The vector to invert
 * @return	The inversion of the input vector
 */
vector3 vector3Invert(vector3 input);

/**
 * Calculate the distance between two vectors
 * @param a
 * @param b
 * @return	The distance between vector a and vector b
 */
float vector3DistanceBetween(vector3 a, vector3 b);

/**
 * Add together all of the vectors in an array of vectors
 * @param inputs		A pointer to the first vector in an array of vectors
 * @param numVectors	The number of vectors in the array
 * @return	The sum of all vectors in the array
 */
vector3 vector3ArraySum(vector3 *inputs, int numVectors);

/**
 * Multiply a vector by a scalar value (scale it).
 * @param input		The vector to scale
 * @param factor	The scale factor
 * @return	The scaled vector
 */
vector3 vector3ScalarProduct(vector3 input, float factor);

/**
 * Multiply each axis in a vector by the equivalent axis in another vector
 * result.x = a.x * b.x; etc.
 * @param a
 * @param b
 * @return	The new vector
 */
vector3 vector3VectorProduct(vector3 a, vector3 b);

/**
 * calculate the dot product of two vectors
 * @param a
 * @param b
 * @return	The dot product of the two inputs
 */
float vector3DotProduct(vector3 a, vector3 b);

/**
 * Calculate the cross product of two vectors
 * @param u
 * @param v
 * @return	The cross product of the two input vectors
 */
vector3 vector3CrossProduct(vector3 u, vector3 v);

/**
 * Calculate the length of a vector
 * @param v	The vector
 * @return	The length of the vector
 */
float vector3Length(vector3 v);

/**
 * Calculate the rotation of a vector for a given axis.
 * @param v				The vector
 * @param rotationAxis	The axis about which the rotation is measured
 * @return	The rotation of the vector on the given axis (in degrees)
 */
float vector3Rotation(vector3 v, axis_t rotationAxis);

/**
 * Normalise a vector. (Set its length to one)
 * @param normal	The vector to be normalised
 * @return	The normal vector
 */
vector3 vector3Normalise(vector3 normal);

/**
 * Reflect a vector in a given normal
 * @param incidence		The incidence vector (the one to reflect)
 * @param normal		The normal of the reflective surface
 * @return	The reflection of the incidence vector in the normal
 */
vector3 vector3Reflection(vector3 incidence, vector3 normal);

/**
 * * Get a vector3 from x, y and z values
 * @param x		The x value
 * @param y		The y value
 * @param z		The z value
 * @return	A vector with the specified values.
 */
vector3 vector3XYZ(float x, float y, float z);

/**
 * Get a null vector (0,0,0)
 * @return	A vector with a value of 0 in x, y and z
 */
vector3 vector3GetNull();

#endif //VECTOR3_INCLUDE
