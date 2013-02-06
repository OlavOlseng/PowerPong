#include "VolumeModel.h"


VolumeModel::VolumeModel(unsigned int numSurfacesX,unsigned int numSurfacesY,unsigned int numSurfacesZ,unsigned int surfaceWidth,unsigned int surfaceHeight,unsigned int surfaceDepth)
{

	unsigned int size = numSurfacesX*numSurfacesY*numSurfacesZ;
	this->surfaces = new VolumeSurface*[size];
	this->numSurfacesX = numSurfacesX;
	this->numSurfacesY = numSurfacesY;
	this->numSurfacesZ = numSurfacesZ;

	this->surfaceWidth = surfaceWidth;
	this->surfaceHeight = surfaceHeight;
	this->surfaceDepth = surfaceDepth;

	

	for(int i = 0;i<size;i++){
		surfaces[i] = nullptr;
	}

	this->numSurfaces = size;

}

void VolumeModel::init(TileAtlas * tileAtlas){

	this->tileAtlas = tileAtlas;
	this->texture = tileAtlas->getTexture();
	surfaceVaos = new GLuint[numSurfaces];
	glGenVertexArrays(numSurfaces,surfaceVaos);
	
	voxelShader = this->getResourceManager()->loadShader("voxelShader");
	voxelShader->bindUniform(ShaderUniforms::MVP,"mvp");
	voxelShader->bindUniform(ShaderUniforms::MODEL,"modelMatrix");
	voxelShader->bindUniform(ShaderUniforms::STEP_SIZE,"stepSize");
	voxelShader->bindAttribute(ShaderAttributes::COORD4D,"coord4d");
	voxelShader->bindAttribute(ShaderAttributes::NORMAL_BYTE,"normal");


	voxelShader->bindUniform(ShaderUniforms::CAMERA_POSITION,"cameraPos");
	const char * memberNames[] = {"diffuse","specular","direction",};
	voxelShader->bindUniformStructArray(ShaderUniforms::LIGHT_DIRECTIONAL,10,3,"dirLights",memberNames);

	voxelShader->bindUniformStructArray(ShaderUniforms::LIGHT_DIRECTIONAL,10,3,"dirLights",memberNames);
	const char * memberNamesPoint[] = {"diffuse","specular","position","constantAttenuation","linearAttenuation","quadraticAttenuation"};
	voxelShader->bindUniformStructArray(ShaderUniforms::LIGHT_POINT,10,6,"pointLights",memberNamesPoint);
	
	voxelShader->bindUniform(ShaderUniforms::NUM_POINT_LIGHTS,"numPointLights");
	voxelShader->bindUniform(ShaderUniforms::NUM_DIRECTIONAL_LIGHTS,"numDirLights");
	voxelShader->bindUniform(ShaderUniforms::MATERIAL_DIFFUSE,"material.diffuse");
	voxelShader->bindUniform(ShaderUniforms::MATERIAL_AMBIENT,"material.ambient");
	voxelShader->bindUniform(ShaderUniforms::MATERIAL_SPECULAR,"material.specular");
	voxelShader->bindUniform(ShaderUniforms::MATERIAL_SHININESS,"material.shininess");

	this->setAttributes(voxelShader->getAttributes());

	



	Material * material = getMaterial();
	material->ambient =  glm::vec3(0.2,0.2,0.2);
	material->specular = glm::vec3(0.2,0.2,0.2);
	material->diffuse = glm::vec3(1.0,1.0,1.0);
	material->shininess = 1.0;

	getBoundingBox()->setBounds(0,numSurfacesX*surfaceWidth,0,numSurfacesY*surfaceHeight,0,numSurfacesZ*surfaceDepth);

}
inline unsigned int VolumeModel::getIndex(unsigned int x,unsigned int y,unsigned int z){

	return x + y*numSurfacesY*numSurfacesY + z*numSurfacesZ;

}
void VolumeModel::setSurface(unsigned int x, unsigned int y, unsigned int z,VolumeSurface * surface){
	
	surfaces[this->getIndex(x,y,z)] = surface;
	this->updateSurface(x,y,z);

}
void VolumeModel::updateSurface(unsigned int x,unsigned int y, unsigned int z){
	unsigned int index = this->getIndex(x,y,z);
	VolumeSurface * surface = this->surfaces[index];
	surface->bufferData();
	Buffer * vertexBuffer = surface->getVertexBuffer();
	Buffer * normalBuffer = surface->getNormalBuffer();
	
	glBindVertexArray(surfaceVaos[index]);
	vertexBuffer->bindTo(vertexAttrib);
	normalBuffer->bindTo(normalAttrib);
	glBindVertexArray(0);
	


}



void VolumeModel::setAttributes(GLint*attributes,GLint*shadowAttributes){

	vertexAttrib = attributes[ShaderAttributes::COORD4D];
	normalAttrib = attributes[ShaderAttributes::NORMAL_BYTE];

}


void VolumeModel::render(Pipeline *pipeline){

	Shader*shader = voxelShader;
	shader->bind();


	
	shader->setUniformFloat(ShaderUniforms::STEP_SIZE,tileAtlas->getStepSizeX());


	unsigned int numDirLights = pipeline->getNumDirectionalLights();
	unsigned int numPointLights = pipeline->getNumPointLights();
	shader->setUniformInt(ShaderUniforms::NUM_DIRECTIONAL_LIGHTS,numDirLights);
	shader->setUniformInt(ShaderUniforms::NUM_POINT_LIGHTS,numPointLights);


	glm::vec4 cameraPosition = pipeline->getCameraPosition();
	shader->setUniformVec4f(ShaderUniforms::CAMERA_POSITION,cameraPosition.x,cameraPosition.y,cameraPosition.z,1.0);

	
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

	glm::mat4 model;
	glm::mat4 mvp ;
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,texture->getTextureHandle());
	VolumeSurface * surface;
	for (unsigned int z = 0; z< this->numSurfacesZ; z++) {
		
		for(unsigned int y= 0; y < this->numSurfacesY;y++){

			for(unsigned int x = 0; x < this->numSurfacesX;x++){
				surface = surfaces[getIndex(x,y,z)];
				if(surface){

					model = pipeline->getTotalRotationTranslation()*getModelMatrix()*glm::translate(glm::mat4(1.0),glm::vec3(x*surfaceWidth,y*surfaceHeight,z*surfaceDepth));
					mvp = pipeline->getProjection()*pipeline->getView()*model;
					shader->setUniformMat4f(ShaderUniforms::MVP,glm::value_ptr(mvp));
					shader->setUniformMat4f(ShaderUniforms::MODEL,glm::value_ptr(model));

					glBindVertexArray(surfaceVaos[getIndex(x,y,z)]);

					glDrawArrays(GL_TRIANGLES,0,surface->getVertexBuffer()->getBufferSize());

					glBindVertexArray(0);
				}

			}
		}
	}
	
	shader->unbind();
}

VolumeModel::~VolumeModel(void)
{

	delete[] surfaceVaos;
	delete[] surfaces;
}
