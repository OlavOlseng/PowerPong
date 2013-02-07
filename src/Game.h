#ifndef game_h
#define game_h

#include "BaseGame.h"




#include "Rendering\Models\Model.h"

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
#include "Screen\ScreenManager.h"
#include "Screen\GameScreen.h"

class Game: public BaseGame
{
public:
	Game();
	
	Game(int argc,char * argv[]);
	~Game(void);
	World* world;
	std::string binaryPath;

private:
	ScreenManager * screenManager;
	GameScreen * gameScreen;
	int width,height;


	
	

	Pipeline *pipeline;
	


protected:
	void reshape(int width, int height);
	void draw();
	void update(double dt);
	void setup();

	std::shared_ptr<ResourceManager> resManager ;



};

#endif
