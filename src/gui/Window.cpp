#include "Window.hpp"
#include <boost/lexical_cast.hpp>
//#include "../common/rand.hpp"

Window& Window::Instance()
{
	static Window instance;
      	return instance;
}
    
//Window::Window():general_window(sf::VideoMode(Config::Instance().SCREEN_WIDTH, Config::Instance().SCREEN_HEIGHT, Config::Instance().BPP), GAME_TITLE){}
Window::Window():render_window(sf::VideoMode(800, 600, 32), "init"){}
Window::~Window(){}

void Window::Update()
{
	DrawFsp();
}

void Window::DrawFsp()
{
	float fps = 1.f / render_window.GetFrameTime();
      	sf::String _str(std::string(	"FPS:" + 
                                  	boost::lexical_cast<std::string>( (int)fps) ),
                                  	font, 14);
      	_str.SetColor(sf::Color(255, 255, 255));
      	_str.SetPosition(100, 15);
      	render_window.Draw(_str);
}
    
   
