#ifndef CONFIG_HPP
#define CONFIG_HPP
#include <boost/property_tree/info_parser.hpp>
#include <boost/property_tree/ptree.hpp>

struct Config
{
	public:
		static Config& Instance();

		int SCREEN_WIDTH_MIN;
		int SCREEN_HEIGHT_MIN;

		bool MODERN_EFFECTS;
					
	private:
		Config();
		Config(const Config&);
		~Config();
		Config& operator=(const Config&);
		
		boost::property_tree::ptree ptree;
};

#endif //CONFIG_HPP
