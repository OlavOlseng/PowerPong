#include "Game.h"
//we need to get hacky since glut is a c api



Game::Game(int argc,char * argv[]):BaseGame()
{
	//will not return

	//temp: need a system for filepaths
	
	
	binaryPath = argv[0];
	int last = binaryPath.find_last_of("\\");
	binaryPath.erase(last+1,20);
	

	init("Game",1280,720);
}

Game::~Game(void)
{
}


void Game::loadShaders(Pipeline*pipeline){

	


}
#include "Rendering\Voxel\Volume\LargeVolume.h"
#include "Rendering\Voxel\Volume\OctreeVolume.h"
#include "Rendering\Voxel\SurfaceExtractors\CubeSurfaceExtractor.h"
#include "Rendering\Voxel\SurfaceExtractors\CubeSurfaceExtractorWithByteNormals.h"
#include "Rendering\Models\VolumeModel.h"



void Game::setup(){

	
	
	

	Assimp::DefaultLogger::create("",Assimp::Logger::VERBOSE);
	resManager = std::make_shared<ResourceManager>();
	resManager->setWorkingDirectory(binaryPath + "\Assets\\");
	resManager->setShaderDirectory(binaryPath + "\Assets\\Shaders\\");
	resManager->setModelDirectory(binaryPath + "\Assets\\Models\\");

	screenManager = new ScreenManager();
	gameScreen = new GameScreen(resManager,true);
	screenManager->pushScreen(gameScreen);

	
	rootNode = new Node();
	pipeline = new Pipeline();
	loadShaders(pipeline);

	
}
void Game::reshape(int width, int height){
	
	glViewport(0,0,width,height);
	gameScreen->reshape(width,height);
	this->width = width;
	this->height = height;

}
void Game::draw(){ 
	

	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

	screenManager->render();
	


	swapBuffers();
}


void Game::update(double dt){
	
	screenManager->update(dt);
	
	
	//model->setRotation(glm::vec3(0.0,rot,0.0));
	
	
	
	
	
	
	//world-> update(dt);
	
	
}