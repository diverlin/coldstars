#include "ConfigV.hpp"
#include <boost/property_tree/info_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <constants.hpp>

namespace jeti
{

ConfigV& ConfigV::instance()
{
    static ConfigV config;
    return config;
}

ConfigV::ConfigV()
{
    boost::property_tree::ptree ptree;
    boost::property_tree::info_parser::read_info(CONFIG_PATH+"config.info", ptree);

    m_video.width     = ptree.get<int>("Video.width");
    m_video.height    = ptree.get<int>("Video.height");
    m_video.bpp       = ptree.get<int>("Video.bpp");
    m_video.fps_limit = ptree.get<int>("Video.fps_limit");
    m_video.vsync     = ptree.get<bool>("Video.vsync");
}

ConfigV::~ConfigV()
{}

}
