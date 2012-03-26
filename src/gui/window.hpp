#ifndef WINDOW_H
#define WINDOW_H

//#include <boost/utility.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace Gui
{
  //class Window:private boost::noncopyable
  class Window:private sf::NonCopyable
  {
    public:
      static Window& instanse();
      sf::RenderWindow& GetWindow();
      sf::Font& GetFont();
      void Update();
    private:
      Window();
      ~Window();
      Window(const Window&);
      Window& operator=(const Window&);

      sf::RenderWindow general_window;
      sf::Font font;

      //
      void DrawFsp();
  };
  sf::RenderWindow& GetWindow();
  sf::Font& GetFont();
  void Update();
}

#endif // WINDOW_H

