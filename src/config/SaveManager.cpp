#include "config.hpp"

SaveManager& SaveManager::Instance()
{
	static SaveManager instance;
	return instance;
}

SaveManager::SaveManager() {}	
SaveManager::~SaveManager(){}

template <typename T>
void SaveManager::PutPair(std::string , T val)
{
	ptree.put();
}

SaveManager Save::DumpToFile()
{		
	write_info("save.info", ptree);
}
