/*
 * test.c
 *
 * Copyright 2016 Steven Webb <bigwebb@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */

#include <stdio.h>
#include <string.h>
//#include <math.h>
#include <GL/glu.h>
//#include <GL/glut.h>
#include <GLFW/glfw3.h>

static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
	static int last_len=0;
	int a;
	char str[80];
	for (a=0;a<last_len;a++) {
		printf("%c",8);
	}
	sprintf(str,"M: %d, %d    ",(int) xpos, (int) ypos);
	fputs(str,stdout);
	fflush(stdout);
	last_len = strlen(str);
}

void resize_callback(GLFWwindow* window, int width, int height) {
	GLfloat h = (GLfloat) height / (GLfloat) width;
//	GLfloat w = (GLfloat) width / (GLfloat) height;
	GLfloat xmax, znear, zfar;

	znear = 1.0f;
	zfar  = 30.0f;
	xmax  = znear * 0.5f;

	glViewport( 0, 0, (GLint) width, (GLint) height );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
//	gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -100.0, 0.0, 1.0, 0.0);
//	gluPerspective(60.0, w, 1.0, 200.0);
	glFrustum( -xmax, xmax, -xmax*h, xmax*h, znear, zfar );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glTranslatef(0.0,0.0,-5.0);
}

int main(void)
{
	float rotx = 0.0;
	float step = 0.2;
	int width, height;
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	printf("Compiled against GLFW %i.%i.%i\n",
		GLFW_VERSION_MAJOR,
		GLFW_VERSION_MINOR,
		GLFW_VERSION_REVISION);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "test", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwSetWindowSizeCallback(window, resize_callback);
	glfwSetCursorPosCallback(window, cursor_pos_callback);
	glfwSwapInterval( 1 );
	glfwMakeContextCurrent(window);
	glfwGetFramebufferSize(window, &width, &height);
	resize_callback(window,width,height);

	static GLfloat pos[4] = {5.f, 5.f, 10.f, 0.f};
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_DEPTH_TEST);
	glMatrixMode( GL_MODELVIEW );

	static GLfloat red[4] = {0.8f, 0.1f, 0.f, 1.f};
	static GLfloat green[4] = {0.f, 0.8f, 0.2f, 1.f};
	static GLfloat blue[4] = {0.2f, 0.2f, 1.f, 1.f};

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)) {
		/* Render here */
		glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		glPushMatrix();
		glLoadIdentity();
		glTranslatef(0.0,0.0,-5.0);
		glRotatef(rotx, 1.0, 0.5, 0.8 );
		rotx += step;

		glBegin(GL_QUADS);
		// top
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-0.5f, 0.5f, 0.5f);
		glVertex3f(0.5f, 0.5f, 0.5f);
		glVertex3f(0.5f, 0.5f, -0.5f);
		glVertex3f(-0.5f, 0.5f, -0.5f);
		glEnd();

		glBegin(GL_QUADS);
		// front
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.5f, -0.5f, 0.5f);
		glVertex3f(0.5f, 0.5f, 0.5f);
		glVertex3f(-0.5f, 0.5f, 0.5f);
		glVertex3f(-0.5f, -0.5f, 0.5f);
		glEnd();

		glBegin(GL_QUADS);
		// right
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.5f, 0.5f, -0.5f);
		glVertex3f(0.5f, 0.5f, 0.5f);
		glVertex3f(0.5f, -0.5f, 0.5f);
		glVertex3f(0.5f, -0.5f, -0.5f);
		glEnd();

		glBegin(GL_QUADS);
		// left
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(-0.5f, -0.5f, 0.5f);
		glVertex3f(-0.5f, 0.5f, 0.5f);
		glVertex3f(-0.5f, 0.5f, -0.5f);
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glEnd();

		glBegin(GL_QUADS);
		// bottom
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(0.5f, -0.5f, 0.5f);
		glVertex3f(-0.5f, -0.5f, 0.5f);
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glVertex3f(0.5f, -0.5f, -0.5f);
		glEnd();

		glBegin(GL_QUADS);
		// back
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(0.5f, 0.5f, -0.5f);
		glVertex3f(0.5f, -0.5f, -0.5f);
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glVertex3f(-0.5f, 0.5f, -0.5f);
		glEnd();
		glPopMatrix();

		glFlush();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
