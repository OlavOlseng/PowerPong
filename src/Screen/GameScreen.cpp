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
#include "../SGL/Rendering/Voxel/Volume/LargeVolume.h"
#include "../SGL/Rendering/Voxel/Volume/ArrayVolume.h"
#include "../SGL/Rendering/Voxel/SurfaceExtractors/ChunkExtractor.h"
#include <string>
#include "../SGL/Rendering/Util/FrameBuffer.h"


void GameScreen::test()
{
	pipeline = new Pipeline(10,10);
	
	LineModel* lm = new LineModel(resourceManager);
	lm->init();
	lm->setLineWidth(2.0f);
	rootNode -> addChild(lm);

	BulletDebugDraw* dbg_draw = new BulletDebugDraw(lm);
	dbg_draw->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
	world -> setDebugDraw(dbg_draw);
	
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
	pipeline->setProjection(cam->getPerspectiveProjection());
	pipeline->setViewDirection(glm::vec4(cam->getViewDirection(),1.0));
	
	rootNode->render(pipeline);

}

void GameScreen::update(double dt)
{
	world->update(dt);
	world->debugDrawWorld();
	cameraController->update(dt);
}

GameScreen::~GameScreen(void)
{
	delete world;
	delete pipeline;
	delete rootNode;
}
