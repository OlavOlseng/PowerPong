#ifndef TEXTURED_QUAD_H
#define TEXTURED_QUAD_H
#include "Model.h"
class TexturedQuad:public Model
{
public:
	TexturedQuad(void);
	~TexturedQuad(void);

	void render(Pipeline *pipeline);
	void setAttributes(GLint*attributes,GLint*shadowAttributes=nullptr);
	void init(Texture * texture);
private:
	Buffer * vertexBuffer;
	Buffer * textureBuffer;
	Texture * texture;
	GLuint vao;
	Shader * shader;
};

#endif