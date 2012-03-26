#include "config.hpp"

Config& Config::instanse()
{
	static Config config;
	return config;
}

Config::Config():	USE_MODERN_HW(false)
{
	boost::property_tree::info_parser::read_info("config.info",ptree);

	USE_MODERN_HW = ptree.get<bool>("Gui.USE_MODERN_HW");
}

Config::~Config(){}
