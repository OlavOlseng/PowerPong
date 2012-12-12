// PowerPong.cpp : Defines the entry point for the console application.
//

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <glm\glm.hpp>

void display(){
	glm::vec3 vec(1,1,1);
	printf("%f",vec.x);
	glClearColor(1.0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();


}
int main(int argc, char* argv[])
{
	glutInit( &argc, argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);
	glutInitWindowSize(600,400),
	glutCreateWindow("test");
	glutDisplayFunc(display);

	glutMainLoop();

	std::cout << "VAGINA!" << std::endl;
	system("PAUSE");
	return 0;
}

