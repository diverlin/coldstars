#include "SFMLWrapper.hpp"
//#include <boost/lexical_cast.hpp>

#include <Render.hpp>
//#include <config/config.hpp>
//#include <common/common.hpp>
#include <constants.hpp>
    
namespace jeti {

SFMLWrapper::SFMLWrapper()
{
    text12.setFont(font);
    text12.setCharacterSize(12);
    text12.setColor(sf::Color(255,0,0,255));
    
    std::string fontpath = DATA_PATH+"font/font.ttf";
    //ftfont.init(fontpath.c_str(), 20);
        
}

SFMLWrapper::~SFMLWrapper()
{}

void SFMLWrapper::wrCreateWindowSpecific(int width, int height, int bpp, bool vert_sync, int fps_limit, const std::string& title)
{    
    this->bpp = bpp;
    this->vert_sync = vert_sync;
    
    window.create(sf::VideoMode(width, height, bpp), title);
    window.setFramerateLimit(fps_limit);
    window.setVerticalSyncEnabled(vert_sync);
}
         
void SFMLWrapper::wrResizeSpecific(int width, int height)
{    
    view.setViewport(sf::FloatRect(0, 0, width, height));
    window.setView(view);
    window.setSize(sf::Vector2u(width, height));
}
        
void SFMLWrapper::wrDrawSpecific()
{    
      window.display();
}

void SFMLWrapper::DrawText(const std::string& str, int font_size, const glm::vec2& pos)
{    
    glm::ivec4 color(255, 255, 255, 255);
    DrawText(str, font_size, pos, color);
}
        
void SFMLWrapper::DrawText(const std::string& str, int font_size, const glm::vec2& pos, const glm::ivec4& color)
{
    //glPushMatrix();
        //glColor4ub(color.r, color.g, color.b, color.a);
        //glScalef(0.5, 0.5, 0.5);
        //freetype::print(ftfont, pos.x, pos.y, str.c_str());
    //glPopMatrix();
        
}

}
   
