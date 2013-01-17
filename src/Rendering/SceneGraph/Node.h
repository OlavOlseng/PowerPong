#ifndef NODE_H
#define NODE_H
#include <glm/gtc/matrix_transform.hpp>
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

	void move(glm::vec3 amount);
	void rotate(glm::vec3 amount);
	void scale(glm::vec3 amount);

	void setPosition(glm::vec3 position);
	void setRotation(glm::vec3 rotation);
	void setScale(glm::vec3 scale);

	glm::vec3 getPosition();
	glm::vec3 getScale();
	glm::vec3 getRotation();

	std::vector<Node*> *getChildren();

private:
	std::vector<Node*> *children;
	Node *parent;
	
	std::vector<DirectionalLight*> directionalLights;
	std::vector<PointLight*> pointLights;
	glm::vec3 localPosition;
	glm::vec3 localRotation;
	glm::vec3 localScale;
	


};



#endif