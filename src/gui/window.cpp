#include "window.hpp"

#include "../common/rand.hpp"
namespace Gui
{
    Window& Window::instanse()
    {
      static Window display_;
      return display_;
    }
    
    Window::Window():general_window(sf::VideoMode(SCREEN_WIDTH_MIN, SCREEN_HEIGHT_MIN, g_BPP), "cold star V0.0.4.50 (SFML/C++)"){}
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
      sf::String _str(std::string("FPS:" + int2str((int)fps)), font, 14);
      _str.SetColor(sf::Color(255, 255, 255));
      _str.SetPosition(100, 15);
      general_window.Draw(_str);
    }
    

    sf::RenderWindow& GetWindow(){ return Gui::Window::instanse().GetWindow();}
    sf::Font& GetFont(){ return Gui::Window::instanse().GetFont();}
    void Update(){Gui::Window::instanse().Update();}
}
   
