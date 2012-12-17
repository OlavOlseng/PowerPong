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
#include "Rendering\WallMeshGenerator.h"
void Game::setup(){
	//setting up physics
	this-> world = new World();
	
	//init stuff here
	cam = new Camera(2.0,20.0,-10,0,0,5,1280,720);
	walls = new std::vector<gWall*>();
	
	gWall *wall = new gWall(1,5,glm::vec3(0,0,5));
	walls->push_back(wall);
	wall->setBlock(0,1,glm::vec3(1.0,0.0,0.0));
	
	wall->setBlock(3,1,glm::vec3(0.0,1.0,0.0));

	
	gWall *wall2 = new gWall(1,10,glm::vec3(0,0,3));
	walls->push_back(wall2);
	wall2->setBlock(0,1,glm::vec3(1.0,0.0,0.0));
	wall2->setBlock(1,2,glm::vec3(0,0.0,1.0));
	wall2->setBlock(3,1,glm::vec3(0.0,1.0,0.0));
	wall2->setBlock(5,1,glm::vec3(0.0,1.0,0.0));
	
	WallMeshGenerator generator = WallMeshGenerator();
	
	renderer = new WallRenderer(walls,cam);
	
	Model*model = new Model();
	Model*model2 = new Model();
	Model* model3 = new Model();
	model2->setPosition(glm::vec3(0,0,5));

	model3->setPosition(glm::vec3(0,1,20));
	models = new std::vector<Model*>();
	
	models->push_back(model);
	models->push_back(model2);
	models->push_back(model3);

	GLTriangleBatch*batch = new GLTriangleBatch(model->getVertexBuffer(),model->getNormalBuffer(),model->getTexcoordBuffer(),model->getElementBuffer());
	gltMakeSphere(*batch,5,25,13);

	GLTriangleBatch*batch2 = new GLTriangleBatch(model2->getVertexBuffer(),model2->getNormalBuffer(),model2->getTexcoordBuffer(),model2->getElementBuffer());
	gltMakeSphere(*batch2,5,25,13);

	
	GLTriangleBatch*batch3 = new GLTriangleBatch(model3->getVertexBuffer(),model3->getNormalBuffer(),model3->getTexcoordBuffer(),model3->getElementBuffer());
	gltMakeDisk(*batch3,5,10,25,13);

	geomRenderer = new GeometryRenderer(cam,models);

	generator.generateMeshFor(wall);
	generator.generateMeshFor(wall2);

	

}
void Game::reshape(int width, int height){
	
	glViewport(0,0,width,height);
	
	this->width = width;
	this->height = height;

}
void Game::draw(){
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glClearColor(0.4,0.4,0.4,1.0);
	renderer->render();
	geomRenderer->render();
	
	swapBuffers();
}


void Game::update(double dt){
	cam->tick();
	world-> update(dt);
	postRedisplay();
	
}