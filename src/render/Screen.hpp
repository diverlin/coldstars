#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "../common/myVector.hpp"
#include "../render/Fbo.hpp"
#include "../render/Bloom.hpp"



class Screen:private sf::NonCopyable
{
	public:
      		static Screen& Instance();
        	void InitBasic(int width, int height, int bpp, bool vert_sync, const std::string&);
      		void InitPostEffects(int, int);
      		      		        	         		
	 	void SetBottomLeftGlobalCoord(const vec2f& bottomLeft_globalCoord) { this->bottomLeft_globalCoord = bottomLeft_globalCoord; UpdateTopRightGlobalCoord(); }; 
	 	void SetCenterGlobalCoord(const vec2f& center_globalCoord);
        
                
              	sf::RenderWindow& GetWindow() { return render_window; };
      		sf::Font& GetFont() { return font; };      			
       	     	
        	const vec2f& GetTopRightGlobalCoord()   const { return topRight_globalCoord; };
        	const vec2f& GetBottomLeftGlobalCoord() const { return bottomLeft_globalCoord; };
        	     			
        	Fbo& GetFbo0() { return fbo0; };
		Fbo& GetFbo1() { return fbo1; };
		Fbo& GetFbo2() { return fbo2; };
		Fbo& GetFbo3() { return fbo3; }
		BloomEffect& GetBloom() { return bloom; };	
		
		const sf::Clock& GetPreciseClock() const { return precise_clock; };
		
		void MovingBy(const vec2f&);

        	void Resize(int, int);   
			
		void Draw();	

    	private:
      		Screen();
      		~Screen();
      		Screen(const Screen&) = delete;
      		Screen& operator=(const Screen&) = delete;

      		int bpp;
      		bool vert_sync;
      		
      		sf::Clock precise_clock;
      			
      		sf::RenderWindow render_window;
      		sf::Font font;
      		sf::View view;
      		
      		Fbo fbo0;
		Fbo fbo1;
		Fbo fbo2;
		Fbo fbo3;

		BloomEffect bloom;
      		
      		vec2f topRight_globalCoord;
      		vec2f bottomLeft_globalCoord;

      		void ResizePostEffects(int, int);
      		
		void UpdateTopRightGlobalCoord();
		
      		void DrawFps();
};


#endif

