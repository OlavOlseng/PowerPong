#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H
#include <string>
#include <hash_map>
#include "../Shaders/Shader.h"
#include <assimp\scene.h>
#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>

class ResourceManager
{
public:
	enum{NO_RESOURCE = -1};
	ResourceManager(void);
	~ResourceManager(void);
	void setWorkingDirectory(std::string dir);
	void setShaderDirectory(std::string dir);
	void setModelDirectory(std::string dir);
	std::string getWorkingDirectiory();
	std::string getModelDirectory();
	std::string getShaderDirectory();
	Shader *loadShader(std::string name);
	GLuint loadTexture(std::string name);
	const aiScene * loadModel(std::string name,int postProcess = aiProcessPreset_TargetRealtime_MaxQuality);
	
private:
	std::string workingDirectory;
	std::string shaderDirectory;
	std::string modelDirectory;

	std::hash_map<std::string,Shader*> shaders;
	std::hash_map<std::string,GLuint> textures;
	std::hash_map<std::string,std::pair<Assimp::Importer *,const aiScene *>> models;

	
	
};

#endif