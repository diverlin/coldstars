#include "config.hpp"
#include "../common/constants.hpp"


Config& Config::Instance()
{
	static Config config;
	return config;
}
        
Config::Config()
:
SCREEN_WIDTH(800),
SCREEN_HEIGHT(600),
BPP(32),
FPS_LIMIT(60),
VSYNC(true),
MODERN_EFFECTS(false),
DEBUG_MODE(false),
AUTO_TURN_MODE(false),
GAME_SPEED(1),
SCROLL_VELOCITY_MAX(20),
SCROLL_VELOCITY_STEP(1),
game_mode(GAME_MODE::NORMAL_RUN),
log_mode(0),
auto_save_mode(false),
auto_load_mode(false),
mouse_camera_scroll(false)		
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
	auto_save_mode 	= ptree.get<bool>("Gameplay.auto_save_mode");
	auto_load_mode 	= ptree.get<bool>("Gameplay.auto_load_mode");
	GAME_SPEED 	= ptree.get<int>("Gameplay.GAME_SPEED");
		
	SCROLL_VELOCITY_MAX 	= ptree.get<int>("Control.SCROLL_VELOCITY_MAX");
	SCROLL_VELOCITY_STEP 	= ptree.get<int>("Control.SCROLL_VELOCITY_STEP");
	mouse_camera_scroll = ptree.get<bool>("Control.mouse_camera_scroll");
}

Config::~Config(){}
