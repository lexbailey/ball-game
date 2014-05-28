#include "fizz-objects.h"

void physObjInitialise(physics_object_t *object, vector3 startPos,
		int numForces, int numConstraints) {

	//Set initial state, enabled, moving, colliding
	object->enabled = true;
	object->isStatic = false;
	object->isGhost = false;

	//initiate location
	object->currentPos = startPos;

	//Allocate space for forces
	if (numForces){
		object->forces = malloc(sizeof(force_t) * numForces);
	}
	object->numForces = numForces;
	object->lastForce = -1;

	//Allocate space for constraints
	if (numConstraints){
		object->constraints = malloc(sizeof(constraint_t) * numConstraints);
	}
	object->numConstraints = numConstraints;
	object->lastConstraint = -1;

	//gravity is initiated to standard earth gravity
	object->gravity.x = 0.0f;
	object->gravity.y = -9.8f;
	object->gravity.z = 0.0f;

	//not moving to start
	object->velocity.x = 0.0f;
	object->velocity.y = 0.0f;
	object->velocity.z = 0.0f;

	//no wind
	object->windSpeed.x = 0.0f;
	object->windSpeed.y = 0.0f;
	object->windSpeed.z = 0.0f;

	//no air resistance
	object->airResistance.x = 0.0f;
	object->airResistance.y = 0.0f;
	object->airResistance.z = 0.0f;

	//air resistance factor low (has a large but finite terminal velocity)
	object->airResistanceFactor.x = 0.1f;
	object->airResistanceFactor.y = 0.1f;
	object->airResistanceFactor.z = 0.1f;
}

void physObjReset(physics_object_t *object, vector3 startPos) {

	//initiate location
	object->currentPos = startPos;

	//not moving
	object->velocity.x = 0.0f;
	object->velocity.y = 0.0f;
	object->velocity.z = 0.0f;

	//no air resistance
	object->airResistance.x = 0.0f;
	object->airResistance.y = 0.0f;
	object->airResistance.z = 0.0f;
}

void physObjFree(physics_object_t *object) {
	//free the forces
	if (object){
		if (object->forces){
			free(object->forces);
			object->forces = NULL;
		}
		//free the constraints
		if (object->constraints){
			free(object->constraints);
			object->constraints = NULL;
		}
	}
}

force_t *physObjAddForce(physics_object_t *object, force_t force) {

	if (force.type == ft_Explosive) {
		//explosive forces are not added to the list, they are simply added to the velocity
		vector3 adjust = vector3ScalarProduct(force.forceVector, force.impulseTime / object->mass);
		object->velocity = vector3Translate(object->velocity, adjust);
	}
	else {
		//get next force ID
		int thisForce = object->lastForce + 1;
		//if we have room...
		if (thisForce < object->numForces) {
			//copy the new force
			(object->forces)[thisForce] = force;
			//up the count
			object->lastForce++;
			//return a pointer to the new force
			return &((object->forces)[thisForce]);
		}
		else {
			//error
			printf("Physics error, too many forces.\n");
		}
	}
	return NULL;
}

constraint_t *physObjAddConstraint(physics_object_t *object,
		constraint_t constraint) {
	//Similar to above function but for constraints
	int thisConstraint = object->lastConstraint + 1;
	if (thisConstraint < object->numConstraints) {
		(object->constraints)[thisConstraint] = constraint;
		object->lastConstraint++;
		return &((object->constraints)[thisConstraint]);
	}
	else {
		//error
		printf("Physics error, too many constraints.\n");
	}

	return NULL;
}

vector3 physObjSumAccels(physics_object_t *object) {
	//Add together all of the forces and divide by the mass to get an acceleration
	int i;
	vector3 *vectors;
	vector3 result;
	int numForces = (object->lastForce + 1) + 2; //2 for gravity and air resistance
	vectors = malloc(sizeof(vector3) * numForces);
	vectors[0] = object->gravity;
	vectors[1] = object->airResistance;
	for (i = 2; i < numForces; i++) {
		vectors[i] = vector3ScalarProduct(((object->forces)[i - 2].forceVector),
				1.0f / (object->mass)); //divide by the mass and add to array
	}
	//do the maths
	result = vector3ArraySum(vectors, numForces);
	//free temporary memory
	free(vectors);
	return result;
}

void physObjDrawForces(physics_object_t *object) {
	//Get all the points we need to draw the lines
	vector3 pos = object->currentPos;
	vector3 airRes = vector3Translate(object->airResistance, pos);
	vector3 vel = vector3Translate(object->velocity, pos);
	vector3 totAccel = vector3Translate(object->totalAccel, pos);

	//Green line for current velocity
	colourEnable(COLOUR_GREEN);
	drawFuncLine(pos, vel);
	//Red line for air resistance
	colourEnable(COLOUR_RED);
	drawFuncLine(pos, airRes);
	//Blue line for acceleration
	colourEnable(COLOUR_BLUE);
	drawFuncLine(pos, totAccel);
}

void physObjStep(physics_object_t *object, float time) {

	//Only step if the object is enabled
	if (object->enabled){
		//Only move is the object is not static
		if (!object->isStatic){

			//calculate new air resistance
			object->airResistance.x = ((-object->velocity.x)
					* object->airResistanceFactor.x) + object->windSpeed.x;
			object->airResistance.y = ((-object->velocity.y)
					* object->airResistanceFactor.y) + object->windSpeed.y;
			object->airResistance.z = ((-object->velocity.z)
					* object->airResistanceFactor.z) + object->windSpeed.z;

			//This position is now the old one
			object->prevPos = object->currentPos;

			//Get the total acceleration
			object->totalAccel = physObjSumAccels(object);

			//Calculate the change in veclocity
			vector3 stepVelocity = vector3ScalarProduct(object->totalAccel, time); //change in velocity is acceleration times time
			//Make the change to the velocity
			object->velocity = vector3Translate(object->velocity, stepVelocity); //new total velocity
			//calculate the ditance and direction to move
			vector3 thisStep = vector3ScalarProduct(object->velocity, time); //distance is velocity times time
			//the new position is the old one plus this distance
			object->currentPos = vector3Translate(thisStep, object->currentPos);	//make the move!
			//Now we just need to compute the speed
			float stepDistance = vector3DistanceBetween(object->currentPos, object->prevPos);
			object->computedSpeed = stepDistance / time;
		}

		//Finally, ensure that the object violates no constraints
		//This is done even if the object is static
		physObjManageConstraints(object);
	}
}

bool physObjIsConstraintViolated(physics_object_t *object, constraint_t con) {
	//This function can explain itself
	switch (con.type){
		case ct_MaxTranslation:
			return (vector3GetAxisValue(&(object->currentPos), con.axis) > con.value);
		case ct_MinTranslation:
			return (vector3GetAxisValue(&(object->currentPos), con.axis) < con.value);
	}
	return false;
}

void physObjManageConstraints(physics_object_t *object) {
	int i;
	//loop through all constraints
	for (i = 0; i<= object->numConstraints-1; i++){
		constraint_t con = object->constraints[i];
		if (physObjIsConstraintViolated(object, con)){
			//if the constraint is violated then move the object within the constraint
			vector3SetAxisValue(&(object->currentPos), con.axis, con.value);
		}
	}
}

bool physObjIsMovingCircle(physics_object_t *object){
	return (object->collisionBounds == pcb_Circle) && (!object->isStatic);
}

bool physObjIsStaticCircle(physics_object_t *object){
	return (object->collisionBounds == pcb_Circle) && (object->isStatic);
}
