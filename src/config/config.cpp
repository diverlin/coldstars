#include "config.hpp"

Config& Config::Instance()
{
	static Config config;
	return config;
}

Config::Config():	

SCREEN_WIDTH_MIN(800),
SCREEN_HEIGHT_MIN(600),

MODERN_EFFECTS(false)

{
	boost::property_tree::info_parser::read_info("config.info", ptree);

	SCREEN_WIDTH_MIN = ptree.get<int>("Screen.WIDTH_MIN");
	SCREEN_HEIGHT_MIN = ptree.get<int>("Screen.HEIGHT_MIN");

	MODERN_EFFECTS = ptree.get<bool>("Graphic.MODERN_EFFECTS");
}

Config::~Config(){}
