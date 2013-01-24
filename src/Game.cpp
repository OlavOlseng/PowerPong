#include "Game.h"
//we need to get hacky since glut is a c api


Game::Game(){

}
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
	gameScreen = GameScreen(true);
	screenManager.pushScreen(&gameScreen);

	
	rootNode = new Node();
	pipeline = new Pipeline();
	loadShaders(pipeline);


	//setting up physics
	this-> world = new World();
	//init stuff here
	cam = new Camera(0,30,-40,0,0,0,1280,720);
	Assimp::Importer imp = Assimp::Importer();
	const aiScene * sphereScene = imp.ReadFile(resManager->getWorkingDirectiory()+"\\Models\\sphere.irr",aiProcessPreset_TargetRealtime_Quality);
	StaticModel*sphereModel = new StaticModel();
	sphereModel->setResourceManager(resManager);
	Node*sphereNode =  new Node();
	sphereModel->initFromScene(sphereScene,sphereNode);
	sphereNode->setScale(glm::vec3(10,10,10));
	//rootNode->addChild(sphereNode);

	imp.FreeScene();





	

	PointLight * light = new PointLight();
	light->position = glm::vec4(0.0,20.0,0.0,1.0);
	light->diffuse = glm::vec4(1.0,1.0,1.0,1.0);
	light->specular = glm::vec4(1.0,1.0,1.0,1.0);
	light->setRange(00.0);
	rootNode->addLight(light);

	



	
	
	
}
void Game::reshape(int width, int height){
	
	glViewport(0,0,width,height);
	cam->setProjection(width,height);
	this->width = width;
	this->height = height;

}
void Game::draw(){ 
	
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glClearColor(0.4,0.4,0.4,1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

	screenManager.render();
	pipeline->clear();
	pipeline->setShadowPass(false);
	pipeline->setView(cam->getView());
	pipeline->setCameraPosition(glm::vec4(cam->getPos(),1.0));
	pipeline->setProjection(cam->getProjection());
	pipeline->setViewDirection(glm::vec4(cam->getDir(),1.0));

	rootNode->render(pipeline);

	swapBuffers();
}


void Game::update(double dt){
	
	screenManager->update(dt);
	static double x = 0;
	static float xrot;
	static double dx = 0.001;
	static bool right = true;
	static float intensity = 0;
	printf("Time per frame %f: \n",dt*1000);
	//model->setRotation(glm::vec3(0.0,rot,0.0));
	
	
	rootNode->rotate(glm::vec3(0,1.0*dt,0));
	rootNode->getChildren()->at(1)->setRotation(glm::vec3(0,-xrot,0));
	rootNode->getChildren()->at(2)->rotate(glm::vec3(0,1.0*dt,0));
	rootNode->getChildren()->at(3)->rotate(glm::vec3(0,1.0*dt,0));
	rootNode->getChildren()->at(4)->rotate(glm::vec3(0,1.0*dt,0));
	rootNode->getChildren()->at(6)->rotate(glm::vec3(1.0*dt,0.2*dt,0));
	xrot+= 0.1*dt;
	
	
	cam->tick();
	//world-> update(dt);
	
	
}