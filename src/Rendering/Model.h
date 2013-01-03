#ifndef model_h
#define model_h
#include "../GLtools/GLTriangleBatch.h"
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\euler_angles.hpp>
#include "Buffer.h";
#include "Pipeline.h"
#include <string>
#include <memory>
#include "../ResourceManager.h"
class Model
{
public:
	Model();
	~Model(void);


	virtual glm::vec3 getPosition();
	virtual glm::vec3  getRotation();
	virtual glm::vec3  getScale();

	virtual void setPosition(glm::vec3 position);
	virtual void setRotation(glm::vec3 rotation);
	virtual void setScale(glm::vec3 scale);

	virtual glm::mat4 getModelMatrix();
	virtual void render(Pipeline *pipeline) = 0;
	virtual void setAttributes(GLint*attributes)=0 ;
	virtual GLuint* getVao() = 0;
	virtual void setShader(int id) = 0;
	virtual int getShader() = 0;
	virtual void setResourceManager(std::shared_ptr<ResourceManager> resourceManager);
	virtual std::shared_ptr<ResourceManager> getResourceManager();
protected:
	glm::vec4 modelMatrix;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	std::shared_ptr<ResourceManager> resourceManager;
	
	
};

#endif