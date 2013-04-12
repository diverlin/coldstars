#include "WindowWrapper.hpp"
//#include <boost/lexical_cast.hpp>

#include "../resources/ShaderCollector.hpp"
#include "../render/Render.hpp"
#include "../config/config.hpp"
#include "../common/common.hpp"

    
WindowWrapper::WindowWrapper()
{}

WindowWrapper::~WindowWrapper()
{}

void WindowWrapper::wrCreateWindowSpecific(int width, int height, int bpp, bool vert_sync, const std::string& title)
{	
      	this->bpp = bpp;
      	this->vert_sync = vert_sync;
      	
      	window.create(sf::VideoMode(width, height, bpp), title);
      	window.setFramerateLimit(Config::Instance().FPS_LIMIT); 
    	window.setVerticalSyncEnabled(vert_sync);
}
         
void WindowWrapper::wrResizeSpecific(int width, int height)
{	
	view.setViewport(sf::FloatRect(0, 0, width, height));
	window.setView(view);
	sf::Vector2u size(width, height);
	window.setSize(size);
}
		
void WindowWrapper::wrDrawSpecific()
{	
  	window.display();
}

void WindowWrapper::DrawText(const std::string& str, int font_size, const vec2f& pos)
{
     	sf::Text text(str, font, font_size);
     	text.setColor(sf::Color(255, 255, 255));
     	text.setPosition(pos.x,  GetHeight() - pos.y); 
     	     	     	
	window.pushGLStates();
	window.draw(text);
	window.popGLStates();	
}
		
void WindowWrapper::DrawText(const std::string& str, int font_size, const vec2f& pos, const Color4i& color)
{
     	sf::Text text(str, font, font_size);
        text.setColor(sf::Color(color.r, color.g, color.b));
        text.setPosition(pos.x, GetHeight() - pos.y); 
                                                
	window.pushGLStates();
	window.draw(text);
	window.popGLStates();	     	
}

   
