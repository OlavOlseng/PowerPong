#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H
#include <string>
class ResourceManager
{
public:
	enum{NO_RESOURCE = -1};
	ResourceManager(void);
	~ResourceManager(void);
	void setWorkingDirectory(std::string dir);
	
	std::string getWorkingDirectiory();
private:
	std::string workingDirectory;
	
};

#endif