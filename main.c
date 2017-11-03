#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <string.h>
#include <math.h>

#define GLUT_WHEEL_UP 3
#define GLUT_WHEEL_DOWN 4

//Prototypes
void display();
void specialKeys();
void computePos(float deltaMove);


//Globals
double rotate_y = 0.0;
double rotate_x = 0.0;

//flat or textured, wireframe or filled
int flat = 0;
int filled = 0;
int light = 0;
int cube = 0;

//Camera
float zoom, rotX, rotY, tx, ty;
float cameraX = 0.0f, cameraY = 0.0f, cameraZ = 0.0f;

//Angle of camera direction
float angle = 0.0f;

//vectors representing camera direction
float lx = 0.0f, lz = -1.0f;

float x = 0.0f, z = 5.0f;
float deltaAngle = 0.0f;
float deltaMove = 0;
int xOrigin = -1;

char* windowName = "James 3D Test";

GLuint model;
char ch = '1';

//load model
void loadModel(char * filename){
	
	FILE *fp;
	int read;
	GLfloat x, y, z;
	char ch;
	model = glGenLists(1);
	fp = fopen(filename, "r");
	
	if(fp == NULL){
		printf("Error: Cannot open model file! Exiting...\n");
		exit(EXIT_FAILURE);
	}
	
	glPointSize(2.0);
	
	glNewList(model, GL_COMPILE);

	{
		glPushMatrix();
		glBegin(GL_POINTS);
		
		while(!feof(fp)){
			read = fscanf(fp, "%c %f %f %f", &ch, &x, &y, &z);
			if(read == 4 && ch == 'v'){
				glVertex3f(x, y, z);
			}
			

		}

		glEnd();
	}

	glPopMatrix();
	glEndList();
	fclose(fp);
	

}

//Draw model function
void drawModel(){
	
	glPushMatrix();
	glCallList(model);
	glTranslatef(0.0f, -40.0f, -150.0f);
	glScalef(0.1f, 0.1f, 0.1f);
	glPopMatrix();

	if(flat == 1){
		glShadeModel(GL_FLAT);
	}
	else {
		glShadeModel(GL_SMOOTH);
	}

	if(filled == 0){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	if(light == 1){
		//enable lighting
		glClearDepth(1);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		//set position of light
		GLfloat lightpos[] = {0.5, 1.0, 1.0, 0.0};
		glLightfv(GL_LIGHT0, GL_POSITION, lightpos); 
	}
	else {
		//disable lighting
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		//drawLines();
		
	}

	glutPostRedisplay();
}


//Draw cube function
void drawCube(){

	//Front
	glBegin(GL_POLYGON);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);

	//back
	glBegin(GL_POLYGON);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glEnd();

	//right
	glBegin(GL_POLYGON);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glEnd();

	//left
	glBegin(GL_POLYGON);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();

	//top
	glBegin(GL_POLYGON);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glEnd();

	//bottom
	glBegin(GL_POLYGON);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();


	if(flat == 1){
		glShadeModel(GL_FLAT);
	}
	else {
		glShadeModel(GL_SMOOTH);
	}

	if(filled == 0){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	if(light == 1){
		//enable lighting
		glClearDepth(1);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		//set position of light
		GLfloat lightpos[] = {0.5, 1.0, 1.0, 0.0};
		glLightfv(GL_LIGHT0, GL_POSITION, lightpos); 
	}
	else {
		//disable lighting
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		//drawLines();
		
	}

	glutPostRedisplay();

}

void drawTeapot(){

	//setup
	//glTranslatef(0,0,-1.0);
	//glRotatef(cameraX, 0, 1, 0);
	//glRotatef(cameraY, 1, 0, 0);

	if(flat == 1){
		glShadeModel(GL_FLAT);
	}
	else {
		glShadeModel(GL_SMOOTH);
	}
	
	if(filled == 0){
		glutWireTeapot(0.5);
	}
	else {
		glutSolidTeapot(0.5);
	}

	if(light == 1){
		//enable lighting
		glClearDepth(1);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		//set position of light
		GLfloat lightpos[] = {0.5, 1.0, 1.0, 0.0};
		glLightfv(GL_LIGHT0, GL_POSITION, lightpos); 
	}
	else {
		//disable lighting
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		//drawLines();
		
	}



	glutPostRedisplay();

}

//Display callback function
void display(){

	if(deltaMove){
		computePos(deltaMove);	
	}

	//Clear buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Reset transformations
	glLoadIdentity();

	//rotate when user changes rotate_x and rotate_y
	glRotatef(rotate_x, 1.0, 0.0, 0.0);
	glRotatef(rotate_y, 0.0, 1.0, 0.0);

	//Draw stuff here
	//if(cube == 0){
	//	drawTeapot();
	//}
	//else {
	//	drawCube();
	//}
	drawModel();
	

	//Clean up
	glFlush();
	glutSwapBuffers();

}

//compute position
void computePos(float deltaMove){

	x += deltaMove * lx * 0.1f;
	z += deltaMove * lz * 0.1f;

}

//Special key escape function
void processNormalKeys(unsigned char key, int x, int y){
	
	if(key == 27){
		exit(EXIT_SUCCESS);
	}
	else if(key == 'c'){
		if(cube == 0){
			cube = 1;
			printf("Cube turned on.\n");
		}
		else{
			cube = 0;
			printf("Teapot turned on.\n");
		}
	}
	else if(key == 'p'){
		if(filled == 0){
			filled = 1;
			printf("Fill turned on.\n");		
		}
		else {
			filled = 0;
			printf("Fill turned off.\n");	
		}
	}
	else if(key == 'm'){
		if(flat == 0){
			flat = 1;
			printf("Smooth turned off.\n");
		}
		else {
			flat = 0;
			printf("Smooth turned on.\n");		
		}
	}
	else if(key == 'l'){
		if(light == 0){
			light = 1;
			printf("Lighting turned on.\n");		
		}
		else {
			light = 0;
			printf("Lighting turned off.\n");
		}
	}
}

//Special keys callback function
void specialKeys(int key, int x, int y){

	if(key == GLUT_KEY_RIGHT){
		rotate_y += 5;	
	}
	else if (key == GLUT_KEY_LEFT){
		rotate_y -= 5;
	}
	else if(key == GLUT_KEY_UP){
		rotate_x += 5;
	}
	else if(key == GLUT_KEY_DOWN){
		rotate_x -= 5;
	}
	

	//Update display
	glutPostRedisplay();

}

//Mouse button function
void mouseButton(int button, int state, int x, int y){
	if(button == GLUT_LEFT_BUTTON){
		printf("Left mouse button clicked.\n");
		
	}
	else if(button == GLUT_WHEEL_UP){
		printf("Mouse wheel up\n");	
	}
	else if(button == GLUT_WHEEL_DOWN){
		printf("Mouse wheel down\n");
	}
	
}

//Mouse move function
void mouseMove(int x, int y){
	rotate_x = x;
	rotate_y = y;

	printf("rotX: %i, rotY: %i\n", x,y);

	glutPostRedisplay();
}


int main(int argc, char *argv[]){
	
	//Init GLUT and create new window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow(windowName);
	glEnable(GL_DEPTH_TEST);
	//Register callbacks
	glutDisplayFunc(display);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(specialKeys);
	glutIdleFunc(display);

	glMatrixMode(GL_MODELVIEW);

	//This function is if we want to stop movement when key held down
	//glutIgnoreKeyRepeat(1);

	//mouse functions
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);
	
	//Load model
	loadModel("/home/james/Desktop/3D/model.obj");

	//Enter GLUT event processing cycle
	glutMainLoop();


	return EXIT_SUCCESS;
}
