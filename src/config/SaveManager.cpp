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

template <typename T>
T SaveManager::Get(std::string key)
{
	T val = ptree.get<T>(key);
	return val;
}

void SaveManager::SaveFile(const std::string& filename)
{		
	write_info(filename, ptree);
}

void SaveManager::LoadFile(const std::string& filename)
{
	read_info(filename, ptree);
}
