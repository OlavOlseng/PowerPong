#ifndef LINE_MODEL_H
#define LINE_MODEL_H
#include "Model.h"
#include <vector>

class LineModel:public Model
{
public:
	LineModel(void);
	~LineModel(void);
	void addLine(glm::vec3 &from ,glm::vec3 &to,glm::vec3 &color);
	void clearLines();
	void bufferLines();
	void init();
	virtual void render(Pipeline *pipeline);
	void setAttributes(GLint*attributes,GLint*shadowAttributes=nullptr);
private:
	std::vector<glm::vec3> * lines;
	std::vector<glm::vec3> * colors;
	Buffer * lineBuffer;
	Buffer * colorBuffer;
	GLuint vao;
	Shader * shader;

	int numVertices;


};

#endif