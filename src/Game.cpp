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
		"varying vec4 f_normal;"
		"varying vec2 f_texcoord;"
		"varying vec4 f_position;"
		"void main()"
		"{"
		"f_position = modelMatrix*vec4(coord3d,1.0);"
		"f_normal = normalize(modelMatrix*vec4(normal3d.xyz,0.0));"
		"f_texcoord = texcoord2d;"
		"gl_Position = mvp*vec4(coord3d.xyz,1.0);"
		"}";
	 char*fs = 
		"varying vec4 f_normal;"
		"varying vec2 f_texcoord;"
		"varying vec4 f_position;"
		"uniform sampler2D tex;"
		"uniform int numDirLights;"
		"uniform int numPointLights;"
		"struct DirectionalLight{"
		"vec4 diffuse;"
		"vec4 specular;"
		"vec4 direction;"
		"};"
		"struct PointLight{"
		"vec4 diffuse;"
		"vec4 specular;"
		"vec4 position;"
		"float constantAttenuation;"
		"float linearAttenuation;"
		"float quadraticAttenuation;"
		"};"
		"uniform DirectionalLight dirLights[10];"
		"uniform PointLight pointLights[10];"
		"struct Material{"
		"vec4 diffuse;"
		"vec4 ambient;"
		"vec4 specular;"
		"float shininess;"
		"};"
		"uniform Material material;"
		"const vec4 globalAmbient = vec4(0.2,0.2,0.2,0.0);"
		"uniform vec4 viewDir;"


		"void main(){"
		"vec4 diffuseLight;"
		"vec4 specularLight;"
		"vec4 direction;"
		"vec4 vecToLight;"
		"DirectionalLight dirLight;"
		"PointLight pointLight;"
		"float diffuseFactor;"
		"float specularFactor;"
		"float attenuation = 0.0;"
		"float distance = 0.0;"
		"vec4 ambientLight = material.ambient*globalAmbient;"
		"for(int i = 0;i<numDirLights;i++){"
		"	dirLight = dirLights[i];"
		"	diffuseFactor = clamp(dot(f_normal,-dirLight.direction),0.0,1.0);"
		"	if(diffuseFactor > 0.0){"
		"	diffuseLight += material.diffuse*dirLight.diffuse*diffuseFactor;"
		"	specularFactor = clamp(dot(reflect(-dirLight.direction,f_normal),viewDir),0.0,1.0);"
		"	if(specularFactor >0.0)"
		"		specularLight += material.specular*dirLight.specular*pow(specularFactor,material.shininess);"
		"}}"
		"for(int i = 0;i<numPointLights;i++){"
		"	pointLight = pointLights[i];"
		"	vecToLight= f_position - pointLight.position;"
		"	distance = length(vecToLight);"
		"	direction = normalize(-vecToLight);"
		"	attenuation = 1.0/(pointLight.constantAttenuation + pointLight.linearAttenuation*distance + pointLight.quadraticAttenuation*distance*distance);"

		"	diffuseFactor = clamp(dot(f_normal,direction),0.0,1.0);"
		"	if(diffuseFactor > 0.0){"
		"		diffuseLight += material.diffuse*pointLight.diffuse*diffuseFactor*attenuation;"
		"	specularFactor = clamp(dot(reflect(direction,f_normal),viewDir),0.0,1.0);"
			"if(specularFactor >0.0)"
		"		specularLight += material.specular*pointLight.specular*pow(specularFactor,material.shininess)*attenuation;"
		"}"
		"}"
		"gl_FragColor =texture2D(tex,f_texcoord)*(diffuseLight+ specularLight + ambientLight);"
		"}";

	diffuseSpecular = new Shader(vs,fs);
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

	vs = 
		"attribute vec3 coord3d;"
		"attribute vec3 color3d;"
		"attribute vec3 normal3d;"
		"attribute float blockType;"
		"uniform mat4 mvp;"
		"uniform mat4 modelMatrix;"
		"varying vec3 f_color;"
		"varying vec4 texcoord;"
		"varying int f_type;"
		"varying vec4 f_normal;"
		"varying vec4 f_position;"
		"void main()"
		"{"
		"texcoord = vec4(coord3d,blockType);"
		"f_type = int(blockType);"
		"f_color = color3d;"
		"f_normal = modelMatrix*vec4(normal3d.xyz,0.0);"
		"f_position = modelMatrix*vec4(coord3d.xyz,1.0);"
		"gl_Position = mvp*vec4(coord3d.xyz,1.0);"

		"}";
	fs = 
		"varying vec3 f_color;"
		"varying vec4 texcoord;"
		"varying int f_type;"
		"uniform int numDirLights;"
		"uniform int numPointLights;"
		"struct DirectionalLight{"
		"vec4 diffuse;"
		"vec4 specular;"
		"vec4 direction;"
		"};"
		"struct PointLight{"
		"vec4 diffuse;"
		"vec4 specular;"
		"vec4 position;"
		"float constantAttenuation;"
		"float linearAttenuation;"
		"float quadraticAttenuation;"
		"};"
		"uniform DirectionalLight dirLights[10];"
		"uniform PointLight pointLights[10];"

		"struct Material{"
		"vec4 diffuse;"
		"vec4 ambient;"
		"vec4 specular;"
		"float shininess;"
		"};"
		"uniform Material material;"
		"const vec4 globalAmbient = vec4(0.2,0.2,0.2,0.0);"
		"uniform sampler2D tex;"

		"uniform float stepSize;"
		"uniform vec4 viewDir;"
		"varying vec4 f_normal;"
		"varying vec4 f_position;"

		"void main(){"
		"vec4 diffuseLight;"
		"vec4 specularLight;"
		"vec4 direction;"
		"vec4 vecToLight;"
		"DirectionalLight dirLight;"
		"PointLight pointLight;"
		"float diffuseFactor;"
		"float specularFactor;"
		"float attenuation = 0.0;"
		"float distance = 0.0;"
		
		"vec4 ambientLight = material.ambient*globalAmbient;"
		"for(int i = 0;i<numDirLights;i++){"
		"	dirLight = dirLights[i];"

		"	diffuseFactor = clamp(dot(f_normal,-dirLight.direction),0.0,1.0);"
		"	if(diffuseFactor > 0.0){"
		"	diffuseLight += material.diffuse*dirLight.diffuse*diffuseFactor;"
		"	specularFactor = clamp(dot(reflect(-dirLight.direction,f_normal),viewDir),0.0,1.0);"
		"	if(specularFactor >0.0)"
		"		specularLight += material.specular*dirLight.specular*pow(specularFactor,material.shininess);"
		"}}"
		"for(int i = 0;i<numPointLights;i++){"
		"	pointLight = pointLights[i];"
		"	vecToLight= f_position - pointLight.position;"

		"	distance = length(vecToLight);"
		"	direction = normalize(-vecToLight);"
		"	attenuation = 1.0/(pointLight.constantAttenuation + pointLight.linearAttenuation*distance + pointLight.quadraticAttenuation*distance*distance);"
		
		"	diffuseFactor = clamp(dot(f_normal,direction),0.0,1.0);"
		"	if(diffuseFactor > 0.0){"
		"		diffuseLight += material.diffuse*pointLight.diffuse*diffuseFactor*attenuation;"
		"	specularFactor = clamp(dot(reflect(direction,f_normal),viewDir),0.0,1.0);"
		"	if(specularFactor >0.0)"
		"		specularLight += material.specular*pointLight.specular*pow(specularFactor,material.shininess)*attenuation;"
		"}"
		"}"
		"vec4 color;"
		"	if(texcoord.w >=0.0){"
		"		color = texture2D(tex,vec2((fract(texcoord.x + texcoord.z)+ texcoord.w)*stepSize ,fract(texcoord.y)));"
		"	}else{"
		"		color = texture2D(tex,vec2((fract(texcoord.x) - texcoord.w)*stepSize ,fract(texcoord.z)));"
		"}"
		"if(texcoord.w == 0.0) "
		"{"
		"	color = vec4(f_color,1.0);"
		"}"
		"gl_FragColor = color*(diffuseLight + specularLight + ambientLight);"
		"}";
	


	wallShader = new Shader(vs,fs);

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

}
void Game::setup(){

	
	Assimp::DefaultLogger::create("",Assimp::Logger::VERBOSE);

	

	
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
	
	const std::string path = std::string(resManager->getWorkingDirectiory() +"duck.dae");
	const aiScene *scene = imp.ReadFile(path.c_str(),aiProcessPreset_TargetRealtime_Quality);
	Node* modelNode = model->initFromScene(scene);
	Node*model2Node = model2->initFromScene(scene);
	Node*model3Node = model3->initFromScene(scene);
	rootNode->addChild(modelNode);
	rootNode->addChild(model2Node);
	rootNode->addChild(model3Node);	
	imp.FreeScene();
	

	const aiScene * sphereScene = imp.ReadFile(resManager->getWorkingDirectiory()+"sphere.irr",aiProcessPreset_TargetRealtime_Quality);
	
	
	StaticModel*sphereModel = new StaticModel(diffuseSpecular->getAttributes());
	sphereModel->setResourceManager(resManager);
	sphereModel->setShader(diffuseSpecularHandle);
	
	Node*sphereNode = sphereModel->initFromScene(sphereScene);
	sphereNode->setScale(glm::vec3(20,20,20));
	sphereNode->move(glm::vec3(0,-20,20));
	rootNode->addChild(sphereNode);
	imp.FreeScene();
	
	
	
	const aiScene * spiderScene= imp.ReadFile(resManager->getWorkingDirectiory()+"spider.obj",aiProcessPreset_TargetRealtime_Quality);

	StaticModel*spiderModel= new StaticModel(diffuseSpecular->getAttributes());
	spiderModel->setResourceManager(resManager);
	spiderModel->setShader(diffuseSpecularHandle);
	
	Node*spiderNode = spiderModel->initFromScene(spiderScene);
	spiderNode->setScale(glm::vec3(0.1,0.1,0.1));
	spiderNode->move(glm::vec3(0,5,0));
	rootNode->addChild(spiderNode);

	imp.FreeScene();
	
	 sun = new DirectionalLight();
	 sun->diffuse = glm::vec4(0.,0.0,0.0,1.0);
	 sun->specular = glm::vec4(1.0,1.0,1.0,1.0);

	sun->direction = glm::normalize(glm::vec4(0.0,-1.0,0.0,.0));
	

	DirectionalLight* light2 = new DirectionalLight();
	light2 ->diffuse = glm::vec4(0.0,0.0,0.0,0.0);
	 light2 ->specular = glm::vec4(1.0,1.0,1.0,1.0);
	
	light2 ->direction = glm::normalize(glm::vec4(0.0,-1.0,0.0,.0));
	

	PointLight * pointlight = new PointLight();
	pointlight->diffuse = glm::vec4(1.0,1.0,1.0,1.0);
	//pointlight->specular = glm::vec4(1.0,1.0,1.0,1.0);

	pointlight->position = glm::vec4(2.0,2,0.0,1.0);
	pointlight->constantAttenuation =1.0;
	pointlight->linearAttenutation = 0.007;
	pointlight->quadraticAttenuation = 0.0002;


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
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glClearColor(0.4,0.4,0.4,1.0);
	glEnable(GL_DEPTH_TEST);
	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	pipeline->clear();
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