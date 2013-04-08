#include "WindowWrapper.hpp"
//#include <boost/lexical_cast.hpp>

#include "../resources/ShaderCollector.hpp"
#include "../render/Render.hpp"
#include "../config/config.hpp"
#include "../common/common.hpp"

    
WindowWrapper::WindowWrapper()/*:RenderWindow(sf::VideoMode(800, 600), "SFML OpenGL", sf::Style::Default, sf::ContextSettings(32))*/
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
	       	
//void WindowWrapper::wrDrawFps()
//{
	////float fps = 1.f / getFrameTime();
      	////sf::Text _str(std::string("FPS:" + boost::lexical_cast<std::string>( (int)fps) +" / game_speed: x" + boost::lexical_cast<std::string>( Config::Instance().GAME_SPEED) ), font, 14);
      	////_str.setColor(sf::Color(255, 255, 255));
      	////_str.setPosition(100, 10);
      	////render_window.draw(_str);
//}
            
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
     	text.setPosition(pos.x, pos.y); 
     	//text.setPosition(pos.x, GetHeight() - pos.y); 
     	     	     	
	window.pushGLStates();
	window.draw(text);
	window.popGLStates();	
}
		
void WindowWrapper::DrawText(const std::string& str, int font_size, const vec2f& pos, const Color4i& color)
{
     	sf::Text text(str, font, font_size);
        text.setColor(sf::Color(color.r, color.g, color.b));
        //s.setPosition(pos.x - scroll_coord.x, (Screen::Instance().GetHeight() - pos.y) + scroll_coord.y); 
        text.setPosition(pos.x, pos.y); 
        //text.setPosition(pos.x, GetHeight() - pos.y); 
                                                
	window.pushGLStates();
	window.draw(text);
	window.popGLStates();	     	
}

   
