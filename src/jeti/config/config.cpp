#include "config.hpp"
#include <boost/property_tree/info_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <constants.hpp>

namespace jeti
{

Config& Config::instance()
{
    static Config config;
    return config;
}

Config::Config()
{
    boost::property_tree::ptree ptree;
    boost::property_tree::info_parser::read_info(CONFIG_PATH+"config.info", ptree);

    m_video.width     = ptree.get<int>("Video.width");
    m_video.height    = ptree.get<int>("Video.height");
    m_video.bpp       = ptree.get<int>("Video.bpp");
    m_video.fps_limit = ptree.get<int>("Video.fps_limit");
    m_video.vsync     = ptree.get<bool>("Video.vsync");
}

Config::~Config()
{}

}
