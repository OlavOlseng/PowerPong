#include "Game.h"
//we need to get hacky since glut is a c api
BaseGame * BaseGame::instance = new Game();

Game::Game(){

}
Game::Game(int argc,char * argv[]):BaseGame()
{
	//will not return

	//temp: need a system for filepaths
	Game* g = (Game*)instance;
	
	g->binaryPath = argv[0];
	int last = g->binaryPath.find_last_of("\\");
	g->binaryPath.erase(last+1,20);
	

	init("Game",1280,720);
}

Game::~Game(void)
{
}


void Game::loadShaders(Pipeline*pipeline){

	

	




	


	wallShader = resManager->loadShader("wallShader");

	wallShader->bindUniform(ShaderUniforms::MVP,"mvp");
	wallShader->bindUniform(ShaderUniforms::MODEL,"modelMatrix");
	wallShader->bindUniform(ShaderUniforms::STEP_SIZE,"stepSize");
	wallShader->bindUniform(ShaderUniforms::NUM_DIRECTIONAL_LIGHTS,"numDirLights");
	wallShader->bindUniform(ShaderUniforms::NUM_POINT_LIGHTS,"numPointLights");
	wallShader->bindUniform(ShaderUniforms::MATERIAL_DIFFUSE,"material.diffuse");
	wallShader->bindUniform(ShaderUniforms::MATERIAL_AMBIENT,"material.ambient");
	wallShader->bindUniform(ShaderUniforms::MATERIAL_SPECULAR,"material.specular");
	wallShader->bindUniform(ShaderUniforms::MATERIAL_SHININESS,"material.shininess");
	wallShader->bindUniform(ShaderUniforms::VIEW_DIRECTION,"viewDir");
	const char * memberNamesWall[] = {"diffuse","specular","direction"};
	wallShader->bindUniformStructArray(ShaderUniforms::LIGHT_DIRECTIONAL,10,3,"dirLights",memberNamesWall);
	const char * memberNamesPointWall[] = {"diffuse","specular","position","constantAttenuation","linearAttenuation","quadraticAttenuation"};
	wallShader->bindUniformStructArray(ShaderUniforms::LIGHT_POINT,10,6,"pointLights",memberNamesPointWall);
	wallShader->bindAttribute(ShaderAttributes::COORD3D,"coord3d");
	wallShader->bindAttribute(ShaderAttributes::COLOR3D,"color3d");
	wallShader->bindAttribute(ShaderAttributes::NORMAL3D,"normal3d");
	wallShader->bindAttribute(ShaderAttributes::BLOCK_TYPE,"blockType");

	



	shadowShader = resManager->loadShader("shadowShader");
	shadowShader->bindUniform(ShaderUniforms::MVP,"mvp");
	shadowShader->bindAttribute(ShaderAttributes::COORD3D,"coord3d");

	







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
	

	
	rootNode = new Node();
	
	pipeline = new Pipeline();

	loadShaders(pipeline);


	//setting up physics
	this-> world = new World();
	
	//init stuff here
	cam = new Camera(4,40,-40,0,0,0,1280,720);
	
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
	model->initFromScene(scene,modelNode);
	Node*model2Node = new Node();
	model2->initFromScene(scene,model2Node);
	Node*model3Node = new Node();
	model3->initFromScene(scene,model3Node);
	rootNode->addChild(modelNode);
	rootNode->addChild(model2Node);
	rootNode->addChild(model3Node);	
	imp.FreeScene();
	

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

			vol.set(x,0,z,2);
		}

	}
	

	CubeSurfaceExtractorWithByteNormals  *extractor = new CubeSurfaceExtractorWithByteNormals(&vol);
	VolumeSurface * surface = extractor->extractSurface(0,0,0,16,2,16);
	
	VolumeModel * volumeModel = new VolumeModel(4,4,4);

	volumeModel->setResourceManager(resManager);
	volumeModel->init();
	volumeModel->setSurface(0,0,0,surface);
	volumeModel->setSurface(1,0,0,surface);
	volumeModel->setPosition(glm::vec3(0,0,0));
	
	rootNode->addChild(volumeModel);

	 sun = new DirectionalLight();
	 sun->diffuse = glm::vec4(1.0,1.0,1.0,1.0);
	// sun->specular = glm::vec4(1.0,1.0,1.0,1.0);

	sun->direction = glm::normalize(glm::vec4(0.0,-1.0,0.0,.0));
	
	PointLight * pointlight = new PointLight();
	pointlight->diffuse = glm::vec4(1.0,1.0,1.0,1.0);
	pointlight->specular = glm::vec4(1.0,1.0,1.0,1.0);

	pointlight->position = glm::vec4(0.0,10.0,0.0,1.0);
	pointlight->setRange(5000.0);


	//rootNode->addLight(sun);
	//rootNode->addLight(light2);
	rootNode->addLight(pointlight);
	
	
	
}
void Game::reshape(int width, int height){
	
	glViewport(0,0,width,height);
	cam->setProjection(width,height);
	this->width = width;
	this->height = height;

}
void Game::draw(){
	glBindFramebuffer(GL_FRAMEBUFFER,0);
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
	//model->setRotation(glm::vec3(0.0,rot,0.0));
	
	
	rootNode->rotate(glm::vec3(0,0.0001*dt,0));
	rootNode->getChildren()->at(1)->setRotation(glm::vec3(0,-xrot,0));
	rootNode->getChildren()->at(2)->rotate(glm::vec3(0,0.001*dt,0));
	rootNode->getChildren()->at(3)->rotate(glm::vec3(0,0.001*dt,0));
	rootNode->getChildren()->at(4)->rotate(glm::vec3(0,0.002*dt,0));
	xrot+= 0.01*dt;
	
	
	cam->tick();
	//world-> update(dt);
	postRedisplay();
	
}