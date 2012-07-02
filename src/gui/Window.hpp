#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Window:private sf::NonCopyable
{
	public:
      		static Window& Instance();
      		sf::RenderWindow& GetWindow() { return render_window; };
      		sf::Font& GetFont() { return font; };
      		void Update();

    	private:
      		Window();
      		~Window();
      		Window(const Window&) = delete;
      		Window& operator=(const Window&) = delete;

      		sf::RenderWindow render_window;
      		sf::Font font;
      
      		void DrawFsp();
};


#endif

