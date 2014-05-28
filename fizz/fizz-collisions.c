#include "fizz-collisions.h"

//http://stackoverflow.com/questions/1073336/circle-line-collision-detection
int collisionLineCircle(vector3 lineA, vector3 lineB, vector3 circlePos, float circleRad){

	//Clever maths stuff...
	vector3 d = vector3Invert(vector3Translate(lineA, vector3Invert(lineB)));
	vector3 f = vector3Translate(lineA, vector3Invert(circlePos));
	float a = vector3DotProduct(d, d);
	float b = 2* vector3DotProduct(f, d);
	float mc = vector3DotProduct(f, f) - (circleRad*circleRad);
	float discriminant = (b*b) - (4*a*mc);

	int result = 0;

	if (discriminant < 0){
		//no intersection at all
		result |= COLLISION_lcc_Miss;
	}
	else{

		discriminant = sqrt( discriminant );
		float t1 = (-b - discriminant)/(2*a);
		float t2 = (-b + discriminant)/(2*a);

		if( t1 >= 0 && t1 <= 1 )
		{
			//The line enters the circle
			result |= COLLISION_lcc_Enter;
		}

		if( t2 >= 0 && t2 <= 1 )
		{
			//The line leaves the circle
			result |= COLLISION_lcc_Exit;
		}
	}
	return result;
}

//The following three functions simply test the output of the function above for you.
bool collisionLineEntersCircle(vector3 lineA, vector3 lineB, vector3 circlePos, float circleRad){
	return collisionLineCircle(lineA, lineB, circlePos, circleRad) & COLLISION_lcc_Enter;
}

bool collisionLineLeavesCircle(vector3 lineA, vector3 lineB, vector3 circlePos, float circleRad){
	return collisionLineCircle(lineA, lineB, circlePos, circleRad) & COLLISION_lcc_Exit;
}

bool collisionLineMissedCircle(vector3 lineA, vector3 lineB, vector3 circlePos, float circleRad){
	return collisionLineCircle(lineA, lineB, circlePos, circleRad) & COLLISION_lcc_Miss;
}

bool collisionCircles(vector3 c1Pos, float c1Rad, vector3 c2Pos, float c2Rad){
	return (vector3DistanceBetween(c1Pos, c2Pos)) <= (c1Rad + c2Rad);
}

bool collisionMovingCircleStaticCircle(physics_object_t object, float circleRad, vector3 target, float targetSize, float time_delta){

	//if the circles are touching we can return right away
	if (collisionCircles(object.currentPos, circleRad, target, targetSize)){
		return true;
	}

	//otherwise we need to see if they are going to collide in the next step

	physics_object_t object2 = object;
	//get a snapshot of where the circle will go next to see if there is a collision about to happen
	physObjStep(&object2, time_delta);
	return (collisionLineEntersCircle(object.currentPos, object2.currentPos, target, targetSize));
}
