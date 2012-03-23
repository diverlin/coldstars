#include "window.hpp"

namespace Gui
{
    Window& Window::instanse()
    {
      static Window display_;
      return display_;
    }
   
    sf::RenderWindow& Window::GetWindow(){ return general_window;}
    sf::Font& Window::GetFont(){ return font;}
    
    Window::Window():general_window(sf::VideoMode(SCREEN_WIDTH_MIN, SCREEN_HEIGHT_MIN, g_BPP), "cold star V0.0.4.50 (SFML/C++)"){}
    Window::~Window(){}
    
    sf::RenderWindow& GetWindow(){ return Gui::Window::instanse().GetWindow();}
    sf::Font& GetFont(){ return Gui::Window::instanse().GetFont();}
}
   
