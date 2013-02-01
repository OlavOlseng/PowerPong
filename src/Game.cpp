#include "Game.h"




Game::Game(int argc,char * argv[]):BaseGame()
{
	//will not return

	//temp: need a system for filepaths
	
	
	binaryPath = argv[0];
	int last = binaryPath.find_last_of("\\");
	binaryPath.erase(last,last + 50);
	

	init("Game",1280,720);
}

Game::~Game(void)
{
}



#include "Rendering\Voxel\Volume\LargeVolume.h"
#include "Rendering\Voxel\Volume\OctreeVolume.h"
#include "Rendering\Voxel\SurfaceExtractors\CubeSurfaceExtractor.h"
#include "Rendering\Voxel\SurfaceExtractors\CubeSurfaceExtractorWithByteNormals.h"
#include "Rendering\Models\VolumeModel.h"



void Game::setup(){
	
	
	resManager = std::make_shared<ResourceManager>();
	resManager->setWorkingDirectory(binaryPath + "\\Assets\\");
	resManager->setShaderDirectory(binaryPath + "\\Assets\\Shaders\\");
	resManager->setModelDirectory(binaryPath + "\\Assets\\Models\\");
	
	screenManager = new ScreenManager();
	gameScreen = new GameScreen(resManager,true);
	screenManager->pushScreen(gameScreen);

	


	
}
void Game::reshape(int width, int height){
	if(gameScreen){
	glViewport(0,0,width,height);
	gameScreen->reshape(width,height);
	this->width = width;
	this->height = height;
	}

}
void Game::draw(){ 
	

	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

	screenManager->render();
	


	swapBuffers();
}


void Game::update(double dt){
	
	screenManager->update(dt);
	

	
	
}