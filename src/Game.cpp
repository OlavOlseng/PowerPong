#include "Game.h"
//we need to get hacky since glut is a c api
BaseGame * BaseGame::instance = new Game();

Game::Game(){

}
Game::Game(int argc,char * argv[]):BaseGame()
{
	//will not return

	init("Game",1280,720);
}

Game::~Game(void)
{
}
#include "Rendering\WallMeshGenerator.h"

void Game::loadShaders(Pipeline*pipeline){
		const char* vs = 
		"attribute vec3 coord3d;"
		"attribute vec3 normal3d;"
		"attribute vec2 texcoord2d;"
		"uniform mat4 mvp;"
		"varying vec3 f_normal;"
		"varying vec2 f_texcoord;"
		"void main()"
		"{"
		"f_normal = normal3d;"
		"f_texcoord = texcoord2d;"
		"gl_Position = mvp*vec4(coord3d.xyz,1.0);"
		"}";
	const char*fs = 
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
	diffuseSpecular->bindUniform(0,"mvp");
	pipeline->addShader(diffuseSpecular,"test");

}
void Game::setup(){
	pipeline = new Pipeline();
	loadShaders(pipeline);

	//setting up physics
	this-> world = new World();
	
	//init stuff here
	models = new std::vector<Model*>();
	cam = new Camera(0,300,-200,0,0,0,1280,720);
	walls = new std::vector<gWall*>();
	
	gWall *wall = new gWall(1,5,glm::vec3(0,0,5));
	walls->push_back(wall);
	wall->setBlock(0,1,glm::vec3(1.0,0.0,0.0));
	
	wall->setBlock(3,1,glm::vec3(0.0,1.0,0.0));

	
	gWall *wall2 = new gWall(1,10,glm::vec3(0,0,3));
	walls->push_back(wall2);
	wall2->setBlock(0,1,glm::vec3(1.0,0.0,0.0));
	wall2->setBlock(1,2,glm::vec3(0,0.0,1.0));
	wall2->setBlock(3,1,glm::vec3(0.0,1.0,0.0));
	wall2->setBlock(5,1,glm::vec3(0.0,1.0,0.0));
	
	WallMeshGenerator generator = WallMeshGenerator();
	
	renderer = new WallRenderer(walls,cam);
	geomRenderer = new GeometryRenderer(cam,models);

	
	StaticModel*model = new StaticModel();
	StaticModel*model2 = new StaticModel();
	StaticModel* model3 = new StaticModel();
/*	model->setPosition(glm::vec3(2,0,10));
	model2->setPosition(glm::vec3(100,0,10));

	model3->setPosition(glm::vec3(-100,0,10));*/
	model->setShader("test");
	model2->setShader("test");
	model3->setShader("test");
	geomRenderer->registerModel(model2,pipeline);
	geomRenderer->registerModel(model,pipeline);
	geomRenderer->registerModel(model3,pipeline);
	//geomRenderer->registerModel(model2);


	Assimp::Importer imp = Assimp::Importer();
	
	const std::string path = std::string("E:\\programming\\games\\PowerPong\\Debug\\duck.dae");
	//const std::string path = std::string("E:\\programming\\games\\PowerPong\\Debug\\teapots.dae");

	const aiScene *scene = imp.ReadFile(path.c_str(),aiProcessPreset_TargetRealtime_Fast);



	Node* modelNode = model->initFromScene(scene);
	modelNode->move(glm::vec3(2,0,10));
	Node*model2Node = model2->initFromScene(scene);
	model2Node->move(glm::vec3(100,0,10));
	Node*model3Node = model3->initFromScene(scene);
	model3Node->move(glm::vec3(-100,0,10));

	rootNode = new Node();
	rootNode->addChild(modelNode);
	rootNode->addChild(model2Node);
	rootNode->addChild(model3Node);

	rootNode->move(glm::vec3(10,0,0));
	



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
	//renderer->render();
	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	
	geomRenderer->render(pipeline,rootNode);
	
	swapBuffers();
}


void Game::update(double dt){
	cam->tick();
	//world-> update(dt);
	postRedisplay();
	
}