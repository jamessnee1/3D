#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

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

//Draw cube function
void drawCube(){

	//Multicoloured side - Front
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);	glVertex3f(0.5, -0.5, -0.5);
	glColor3f(0.0, 1.0, 0.0);	glVertex3f(0.5, 0.5, -0.5);
	glColor3f(0.0, 0.0, 1.0);	glVertex3f(-0.5, 0.5, -0.5);
	glColor3f(1.0, 0.0, 1.0);	glVertex3f(-0.5, -0.5, -0.5);

	//white side - back
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glEnd();

	//purple side - right
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 1.0);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glEnd();

	//green side - left
	glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();

	//blue side - top
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glEnd();

	//red side - bottom
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();



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
	drawTeapot();
	//drawCube();

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
			printf("Flat turned on.\n");
		}
		else {
			flat = 0;
			printf("Flat turned off.\n");		
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

	//This function is if we want to stop movement when key held down
	//glutIgnoreKeyRepeat(1);

	//mouse functions
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);
	//Enter GLUT event processing cycle
	glutMainLoop();


	return EXIT_SUCCESS;
}
