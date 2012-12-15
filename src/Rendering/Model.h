#ifndef model_h
#define model_h
#include "../GLtools/GLTriangleBatch.h"
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Buffer.h";
class Model
{
public:
	Model();
	~Model(void);


	virtual glm::vec3 *getPosition();
	virtual void setPosition(glm::vec3 position);
	virtual glm::mat4 getModelMatrix();
	
	
	Buffer *getVertexBuffer();
	Buffer*getNormalBuffer();
	Buffer * getTexcoordBuffer();
	Buffer * getElementBuffer();

private:
	glm::vec4 modelMatrix;
	glm::vec3 position;
	Buffer *vertexBuffer;
	Buffer*normalBuffer;
	Buffer * texcoordBuffer;
	Buffer * elementBuffer;
	
};

#endif