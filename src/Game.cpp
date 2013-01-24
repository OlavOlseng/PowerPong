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


void Game::testScene(){
	


	model = new StaticModel();
	model->setScale(glm::vec3(0.01,0.01,0.01));
	StaticModel*model2 = new StaticModel();
	model2->setScale(glm::vec3(0.01,0.01,0.01));
	StaticModel* model3 = new StaticModel();
	model3->setScale(glm::vec3(0.01,0.01,0.01));

	model->setPosition(glm::vec3(0,2,0));
	model2->setPosition(glm::vec3(0,2,4));
	model3->setPosition(glm::vec3(0,2,2));

	model->setResourceManager(resManager);
	model2->setResourceManager(resManager);
	model3->setResourceManager(resManager);

	Assimp::Importer imp = Assimp::Importer();
	
	const std::string path = std::string(resManager->getModelDirectory()+"duck.dae");
	const aiScene *scene = imp.ReadFile(path.c_str(),aiProcessPreset_TargetRealtime_Quality);
	Node* modelNode = new Node();
	model->initFromScene(scene,model);
	Node*model2Node = new Node();
	model2->initFromScene(scene,model2Node);
	Node*model3Node = new Node();
	model3->initFromScene(scene,model3Node);
	rootNode->addChild(modelNode);
	rootNode->addChild(model2Node);
	rootNode->addChild(model3Node);	
	imp.FreeScene();
	
	//ThomasFechten.csm
	const aiScene * sphereScene = imp.ReadFile(resManager->getWorkingDirectiory()+"\\Models\\sphere.irr",aiProcessPreset_TargetRealtime_Quality);
	


	
	StaticModel*sphereModel = new StaticModel();
	sphereModel->setResourceManager(resManager);
	Node*sphereNode =  new Node();
	sphereModel->initFromScene(sphereScene,sphereNode);
	sphereNode->setScale(glm::vec3(20,20,20));
	sphereNode->move(glm::vec3(0,-20,20));
	rootNode->addChild(sphereNode);
	imp.FreeScene();


	
	const aiScene * spiderScene= imp.ReadFile(resManager->getWorkingDirectiory()+"\\Models\\spider.obj",aiProcessPreset_TargetRealtime_Quality);

	StaticModel*spiderModel= new StaticModel();
	spiderModel->setResourceManager(resManager);
	
	Node*spiderNode = new Node();
	spiderModel->initFromScene(spiderScene,spiderNode);
	spiderNode->setScale(glm::vec3(0.1,0.1,0.1));
	spiderNode->move(glm::vec3(0,5,0));
	rootNode->addChild(spiderNode);


	imp.FreeScene();

	LargeVolume<OctreeVolume> vol(32,32,32,16,16,16);

	for(int x = 0;x<16;x++){
		for(int z = 0;z< 16;z++){
			for(int y = 0;y<3;y++){
				vol.set(x,y,z,2);
			}
			
		}

	}
	

	CubeSurfaceExtractorWithByteNormals  *extractor = new CubeSurfaceExtractorWithByteNormals(&vol);
	VolumeSurface * surface = extractor->extractSurface(0,0,0,16,3,16);
	VolumeModel * volumeModel = new VolumeModel(4,4,4,16,16,16);
	volumeModel->setResourceManager(resManager);
	volumeModel->init();
	volumeModel->setSurface(0,0,0,surface);
	volumeModel->setSurface(3,0,0,surface);
	volumeModel->setSurface(0,0,3,surface);
	volumeModel->setSurface(3,0,3,surface);
	volumeModel->setPosition(glm::vec3(0,0,0));
	rootNode->addChild(volumeModel);

	VolumeModel * smallVolumeModel = new VolumeModel(1,1,1,16,16,16);
	smallVolumeModel->setResourceManager(resManager);
	smallVolumeModel->init();
	VolumeSurface * anotherSurface = extractor->extractSurface(0,0,0,16,1,16);
	smallVolumeModel->setSurface(0,0,0,surface);

	Node * testNode = new Node();
	testNode->setScale(glm::vec3(2.0,1.0,2.0));
	testNode->addChild(smallVolumeModel);
	rootNode->addChild(testNode);

	 sun = new DirectionalLight();
	 sun->diffuse = glm::vec4(1.0,1.0,1.0,1.0);
	// sun->specular = glm::vec4(1.0,1.0,1.0,1.0);

	sun->direction = glm::normalize(glm::vec4(0.0,-1.0,0.0,.0));
	
	PointLight * pointlight = new PointLight();
	pointlight->diffuse = glm::vec4(1.0,1.0,1.0,1.0);
	pointlight->specular = glm::vec4(1.0,1.0,1.0,1.0);

	pointlight->position = glm::vec4(0.0,10.0,0.0,1.0);
	pointlight->setRange(0.01);


	//rootNode->addLight(sun);
	//rootNode->addLight(light2);
	//rootNode->addLight(pointlight);


}
void Game::setup(){

	
	
	

	Assimp::DefaultLogger::create("",Assimp::Logger::VERBOSE);
	resManager = std::make_shared<ResourceManager>();
	resManager->setWorkingDirectory(binaryPath + "\Assets\\");
	resManager->setShaderDirectory(binaryPath + "\Assets\\Shaders\\");
	resManager->setModelDirectory(binaryPath + "\Assets\\Models\\");
	

	
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
	light->setRange(500.0);
	rootNode->addLight(light);

	testScene();



	
	
	
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