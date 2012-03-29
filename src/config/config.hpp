#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <boost/property_tree/info_parser.hpp>
#include <boost/property_tree/ptree.hpp>

struct Config
{
	public:
		static Config& Instance();

		int SCREEN_WIDTH;
		int SCREEN_HEIGHT;
		int BPP;
		int FPS_LIMIT;
		
		bool VSYNC;
		bool MODERN_EFFECTS;

		bool DEBUG_MODE;
		
		bool AUTOTURN_MODE;
		int GAMESPEED;
		
		int SCROLL_VELOCITY_MAX;
		int SCROLL_VELOCITY_STEP;
							
	private:
		Config();
		Config(const Config&);
		~Config();
		Config& operator=(const Config&);
		
		boost::property_tree::ptree ptree;
};

#endif //CONFIG_HPP
