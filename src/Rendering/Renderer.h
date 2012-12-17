#ifndef renderer_base__h
#define renderer_base_h
#include "Model.h"
class Renderer
{
public:
	virtual void registerModel(Model *) = 0;
};

#endif