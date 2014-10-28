#include "SFML_Wrapper.hpp"
//#include <boost/lexical_cast.hpp>

#include <Render.hpp>
#include <config/config.hpp>
#include <common/common.hpp>
#include <common/constants.hpp>
    
namespace jeti {

SFML_Wrapper::SFML_Wrapper()
{
    text12.setFont(font);
    text12.setCharacterSize(12);
    text12.setColor(sf::Color(255,0,0,255));
    
    std::string fontpath = DATA_PATH+"font/font.ttf";
    //ftfont.init(fontpath.c_str(), 20);
        
}

SFML_Wrapper::~SFML_Wrapper()
{}

void SFML_Wrapper::wrCreateWindowSpecific(int width, int height, int bpp, bool vert_sync, const std::string& title)
{    
    this->bpp = bpp;
    this->vert_sync = vert_sync;
    
    window.create(sf::VideoMode(width, height, bpp), title);
    window.setFramerateLimit(Config::Instance().FPS_LIMIT); 
    window.setVerticalSyncEnabled(vert_sync);
}
         
void SFML_Wrapper::wrResizeSpecific(int width, int height)
{    
    view.setViewport(sf::FloatRect(0, 0, width, height));
    window.setView(view);
    window.setSize(sf::Vector2u(width, height));
}
        
void SFML_Wrapper::wrDrawSpecific()
{    
      window.display();
}

void SFML_Wrapper::DrawText(const std::string& str, int font_size, const glm::vec2& pos)
{    
    glm::ivec4 color(255, 255, 255, 255);
    DrawText(str, font_size, pos, color);
}
        
void SFML_Wrapper::DrawText(const std::string& str, int font_size, const glm::vec2& pos, const glm::ivec4& color)
{
    //glPushMatrix();
        //glColor4ub(color.r, color.g, color.b, color.a);
        //glScalef(0.5, 0.5, 0.5);
        //freetype::print(ftfont, pos.x, pos.y, str.c_str());
    //glPopMatrix();
        
}

}
   
