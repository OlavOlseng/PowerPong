#ifndef NODE_H
#define NODE_H
#include <glm/gtc/matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\quaternion.hpp>
#include "Pipeline.h"
#include <vector>
#include <glm\glm.hpp>
#include <glm\gtx\euler_angles.hpp>

#include "../Models/Light.h"
class Node
{
public:
	Node(void);
	~Node(void);

	void addChild(Node *node);
	
	void addLight(DirectionalLight*light);
	void addLight(PointLight*light);
	virtual void render(Pipeline *pipeline);

	void setParent(Node *parent);

	virtual void move(glm::vec3 &amount);
	virtual void rotate(glm::vec3 &amount);
	virtual void scale(glm::vec3 &amount);

	virtual void setPosition(glm::vec3 &position);
	virtual void setOrientation(glm::vec3 &orientation);
	virtual void setScale(glm::vec3 &scale);

	
	
	
	glm::mat4 getCachedModelMatrix();

	virtual glm::vec3 getPosition();
	virtual glm::vec3 getScale();
	virtual glm::vec3 getOrientation();
	
	virtual glm::mat4 getModelMatrix();
	std::vector<Node*> *getChildren();
	bool isChanged();
	void setChanged(bool value);


private:
	
	std::vector<Node*> *children;
	Node *parent;
	
	std::vector<DirectionalLight*> directionalLights;
	std::vector<PointLight*> pointLights;
	glm::vec3 localPosition;
	glm::vec3 localOrientation;
	glm::vec3 localScale;
	glm::mat4 cachedModelMatrix;

	bool changed;

protected:
	void setCachedModelMatrix(glm::mat4 model);
	


};



#endif