#include "config.hpp"

Config& Config::Instance()
{
	static Config config;
	return config;
}

Config::Config():	

SCREEN_WIDTH(800),
SCREEN_HEIGHT(600),
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

	SCREEN_WIDTH = ptree.get<int>("Window.WIDTH");
	SCREEN_HEIGHT = ptree.get<int>("Window.HEIGHT");
	BPP = ptree.get<int>("Window.BPP");
	FPS_LIMIT = ptree.get<int>("Window.FPS_LIMIT");
		
	VSYNC = ptree.get<bool>("Window.VSYNC");
	MODERN_EFFECTS = ptree.get<bool>("Window.MODERN_EFFECTS");

	DEBUG_MODE = ptree.get<bool>("General.DEBUG_MODE");
	
	AUTOTURN_MODE = ptree.get<bool>("Gameplay.AUTOTURN_MODE");
	GAMESPEED = ptree.get<int>("Gameplay.GAMESPEED");
	
	SCROLL_VELOCITY_MAX = ptree.get<int>("Control.SCROLL_VELOCITY_MAX");
	SCROLL_VELOCITY_STEP = ptree.get<int>("Control.SCROLL_VELOCITY_STEP");
}

Config::~Config(){}
