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
	StaticModel(GLint*attributes = nullptr);
	~StaticModel(void);
	Buffer *getVertexBuffer();
	Buffer*getNormalBuffer();
	Buffer * getTexcoordBuffer();
	Buffer * getElementBuffer();
	void setAttributes(GLint*attributes);
	void setAttributes(GLint coord3D,GLint normal3D,GLint texcoord2D);
	void render(Pipeline *pipeline);
	Node* initFromScene(const aiScene * scene,Node * modelRoot);
	void initFromMesh(aiMesh * mesh,aiMaterial** materials,bool moveTocenter = true);
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
	GLuint shadowVao;
	int numVertices;
	int numIdices;
	int shaderName;
	void shadowPass(Pipeline*pipeline);
	

};

#endif