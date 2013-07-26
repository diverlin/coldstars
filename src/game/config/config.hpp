#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <boost/property_tree/info_parser.hpp>
#include <boost/property_tree/ptree.hpp>

struct Config
{
	public:
		static Config& Instance();

		void SetAutoSaveMode(bool auto_save_mode) { this->auto_save_mode = auto_save_mode; }
		void SetAutoLoadMode(bool auto_load_mode) { this->auto_load_mode = auto_load_mode; }
		
		int GetGameMode() const { return game_mode; };
		int GetLogMode() const { return log_mode; };

		bool GetAutoSaveMode() const { return auto_save_mode; }
		bool GetAutoLoadMode() const { return auto_load_mode; }

		bool GetMouseCameraScroll() const { return mouse_camera_scroll; }
										
		int SCREEN_WIDTH;
		int SCREEN_HEIGHT;
		int BPP;
		int FPS_LIMIT;
		
		bool VSYNC;
		bool MODERN_EFFECTS;

		bool DEBUG_MODE;
		
		bool AUTO_TURN_MODE;
		int GAME_SPEED;
		
		int SCROLL_VELOCITY_MAX;
		int SCROLL_VELOCITY_STEP; 
        							
	private:
		Config();
		Config(const Config&) = delete;
		~Config();
		Config& operator=(const Config&) = delete;
		
		int game_mode;
		int log_mode;
		
		bool auto_save_mode;
		bool auto_load_mode;
		
		bool mouse_camera_scroll;
						
		boost::property_tree::ptree ptree;

};

#endif //CONFIG_HPP
