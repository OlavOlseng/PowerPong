#include "GameScreen.h"




GameScreen::GameScreen(std::shared_ptr<ResourceManager> resourceManager,bool enableTest)
{
	
	this -> renderBlock = 1;
	this -> updateBlock = 1;

	this->resourceManager = resourceManager;
	rootNode = new Node();
	this -> world = new World();
	cam = new FreeMovementCamera(0,5.0,50.0,1280,728,glm::quat(),0.1,300);
	cam->rotateRight(6.28);
	//cam->setPosition(100,40,00);
	

	
	
	KeyMap<KeyMovementBehaviour::Key,Direction> map ;
	map.setKey('A',KeyMovementBehaviour::Key::LEFT,Direction(-1,0.0,0.0));
	map.setKey('D',KeyMovementBehaviour::Key::RIGHT,Direction(1,0.0,0.0));
	map.setKey('W',KeyMovementBehaviour::Key::FORWARD,Direction(0.0,0.0,-1.0));
	map.setKey('S',KeyMovementBehaviour::Key::BACKWARDS,Direction(0.0,0.0,1.0));
	map.setKey('Q',KeyMovementBehaviour::Key::UP,Direction(0.0,1.0,0.0));
	map.setKey('E',KeyMovementBehaviour::Key::DOWN,Direction(0.0,-1.0,0.0));
	
	KeyMovementBehaviour * behaviour = new KeyMovementBehaviour(map);
	behaviour->setSpeed(20);

	MouseFPSBehaviour * mouseB= new MouseFPSBehaviour(true);
	mouseB->setSpeed(1.0,1.0);
	mouseB->setInverted(false);
	cameraController = new UnconstrainedCameraController(cam);

	cameraController->addBehaviour(behaviour);
	cameraController->addBehaviour(mouseB);

	


	if (enableTest)
	{
		test();
	}
	
}


#include <glm\gtx\noise.hpp>
#include "../Rendering/Voxel/Volume/LargeVolume.h"
#include "../Rendering/Voxel/Volume/ArrayVolume.h"
#include "../Rendering/Voxel/SurfaceExtractors/ChunkExtractor.h"
#include <string>
#include "../Rendering/Util/FrameBuffer.h"

void GameScreen::test()
{
	


	
	const aiScene * sphereScene = resourceManager->loadModel("sphere.irr");


	PointLight * light = new PointLight();
	light->diffuse = glm::vec4(1.0,1.0,1.0,1.0);
	light->specular = glm::vec4(1.0,1.0,1.0,1.0);
	light->setRange(5000);
	light->position = glm::vec4(50.0,50.0,50,1.0);
	rootNode->addLight(light);
	pipeline = new Pipeline(10,10);

	
	/*crossHair = new LineModel();
	crossHair->setResourceManager(resourceManager);
	crossHair->addLine(glm::vec3(-20,0,0),glm::vec3(20,0,0),glm::vec3(0,0,0));
	crossHair->addLine(glm::vec3(0,20,0),glm::vec3(0,20,0),glm::vec3(0,0,0));
	crossHair->bufferLines();
	crossHair->clearLines();*/





	


	TileAtlas * atlas = new TileAtlas("tileAtlas.png",4,1,resourceManager);
	Volume * floorVolume = new OctreeVolume(32);
	for(int x = 0;x <32 ;x++)
		for(int z = 0;z<32;z++)
			floorVolume->set(x,0,z,2);
	
	TileAtlas * frameBufferAtlas = new TileAtlas("tileAtlas.png",1,1,resourceManager);
	VolumeModel * floorModel = new VolumeModel(1,1,1,32,1,32);
	floorModel->setResourceManager(resourceManager);
	floorModel->init(atlas);
	floorModel->setSurface(0,0,0,CubeSurfaceExtractorWithByteNormals(floorVolume).extractSurface(0,0,0,32,32,32));
	floorModel->setScale(glm::vec3(100,1,100));
	floorNode = floorModel;
	rootNode->addChild(floorModel);

	
	Volume * volume = new OctreeVolume(32);

	for(int x = 0;x <32 ;x++){
		for(int y = 0;y<32;y++){
			for(int z = 0;z<32;z++){

				volume->set(x,y,z,2);
				
			}
		}
	}



	Texture * quadTex = new Texture(Texture::ColorFormat::FORMAT_RGB,1280,728);
	
	VolumeModel * model = new VolumeModel(1,1,1,32,1,32);
	model->setResourceManager(resourceManager);
	model->init(atlas);
	model->move(glm::vec3(20,0.0,0.0));
	
	ChunkExtractor extractor = ChunkExtractor(&CubeSurfaceExtractorWithByteNormals(volume),32,32,32);
	model->setSurface(0,0,0,extractor.extractSurface(0,0,0));
	rootNode->addChild(model);
	pipeline = new Pipeline(10,10);


	
	
	texturedQuad = new TexturedQuad();
	texturedQuad->setResourceManager(resourceManager);
	texturedQuad->init(quadTex);
	texturedQuad->setSize(1280/4.0,728/4.0,1);
	texturedQuad->setPosition(glm::vec3(300,100,1));

	
	translatedQuad = new TexturedQuad();
	translatedQuad->setResourceManager(resourceManager);
	translatedQuad->init(quadTex);
	translatedQuad->setSize(1280/20.0,728/20.0,1);

	translatedQuad->setPosition(glm::vec3(100,2,50));

	
	
	this->frameBuffer= new FrameBuffer();
	this->frameBuffer->setDepthBuffer(1280,728);
	this->frameBuffer->addRenderTexture(quadTex);

	delete rootNode;
	
	
}



void GameScreen::reshape(int width, int height){
	if(cam)
	cam->setProjection(width,height);

}

void GameScreen::render()
{

	/*
	frameBuffer->bind();


	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glClearColor(0.4,0.4,0.4,1.0);
	
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);

	pipeline->clear();
	pipeline->setShadowPass(false);
	pipeline->setView(cam->getViewMatrix());
	pipeline->setCameraPosition(glm::vec4(cam->getPosition(),1.0));
	pipeline->setProjection(cam->getPerspectiveProjection());
	pipeline->setViewDirection(glm::vec4(cam->getViewDirection(),1.0));
	

	rootNode->render(pipeline);

	glBindFramebuffer(GL_FRAMEBUFFER,0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glClearColor(0.4,0.4,0.4,1.0);
	pipeline->clear();
	pipeline->setShadowPass(false);
	pipeline->setView(cam->getViewMatrix());
	pipeline->setCameraPosition(glm::vec4(cam->getPosition(),1.0));
	pipeline->setProjection(cam->getPerspectiveProjection());
	pipeline->setViewDirection(glm::vec4(cam->getViewDirection(),1.0));
	rootNode->render(pipeline);
	translatedQuad->render(pipeline);

	glDisable(GL_DEPTH_TEST);
	pipeline->clear();
	pipeline->setProjection(glm::ortho(0.0f,(float)cam->getWidth(),0.0f,(float)cam->getHeight()));
	pipeline->setView(glm::mat4(1.0));
	
	//crossHair->render(pipeline);
	texturedQuad->render(pipeline);
	
	

	*/
	

	
	

}

void GameScreen::update(double dt)
{
	

	
	//rootNode->rotate(glm::quat(glm::vec3(0,1*dt,0)));
	//rootNode->getChildren()->at(0)->rotate(glm::quat(glm::vec3(0.0,1*dt,0.0)));
	
	//floorNode->rotate(glm::quat(glm::vec3(0,1.0*dt,0)));

	cameraController->update(dt);




	

	
	
}

GameScreen::~GameScreen(void)
{
	delete world;
	delete pipeline;
}
