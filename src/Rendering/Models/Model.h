#ifndef model_h
#define model_h
#include "../GLtools/GLTriangleBatch.h"
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\euler_angles.hpp>
#include "../Shaders/Buffer.h";
#include "../SceneGraph/Pipeline.h"
#include <string>
#include <memory>
#include "ResourceManager.h"
#include "Material.h"
#include "../SceneGraph/Node.h"
class Model:public Node
{
public:
	Model();
	~Model(void);





	virtual glm::mat4 getModelMatrix();
	virtual void render(Pipeline *pipeline) = 0;
	virtual void setShader(int id) = 0;
	virtual void setAttributes(GLint*attributes,GLint*shadowAttributes=nullptr)=0 ;
	
	virtual int getShader() = 0;

	virtual void setResourceManager(std::shared_ptr<ResourceManager> resourceManager);
	virtual std::shared_ptr<ResourceManager> getResourceManager();
	virtual Material *getMaterial();

protected:
	glm::vec4 modelMatrix;

	std::shared_ptr<ResourceManager> resourceManager;
	Material material;
	
};

#endif