#ifndef static_model_h
#define static_model_h

#include <GL\glew.h>
#include <GL\freeglut.h>;
#include <GL\GL.h>
#include <GL\GLU.h>

#include "Model.h"
#include "Buffer.h"

#include <assimp\scene.h>
#include "glm/gtc/type_ptr.hpp"
#include "Node.h"
class StaticModel:public Model
{
public:
	StaticModel(void);
	~StaticModel(void);

	Buffer *getVertexBuffer();
	Buffer*getNormalBuffer();
	Buffer * getTexcoordBuffer();
	Buffer * getElementBuffer();
	void setAttributes(GLint vertexAttrib,GLint normalAttrib,GLint texAttrib);
	void render(Pipeline *pipeline);
	Node* initFromScene(const aiScene * scene);
	void initFromMesh(aiMesh * mesh,aiMaterial** materials);
	GLuint* getVao();
	void setVao(GLuint vao);


	void setShader(std::string name);
	std::string getShader();
private:

	Buffer *vertexBuffer;
	Buffer*normalBuffer;
	Buffer * texcoordBuffer;
	Buffer * elementBuffer;
	StaticModel*children;
	GLuint vao;
	int numVertices;
	int numIdices;
	std::string shaderName;
	GLuint textureHandle;

};

#endif