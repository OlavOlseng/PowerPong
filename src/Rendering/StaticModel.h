#ifndef static_model_h
#define static_model_h

#include <GL\glew.h>
#include <GL\freeglut.h>;
#include <GL\GL.h>
#include <GL\GLU.h>

#include "Model.h"
#include "Buffer.h"

#include <assimp\scene.h>

#include "Node.h"
#include "ShaderUniforms.h"
#include "ShaderAttributes.h"
#include "../ResourceManager.h"
#include <memory>
class StaticModel:public Model
{
public:
	StaticModel(void);
	~StaticModel(void);
	Buffer *getVertexBuffer();
	Buffer*getNormalBuffer();
	Buffer * getTexcoordBuffer();
	Buffer * getElementBuffer();
	void setAttributes(GLint*attributes);
	void render(Pipeline *pipeline);
	Node* initFromScene(const aiScene * scene);
	void initFromMesh(aiMesh * mesh,aiMaterial** materials);
	GLuint* getVao();
	void setVao(GLuint vao);
	

	void setShader(int id);
	int getShader();
private:
	Node*modelRoot;
	GLuint textureHandle;
	Buffer *vertexBuffer;
	Buffer*normalBuffer;
	Buffer * texcoordBuffer;
	Buffer * elementBuffer;
	StaticModel*children;
	GLuint vao;
	int numVertices;
	int numIdices;
	int shaderName;
	

};

#endif