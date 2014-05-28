#include "fizz-world.h"

void physWorldInitialise(physics_world_t *world, vector3 gravity, int numObjects){
	//set desired gravity
	world->gravity = gravity;

	//wind starts at zero (program must change this later if desired)
	world->windSpeed = vector3GetNull();

	//Allocate space for all of the objects that could be added
	world->physObjects = malloc(sizeof(physics_object_t) * numObjects);
	world->numObjects = numObjects;
	world->lastObject = -1;
}

physics_object_t *physWorldAddObject(physics_world_t *world, physics_object_t object){

	//Get the next object ID
	int thisObj = world->lastObject + 1;

	//If we have room for it
	if (thisObj < world->numObjects) {
		//add it
		(world->physObjects)[thisObj] = object;
		//up the count
		world->lastObject++;
		//return a pointer to it
		return &((world->physObjects)[thisObj]);
	}
	else {
		//error
		printf("Physics error, too many objects.");
	}

	return NULL;
}

bool physWorldObjectCollision(physics_object_t *obj1, physics_object_t *obj2, float timeFrame, bool examineReverse, vector3 *normal){
	//So many collision types, such little time

	//Moving circle on static circle collisions are simple
	//let's see if it's one of them first
	if (physObjIsMovingCircle(obj1)){
		if (physObjIsMovingCircle(obj2)){
			//moving circle collides with moving circle
		}

		if(physObjIsStaticCircle(obj2)){
			//Moving circle collides with static circle
			if (collisionMovingCircleStaticCircle(*obj1, obj1->collisionRadius, obj2->currentPos, obj2->collisionRadius, timeFrame)){
				*normal = vector3Normalise(vector3Translate(obj1->currentPos, vector3Invert(obj2->currentPos)));
				return true;
			}
		}
	}
	//Not all collision types implemented yet.

	if (examineReverse){
		if (physWorldObjectCollision(obj2, obj1, timeFrame, false, normal)){
			return true;
		}
	}

	return false;
}

void physWorldStep(physics_world_t *world, float time) {
	int i;

	//Loop through all objects to see if any have collided and need updating
	for (i = 0; i<= world->lastObject; i++){
		physics_object_t *thisObject = &(world->physObjects[i]);
		thisObject->windSpeed = world->windSpeed;
		//Check for collisions on any object that is enabled, is moving and not a ghost
		if (thisObject->enabled && !thisObject->isGhost && !thisObject->isStatic){
			//Loop through other objects (only the ones after this object)
			int j;
			for (j = i+1; j<= world->lastObject; j++){
				//check!
				physics_object_t *collideObject = &(world->physObjects[j]);
				vector3 normal;
				//If there was a collision
				if (physWorldObjectCollision(thisObject, collideObject, time, true, &normal)){
					//Update the velocities of the objects involved
					if (!thisObject->isStatic){
						thisObject->velocity = vector3ScalarProduct(vector3Reflection(vector3Translate(thisObject->velocity, collideObject->velocity), normal), thisObject->relativeCOR * collideObject->relativeCOR);
					}
					if (!collideObject->isStatic){
						collideObject->velocity = vector3ScalarProduct(vector3Reflection(vector3Translate(thisObject->velocity, collideObject->velocity), normal), thisObject->relativeCOR * collideObject->relativeCOR);
					}
				}
			}
		}
	}

	//Now loop through all objects, stepping each one
	for (i = 0; i<= world->lastObject; i++){
		physObjStep(&(world->physObjects[i]), time);
	}

	//(All objects have to be tested for collisions before any of them is stepped, these loops must be seperate)
}

void physWorldFree(physics_world_t *world){
	//Free the physics objects
	if (world){
		if (world->physObjects){
			free(world->physObjects);
			world->physObjects = NULL;
		}
	}
}
