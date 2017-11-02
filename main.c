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

//Angle of camera direction
float angle = 0.0f;

//vectors representing camera direction
float lx = 0.0f, lz = -1.0f;

float x = 0.0f, z = 5.0f;
float deltaAngle = 0.0f;
float deltaMove = 0;
int xOrigin = -1;

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

	glFlush();
	glutSwapBuffers();


}

//compute position
void computePos(float deltaMove){

	x += deltaMove * lx * 0.1f;
	z += deltaMove * lz * 0.1f;

}

//Special keys callback function
void specialKeys(int key, int x, int y){

	if(key == GLUT_KEY_RIGHT){
		rotate_y += 1.5;	
	}
	else if (key == GLUT_KEY_LEFT){
		rotate_y -= 1.5;
	}
	else if(key == GLUT_KEY_UP){
		rotate_x += 1.5;
	}
	else if(key == GLUT_KEY_DOWN){
		rotate_x -= 1.5;
	}
	else if(key == 27){
		exit(0);
	}

	//Update display
	glutPostRedisplay();

}

//Mouse button function
void mouseButton(int button, int state, int x, int y){
	if(button == GLUT_LEFT_BUTTON){
		if(state == GLUT_UP){
			angle += deltaAngle;
			xOrigin = -1;
		}
		else {
			xOrigin = x;
		}
	}
}

//Mouse move function
void mouseMove(int x, int y){
	if(xOrigin >= 0){
		deltaAngle = (x - xOrigin) * 0.001f;

		lx = sin(angle + deltaAngle);
		lz = -cos(angle + deltaAngle);
	}
}


int main(int argc, char *argv[]){
	
	//Init GLUT and create new window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("James Window Test");
	glEnable(GL_DEPTH_TEST);
	//Register callbacks
	glutDisplayFunc(display);
	glutSpecialFunc(specialKeys);
	glutIdleFunc(display);

	glutIgnoreKeyRepeat(1);
	//mouse functions
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);
	//Enter GLUT event processing cycle
	glutMainLoop();


	return EXIT_SUCCESS;
}
