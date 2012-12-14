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
	cam = new Camera(0,2,0,5,5,5,1280,720);
	walls = new std::vector<Wall*>();
	Wall *wall = new Wall(1,5,5,glm::vec3(3,0,3));
	renderer = new WallRenderer(walls,cam);





}
void Game::reshape(int width, int height){

	glViewport(0,0,width,height);
	this->width = width;
	this->height = height;

}
void Game::draw(){

	renderer->render();
	
	swapBuffers();
}


void Game::update(double dt){
	
	
	postRedisplay();
	
}