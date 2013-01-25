#include "GameScreen.h"




GameScreen::GameScreen(std::shared_ptr<ResourceManager> resourceManager,bool enableTest)
{
	
	this -> renderBlock = 1;
	this -> updateBlock = 1;

	this->resourceManager = resourceManager;
	rootNode = new Node();
	this -> world = new World();
	cam = new Camera(0,40,50,0,0,0,1280,780);
	if (enableTest)
	{
		test();
	}
	
}

void GameScreen::test()
{
	
	
	Assimp::Importer imp = Assimp::Importer();
	const aiScene * sphereScene = imp.ReadFile(resourceManager->getWorkingDirectiory() +"\\Models\\sphere.irr",aiProcessPreset_TargetRealtime_Quality);
	StaticModel*sphereModel = new StaticModel();
	sphereModel->setResourceManager(resourceManager);
	sphereModel->initFromScene(sphereScene,sphereModel);
	//rootNode->addChild(sphereModel);

	ballModel = sphereModel;
	PointLight * light = new PointLight();
	light->diffuse = glm::vec4(1.0,1.0,1.0,1.0);
	light->specular = glm::vec4(1.0,1.0,1.0,1.0);
	light->setRange(10000);
	light->position = glm::vec4(0.0,100.0,0.0,1.0);
	rootNode->addLight(light);
	imp.FreeScene();
	
	OctreeVolume vol = OctreeVolume(16);
	for(int x = 0;x<16;x++){
		for(int z = 0;z< 16;z++)
		vol.set(x,0,z,2);
	}
	
	CubeSurfaceExtractorWithByteNormals  extractor = CubeSurfaceExtractorWithByteNormals(&vol);
	VolumeSurface * surface = extractor.extractSurface(0,0,0,16,1,16);
	blockModel = new VolumeModel(1,1,1,16,1,16);
	blockModel->setResourceManager(resourceManager);
	blockModel->init();
	blockModel->setSurface(0,0,0,surface);
	//rootNode->addChild(blockModel);
	

	ballEntity = new Ball(10.0,0,100,0);
	blockEntity = new Block(10,1,10,0,0,0);
	sphereModel->setSize(20,20,10);
	blockModel->setSize(10,1,10);
	
	LineModel *lineModel = new LineModel();
	lineModel->setResourceManager(resourceManager);
	lineModel->init();
	rootNode->addChild(lineModel);

	BulletDebugDraw  *debugDraw = new BulletDebugDraw(lineModel);
	debugDraw->setDebugMode(btIDebugDraw::DBG_DrawWireframe);

	for(int x = 0;x<10;x++)
		for(int y = 0;y<10;y++)
		world->addEntity(new Block(x*4,y*4,x*y));
	
	this -> world -> addEntity(ballEntity);
	this->world->addEntity(blockEntity);
	this -> world ->setDebugDraw(debugDraw);

	pipeline = new Pipeline(10,10);
}


void GameScreen::reshape(int width, int height){

	cam->setProjection(width,height);

}

void GameScreen::render()
{



	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glClearColor(0.4,0.4,0.4,1.0);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	

	pipeline->clear();
	pipeline->setShadowPass(false);
	pipeline->setView(cam->getView());
	pipeline->setCameraPosition(glm::vec4(cam->getPos(),1.0));
	pipeline->setProjection(cam->getProjection());
	pipeline->setViewDirection(glm::vec4(cam->getDir(),1.0));
	world->debugDrawWorld();
	rootNode->render(pipeline);

	

}

void GameScreen::update(double dt)
{

	rootNode->rotate(glm::vec3(0,1*dt,0));
	
	float * position = ballEntity->getPosition();
	
	ballModel->setPosition(glm::vec3(position[0] ,position[1],position[2]));
	
	position = blockEntity->getPosition();

	blockModel->setPosition(glm::vec3(position[0],position[1] ,position[2]));
	
	this -> world -> update(dt);
	
	cam->tick();
}

GameScreen::~GameScreen(void)
{
	delete world;
	delete pipeline;
}
