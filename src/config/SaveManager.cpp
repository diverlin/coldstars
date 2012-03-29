#include "config.hpp"

SaveManager& SaveManager::Instance()
{
	static SaveManager instance;
	return instance;
}

SaveManager::SaveManager() {}	
SaveManager::~SaveManager(){}

template <typename T>
void SaveManager::Put(std::string key, T val)
{
	ptree.put(key, val);
}

void SaveManager::DumpToFile()
{		
	write_info("save.info", ptree);
}
