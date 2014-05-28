/*
 *  Copyright Y1400261 2013 - 2014
 *  See vector3.h for function documentation
 *  (University of York C Programming Labs assessment)
 */

#include "vector3.h"

float vector3GetAxisValue(vector3 *v, axis_t axis){
	//Return the value for the desired axis
	switch (axis){
		case x_axis: return v->x;
		case y_axis: return v->y;
		case z_axis: return v->z;
	}
	return 0;
}

void  vector3SetAxisValue(vector3 *v, axis_t axis, float value){
	//set the value of the specified axis
	switch (axis){
		case x_axis: v->x = value; break;
		case y_axis: v->y = value; break;
		case z_axis: v->z = value; break;
	}
}

vector3 vector3Translate(vector3 input, vector3 translation){
	vector3 result;
	//add each axis individually
	result.x = input.x + translation.x;
	result.y = input.y + translation.y;
	result.z = input.z + translation.z;
	return result;
}

vector3 vector3Invert(vector3 input){
	vector3 result;
	//invert each axis value (like multiplying the vector by -1)
	result.x = -input.x;
	result.y = -input.y;
	result.z = -input.z;
	return result;
}

float vector3DistanceBetween(vector3 a, vector3 b){
	//get the distances for each axis
	float distx = b.x - a.x;
	float disty = b.y - a.y;
	float distz = b.z - a.z;

	//return the square root of the sum of the squares (the length according to Pythagoras' theorem)
	return sqrt((distx * distx) + (disty * disty) + (distz * distz));
}

vector3 vector3ArraySum(vector3 *inputs, int numVectors){
	int i;

	//Initialise an output vector to 0
	vector3 output;
	output.x = 0;
	output.y = 0;
	output.z = 0;

	//loop through all of the vectors
	for (i=0; i<numVectors; i++){
		//add each vector on
		output = vector3Translate(inputs[i], output);
	}

	return output;
}

vector3 vector3ScalarProduct(vector3 input, float factor){
	vector3 result;
	//multiply each axis value by the scale factor
	result.x = input.x * factor;
	result.y = input.y * factor;
	result.z = input.z * factor;
	return result;
}

vector3 vector3VectorProduct(vector3 a, vector3 b){
	vector3 result;
	//Multiply the two together
	result.x = a.x * b.x;
	result.y = a.y * b.y;
	result.z = a.z * b.z;
	return result;
}

float vector3DotProduct(vector3 a, vector3 b){
	return
			(a.x*b.x)+
			(a.y*b.y)+
			(a.z*b.z);
}

vector3 vector3CrossProduct(vector3 u, vector3 v){
	vector3 output;
	output.x = (u.y * v.z) - (u.z * v.y);
	output.y = (u.z * v.x) - (u.x * v.z);
	output.z = (u.x * v.y) - (u.y * v.x);
	return output;
}

float vector3Length(vector3 v){
	vector3 zero;
	zero.x = 0;
	zero.y = 0;
	zero.z = 0;
	//All vectors are relative to 0 and so the length is the distance to 0
	return vector3DistanceBetween(zero, v);
}

float vector3Rotation(vector3 v, axis_t rotationAxis){
	switch (rotationAxis){
	//the rotation is the arc-tangent of two of the sides (which two depends on the rotation axis)
	case x_axis:
		if (v.y<0){
				return (atan(v.y/v.z)) IN_DEGREES;
			}
			else{
				return 180 - (atan(v.y/v.z)) IN_DEGREES;
			}
	case y_axis:
			if (v.z<0){
				return (atan(v.z/v.x)) IN_DEGREES;
			}
			else{
				return 180 - (atan(v.z/v.x)) IN_DEGREES;
			}
	case z_axis:
		if (v.y<0){
			return (atan(v.y/v.x)) IN_DEGREES;
		}
		else{
			return 180 - (atan(v.y/v.x)) IN_DEGREES;
		}

	}
}

vector3 vector3Normalise(vector3 normal){
	//Find the length of the normal
	float normalScale = vector3Length(normal);
	//Divide the vector by this length to get a vector of length 1
	return vector3ScalarProduct(normal, 1.0f/normalScale);
}

vector3 vector3Reflection(vector3 incidence, vector3 normal){
	//Find the dot product of the incidence vector and the normal vector
	float IdotN = vector3DotProduct(incidence, normal);
	//Now return the normal, multiplied by minus two times IdotN, added to the incidence vector
	return	vector3Translate( vector3ScalarProduct(normal, IdotN * -2), incidence);
}

vector3 vector3XYZ(float x, float y, float z){
	vector3 output;
	output.x = x;
	output.y = y;
	output.z = z;
	return output;
}

vector3 vector3GetNull(){
	return vector3XYZ(0.0f,0.0f,0.0f);
}
