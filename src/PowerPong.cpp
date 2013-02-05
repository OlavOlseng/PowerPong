// PowerPong.cpp : Defines the entry point for the console application.
//



#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <GL\glew.h>
#include <glm\glm.hpp>
#include "Game.h"




int main(int argc, char* argv[])
{


	Game * game = new Game(argc,argv);
	
	return 0;
}

