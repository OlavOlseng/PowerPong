#ifndef NODE_H
#define NODE_H
#include "Model.h"
#include "Pipeline.h"
#include <vector>
#include <glm\glm.hpp>
class Node
{
public:
	Node(void);
	~Node(void);

	void addChild(Node *node);
	void addChild(Model*model);
	void render(Pipeline *pipeline);

	void setParent(Node *parent);
	void move(glm::vec3 amount);
	glm::vec3 getGlobalPosition();
private:
	std::vector<Node*> *children;
	Node *parent;
	std::vector<Model*> *leaves;
	glm::vec3 globalPosition;
	glm::vec3 localPosition;

};

#endif