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
#include "Rendering\WallMeshGenerator.h"

void Game::loadShaders(Pipeline*pipeline){
	wallShaderHandle = 0;
	diffuseSpecularHandle = 1;
	shadowShaderHandle = 2;
	
	

	diffuseSpecular = resManager->loadShader("diffuseSpecular");
	diffuseSpecular->bindUniform(ShaderUniforms::MVP,"mvp");
	diffuseSpecular->bindUniform(ShaderUniforms::MODEL,"modelMatrix");
	diffuseSpecular->bindUniform(ShaderUniforms::NUM_DIRECTIONAL_LIGHTS,"numDirLights");
	diffuseSpecular->bindUniform(ShaderUniforms::NUM_POINT_LIGHTS,"numPointLights");
	diffuseSpecular->bindUniform(ShaderUniforms::MATERIAL_DIFFUSE,"material.diffuse");
	diffuseSpecular->bindUniform(ShaderUniforms::MATERIAL_AMBIENT,"material.ambient");
	diffuseSpecular->bindUniform(ShaderUniforms::MATERIAL_SPECULAR,"material.specular");
	diffuseSpecular->bindUniform(ShaderUniforms::MATERIAL_SHININESS,"material.shininess");
	diffuseSpecular->bindUniform(ShaderUniforms::VIEW_DIRECTION,"viewDir");
	const char * memberNames[] = {"diffuse","specular","direction",};
	diffuseSpecular->bindUniformStructArray(ShaderUniforms::LIGHT_DIRECTIONAL,10,3,"dirLights",memberNames);
	const char * memberNamesPoint[] = {"diffuse","specular","position","constantAttenuation","linearAttenuation","quadraticAttenuation"};
	diffuseSpecular->bindUniformStructArray(ShaderUniforms::LIGHT_POINT,10,6,"pointLights",memberNamesPoint);
	diffuseSpecular->bindAttribute(ShaderAttributes::COORD3D,"coord3d");
	diffuseSpecular->bindAttribute(ShaderAttributes::NORMAL3D,"normal3d");
	diffuseSpecular->bindAttribute(ShaderAttributes::TEXCOORD2D,"texcoord2d");

	pipeline->addShader(diffuseSpecular,diffuseSpecularHandle);


	


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

	pipeline->addShader(wallShader,wallShaderHandle);



	shadowShader = resManager->loadShader("shadowShader");
	shadowShader->bindUniform(ShaderUniforms::MVP,"mvp");
	shadowShader->bindAttribute(ShaderAttributes::COLOR3D,"coord3d");

	pipeline->addShader(shadowShader,shadowShaderHandle);



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
	models = new std::vector<Model*>();
	cam = new Camera(4,20,-20,0,0,0,1280,720);
	geomRenderer = new GeometryRenderer(cam,models);
	
	WallMeshGenerator generator = WallMeshGenerator();
	Node*wallNode = new Node();
	
	for(int i = 0;i<5;i++){

	gWall *wall = new gWall(1,5,glm::vec3(0,0,0));
	wall->setBlock(0,5,gBlock::BlockType::PLANK);
	wall->setShader(wallShaderHandle);
	wall->setResourceManager(resManager);
	wall->init();
	
	wall->setAttributes(wallShader->getAttributes());
	wall->setPosition(glm::vec3(-2.5,0,-2.5+i));
	wallNode->addChild(wall);
	generator.generateMeshFor(wall);
	
	}
	
	rootNode->addChild(wallNode);
	wallNode->scale(glm::vec3(1.0,0,2.0));
	


	
	model = new StaticModel();
	model->setScale(glm::vec3(0.01,0.01,0.01));
	StaticModel*model2 = new StaticModel();
	model2->setScale(glm::vec3(0.01,0.01,0.01));
	StaticModel* model3 = new StaticModel();
	model3->setScale(glm::vec3(0.01,0.01,0.01));

	model->setPosition(glm::vec3(0,2,0));
	model2->setPosition(glm::vec3(0,2,4));
	model3->setPosition(glm::vec3(0,2,2));

	model->setShader(diffuseSpecularHandle);
	model2->setShader(diffuseSpecularHandle);
	model3->setShader(diffuseSpecularHandle);

	model->setResourceManager(resManager);
	model2->setResourceManager(resManager);
	model3->setResourceManager(resManager);


	model->setAttributes(diffuseSpecular->getAttributes());
	model2->setAttributes(diffuseSpecular->getAttributes());
	model3->setAttributes(diffuseSpecular->getAttributes());

	//geomRenderer->registerModel(model2);


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
	
	
	StaticModel*sphereModel = new StaticModel(diffuseSpecular->getAttributes());
	sphereModel->setResourceManager(resManager);
	sphereModel->setShader(diffuseSpecularHandle);
	
	Node*sphereNode =  new Node();
	sphereModel->initFromScene(sphereScene,sphereNode);
	sphereNode->setScale(glm::vec3(20,20,20));
	sphereNode->move(glm::vec3(0,-20,20));
	rootNode->addChild(sphereNode);
	imp.FreeScene();
	
	
	
	const aiScene * spiderScene= imp.ReadFile(resManager->getWorkingDirectiory()+"\\Models\\spider.obj",aiProcessPreset_TargetRealtime_Quality);

	StaticModel*spiderModel= new StaticModel(diffuseSpecular->getAttributes());
	spiderModel->setResourceManager(resManager);
	spiderModel->setShader(diffuseSpecularHandle);
	
	Node*spiderNode = new Node();
	spiderModel->initFromScene(spiderScene,spiderNode);
	spiderNode->setScale(glm::vec3(0.1,0.1,0.1));
	spiderNode->move(glm::vec3(0,5,0));
	rootNode->addChild(spiderNode);

	imp.FreeScene();
	
	 sun = new DirectionalLight();
	 sun->diffuse = glm::vec4(1.0,1.0,1.0,1.0);
	// sun->specular = glm::vec4(1.0,1.0,1.0,1.0);

	sun->direction = glm::normalize(glm::vec4(0.0,-1.0,0.0,.0));
	

	DirectionalLight* light2 = new DirectionalLight();
	light2 ->diffuse = glm::vec4(0.0,0.0,0.0,0.0);
	 light2 ->specular = glm::vec4(1.0,1.0,1.0,1.0);
	
	light2 ->direction = glm::normalize(glm::vec4(0.0,-1.0,0.0,.0));
	

	PointLight * pointlight = new PointLight();
	pointlight->diffuse = glm::vec4(1.0,1.0,1.0,1.0);
	//pointlight->specular = glm::vec4(1.0,1.0,1.0,1.0);

	pointlight->position = glm::vec4(0.0,5.0,0.0,1.0);
	pointlight->constantAttenuation =1.0;
	pointlight->linearAttenutation = 0.007;
	pointlight->quadraticAttenuation = 0.0002;


	rootNode->addLight(sun);
	//rootNode->addLight(light2);
//	rootNode->addLight(pointlight);
	/*
	glGenFramebuffers(1,&frameBufferHandle);
	glBindFramebuffer(GL_FRAMEBUFFER,frameBufferHandle);

	glGenTextures(1,&depthTexture);
	glBindTexture(GL_TEXTURE_2D,depthTexture);
	glTexImage2D(GL_TEXTURE_2D,0,GL_DEPTH_COMPONENT16,1024,1024,0,GL_DEPTH_COMPONENT,GL_FLOAT,0);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);

	glFramebufferTexture(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,depthTexture,0);
	
	glDrawBuffer(GL_NONE);

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
		printf("\nframebuffer ready \n");
	cam->move(2,20,0);*/
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
	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	
	pipeline->clear();
	
	pipeline->setShadowPass(false);
	pipeline->setView(cam->getView());
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