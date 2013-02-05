#include "GameScreen.h"




GameScreen::GameScreen(std::shared_ptr<ResourceManager> resourceManager,bool enableTest)
{
	
	this -> renderBlock = 1;
	this -> updateBlock = 1;

	this->resourceManager = resourceManager;
	rootNode = new Node();
	this -> world = new World();
	cam = new FreeMovementCamera(0,5.0,20.0,1280,720);
	cam->rotateRight(6.28);
	cam->setPosition(100,40,00);
	
	

	if (enableTest)
	{
		test();
	}
	
}


#include <glm\gtx\noise.hpp>
#include "../Rendering/Voxel/Volume/LargeVolume.h"
#include "../Rendering/Voxel/Volume/ArrayVolume.h"
#include "../Rendering/Voxel/SurfaceExtractors/ChunkExtractor.h"
void GameScreen::test()
{
	
	
	
	const aiScene * sphereScene = resourceManager->loadModel("sphere.irr");

	
	
	PointLight * light = new PointLight();
	light->diffuse = glm::vec4(1.0,1.0,1.0,1.0);
	light->specular = glm::vec4(1.0,1.0,1.0,1.0);
	light->setRange(5000);
	light->position = glm::vec4(0,50.0,0.0,1.0);
	rootNode->addLight(light);
	pipeline = new Pipeline(10,10);

	
	crossHair = new LineModel();
	crossHair->addLine(glm::vec3(-20,0,0),glm::vec3(20,0,0),glm::vec3(0,0,0));
	crossHair->addLine(glm::vec3(0,20,0),glm::vec3(0,20,0),glm::vec3(0,0,0));
	crossHair->bufferLines();
	crossHair->clearLines();




	
}



void GameScreen::reshape(int width, int height){
	if(cam)
	cam->setProjection(width,height);

}

void GameScreen::render()
{

	

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glClearColor(0.4,0.4,0.4,1.0);
	
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);

	pipeline->clear();
	pipeline->setShadowPass(false);
	pipeline->setView(cam->getViewMatrix());
	pipeline->setCameraPosition(glm::vec4(cam->getPosition(),1.0));
	pipeline->setProjection(cam->getProjectionMatrix());
	pipeline->setViewDirection(glm::vec4(cam->getViewDirection(),1.0));
	//world->debugDrawWorld();

	rootNode->render(pipeline);
	pipeline->clear();
	pipeline->setProjection(glm::ortho(0.0f,1280.0f,0.0f,720.0f));
	pipeline->setView(glm::mat4(1.0));
	glDisable(GL_DEPTH_TEST);
	crossHair->render(pipeline);
	
	

	

}

void GameScreen::update(double dt)
{
	

	
	//rootNode->rotate(glm::quat(glm::vec3(0,1*dt,0)));
	inputHandler.update();

	
	
}

GameScreen::~GameScreen(void)
{
	delete world;
	delete pipeline;
}
