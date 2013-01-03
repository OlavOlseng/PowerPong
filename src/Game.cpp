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
	Shader* diffuseSpecular = new Shader(vs,fs);
	diffuseSpecular->bindUniform(ShaderUniforms::MVP,"mvp");
	diffuseSpecular->bindUniform(ShaderUniforms::MODEL,"modelMatrix");
	diffuseSpecular->bindAttribute(ShaderAttributes::COORD3D,"coord3d");
	diffuseSpecular->bindAttribute(ShaderAttributes::NORMAL3D,"normal3d");
	diffuseSpecular->bindAttribute(ShaderAttributes::TEXCOORD2D,"texcoord2d");

	pipeline->addShader(diffuseSpecular,10);

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
	


	Shader* wallShader = new Shader(vs,fs);

	wallShader->bindUniform(ShaderUniforms::MVP,"mvp");
	wallShader->bindUniform(ShaderUniforms::STEP_SIZE,"stepSize");
	wallShader->bindAttribute(ShaderAttributes::COORD3D,"coord3d");
	wallShader->bindAttribute(ShaderAttributes::COLOR3D,"color3d");
	wallShader->bindAttribute(ShaderAttributes::BLOCK_TYPE,"blockType");

	pipeline->addShader(wallShader,1);

}
void Game::setup(){

	printf("\n WorkingDir: %s \n",binaryPath.c_str());
	pipeline = new Pipeline();
	loadShaders(pipeline);

	//setting up physics
	this-> world = new World();
	
	//init stuff here
	models = new std::vector<Model*>();
	cam = new Camera(4,5,-5,2,0,0,1280,720);
	
	
	gWall *wall = new gWall(1,5,glm::vec3(0,0,0));
	
	wall->setBlock(0,1,gBlock::BlockType::ROCK);
	wall->setBlock(1,1,glm::vec3(0.0,1.0,0.0));
	wall->setBlock(2,1,gBlock::BlockType::DIRT);

	wall->setShader(1);
	std::shared_ptr<ResourceManager> resManager = std::make_shared<ResourceManager>();
	resManager->setWorkingDirectory(binaryPath);
	wall->setResourceManager(resManager);
	wall->init();

	WallMeshGenerator generator = WallMeshGenerator();
	
	geomRenderer = new GeometryRenderer(cam,models);

	
	model = new StaticModel();
	
	model->setScale(glm::vec3(0.01,0.01,0.01));
	StaticModel*model2 = new StaticModel();
	model2->setScale(glm::vec3(0.01,0.01,0.01));
	StaticModel* model3 = new StaticModel();

	model->setShader(10);
	model2->setShader(10);
	model3->setShader(10);
	model->setResourceManager(resManager);
	model2->setResourceManager(resManager);
	model3->setResourceManager(resManager);



	geomRenderer->registerModel(model2,pipeline);
	geomRenderer->registerModel(model,pipeline);
	geomRenderer->registerModel(model3,pipeline);
	geomRenderer->registerModel(wall,pipeline);

	generator.generateMeshFor(wall);
	

	//geomRenderer->registerModel(model2);


	Assimp::Importer imp = Assimp::Importer();
	
	const std::string path = std::string(resManager->getWorkingDirectiory() +"duck.dae");

	

	const aiScene *scene = imp.ReadFile(path.c_str(),aiProcessPreset_TargetRealtime_Fast);



	Node* modelNode = model->initFromScene(scene);
	//modelNode->move(glm::vec3(2,0,10));
	Node*model2Node = model2->initFromScene(scene);
	//model2Node->move(glm::vec3(100,0,10));
	Node*model3Node = model3->initFromScene(scene);
	model3Node->move(glm::vec3(-100,0,10));

	Node*wallNode = new Node();
	wallNode->addChild(wall);
	
	
	rootNode = new Node();
	rootNode->addChild(modelNode);
	rootNode->addChild(model2Node);
	rootNode->addChild(wallNode);
	//rootNode->addChild(model3Node);

	rootNode->move(glm::vec3(2,0,0));
	modelNode->move(glm::vec3(2.0,0.0,.0));
	model2Node->move(glm::vec3(-2.0,0.0,0.0));
	model2Node->rotate(glm::vec3(0,3.14,0));
	//wallNode->move(glm::vec3(4,0.0,0.0));

	
		
	imp.FreeScene();


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
	
	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	pipeline->clear();

	geomRenderer->render(pipeline,rootNode);

	swapBuffers();
}


void Game::update(double dt){
	static double rot;
	static double xrot;
	//model->setRotation(glm::vec3(0.0,rot,0.0));
	rot+= 0.01;
	//rootNode->rotate(glm::vec3(0.0,0.01,0.0));
	rootNode->getChildren()->at(0)->rotate(glm::vec3(0.0,0.01,0.0));
	rootNode->getChildren()->at(1)->rotate(glm::vec3(0.01,0.00,0.0));
	rootNode->getChildren()->at(2)->rotate(glm::vec3(0.00,0.01,0.0));
	xrot+= 0.001;
	cam->tick();
	//world-> update(dt);
	postRedisplay();
	
}