#include "StaticModel.h"


StaticModel::StaticModel(void)
{

	this->vertexBuffer = new Buffer(Buffer::ARRAY_BUFFER,Buffer::STATIC,3,GL_FLOAT);
	this->normalBuffer= new Buffer(Buffer::ARRAY_BUFFER,Buffer::STATIC,3,GL_FLOAT);
	this->texcoordBuffer = new Buffer(Buffer::ARRAY_BUFFER,Buffer::STATIC,2,GL_FLOAT);
	this->elementBuffer= new Buffer(Buffer::ELEMENT_BUFFER,Buffer::STATIC,0,0);

	glGenVertexArrays(1,&vao);
	
}


StaticModel::~StaticModel(void)
{
}

void StaticModel::setResourceManager(std::shared_ptr<ResourceManager> resourceManager){

	this->resourceManager = resourceManager;
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
#include "../BaseGame.h"
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
	
	GLuint diffuseTexHandle = ShaderUtil::loadTexture(resourceManager->getWorkingDirectiory()+ std::string(path.data),0);
	

	//Need to find the center of the model
	//and then adjust the vertices
	
	//Can find the center by finding the average of min/max
	glm::vec3 min(vertices[0]),max(vertices[0]);
	for(int i = 0;i<mesh->mNumVertices;i++){
		glm::vec3 &vertex = vertices[i];
		if(vertex.x < min.x) min.x = vertex.x;
		if(vertex.y < min.y) min.y = vertex.y;
		if(vertex.z < min.z) min.z = vertex.z;

		if(vertex.x > max.x) max.x = vertex.x;
		if(vertex.y > max.y) max.y = vertex.y;
		if(vertex.z > max.z) max.z = vertex.z;
	}
	glm::vec3 avg = (min + max);
	avg /=2;
	for(int i = 0;i<mesh->mNumVertices;i++){
		vertices[i] -= avg;
	}

	min = vertices[0];
	max = vertices[0];
	for(int i = 0;i<mesh->mNumVertices;i++){
		glm::vec3 &vertex = vertices[i];
		if(vertex.x < min.x) min.x = vertex.x;
		if(vertex.y < min.y) min.y = vertex.y;
		if(vertex.z < min.z) min.z = vertex.z;

		if(vertex.x > max.x) max.x = vertex.x;
		if(vertex.y > max.y) max.y = vertex.y;
		if(vertex.z > max.z) max.z = vertex.z;
	}

	 avg = (min + max);
	avg /=2;

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

void StaticModel::setAttributes(GLint*attributes){


	this->vertexBuffer->setVertexAttribute(attributes[ShaderAttributes::COORD3D]);
	this->normalBuffer->setVertexAttribute(attributes[ShaderAttributes::NORMAL3D]);
	this->texcoordBuffer->setVertexAttribute(attributes[ShaderAttributes::TEXCOORD2D]);
	this->elementBuffer->setVertexAttribute(-1);
	
};


void StaticModel::setShader(int id){
	this->shaderName = id;

}
int StaticModel::getShader(){
	return this->shaderName;

}
void StaticModel::setVao(GLuint vao){
	this->vao = vao;
}
void StaticModel::render(Pipeline *pipeline){



	pipeline->useShader(shaderName);
	Shader*shader = pipeline->getActiveShader();
	shader->bind();
	glm::mat4 model = pipeline->getTotalRotationTranslation()*this->getModelMatrix();


	glm::mat4 mvp  = pipeline->getProjection()*pipeline->getView()*model;
	shader->setUniformMat4f(ShaderUniforms::MVP,glm::value_ptr(mvp));
	shader->setUniformMat4f(ShaderUniforms::MODEL,glm::value_ptr(model));

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
