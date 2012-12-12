#pragma once

class Screen
{


public:
	Screen(void);
	~Screen(void);

	virtual void update() = 0;
	virtual void render() = 0;


private:

};
