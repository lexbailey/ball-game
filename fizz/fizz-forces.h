/*! \file fizz-forces.h
    \brief Defines forces
    \author Daniel Bailey
*/

#ifndef PHYSICS_FORCES_INCLUDE
#define PHYSICS_FORCES_INCLUDE

///Type of force ft_Static for a constant force, ft_Explosive for a timed impulse
typedef enum {ft_Static, ft_Explosive} forceType;

///Defines a force that can be applied to an object
typedef struct {
	vector3 forceVector;
	forceType type;
	float impulseTime;
} force_t;

#endif //PHYSICS_FORCES_INCLUDE
