#include "SFMLWrapper.hpp"
//#include <boost/lexical_cast.hpp>

#include <Render.hpp>
//#include <common/Config.hpp>
//#include <common/common.hpp>
#include <constants.hpp>
    
namespace jeti {

SFMLWrapper::SFMLWrapper()
{
    m_text12.setFont(m_font);
    m_text12.setCharacterSize(12);
    m_text12.setColor(sf::Color(255,0,0,255));
    
    std::string fontpath = DATA_PATH+"font/font.ttf";
    //ftfont.init(fontpath.c_str(), 20);
        
}

SFMLWrapper::~SFMLWrapper()
{}

void SFMLWrapper::wrCreateWindowSpecific(int width, int height, int bpp, bool vert_sync, int fps_limit, const std::string& title)
{    
    this->m_bpp = bpp;
    this->m_vsync = vert_sync;
    
    m_window.create(sf::VideoMode(width, height, bpp), title);
    m_window.setFramerateLimit(fps_limit);
    m_window.setVerticalSyncEnabled(vert_sync);
}
         
void SFMLWrapper::wrResizeSpecific(int width, int height)
{    
    m_view.setViewport(sf::FloatRect(0, 0, width, height));
    m_window.setView(m_view);
    m_window.setSize(sf::Vector2u(width, height));
}
        
void SFMLWrapper::wrDrawSpecific()
{    
      m_window.display();
}

void SFMLWrapper::drawText(const std::string& str, int font_size, const glm::vec2& pos)
{    
    glm::ivec4 color(255, 255, 255, 255);
    drawText(str, font_size, pos, color);
}
        
void SFMLWrapper::drawText(const std::string& str, int font_size, const glm::vec2& pos, const glm::ivec4& color)
{
    //glPushMatrix();
        //glColor4ub(color.r, color.g, color.b, color.a);
        //glScalef(0.5, 0.5, 0.5);
        //freetype::print(ftfont, pos.x, pos.y, str.c_str());
    //glPopMatrix();
        
}

}
   
