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
#include <math.h>
#include <GLFW/glfw3.h>

static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
	static int last_len=0;
	int a;
	char str[80];
	for (a=0;a<last_len;a++) {
		printf("%c",8);
	}
	sprintf(str,"M: %d, %d    ",(int) floor(xpos), (int) floor(ypos));
	fputs(str,stdout);
	fflush(stdout);
	last_len = strlen(str);
}

int main(void)
{
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

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSetCursorPosCallback(window, cursor_pos_callback);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)) {
		/* Render here */
		glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
		glClear( GL_COLOR_BUFFER_BIT);
		glGetError();
		glLoadIdentity();

		glBegin(GL_TRIANGLES); {
			glColor3f(1.0f, 1.0f, 1.0f);
			glVertex2f(0.0f, 1.0f);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex2f(-1.0f, -1.0f);
			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex2f(1.0f, -1.0f);
		}
		glEnd();
		glFlush();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
