#include "config.hpp"

Config& Config::Instance()
{
	static Config config;
	return config;
}

Config::Config():	

SCREEN_WIDTH_MIN(800),
SCREEN_HEIGHT_MIN(600),
BPP(32),
VSYNC(true),
FPS_LIMIT(60),

MODERN_EFFECTS(false),

DEBUG_MODE(false),

AUTOTURN_MODE(false),
GAMESPEED(1),

SCROLL_VELOCITY_MAX(20),
SCROLL_VELOCITY_STEP(1)
		
{
	boost::property_tree::info_parser::read_info("config.info", ptree);

	SCREEN_WIDTH_MIN = ptree.get<int>("Graphic.WIDTH_MIN");
	SCREEN_HEIGHT_MIN = ptree.get<int>("Graphic.HEIGHT_MIN");
	BPP = ptree.get<int>("Graphic.BPP");
	FPS_LIMIT = ptree.get<int>("Graphic.FPS_LIMIT");
		
	VSYNC = ptree.get<bool>("Graphic.VSYNC");
	MODERN_EFFECTS = ptree.get<bool>("Graphic.MODERN_EFFECTS");

	DEBUG_MODE = ptree.get<bool>("General.DEBUG_MODE");
	
	AUTOTURN_MODE = ptree.get<bool>("Gameplay.AUTOTURN_MODE");
	GAMESPEED = ptree.get<int>("Gameplay.GAMESPEED");
	
	SCROLL_VELOCITY_MAX = ptree.get<int>("Control.SCROLL_VELOCITY_MAX");
	SCROLL_VELOCITY_STEP = ptree.get<int>("Control.SCROLL_VELOCITY_STEP");
}

Config::~Config(){}
