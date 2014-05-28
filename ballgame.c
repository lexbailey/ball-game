#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/freeglut.h>
#include "fizz/fizz.h"

#define NUM_OBSTACLES 52

float obstaclesPos[]={

-4.7f, -4.7f, 0.0f,
-4.0f, -5.0f, 0.0f,
-3.3f, -4.7f, 0.0f,
-2.0f, -5.0f, 0.0f,
-1.3f, -4.7f, 0.0f,
-0.0f, -5.0f, 0.0f,
1.3f, -4.7f, 0.0f,
2.0f, -5.0f, 0.0f,
3.3f, -4.7f, 0.0f,
4.0f, -5.0f, 0.0f,
4.7f, -4.7f, 0.0f,
-5.0f, -4.0f, 0.0f,
-3.0f, -4.0f, 0.0f,
-1.0f, -4.0f, 0.0f,
1.0f, -4.0f, 0.0f,
3.0f, -4.0f, 0.0f,
5.0f, -4.0f, 0.0f,
2.7f, -4.7f, 0.0f,
-0.7f, -4.7f, 0.0f,
0.7f, -4.7f, 0.0f,
-2.7f, -4.7f, 0.0f,

-4.0f, -2.0f, 0.0f,
-2.0f, -2.0f, 0.0f,
0.0f, -2.0f, 0.0f,
2.0f, -2.0f, 0.0f,
4.0f, -2.0f, 0.0f,

-5.0f, -1.0f, 0.0f,
-3.0f, -1.0f, 0.0f,
-1.0f, -1.0f, 0.0f,
1.0f, -1.0f, 0.0f,
3.0f, -1.0f, 0.0f,
5.0f, -1.0f, 0.0f,


//-4.0f, 0.0f, 0.0f,
-2.0f, 0.0f, 0.0f,
0.0f, 0.0f, 0.0f,
2.0f, 0.0f, 0.0f,
//4.0f, 0.0f, 0.0f,

-5.0f, 1.0f, 0.0f,
-3.0f, 1.0f, 0.0f,
-1.0f, 1.0f, 0.0f,
1.0f, 1.0f, 0.0f,
3.0f, 1.0f, 0.0f,
5.0f, 1.0f, 0.0f,

-4.0f, 2.0f, 0.0f,
-2.0f, 2.0f, 0.0f,
0.0f, 2.0f, 0.0f,
2.0f, 2.0f, 0.0f,
4.0f, 2.0f, 0.0f,

-5.0f, 3.0f, 0.0f,
-3.0f, 3.0f, 0.0f,
-1.0f, 3.0f, 0.0f,
1.0f, 3.0f, 0.0f,
3.0f, 3.0f, 0.0f,
5.0f, 3.0f, 0.0f,
};

int mousex, mousey;

physics_world_t world;
physics_object_t *pPinball;
physics_object_t *pObstacles[NUM_OBSTACLES];

bool click = false;

//this function adapted from: http://nehe.gamedev.net/article/using_gluunproject/16013/
vector3 glWindowGetOGLPos(int x, int y)
{
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZ;
 
	//Get a copy of the modelview and projection matricies and the viewport info
	glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
	glGetDoublev( GL_PROJECTION_MATRIX, projection );
	glGetIntegerv( GL_VIEWPORT, viewport );
 
	winX = (float)x;
	winY = (float)(viewport[3] - y); //subtract Y from viewport height (flip y coordinate)

	//read the depth of the pixel under the mouse cursor to get a z value
	glReadPixels( x, (int)(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );

	//Un-project the x, y and z coordinates from the screen to the model to get the OpenGL mouse position
	gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

	//All done, return the position as a vector
	vector3 output;
	output.x = (float)posX;
	output.y = (float)posY;
	output.z = (float)posZ;

	return output;
}

void reshape (int width, int height) {
/*
	glViewport(0, 0, (GLsizei)width, (GLsizei)height); // Set our viewport to the size of our window
	glMatrixMode(GL_PROJECTION); // Switch to the projection matrix so that we can manipulate how our scene is viewed
	glLoadIdentity(); // Reset the projection matrix to the identity matrix so that we don't get any artifacts (cleaning up)
	gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 1000.0); // Set the Field of view angle (in degrees), the aspect ratio of our window, and the near and far planes
	glMatrixMode(GL_MODELVIEW); // Switch back to the model view matrix, so that we can start drawing shapes correctly
*/
	//This simple resize method will not maintain aspect ration :-( this can be fixed, perhaps later...
	glViewport(0, 0, (GLsizei)width, (GLsizei)height); // Set our viewport to the size of our window
	glMatrixMode(GL_PROJECTION); 			//Switch to the projection matrix so that we can manipulate how our scene is viewed
	glLoadIdentity(); 						//Reset the projection matrix
	glOrtho(-8, 8, -6, 6, 0.1f, 1000.0f);	//Tell OpenGL how we want the coordinates set up (Orthographic mode, not projection)
	glMatrixMode(GL_MODELVIEW); 			//Switch back to the model view matrix, so that we can start drawing shapes correctly
}

//http://stackoverflow.com/questions/1952290/how-can-i-get-utctime-in-milisecond-since-january-1-1970-in-c-language
long int getTimeMilliSeconds(){
	struct timeval tp;
	gettimeofday(&tp, NULL);
	return (tp.tv_sec *1000) + (tp.tv_usec / 1000);
}

long int lastDraw;

void render (){

	//draw stuff here
	float time_delta;
	long int thisDraw = getTimeMilliSeconds();
	time_delta = ((thisDraw - lastDraw)) /1000.0f;

	time_delta /= 1;

	lastDraw = thisDraw;

	physWorldStep(&world, time_delta);
	if (fabs(pPinball->currentPos.x)>=5.0f){
		pPinball->velocity = vector3ScalarProduct(vector3Reflection(vector3Translate(pPinball->velocity, vector3XYZ(0,0,0)), vector3XYZ(1,0,0)), 0.95f);
	}

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glLoadIdentity();	


	glColor3f(0.8f,0.6f,0.5f);
	glTranslatef(0.0f,0.0f,-10.0f);

	vector3 mouse = glWindowGetOGLPos(mousex, mousey);

	float ballX = mouse.x;
	if (ballX >5.0f){ballX = 5.0f;}
	if (ballX <-5.0f){ballX = -5.0f;}

	pPinball->enabled = !click;

	if (click){
		physObjReset(pPinball, vector3XYZ(ballX, 5.0f, 0.0f));
	}

	glBegin(GL_QUADS);
		glVertex3f(-10.0f, -5.0f, 0.0f);
		glVertex3f(-10.0f, 5.0f, 0.0f);
		glVertex3f(10.0f, 5.0f, 0.0f);
		glVertex3f(10.0f, -5.0f, 0.0f);
	glEnd();
	int i;
	for (i = 0; i<NUM_OBSTACLES; i++){
		glColor3f(1.0f,0.0f,0.0f);
		drawFuncDisc(pObstacles[i]->currentPos, 0.2f, 20);
	}

	vector3 zero = vector3XYZ(0,0,0);
	//drawFuncLine(zero, mouse);

	glColor3f(0.0f,1.0f,0.0f);
	drawFuncDisc(pPinball->currentPos, 0.3f, 20);
	//physObjDrawForces(pPinball);

	glutSwapBuffers();
}

void mouse(int button, int state, int x, int y){
	click = ((button == 0)&&(state==0));
}

void motion(int x, int y){
	mousex = x;
	mousey = y;
}

void initPinball(){
	vector3 pos;
	pos.z = 0.0f;
	pos.y = 5.0f;
	pos.x = 4.2f;
	physics_object_t pinball;
	physObjInitialise(&pinball, pos, 0, 0);
	pinball.isStatic = false;
	pinball.isGhost = false;
	pinball.enabled = true;
	pinball.mass = 0.6f;
	pinball.relativeCOR = 0.95f;
	pinball.collisionBounds = pcb_Circle;
	pinball.collisionRadius = 0.3f;
	pPinball = physWorldAddObject(&world, pinball);
}

void initObstacles(){
	int i;
	physics_object_t obstacles[NUM_OBSTACLES];
	for (i = 0; i<NUM_OBSTACLES; i++){
		vector3 pos;
		pos.x = obstaclesPos[i*3];
		pos.y = obstaclesPos[(i*3)+1];
		pos.z = obstaclesPos[(i*3)+2];
		physObjInitialise(&obstacles[i], pos, 0, 0);
		obstacles[i].isStatic = true;
		obstacles[i].isGhost = false;
		obstacles[i].enabled = true;
		obstacles[i].mass = 0.1f;
		obstacles[i].relativeCOR = 0.95f;
		obstacles[i].collisionBounds = pcb_Circle;
		obstacles[i].collisionRadius = 0.2f;
		pObstacles[i] = physWorldAddObject(&world, obstacles[i]);
	}
}

void initPhysics(){
	vector3 gravity;
	gravity.x=0.0f;
	gravity.y=-9.8f;
	gravity.z=0.0f;
	physWorldInitialise(&world, gravity, NUM_OBSTACLES +1);
	initPinball();
	initObstacles();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv); // Initialize GLUT
	glutInitDisplayMode (GLUT_DOUBLE); // Set up a double display buffer
	glutInitWindowSize (700, 500); // Set the width and height of the window
	glutInitWindowPosition (100, 100); // Set the position of the window
	glutCreateWindow ("Ball Game"); // Set the title for the window
	glutDisplayFunc(render);
	glutIdleFunc(render);
	glutReshapeFunc(reshape);
	glutMotionFunc(motion);
	glutPassiveMotionFunc(motion);

	glutMouseFunc(mouse);

	glMatrixMode(GL_MODELVIEW);
	glClearColor(0.0f,0.0f,0.0f,1.0f);

	initPhysics();
	lastDraw = getTimeMilliSeconds();

	glutMainLoop();
	return 0;
}

