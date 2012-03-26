#include "window.hpp"
#include <boost/lexical_cast.hpp>
//#include "../common/rand.hpp"
namespace Gui
{
    Window& Window::instanse()
    {
      static Window display_;
      return display_;
    }
    
    Window::Window():general_window(sf::VideoMode(800, 600, 32), "cold star V0.0.4.50 (SFML/C++)"){}
    Window::~Window(){}
    
    sf::RenderWindow& Window::GetWindow(){ return general_window;}
    sf::Font& Window::GetFont(){ return font;}

    void Window::Update()
    {
      DrawFsp();
    }
    void Window::DrawFsp()
    {
      float fps = 1.f / general_window.GetFrameTime();
      sf::String _str(std::string("FPS:" + 
						boost::lexical_cast<std::string>( (int)fps) )
					, font, 14);
      _str.SetColor(sf::Color(255, 255, 255));
      _str.SetPosition(100, 15);
      general_window.Draw(_str);
    }
    

    sf::RenderWindow& GetWindow(){ return Gui::Window::instanse().GetWindow();}
    sf::Font& GetFont(){ return Gui::Window::instanse().GetFont();}
    void Update(){Gui::Window::instanse().Update();}
}
   
