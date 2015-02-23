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
        
        int GetGameMode() const { return game_mode; };
        int GetLogMode() const { return log_mode; };

        bool GetAutoSaveMode() const { return auto_save_mode; }
        bool GetAutoLoadMode() const { return auto_load_mode; }

        bool GetMouseCameraScroll() const { return mouse_camera_scroll; }

        bool DEBUG_MODE;
        
        bool AUTO_TURN_MODE;
        int GAME_SPEED;
        
        int SCROLL_VELOCITY_MAX;
        int SCROLL_VELOCITY_STEP;

    private:
        int game_mode;
        int log_mode;
        
        bool auto_save_mode;
        bool auto_load_mode;
        
        bool mouse_camera_scroll;

        boost::property_tree::ptree ptree;
};

