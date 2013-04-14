#include "SFML_Wrapper.hpp"
//#include <boost/lexical_cast.hpp>

#include "../resources/ShaderCollector.hpp"
#include "../render/Render.hpp"
#include "../config/config.hpp"
#include "../common/common.hpp"

    
SFML_Wrapper::SFML_Wrapper()
{}

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

void SFML_Wrapper::DrawText(const std::string& str, int font_size, const vec2f& pos)
{
     	//sf::Text text(str, font, font_size);
     	//text.setColor(sf::Color(255, 255, 255));
     	//text.setPosition(pos.x,  GetHeight() - pos.y); 
     	     	     	
	//window.pushGLStates();
	//window.draw(text);
	//window.popGLStates();	
}
		
void SFML_Wrapper::DrawText(const std::string& str, int font_size, const vec2f& pos, const Color4i& color)
{
     	//sf::Text text(str, font, font_size);
        //text.setColor(sf::Color(color.r, color.g, color.b));
        //text.setPosition(pos.x, GetHeight() - pos.y); 
                                                
	//window.pushGLStates();
	//window.draw(text);
	//window.popGLStates();	     	
}

   
