#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H
#include <string>
#include <hash_map>
#include "../Shaders/Shader.h"
#include <assimp\scene.h>
#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>
#include "../Util/Texture.h"

//Uses refrence counting
class ResourceManager
{
public:
	enum{NO_RESOURCE = -1};
	ResourceManager(void);
	~ResourceManager(void);
	//Increases the refrence count by 1
	void setWorkingDirectory(std::string dir);
	//Increases the refrence count by 1
	void setShaderDirectory(std::string dir);
	//Increases the refrence count by 1
	void setModelDirectory(std::string dir);
	std::string getWorkingDirectiory();
	std::string getModelDirectory();
	std::string getShaderDirectory();
	Shader *loadShader(std::string name,bool takeOwnership = false);
	Texture *  loadTexture(std::string name,bool takeOwnership = false);
	const aiScene * loadModel(std::string name,int postProcess = aiProcessPreset_TargetRealtime_MaxQuality);
	//Reduces refrence count by 1
	void freeTexture(std::string name);
	//Reduces refrence count by 1
	void freeModel(std::string name);
	//Reduces refrence count by 1
	void freeShader(std::string name);
	
private:
	std::string workingDirectory;
	std::string shaderDirectory;
	std::string modelDirectory;
	
	std::hash_map<std::string,std::pair<Shader*,int>> shaders;
	std::hash_map<std::string,std::pair<Texture*,int>> textures;
	std::hash_map<std::string,std::pair<std::pair<Assimp::Importer *,const aiScene *>,int>> models;

	
	
};

#endif