#include "Config.hpp"
#include <common/constants.hpp>

const std::string CONFIG_PATH("");

Config::Config()
    :
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
    boost::property_tree::info_parser::read_info(CONFIG_PATH+"config.info", ptree);

    DEBUG_MODE    = ptree.get<bool>("General.DEBUG_MODE");
    game_mode     = ptree.get<int>("General.game_mode");
    
    log_mode     = ptree.get<int>("General.log_mode");

    AUTO_TURN_MODE     = ptree.get<bool>("Gameplay.AUTO_TURN_MODE");
    auto_save_mode     = ptree.get<bool>("Gameplay.auto_save_mode");
    auto_load_mode     = ptree.get<bool>("Gameplay.auto_load_mode");
    GAME_SPEED     = ptree.get<int>("Gameplay.GAME_SPEED");

    SCROLL_VELOCITY_MAX     = ptree.get<int>("Control.SCROLL_VELOCITY_MAX");
    SCROLL_VELOCITY_STEP    = ptree.get<int>("Control.SCROLL_VELOCITY_STEP");
    mouse_camera_scroll = ptree.get<bool>("Control.mouse_camera_scroll");
}

Config::~Config() {}
