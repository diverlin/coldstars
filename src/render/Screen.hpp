#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "../common/myVector.hpp"
#include "../render/fbo.hpp"
//#include "../render/bloom.hpp"

class Screen:private sf::NonCopyable
{
	public:
      		static Screen& Instance();
        	void InitBasic(int width, int height, int bpp, bool vert_sync, const std::string&);
      		void InitPostEffects(int, int);
      		      		        	         		
	 	void SetBottomLeftGlobalCoord(vec2f bottomLeft_globalCoord) { this->bottomLeft_globalCoord = bottomLeft_globalCoord; }; 
        
              	sf::RenderWindow& GetWindow() { return render_window; };
      		sf::Font& GetFont() { return font; };      			
       	     	
        	const vec2f& GetTopRightGlobalCoord()   const { return topRight_globalCoord; };
        	const vec2f& GetBottomLeftGlobalCoord() const { return bottomLeft_globalCoord; };
        	     			
        	FBO& GetFbo0() { return fbo0; };
		FBO& GetFbo1() { return fbo1; };
		FBO& GetFbo2() { return fbo2; };
		FBO& GetFbo3() { return fbo3; }

		BloomEffect* GetBloom() const { return bloom; };	
		
		void MovingBy(vec2f);

        	void Resize(int, int);
   
      		void Update();     					
		void Display();	

    	private:
      		Screen();
      		~Screen();
      		Screen(const Screen&) = delete;
      		Screen& operator=(const Screen&) = delete;

      		int bpp;
      		bool vert_sync;
      		
      		sf::RenderWindow render_window;
      		sf::Font font;
      		sf::View view;
      		
      		FBO fbo0;
		FBO fbo1;
		FBO fbo2;
		FBO fbo3;

		BloomEffect* bloom;
      		
      		vec2f topRight_globalCoord;
      		vec2f bottomLeft_globalCoord;

      		void ResizePostEffects(int, int);
      		
		void UpdateOnEvent();
		
      		void DrawFsp();
};


#endif

