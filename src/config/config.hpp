#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <boost/property_tree/info_parser.hpp>
#include <boost/property_tree/ptree.hpp>

struct Config
{
	public:
		static Config& Instance();

		int GetGameMode() const { return game_mode; };
		
		int SCREEN_WIDTH;
		int SCREEN_HEIGHT;
		int BPP;
		int FPS_LIMIT;
		
		bool VSYNC;
		bool MODERN_EFFECTS;

		bool DEBUG_MODE;
		
		bool AUTO_TURN_MODE;
		bool AUTO_SAVE_MODE;
		int GAME_SPEED;
		
		int SCROLL_VELOCITY_MAX;
		int SCROLL_VELOCITY_STEP;
		

							
	private:
		Config();
		Config(const Config&) = delete;
		~Config();
		Config& operator=(const Config&) = delete;
		
		int game_mode;
		
		boost::property_tree::ptree ptree;

};

#endif //CONFIG_HPP
