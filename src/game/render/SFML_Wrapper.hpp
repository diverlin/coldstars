#ifndef WINDOWWRAPPER_H
#define WINDOWWRAPPER_H

#include <SFML/Graphics.hpp>
#include "../math/myVector.hpp"

class SFML_Wrapper
{
	public:
      		SFML_Wrapper();
      		~SFML_Wrapper();
      		      		
        	void wrCreateWindowSpecific(int width, int height, int bpp, bool vert_sync, const std::string&);
                
                int GetWidth() const { return window.getSize().x; };
                int GetHeight() const { return window.getSize().y; };
                                
      		sf::Font& GetFont() { return font; }; 
      		sf::RenderWindow& GetWindow() { return window; };
      		
		float GetElapsedTimeInSeconds() { return clock.getElapsedTime().asSeconds(); };
				
		void wrResizeSpecific(int width, int height);

		void wrDrawSpecific();
		
		void DrawText(const std::string& str, int font_size, const Vec2<float>& pos);
		void DrawText(const std::string& str, int font_size, const Vec2<float>& pos, const Color4<int>& color);

    	private:
      		int bpp;
      		bool vert_sync;

      		sf::Clock clock;
      		sf::Font font;
      		sf::View view;
      		sf::RenderWindow window;
};

#endif

