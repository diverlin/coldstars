#include "config.hpp"
#include "../common/constants.hpp"

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
game_mode(GAME_MODE::NORMAL_RUN),

AUTO_TURN_MODE(false),
AUTO_SAVE_MODE(false),
GAME_SPEED(1),

SCROLL_VELOCITY_MAX(20),
SCROLL_VELOCITY_STEP(1)
		
{
	boost::property_tree::info_parser::read_info("config.info", ptree);

	SCREEN_WIDTH 	= ptree.get<int>("Window.WIDTH");
	SCREEN_HEIGHT	= ptree.get<int>("Window.HEIGHT");
	BPP 		= ptree.get<int>("Window.BPP");
	FPS_LIMIT 	= ptree.get<int>("Window.FPS_LIMIT");
		
	VSYNC 		= ptree.get<bool>("Window.VSYNC");
	MODERN_EFFECTS 	= ptree.get<bool>("Window.MODERN_EFFECTS");

	DEBUG_MODE 	= ptree.get<bool>("General.DEBUG_MODE");
	game_mode 	= ptree.get<int>("General.game_mode");
	
	log_mode 	= ptree.get<int>("General.log_mode");
		
	AUTO_TURN_MODE 	= ptree.get<bool>("Gameplay.AUTO_TURN_MODE");
	AUTO_SAVE_MODE 	= ptree.get<bool>("Gameplay.AUTO_SAVE_MODE");
	GAME_SPEED 	= ptree.get<int>("Gameplay.GAME_SPEED");
	
	SCROLL_VELOCITY_MAX 	= ptree.get<int>("Control.SCROLL_VELOCITY_MAX");
	SCROLL_VELOCITY_STEP 	= ptree.get<int>("Control.SCROLL_VELOCITY_STEP");
}

Config::~Config(){}
