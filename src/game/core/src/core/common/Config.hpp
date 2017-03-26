#pragma once

#include <boost/property_tree/info_parser.hpp>
#include <boost/property_tree/ptree.hpp>

struct Config
{
    public:
        Config();
        ~Config();

        void SetAutoSaveMode(bool auto_save_mode) { this->auto_save_mode = auto_save_mode; }
        void SetAutoLoadMode(bool auto_load_mode) { this->auto_load_mode = auto_load_mode; }
        
        int GetGameMode() const { return game_mode; }
        int GetLogMode() const { return log_mode; }

        bool GetAutoSaveMode() const { return auto_save_mode; }
        bool GetAutoLoadMode() const { return auto_load_mode; }

        bool GetMouseCameraScroll() const { return mouse_camera_scroll; }

        bool DEBUG_MODE = false;
        
        bool AUTO_TURN_MODE = false;
        int GAME_SPEED = 1; // 1-10
        
        int SCROLL_VELOCITY_MAX = 20;
        int SCROLL_VELOCITY_STEP = 1;

    private:
        int game_mode = 0;
        int log_mode = 1;
        
        bool auto_save_mode = false;
        bool auto_load_mode = false;
        
        bool mouse_camera_scroll = false;

        boost::property_tree::ptree ptree;
};

