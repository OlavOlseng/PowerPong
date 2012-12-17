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
	virtual void render() = 0;
	virtual void setAttributes(GLint vertexAttrib,GLint normalAttrib,GLint texAttrib)=0 ;
	virtual GLuint* getVao() = 0;
	
	
private:
	glm::vec4 modelMatrix;
	glm::vec3 position;
	
	
};

#endif