/*! \file fizz-constraints.h
    \brief Defines constraints
    \author Daniel Bailey
*/

#ifndef CONSTRAINTS_INCLUDE
#define CONSTRAINTS_INCLUDE

///Enumerated type marking constratints as minimums or maximums
typedef enum {ct_MinTranslation, ct_MaxTranslation} constraintType;

///A constraint for a physics object
typedef struct {
	float value;
	axis_t axis;
	constraintType type;
}
constraint_t;

#endif //CONSTRAINTS_INCLUDE
