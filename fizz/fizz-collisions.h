/*! \file fizz-collisions.h
    \brief Detects collisions between various objects
    \author Daniel Bailey
*/

#ifndef PHYSICS_COLLISIONS_INCLUDE
#define PHYSICS_COLLISIONS_INCLUDE

#include <math.h>
#include "vector3.h"
#include "boolean.h"
#include "fizz-objects.h"

#define COLLISION_lcc_Miss 1
#define COLLISION_lcc_Enter 2
#define COLLISION_lcc_Exit 4

/**
 * Check to see if a line has collided with a circle.
 * Returns a bitmasked integer. One bit for each of 'Miss', 'Enter' and 'Exit'
 * Miss - Line didn't collide with circle at all. (This includes the line being inside the circle)
 * Enter - The line entered the circle (moving from a to b)
 * Exit - The line exited the circle (moving from a to b)
 * If miss is set then neither enter or exit is set.
 * Enter and Exit can both be set at the same time
 * @param lineA		Start point of the line to collide
 * @param lineB		End point of the line to collide
 * @param circlePos	Centre of the circle to collide
 * @param circleRad	Radius of the circle to collide
 * @return	(Bitmask) COLLISION_lcc_Miss, COLLISION_lcc_Enter, COLLISION_lcc_Exit
 */
int collisionLineCircle(vector3 lineA, vector3 lineB, vector3 circlePos, float circleRad);

/**
 * Check to see if a line enters a circle
 * @param lineA		Start point of the line to collide
 * @param lineB		End point of the line to collide
 * @param circlePos	Centre of the circle to collide
 * @param circleRad	Radius of the circle to collide
 * @return true if line enters circle
 */
bool collisionLineEntersCircle(vector3 lineA, vector3 lineB, vector3 circlePos, float circleRad);

/**
 * Check to see if a line leaves a circle
 * @param lineA		Start point of the line to collide
 * @param lineB		End point of the line to collide
 * @param circlePos	Centre of the circle to collide
 * @param circleRad	Radius of the circle to collide
 * @return true if line leaves circle
 */
bool collisionLineLeavesCircle(vector3 lineA, vector3 lineB, vector3 circlePos, float circleRad);

/**
 * Check to see if a line isn't touching a circle
 * @param lineA		Start point of the line to collide
 * @param lineB		End point of the line to collide
 * @param circlePos	Centre of the circle to collide
 * @param circleRad	Radius of the circle to collide
 * @return true if line missed the circle
 */
bool collisionLineMissedCircle(vector3 lineA, vector3 lineB, vector3 circlePos, float circleRad);

/**
 * Check to see if two circles are touching
 * @param c1Pos	Position of the first circle
 * @param c1Rad	Radius of the first circle
 * @param c2Pos	Position of the second circle
 * @param c2Rad	Radius of the second circle
 * @return	true if circles are touching
 */
bool collisionCircles(vector3 c1Pos, float c1Rad, vector3 c2Pos, float c2Rad);

/**
 * Checks to see if a moving circle will hit a standing circle within a particular time frame
 * @param object		The physics object that represents the moving circle
 * @param circleRad		The radius of the moving circle object
 * @param target		The position of the static circle
 * @param targetSize	The radius of the static circle
 * @param time_delta	The time frame in which the object will move
 * @return	true if the circle is touching the target or if its centre will be within the target circle before the time frame is up
 */
bool collisionMovingCircleStaticCircle(physics_object_t object, float circleRad, vector3 target, float targetSize, float time_delta);
#endif //PHYSICS_COLLISIONS_INCLUDE
