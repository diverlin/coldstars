#ifndef CONFIG_HPP
#define CONFIG_HPP
#include <boost/property_tree/info_parser.hpp>
#include <boost/property_tree/ptree.hpp>

struct Config
{
	static Config& instanse();
	bool USE_MODERN_HW;
	private:
	Config();
	Config(const Config&);
	~Config();
	Config& operator=(const Config&);
	boost::property_tree::ptree ptree;
};

#endif //CONFIG_HPP
