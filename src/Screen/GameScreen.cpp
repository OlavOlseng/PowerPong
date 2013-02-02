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
	cam->setPosition(40,40,40);
	
	

	if (enableTest)
	{
		test();
	}
	
}

void GameScreen::test()
{
	
	
	Assimp::Importer imp = Assimp::Importer();
	const aiScene * sphereScene = imp.ReadFile(resourceManager->getWorkingDirectiory() +"\\Models\\sphere.irr",aiProcessPreset_TargetRealtime_Quality);

	
	
	PointLight * light = new PointLight();
	light->diffuse = glm::vec4(1.0,1.0,1.0,1.0);
	light->specular = glm::vec4(1.0,1.0,1.0,1.0);
	light->setRange(5000);
	light->position = glm::vec4(0,50.0,0.0,1.0);
	rootNode->addLight(light);
	
	
	OctreeVolume *  vol = new OctreeVolume(16);
	for(int x = 0;x<16;x++){
		for(int z = 0;z< 16;z++)
		vol->set(x,0,z,2);
	}
	
	CubeSurfaceExtractorWithByteNormals  extractor = CubeSurfaceExtractorWithByteNormals(vol);
	VolumeSurface * surface = extractor.extractSurface(0,0,0,16,1,16);
	VolumeModel *  blockModel = new VolumeModel(1,1,1,16,1,16);
	blockModel->setResourceManager(resourceManager);
	blockModel->init();
	
	blockModel->setSurface(0,0,0,surface);

	rootNode->addChild(blockModel);
	blockModel->setSize(10,1,10);
	blockEntity = new Block(10,1,10,0,0,0);
	blockEntity->setUserPointer(blockModel);
	this->world->addEntity(blockEntity);

	
	
		
	VolumeModel * floorM = new VolumeModel(1,1,1,16,1,16);
	floorM->setResourceManager(resourceManager);
	floorM->init();
	floorM->setSurface(0,0,0,extractor.extractSurface(0,0,0,16,1,16));
	floorM->setScale(glm::vec3(20.0,1.0,20.0));
	floorM->move(glm::vec3(0,-0.5,0));
	rootNode->addChild(floorM);
	
	
	

	
	

	


	
	
	for(int x = 0;x<100;x++)
		for(int y = 0;y<100;y++){

			
			StaticModel*sphere = new StaticModel();
			sphere->setResourceManager(resourceManager);
			sphere->initFromScene(sphereScene,sphere);
			sphere->setSize(glm::vec3(2.0,2.0,2.0));
			rootNode->addChild(sphere);

			Ball * ballEntity = new Ball(1.0,x*4 % 40,y*4 % 40,x*y % 40);
			world->addEntity(ballEntity);
			ballEntity->setUserPointer(sphere);

	}
	
	
	pipeline = new Pipeline(10,10);
	imp.FreeScene();
}



void GameScreen::reshape(int width, int height){
	if(cam)
	cam->setProjection(width,height);

}

void GameScreen::render()
{

	

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glClearColor(0.4,0.4,0.4,1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	

	pipeline->clear();
	pipeline->setShadowPass(false);
	pipeline->setView(cam->getViewMatrix());
	pipeline->setCameraPosition(glm::vec4(cam->getPosition(),1.0));
	pipeline->setProjection(cam->getProjectionMatrix());
	pipeline->setViewDirection(glm::vec4(cam->getViewDirection(),1.0));
	//world->debugDrawWorld();
	rootNode->render(pipeline);

	

}
#include <GL\glfw.h>
void GameScreen::update(double dt)
{
	

	
	
	

	if(glfwGetKey('A') == GLFW_PRESS)
		cam->rotateLeft(1.0*dt);
	if(glfwGetKey('D') == GLFW_PRESS)
		cam->rotateRight(1.0*dt);

	
	



	if(glfwGetKey('W') == GLFW_PRESS)
		cam->rotateUp(1.0*dt);
	if(glfwGetKey('S') == GLFW_PRESS)
		cam->rotateDown(1.0*dt);

	if(glfwGetKey('G') == GLFW_PRESS)
		cam->rotate(1.0*dt,0.0,0.0);
	if(glfwGetKey('H') == GLFW_PRESS)
		cam->rotate(0.0,0.0,1.0*dt);



	this -> world -> update(dt);

	for(Entity * entity: world->getEntities()){

		Model * model = (Model*)entity->getUserPointer();
		if(model && entity->body->isActive()){
			float * position = entity->getPosition();
			model->setPosition(glm::vec3(position[0] ,position[1],position[2]));
		}
	}
	
	
}

GameScreen::~GameScreen(void)
{
	delete world;
	delete pipeline;
}
