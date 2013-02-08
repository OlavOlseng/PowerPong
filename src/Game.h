#ifndef game_h
#define game_h

#include "src\BaseGame.h"




#include "src\Rendering\Models\Model.h"

#include "src\Rendering\Models\StaticModel.h"

#include <assimp\scene.h>
#include <assimp\Importer.hpp>
#include <assimp\DefaultLogger.hpp>
#include <assimp\postprocess.h>
#include "World\World.h"
#include "Entities\Block.h"
#include "src\Rendering\SceneGraph\Pipeline.h"
#include "src\Rendering\SceneGraph\Node.h"
#include "src\Rendering\Models\ResourceManager.h"
#include "src\Rendering\Screen\ScreenManager.h"
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
	std::shared_ptr<ResourceManager> resManager;
	


protected:
	void reshape(int width, int height);
	void draw();
	void update(double dt);
	void setup();

	



};

#endif
