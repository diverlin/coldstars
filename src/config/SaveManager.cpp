#include "config.hpp"

SaveManager& SaveManager::Instance()
{
	static SaveManager instance;
	return instance;
}

SaveManager::SaveManager() {}	
SaveManager::~SaveManager() {}

void SaveManager::SaveFile(const std::string& filename, boost::property_tree::ptree& ptree) const
{		
	write_info(filename, ptree);
}

void SaveManager::LoadFile(const std::string& filename, boost::property_tree::ptree& ptree) const
{
	read_info(filename, ptree);
}

