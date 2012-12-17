#ifndef game_h
#define game_h

#include "BaseGame.h"
#include "Rendering\WallRenderer.h"
#include "Graphics\gWall.h"
#include "camera\camera.h";

#include "Rendering\Model.h"
#include "GLtools\GLTools.h"
#include "GLtools\GLTriangleBatch.h"
#include "Rendering\GeometryRenderer.h"

#include "World\World.h"
#include "Entities\Block.h"

class Game: public BaseGame
{
public:
	Game();
	Game(int argc,char * argv[]);
	~Game(void);
	World* world;

private:
	int width,height;
	std::vector<gWall*> *walls;
	std::vector<Model*>*models;
	WallRenderer*renderer;
	GeometryRenderer * geomRenderer;
	Camera*cam;

protected:

	void reshape(int width, int height);
	void draw();
	void update(double dt);
	void setup();
};

#endif
