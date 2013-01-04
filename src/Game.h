#ifndef game_h
#define game_h

#include "BaseGame.h"

#include "Graphics\gWall.h"
#include "camera\camera.h";

#include "Rendering\Model.h"
#include "GLtools\GLTools.h"
#include "GLtools\GLTriangleBatch.h"
#include "Rendering\GeometryRenderer.h"
#include "Rendering\StaticModel.h"

#include <assimp\scene.h>
#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>
#include "World\World.h"
#include "Entities\Block.h"
#include "Rendering\Pipeline.h"
#include "Rendering\Node.h"
#include "ResourceManager.h"
class Game: public BaseGame
{
public:
	Game();
	Game(int argc,char * argv[]);
	~Game(void);
	World* world;
	std::string binaryPath;
private:
	int width,height;
	std::vector<gWall*> *walls;
	std::vector<Model*>*models;

	Shader*diffuseSpecular;
	Shader*wallShader;
	GeometryRenderer * geomRenderer;
	Camera*cam;

	Pipeline *pipeline;
	void loadShaders(Pipeline*pipeline);

	Node*rootNode;
	StaticModel*model;

protected:

	void reshape(int width, int height);
	void draw();
	void update(double dt);
	void setup();
	
};

#endif
