#ifndef renderer_base__h
#define renderer_base_h
#include "Model.h"
#include "Pipeline.h"
class Renderer
{
public:
	virtual void registerModel(Model *model,Pipeline *pipeline) = 0;
};

#endif