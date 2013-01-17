#ifndef game_h
#define game_h

#include "BaseGame.h"

#include "Rendering\Voxel\Volume\gWall.h"
#include "camera\camera.h";

#include "Rendering\Models\Model.h"
#include "GLtools\GLTools.h"
#include "GLtools\GLTriangleBatch.h"

#include "Rendering\Models\StaticModel.h"

#include <assimp\scene.h>
#include <assimp\Importer.hpp>
#include <assimp\DefaultLogger.hpp>
#include <assimp\postprocess.h>
#include "World\World.h"
#include "Entities\Block.h"
#include "Rendering\SceneGraph\Pipeline.h"
#include "Rendering\SceneGraph\Node.h"
#include "Rendering\Models\ResourceManager.h"
#include "Rendering\Voxel\Volume\gWall.h"
#include "Rendering\Voxel\SurfaceExtractors\WallMeshGenerator.h"

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
	Shader*shadowShader;
	Shader*voxelShader;

	Camera*cam;

	Pipeline *pipeline;
	void loadShaders(Pipeline*pipeline);

	Node*rootNode;
	StaticModel*model;
	DirectionalLight * sun;

protected:
	unsigned int diffuseSpecularHandle;
	unsigned int wallShaderHandle;
	unsigned int shadowShaderHandle;
	unsigned int voxelShaderHandle;
	void reshape(int width, int height);
	void draw();
	void update(double dt);
	void setup();

	std::shared_ptr<ResourceManager> resManager ;

	//shadowmapTesting
	GLuint frameBufferHandle;
	GLuint depthTexture;
	
};

#endif
