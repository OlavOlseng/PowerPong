#include "StaticModel.h"


StaticModel::StaticModel(GLint*attributes)
{

	this->vertexBuffer = new Buffer(Buffer::ARRAY_BUFFER,Buffer::STATIC,3,GL_FLOAT);
	this->normalBuffer= new Buffer(Buffer::ARRAY_BUFFER,Buffer::STATIC,3,GL_FLOAT);
	this->texcoordBuffer = new Buffer(Buffer::ARRAY_BUFFER,Buffer::STATIC,2,GL_FLOAT);
	this->elementBuffer= new Buffer(Buffer::ELEMENT_BUFFER,Buffer::STATIC,0,0);

	if(attributes)
		setAttributes(attributes);
	glGenVertexArrays(1,&vao);
	glGenVertexArrays(1,&shadowVao);
	
}


StaticModel::~StaticModel(void)
{
	delete vertexBuffer;
	delete normalBuffer;
	delete texcoordBuffer;
	delete elementBuffer;
}



Node* StaticModel::initFromScene(const aiScene * scene,Node*modelRoot){
	
	
		
			for (int i = 1;i<scene->mNumMeshes;i++){
				StaticModel*model = new StaticModel();
				model->setShader(shaderName);
				model->setResourceManager(getResourceManager());
				model->setAttributes(vertexBuffer->getVertexAttribute(),normalBuffer->getVertexAttribute(),texcoordBuffer->getVertexAttribute());
				model->initFromMesh(scene->mMeshes[i],scene->mMaterials,false);
				modelRoot->addChild(model);
			}

		
			initFromMesh(scene->mMeshes[0],scene->mMaterials,scene->mNumMeshes == 0);
		
		modelRoot->addChild(this);
	
	
		return modelRoot;
}

void StaticModel::initFromMesh(aiMesh * mesh,aiMaterial** materials,bool moveTocenter){
		

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

	aiString path;
	material->GetTexture(aiTextureType_DIFFUSE,0,&path);
	textureHandle = resourceManager->loadTexture(path.data);
	
	


	aiColor3D diffuse(0.0,0.0,0.0);
	material->Get(AI_MATKEY_COLOR_DIFFUSE,diffuse);
	aiColor3D ambient(1.0,1.0,1.0);
	material->Get(AI_MATKEY_COLOR_AMBIENT,ambient);
	aiColor3D specular(1.0,1.0,1.0);
	material->Get(AI_MATKEY_COLOR_SPECULAR,specular);
	float shininess=1.0,strength =1.0;
	material->Get(AI_MATKEY_SHININESS,shininess);
	material->Get(AI_MATKEY_SHININESS_STRENGTH,strength);
	Material * mat = getMaterial();
	mat->ambient = glm::vec3(ambient.r,ambient.g,ambient.b);
	mat->diffuse = glm::vec3(diffuse.r,diffuse.g,diffuse.b);
	mat->specular = glm::vec3(specular.r,specular.g,specular.b);
	if(shininess == 0)
		shininess = 1000.0;
	mat->shininess = shininess;


	if(moveTocenter){
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
	}
	glBindTexture(GL_TEXTURE_2D,textureHandle);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 

	vertexBuffer->setData(vertices,sizeof(glm::vec3)*mesh->mNumVertices);
	texcoordBuffer->setData(texCoord,sizeof(glm::vec2)*mesh->mNumVertices);
	normalBuffer->setData(normals,sizeof(glm::vec3)*mesh->mNumVertices);
	elementBuffer->setData(indices,sizeof(GLushort)*mesh->mNumFaces*3);

	glBindVertexArray(vao);
	vertexBuffer->bindTo(vertexBuffer->getVertexAttribute());
	texcoordBuffer->bindTo(texcoordBuffer->getVertexAttribute());
	normalBuffer->bindTo(normalBuffer->getVertexAttribute());
	elementBuffer->bind();
	glBindVertexArray(0);
	/*
	glBindVertexArray(shadowVao);
	vertexBuffer->bind();
	elementBuffer->bind();
	glBindVertexArray(0);*/

	this->numVertices = mesh->mNumVertices;

	this->numIdices = mesh->mNumFaces*3;


	if(mesh->HasPositions()){


	}

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
void StaticModel::setAttributes(GLint coord3D,GLint normal3D,GLint texcoord2D){
	this->vertexBuffer->setVertexAttribute(coord3D);
	this->normalBuffer->setVertexAttribute(normal3D);
	this->texcoordBuffer->setVertexAttribute(texcoord2D);
	this->elementBuffer->setVertexAttribute(-1);

}

void StaticModel::setShader(int id){
	this->shaderName = id;

}
int StaticModel::getShader(){
	return this->shaderName;

}
void StaticModel::setVao(GLuint vao){
	this->vao = vao;
}

void StaticModel::shadowPass(Pipeline*pipeline){

	Shader*shadowShader = pipeline->getActiveShader();
	shadowShader->bind();
	glBindVertexArray(shadowVao);
	glDrawElements(GL_TRIANGLES,elementBuffer->getBufferSize()/sizeof(GLushort),GL_UNSIGNED_SHORT,0);
	shadowShader->unbind();

};
void StaticModel::render(Pipeline *pipeline){

	if(pipeline->isShadowPass()){
		shadowPass(pipeline);
	}else{


	pipeline->useShader(shaderName);
	Shader*shader = pipeline->getActiveShader();
	shader->bind();
	glm::mat4 model = pipeline->getTotalRotationTranslation()*this->getModelMatrix();
	
	unsigned int numDirLights = pipeline->getNumDirectionalLights();
	unsigned int numPointLights = pipeline->getNumPointLights();
	shader->setUniformInt(ShaderUniforms::NUM_DIRECTIONAL_LIGHTS,numDirLights);
	shader->setUniformInt(ShaderUniforms::NUM_POINT_LIGHTS,numPointLights);

	glm::vec4 viewDirection = pipeline->getViewDirection();
	shader->setUniformVec4f(ShaderUniforms::VIEW_DIRECTION,viewDirection.x,viewDirection.y,viewDirection.z,1.0);



	//set lights
	for(int i = 0;i<numDirLights;i++){
		DirectionalLight*light = pipeline->getDirectionalLight(i);
		//diffuse
		shader->setUniformStructVec4f(ShaderUniforms::LIGHT_DIRECTIONAL,i,0,light->diffuse.x,light->diffuse.y,light->diffuse.z,light->diffuse.w);
		//specular
		shader->setUniformStructVec4f(ShaderUniforms::LIGHT_DIRECTIONAL,i,1,light->specular.x,light->specular.y,light->specular.z,light->specular.w);
		//direction
		shader->setUniformStructVec4f(ShaderUniforms::LIGHT_DIRECTIONAL,i,2,light->transformedDirection.x,light->transformedDirection.y,light->transformedDirection.z,0.0);
		
	}
	for(int i = 0;i< numPointLights;i++){
		PointLight *light = pipeline->getPointLight(i);

		//diffuse
		shader->setUniformStructVec4f(ShaderUniforms::LIGHT_POINT,i,0,light->diffuse.x,light->diffuse.y,light->diffuse.z,light->diffuse.w);
		//specular
		shader->setUniformStructVec4f(ShaderUniforms::LIGHT_POINT,i,1,light->specular.x,light->specular.y,light->specular.z,light->specular.w);
		//position
		shader->setUniformStructVec4f(ShaderUniforms::LIGHT_POINT,i,2,light->transformedPosition.x,light->transformedPosition.y,light->transformedPosition.z,0.0);
		//constantAttenuation
		shader->setUniformStructFloat(ShaderUniforms::LIGHT_POINT,i,3,light->constantAttenuation);
		//linearAttenuation
		shader->setUniformStructFloat(ShaderUniforms::LIGHT_POINT,i,4,light->linearAttenutation);
		//quadraticAttenuation
		shader->setUniformStructFloat(ShaderUniforms::LIGHT_POINT,i,5,light->quadraticAttenuation);


	}

	//set Material
	Material * material = getMaterial();
	glm::vec3 diffuse = material->diffuse;
	glm::vec3 ambient = material->ambient;
	glm::vec3 specular = material->specular;
	float shininess = material->shininess;

	shader->setUniformVec4f(ShaderUniforms::MATERIAL_DIFFUSE,diffuse.x,diffuse.y,diffuse.z,1.0);
	shader->setUniformVec4f(ShaderUniforms::MATERIAL_AMBIENT,ambient.x,ambient.y,ambient.z,1.0);
	shader->setUniformVec4f(ShaderUniforms::MATERIAL_SPECULAR,specular.x,specular.y,specular.z,1.0);
	shader->setUniformFloat(ShaderUniforms::MATERIAL_SHININESS,shininess);
	//set mvp and modelMatrix
	glm::mat4 mvp  = pipeline->getProjection()*pipeline->getView()*model;
	shader->setUniformMat4f(ShaderUniforms::MVP,glm::value_ptr(mvp));
	shader->setUniformMat4f(ShaderUniforms::MODEL,glm::value_ptr(model));
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,textureHandle);

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES,elementBuffer->getBufferSize()/sizeof(GLushort),GL_UNSIGNED_SHORT,0);
	glBindVertexArray(0);
	shader->unbind();
	}
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
