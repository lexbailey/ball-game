/*
 *  Copyright Y1400261 2013 - 2014
 *  See glDrawFuncs.h for function documentation
 *  (University of York C Programming Labs assessment)
 */

#include "glDrawFuncs.h"

//This functions calls the OpenGL function glVertex (variant 3f for three floating point values) to add a vertex to an OpenGL primitive
void drawFuncAddVertex(vector3 v) {
	glVertex3f(v.x, v.y, v.z);
}

//Same as above but for normals
void drawFuncAddNormal(vector3 v) {
	glNormal3f(v.x, v.y, v.z);
}

//The next few functions explain themselves...
void drawFuncLine(vector3 P1, vector3 P2) {
	glBegin(GL_LINES);
		drawFuncAddVertex(P1);
		drawFuncAddVertex(P2);
	glEnd();
}

void drawFuncTriangle(vector3 P1, vector3 P2, vector3 P3) {
	glBegin(GL_TRIANGLES);
		drawFuncAddVertex(P1);
		drawFuncAddVertex(P2);
		drawFuncAddVertex(P2);
	glEnd();
}

void drawFuncRectangle(vector3 TopLeft, vector3 BottomRight, float rotation) {
	//We need to generate a vector3 for each corner
	vector3 TopRight, BottomLeft;
	TopRight.y = TopLeft.y;
	TopRight.x = BottomRight.x;

	BottomLeft.y = BottomRight.y;
	BottomLeft.x = TopLeft.x;

	TopRight.z = TopLeft.z;
	BottomLeft.z = BottomRight.z;

	glRotatef(rotation, 0, 0, 1); //rotate about z

	//draw as two triangles (This is faster than a GL_QUAD on most graphics cards)
	glBegin(GL_TRIANGLE_STRIP);
		drawFuncAddVertex(TopLeft);
		drawFuncAddVertex(TopRight);
		drawFuncAddVertex(BottomLeft);
		drawFuncAddVertex(BottomRight);
	glEnd();
}

//Draw a circle!
//The parameter f decides if the circle is filled
void drawFuncCircleF(vector3 centre, float radius, int resolution, bool filled) {
	float step = 360 / resolution; //number of degrees per step
	GLenum mode;
	if (filled) {
		mode = GL_POLYGON;
	} else {
		mode = GL_LINE_LOOP;
	}
	int i = 0;
	glBegin(mode);
		for (i = 0; i <= resolution - 1; i++) {
			float totalRotation = step * i;
			float sinRot = sin(totalRotation IN_RADIANS) * radius;
			float cosRot = cos(totalRotation IN_RADIANS) * radius;
			glVertex3f(centre.x + sinRot, centre.y + cosRot, centre.z);
		}
	glEnd();
}

//This function draws an empty circle (a ring)
void drawFuncCircle(vector3 centre, float radius, int resolution) {
	drawFuncCircleF(centre, radius, resolution, false);
}

//This functions draws a filled circle (a disc)
void drawFuncDisc(vector3 centre, float radius, int resolution) {
	drawFuncCircleF(centre, radius, resolution, true);
}

//This is a function that draws an arc with a given centre, radius, start angle and stop angle and then sets two output vectors to equal the points at the end of the arc
void drawFuncArcResult(vector3 centre, float radius, int resolution,
		float startAngle, float stopAngle, vector3 *startPos, vector3 *endPos) {

	float arcDegrees = stopAngle - startAngle; //Total rotation of arc (angle at centre)

	float step = arcDegrees / resolution; //number of degrees per step

	//variable for use in the loop
	int i = 0;
	float sinRot, sinRotLast;
	float cosRot, cosRotLast;
	float totalRotation;

	glBegin(GL_LINES);
		for (i = 0; i <= resolution - 1; i++) {
			//Rotate a little each time
			totalRotation = startAngle + (step * i);
			//calculate new coordinates
			sinRot = sin(totalRotation IN_RADIANS) * radius;
			cosRot = cos(totalRotation IN_RADIANS) * radius;

			//if the first vertex has been computed then you can draw the next segment
			//(you need at least two points to draw a line)
			if (i > 0) {
				glVertex3f(centre.x + sinRotLast, centre.y + cosRotLast, centre.z);
				glVertex3f(centre.x + sinRot, centre.y + cosRot, centre.z);
			}

			//remember the last coords
			sinRotLast = sinRot;
			cosRotLast = cosRot;

			//remember the end points...
			if (i <= 0) {
				startPos->x = centre.x + sinRot;
				startPos->y = centre.y + cosRot;
				startPos->z = centre.z;
			}
			if (i >= resolution - 1) {
				endPos->x = centre.x + sinRot;
				endPos->y = centre.y + cosRot;
				endPos->z = centre.z;
			}
		}
	glEnd();
}

//A function for drawing an arc if the caller isn't worried about where it starts and ends
void drawFuncArc(vector3 centre, float radius, int resolution, float startAngle,
		float stopAngle) {

	vector3 a, b;
	drawFuncArcResult(centre, radius, resolution, startAngle, stopAngle,
			&a,	&b);
}

//A functions for translating the OpenGL matrix using a vector
void drawFuncApplyTranslation(vector3 v) {
	glTranslatef(v.x, v.y, v.z);
}
