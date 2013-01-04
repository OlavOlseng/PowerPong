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

		char* vs = 
		"attribute vec3 coord3d;"
		"attribute vec3 normal3d;"
		"attribute vec2 texcoord2d;"
		"uniform mat4 mvp;"
		"uniform mat4 modelMatrix;"
		"varying vec3 f_normal;"
		"varying vec2 f_texcoord;"
		"void main()"
		"{"
		"f_normal = normalize(modelMatrix*vec4(normal3d.xyz,0.0));"
		"f_texcoord = texcoord2d;"
		"gl_Position = mvp*vec4(coord3d.xyz,1.0);"
		"}";
	 char*fs = 
		"varying vec3 f_normal;"
		"varying vec2 f_texcoord;"
		"uniform sampler2D tex;"
		"const vec3 lightColor = vec3(1.0,1.0,1.0);"
		"const vec3 lightDir = vec3(0.0,-1.0,0.0);"
		"uniform vec3 diffuseColor;"
		"void main(){"
		"gl_FragColor = texture2D(tex,f_texcoord)*(vec4(lightColor.xyz,0)*dot(f_normal,-lightDir)*0.7);"
		"}";
	diffuseSpecular = new Shader(vs,fs);
	diffuseSpecular->bindUniform(ShaderUniforms::MVP,"mvp");
	diffuseSpecular->bindUniform(ShaderUniforms::MODEL,"modelMatrix");
	diffuseSpecular->bindAttribute(ShaderAttributes::COORD3D,"coord3d");
	diffuseSpecular->bindAttribute(ShaderAttributes::NORMAL3D,"normal3d");
	diffuseSpecular->bindAttribute(ShaderAttributes::TEXCOORD2D,"texcoord2d");

	pipeline->addShader(diffuseSpecular,diffuseSpecularHandle);

	vs = 
		"attribute vec3 coord3d;"
		"attribute vec3 color3d;"
		"attribute float blockType;"
		"uniform mat4 mvp;"
		"varying vec3 f_color;"
		"varying vec4 texcoord;"
		"varying float type;"
		"void main()"
		"{"
		"texcoord = vec4(coord3d,blockType);"
		"type = blockType;"
		"f_color = color3d;"
		"gl_Position = mvp*vec4(coord3d.xyz,1.0);"

		"}";
	fs = 
		"varying vec3 f_color;"

		"varying vec4 texcoord;"
		"varying float type;"
		"uniform sampler2D tex;"
		"uniform float stepSize;"
		"void main(){"
		"vec4 color = vec4(0.0,0.0,0.0,0.0);"
		"if(texcoord.w == 0.0) "
		"{"
		"	gl_FragColor = vec4(f_color,1.0);"
			"return;"
		"}"
		"	if(texcoord.w >=0.0){"
		"		color = texture2D(tex,vec2((fract(texcoord.x + texcoord.z)+ texcoord.w)*stepSize ,fract(texcoord.y)));"
		"	}else{"
		"		color = texture2D(tex,vec2((fract(texcoord.x) - texcoord.w)*stepSize ,fract(texcoord.z)));"
		"}"
		"gl_FragColor = color;"
		"}";
	


	wallShader = new Shader(vs,fs);

	wallShader->bindUniform(ShaderUniforms::MVP,"mvp");
	wallShader->bindUniform(ShaderUniforms::STEP_SIZE,"stepSize");
	wallShader->bindAttribute(ShaderAttributes::COORD3D,"coord3d");
	wallShader->bindAttribute(ShaderAttributes::COLOR3D,"color3d");
	wallShader->bindAttribute(ShaderAttributes::BLOCK_TYPE,"blockType");

	pipeline->addShader(wallShader,wallShaderHandle);

}
void Game::setup(){
	rootNode = new Node();
	
	pipeline = new Pipeline();

	loadShaders(pipeline);
	std::shared_ptr<ResourceManager> resManager = std::make_shared<ResourceManager>();
	resManager->setWorkingDirectory(binaryPath + "\Assets\\");
	printf("\n WorkingDir: %s \n",resManager->getWorkingDirectiory().c_str());
	//setting up physics
	this-> world = new World();
	
	//init stuff here
	models = new std::vector<Model*>();
	cam = new Camera(4,40,-5,2,0,0,1280,720);
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
	
	const std::string path = std::string(resManager->getWorkingDirectiory() +"duck.dae");
	const aiScene *scene = imp.ReadFile(path.c_str(),aiProcessPreset_TargetRealtime_Fast);
	Node* modelNode = model->initFromScene(scene);
	Node*model2Node = model2->initFromScene(scene);
	Node*model3Node = model3->initFromScene(scene);
	rootNode->addChild(modelNode);
	rootNode->addChild(model2Node);
	rootNode->addChild(model3Node);	
	imp.FreeScene();
	Assimp::Importer imp2;

	const aiScene * spiderScene = imp2.ReadFile(resManager->getWorkingDirectiory()+"sphere.irr",aiProcessPreset_TargetRealtime_Fast);
	

	StaticModel*spiderModel = new StaticModel(diffuseSpecular->getAttributes());
	spiderModel->setResourceManager(resManager);
	spiderModel->setShader(diffuseSpecularHandle);
	
	Node*spidernode = spiderModel->initFromScene(spiderScene);
	spidernode->setScale(glm::vec3(20,20,20));
	spidernode->move(glm::vec3(0,-20,20));

	rootNode->addChild(spidernode);

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
	pipeline->setView(cam->getView());
	pipeline->setProjection(cam->getProjection());
	
	rootNode->render(pipeline);

	swapBuffers();
}


void Game::update(double dt){
	static double x = 0;
	static double xrot;
	static double dx = 0.001;
	static bool right = true;
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