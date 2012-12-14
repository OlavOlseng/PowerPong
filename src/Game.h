#ifndef game_h
#define game_h

#include "BaseGame.h"
#include "Rendering\WallRenderer.h"
#include "Entities\Wall.h"
#include "camera\camera.h";
class Game: public BaseGame
{
public:
	Game();
	Game(int argc,char * argv[]);
	~Game(void);

private:
	int width,height;
	std::vector<Wall*> *walls;
	WallRenderer*renderer;
	Camera*cam;

protected:

	void reshape(int width, int height);
	void draw();
	void update(double dt);
	void setup();
};

#endif
