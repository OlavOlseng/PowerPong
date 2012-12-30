#include "StaticModel.h"


StaticModel::StaticModel(void)
{

	this->vertexBuffer = new Buffer(Buffer::ARRAY_BUFFER,Buffer::STATIC,3,GL_FLOAT);
	this->normalBuffer= new Buffer(Buffer::ARRAY_BUFFER,Buffer::STATIC,3,GL_FLOAT);
	this->texcoordBuffer = new Buffer(Buffer::ARRAY_BUFFER,Buffer::STATIC,2,GL_FLOAT);
	this->elementBuffer= new Buffer(Buffer::ELEMENT_BUFFER,Buffer::STATIC,0,0);

	glGenVertexArrays(1,&vao);
	glBindVertexArray(vao);
	glBindVertexArray(0);
}


StaticModel::~StaticModel(void)
{
}

Node* StaticModel::initFromScene(const aiScene * scene){
	
	
		Node * modelRoot = new Node();
		if(scene->mNumMeshes > 1){

		}else{

			initFromMesh(scene->mMeshes[0],scene->mMaterials);
		}
		modelRoot->addChild(this);
	
	
		return modelRoot;
}
void StaticModel::initFromMesh(aiMesh * mesh,aiMaterial** materials){
		

	glm::vec3* vertices = new glm::vec3[mesh->mNumVertices];
	GLushort * indices = new GLushort[mesh->mNumFaces*3];
	glm::vec2 *texCoord = new glm::vec2[mesh->mNumVertices];
	glm::vec3 * normals = new glm::vec3[mesh->mNumVertices];
	for(int i = 0;i<mesh->mNumVertices;i++){
	
			aiVector3D p1 = mesh->mVertices[i];
			vertices[i] =(glm::vec3(p1.x,p1.y,p1.z));
			aiVector3D tex = mesh->mTextureCoords[0][i];
			texCoord[i] =glm::vec2(tex.x,tex.y);
			aiVector3D norm = mesh->mNormals[i];
			normals[i] = glm::vec3(norm.x,norm.y,norm.z);
	}

	

	int j = 0;

	for(int i =0;	i<mesh->mNumFaces;i++){
			aiFace face = mesh->mFaces[i];
			
			
			indices[j++] = (face.mIndices[0]);
			indices[j++] = (face.mIndices[1]);
			indices[j++] = (face.mIndices[2]);
			
	}
	


	aiMaterial* material = materials[mesh->mMaterialIndex];
	aiColor3D diffuseColor(1.0,1.0,1.0);
	material->Get(AI_MATKEY_COLOR_DIFFUSE,diffuseColor);



	aiString path;
	material->GetTexture(aiTextureType_DIFFUSE,0,&path);

	GLuint diffuseTexHandle = ShaderUtil::loadTexture("E:\\programming\\games\\PowerPong\\Debug" +std::string(path.data),0);
	

	
	glBindVertexArray(vao);

	glBindTexture(GL_TEXTURE_2D,diffuseTexHandle);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	vertexBuffer->setData(vertices,sizeof(glm::vec3)*mesh->mNumVertices);
	texcoordBuffer->setData(texCoord,sizeof(glm::vec2)*mesh->mNumVertices);
	normalBuffer->setData(normals,sizeof(glm::vec3)*mesh->mNumVertices);
	elementBuffer->setData(indices,sizeof(GLushort)*mesh->mNumFaces*3);
	glBindVertexArray(0);
	

	this->numVertices = mesh->mNumVertices;

	this->numIdices = mesh->mNumFaces*3;


	delete[] vertices;
	delete[] texCoord;
	delete[] normals;
	delete indices;

}

GLuint* StaticModel::getVao(){
		return &vao;

}

void StaticModel::setAttributes(GLint vertexAttrib,GLint normalAttrib,GLint texAttrib){


	this->vertexBuffer->setVertexAttribute(vertexAttrib);
	this->normalBuffer->setVertexAttribute(normalAttrib);
	this->texcoordBuffer->setVertexAttribute(texAttrib);
	this->elementBuffer->setVertexAttribute(-1);
	
};


void StaticModel::setShader(std::string name){
	this->shaderName = name;

}
std::string StaticModel::getShader(){
	return this->shaderName;

}
void StaticModel::setVao(GLuint vao){
	this->vao = vao;
}
void StaticModel::render(Pipeline *pipeline){

	pipeline->useShader(shaderName);
	Shader*shader = pipeline->getActiveShader();
	shader->bind();
	glm::mat4 mvp  = pipeline->getProjection()*pipeline->getView()*this->getModelMatrix();
	shader->setUniformMat4f(0,glm::value_ptr(mvp));
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES,elementBuffer->getBufferSize()/sizeof(GLushort),GL_UNSIGNED_SHORT,0);
	glBindVertexArray(0);
	shader->unbind();
	
};

Buffer *StaticModel::getVertexBuffer(){
	return this->vertexBuffer;
}
Buffer*StaticModel::getNormalBuffer(){
	return this->normalBuffer;
}
Buffer * StaticModel::getTexcoordBuffer(){
	return this->texcoordBuffer;
}
Buffer * StaticModel::getElementBuffer(){
	return this->elementBuffer;
}
