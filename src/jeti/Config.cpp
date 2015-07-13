#include "Config.hpp"
#include <boost/property_tree/info_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <constants.hpp>

namespace jeti
{

Config::Config()
    :
      width(800),
      height(600),
      bpp(32),
      fps_limit(60),
      vsync(true)
{
    try {
        boost::property_tree::ptree ptree;
        boost::property_tree::info_parser::read_info(CONFIG_PATH+"config.info", ptree);

        width     = ptree.get<int>("Video.width");
        height    = ptree.get<int>("Video.height");
        bpp       = ptree.get<int>("Video.bpp");
        fps_limit = ptree.get<int>("Video.fps_limit");
        vsync     = ptree.get<bool>("Video.vsync");
    } catch (...) {

    }
}

Config::~Config()
{}

}
