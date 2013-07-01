#include "SFML_Wrapper.hpp"
//#include <boost/lexical_cast.hpp>

#include "../resources/ShaderCollector.hpp"
#include "../render/Render.hpp"
#include "../config/config.hpp"
#include "../common/common.hpp"

    
SFML_Wrapper::SFML_Wrapper()
{
	text12.setFont(font);
	text12.setCharacterSize(12);
	text12.setColor(sf::Color(255,0,0,255));
	
	ftfont.init("data/font/font.ttf", 20);
	    
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
	sf::Vector2u size(width, height);
	window.setSize(size);
}
		
void SFML_Wrapper::wrDrawSpecific()
{	
  	window.display();
}

void SFML_Wrapper::DrawText(const std::string& str, int font_size, const Vec2<float>& pos)
{

     	Color4<int> color(255, 255, 255, 255);
     	DrawText(str, font_size, pos, color);
}
		
void SFML_Wrapper::DrawText(const std::string& str, int font_size, const Vec2<float>& pos, const Color4<int>& color)
{
     	//text12.setString(str);
        //text12.setPosition(pos.x, GetHeight() - pos.y); 
                                                
	////window.pushGLStates();
	//window.draw(text12);
	////window.popGLStates();	     	

	glPushMatrix();
		glColor4ub(color.r, color.g, color.b, color.a);
		glScalef(0.5, 0.5, 0.5);
		freetype::print(ftfont, pos.x, pos.y, str.c_str());
	glPopMatrix();
		
}

   
