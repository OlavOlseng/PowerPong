#ifndef NODE_H
#define NODE_H
#include "Model.h"
#include "Pipeline.h"
#include <vector>
#include <glm\glm.hpp>


#include "Light.h"
class Node
{
public:
	Node(void);
	~Node(void);

	void addChild(Node *node);
	void addChild(Model*model);
	void addLight(DirectionalLight*light);
	void render(Pipeline *pipeline);

	void setParent(Node *parent);

	void move(glm::vec3 amount);
	void rotate(glm::vec3 amount);
	void scale(glm::vec3 amount);

	void setPosition(glm::vec3 position);
	void setRotation(glm::vec3 rotation);
	void setScale(glm::vec3 scale);

	std::vector<Node*> *getChildren();

private:
	std::vector<Node*> *children;
	Node *parent;
	std::vector<Model*> *leaves;
	std::vector<DirectionalLight*> directionalLights;

	glm::vec3 localPosition;
	glm::vec3 localRotation;
	glm::vec3 localScale;


};



#endif