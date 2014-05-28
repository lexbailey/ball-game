/*! \file fizz-objects.h
    \brief Objects used by a physics world
    \author Daniel Bailey

    This file provides definitions for physics simulation objects.

*/

#ifndef PHYSICS_OBJECTS_INCLUDE
#define PHYSICS_OBJECTS_INCLUDE

#include <stdio.h>
#include <stdlib.h>
#include "vector3.h"
#include "boolean.h"
#include "colours.h"
#include "CustomColours.h"
#include "glDrawFuncs.h"
#include "fizz-forces.h"
#include "fizz-constraints.h"
#include "fizz-collisionTypes.h"

///A structure to hold information about a physics object
typedef struct {

	bool enabled;				//!< is the object part of the simulation? (is stepped and can collide with things)
	bool isStatic;				//!< is the object a non moving object? (stays still when stepped)
	bool isGhost;				//!< is the object a ghost? (other objects pass through it even when enabled)

	vector3 prevPos;			//!< previous position of the object (for reference)
	vector3 currentPos;			//!< current position of the object
	vector3 totalAccel;			//!< the calculated total acceleration of the object
	vector3 velocity;			//!< the current velocity of the object
	vector3 windSpeed;			//!< the total wind speed affecting this object
	vector3 gravity;			//!< gravity acting on this object
	vector3 airResistance;		//!< the total air resistance acting on this object
	vector3 airResistanceFactor;//!< air resistance factor determines terminal velocity 0 is no terminal velocity, 1 is a terminal velocity equal to gravity

	float mass;					//!< the mass of the object in kG

	float relativeCOR;			//!< the relative coefficient of restitution. (the coefficient of restitution when colliding with a completely rigid object)

	float computedSpeed;		//!< the computed speed of the object in the previous step

	int numForces;				//!< the number of forces acting on the object
	int lastForce;				//!< the ID of the last force inserted
	force_t *forces;			//!< array of external forces

	int numConstraints;			//!< number of constraints acting on the object
	int lastConstraint;			//!< the ID of the last constraint inserted
	constraint_t *constraints;	//!< array of external constraints

	physics_collision_bounds_t collisionBounds; //!< the type of bounds for the purpose of detecting collision
	float collisionRadius;		//!< the radius of the collision bounds

} physics_object_t;

#include "fizz-collisions.h"

/**
 * Initialise a physics object
 * @param object			A pointer to the object to initialise
 * @param startPos			The initial position of the object in the simulation
 * @param numForces			The total number of external forces that will act on the object
 * @param numConstraints	The total number of external constraints that will act on the object
 */
void physObjInitialise(physics_object_t *object, vector3 startPos,
		int numForces, int numConstraints);

/**
 * Resets a physics object, setting it's velocity to 0 and moving it to a specified position
 * @param object	A pointer to the object to reset
 * @param startPos	The position that the object will start in
 */
void physObjReset(physics_object_t *object, vector3 startPos);

/**
 * Free a physics object and all associated data
 * @param object	A pointer to the object to free
 */
void physObjFree(physics_object_t *object);

/**
 * Add a force to a physics object
 * @param object	A pointer to the object to which the force will be added
 * @param force		The force to be added (if it is an ft_Explosive type force then it will not count towards the limit numForces)
 * @return	A pointer to the force in the array where it was added
 */
force_t *physObjAddForce(physics_object_t *object, force_t force);

/**
 * Add a constraint to a physics object
 * @param object		A pointer to the object to which the constraint will be added
 * @param constraint	The constraint to be added
 * @return	A pointer to the constraint in the array where it was added
 */
constraint_t *physObjAddConstraint(physics_object_t *object,
		constraint_t constraint);

/**
 * Get the sum of all accelerations of all associated forces for a given object
 * @param object	A pointer to the physics object
 * @return	the sum of all accelerations due to all forces
 */
vector3 physObjSumAccels(physics_object_t *object);

/**
 * This is a debugging tool that draws lines to represent the forces on a given object (using OpenGL)
 * @param object	A pointer to the physics object
 */
void physObjDrawForces(physics_object_t *object);

/**
 * Step a physics object by a given time
 * @param object	A pointer to the object to be stepped
 * @param time		This total time of the step in seconds
 */
void physObjStep(physics_object_t *object, float time);

/**
 * Check to see if an object currently violates a constraint
 * @param object	A pointer to the object to test
 * @param con		The constraint to check
 * @return	true if the object violates the constraint
 */
bool physObjIsConstraintViolated(physics_object_t *object, constraint_t con);

/**
 * Manage all of the constraints for a given object (moving the object to comply if needed)
 * @param object	A pointer to the object to constrain
 */
void physObjManageConstraints(physics_object_t *object);

/**
 * Check to see if a physics object is defined as a moving circle
 * An object is a moving circle is it is not static and its collision bound type is a circle
 * @param object	A pointer to the object to test
 * @return	True if the object is a moving circle
 */
bool physObjIsMovingCircle(physics_object_t *object);

/**
 * Check to see if a physics object is defined as a static circle
 * An object is a moving circle is it is static and its collision bound type is a circle
 * @param object	A pointer to the object to test
 * @return	True if the object is a static circle
 */
bool physObjIsStaticCircle(physics_object_t *object);

#endif  //PHYSICS_OBJECTS_INCLUDE
