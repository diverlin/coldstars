#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "../common/myVector.hpp"
#include "../render/fbo.hpp"
#include "../render/bloom.hpp"

class Screen:private sf::NonCopyable
{
	public:
      		static Screen& Instance();
      		sf::RenderWindow& GetWindow() { return render_window; };
      		sf::Font& GetFont() { return font; };
      		void Update();
      		
      		 	void SetBottomLeftGlobalCoord(vec2f bottomLeft_globalCoord) { this->bottomLeft_globalCoord = bottomLeft_globalCoord; UpdateOnEvent(); };
        	
        	int GetWidth() const  { return width; };
        	int GetHeight() const { return height; };
        	     	
        	const vec2f& GetTopRightGlobalCoord()   const { return topRight_globalCoord; };
        	const vec2f& GetBottomLeftGlobalCoord() const { return bottomLeft_globalCoord; };
        	     			
        	FBO* GetFbo0() const { return fbo0; };
		FBO* GetFbo1() const { return fbo1; };
		FBO* GetFbo2() const { return fbo2; };
		FBO* GetFbo3() const { return fbo3; }

		BloomEffect* GetBloom() const { return bloom; };	
		
		void MovingBy(vec2f);

        	void Resize(int, int);
        					
		void Display();	

    	private:
      		Screen();
      		~Screen();
      		Screen(const Screen&) = delete;
      		Screen& operator=(const Screen&) = delete;

      		sf::RenderWindow render_window;
      		sf::Font font;
      
            		int width, height;
      		int bpp;
      		bool vert_sync;
      		
      		FBO* fbo0;
		FBO* fbo1;
		FBO* fbo2;
		FBO* fbo3;

		BloomEffect* bloom;
      		
      		vec2f topRight_globalCoord;
      		vec2f bottomLeft_globalCoord;
      		
      		sf::View view;
      		
      		void InitGl();
      		void ResizeGl();
      		
      		void ResizePostProcess();
		void UpdateOnEvent();
		
      		void DrawFsp();
};


#endif

