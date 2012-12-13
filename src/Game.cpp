#include "Game.h"
//we need to get hacky since glut is a c api
static char*t = new char[];
BaseGame * BaseGame::instance = new Game();

Game::Game(){
}
Game::Game(int argc,char * argv[]):BaseGame()
{
	//will not return
	init("Game",1280,720);
}

Game::~Game(void)
{
}

void Game::setup(){
	//init stuff here
	printf("setup");







}
void Game::reshape(int width, int height){

	glViewport(0,0,width,height);
	this->width = width;
	this->height = height;

}
void Game::draw(){
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0,0.0,0.0,1.0);

	
	swapBuffers();
}


void Game::update(double dt){
	
	
	postRedisplay();
	
}