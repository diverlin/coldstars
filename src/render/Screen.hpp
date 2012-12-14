#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "../common/myVector.hpp"
#include "../render/Fbo.hpp"
#include "../render/Bloom.hpp"
#include "../common/rect.hpp"


class Screen:private sf::NonCopyable
{
	public:
      		static Screen& Instance();
        	void InitBasic(int width, int height, int bpp, bool vert_sync, const std::string&);
      		void InitPostEffects(int, int);
                
              	sf::RenderWindow& GetWindow() { return render_window; };
      		sf::Font& GetFont() { return font; };      			
       	     	
        	Rect& GetRect() { return rect; };
        	     			
        	Fbo& GetFbo0() { return fbo0; };
		Fbo& GetFbo1() { return fbo1; };
		Fbo& GetFbo2() { return fbo2; };
		Fbo& GetFbo3() { return fbo3; }
		Fbo& GetFbo4() { return fbo4; }
		BloomEffect& GetBloom() { return bloom; };	
		
		const sf::Clock& GetPreciseClock() const { return precise_clock; };
		
		void MovingBy(const vec2f&);
		void InitiateScrollTo(const vec2f& scroll_coord) { target_center = scroll_coord; auto_scroll = true; };
		void UpdateInSpace();
		
        	void Resize(int, int);   
			
		void Draw();	

    	private:
      		Screen();
      		~Screen();
      		Screen(const Screen&) = delete;
      		Screen& operator=(const Screen&) = delete;

      		int bpp;
      		bool vert_sync;
      		
      		bool auto_scroll;
      		
      		sf::Clock precise_clock;
      			
      		sf::RenderWindow render_window;
      		sf::Font font;
      		sf::View view;
      		
      		Fbo fbo0;
		Fbo fbo1;
		Fbo fbo2;
		Fbo fbo3;
		Fbo fbo4;
		
		BloomEffect bloom;
      		
      		Rect rect;
      		vec2f target_center;
      				
      		void ResizePostEffects(int, int);
		
      		void DrawFps();
};


#endif

