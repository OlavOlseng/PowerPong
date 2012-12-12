#ifndef game_h
#define game_h

#include "BaseGame.h"


class Game: public BaseGame
{
public:
	Game();
	Game(int argc,char * argv[]);
	~Game(void);

private:
	int width,height;
protected:

	void reshape(int width, int height);
	void draw();
	void update(double dt);
};

#endif
