#include "Screen.hpp"
#include <boost/lexical_cast.hpp>

#include "../resources/ShaderCollector.hpp"
#include "../render/Render.hpp"
#include "../config/config.hpp"
#include "../common/common.hpp"

Screen& Screen::Instance()
{
	static Screen instance;
      	return instance;
}
    
Screen::Screen()/*:RenderWindow(sf::VideoMode(800, 600), "SFML OpenGL", sf::Style::Default, sf::ContextSettings(32))*/
{}

Screen::~Screen()
{}

void Screen::InitBasic(int width, int height, int bpp, bool vert_sync, const std::string& title)
{	
      	this->bpp = bpp;
      	this->vert_sync = vert_sync;
      	auto_scroll = false;
      	
      	create(sf::VideoMode(width, height, bpp), title);
      	setFramerateLimit(Config::Instance().FPS_LIMIT); 
    	setVerticalSyncEnabled(vert_sync);

      	glewInit();    	 	
      	initGl(width, height);
      	
      	rect.Set(0.0, 0.0, width, height);
}

void Screen::InitPostEffects(int width, int height)
{
 	fbo0.Create();
	fbo1.Create();	
	fbo2.Create();
	fbo3.Create();
	fbo4.Create();
		
	bloom.Create(ShaderCollector::Instance().blur, ShaderCollector::Instance().extractbright, ShaderCollector::Instance().combine);
	
	ResizePostEffects(width, height);
}
	       	
void Screen::DrawFps()
{
	//float fps = 1.f / getFrameTime();
      	//sf::Text _str(std::string("FPS:" + boost::lexical_cast<std::string>( (int)fps) +" / game_speed: x" + boost::lexical_cast<std::string>( Config::Instance().GAME_SPEED) ), font, 14);
      	//_str.setColor(sf::Color(255, 255, 255));
      	//_str.setPosition(100, 10);
      	//render_window.draw(_str);
}
    
    
     
void Screen::Resize(int width, int height)
{
	resizeGl(width, height);
	
	view.setViewport(sf::FloatRect(0, 0, width, height));
	setView(view);
	sf::Vector2u size(width, height);
	setSize(size);
	
	if (Config::Instance().MODERN_EFFECTS == true)
	{
		ResizePostEffects(width, height);
	}
}
	
	
void Screen::ResizePostEffects(int width, int height)
{
	fbo0.Resize(width, height);
	fbo1.Resize(width, height);	
	fbo2.Resize(width, height);
	fbo3.Resize(width, height);
	fbo4.Resize(width, height);
		
	bloom.Resize(width, height);
}

void Screen::MovingBy(const vec2f& delta)
{
	rect.MovingBy(delta);
}

void Screen::UpdateInSpace()
{	
	if (auto_scroll == true)
	{
		vec2f d_pos;
		float speed = 15.0;
		get_dPos_ToPoint(rect.GetCenter(), target_center, speed, d_pos);
		MovingBy(d_pos);
		if ( ( fabs(rect.GetCenter().x - target_center.x) < speed ) and ( fabs(rect.GetCenter().y - target_center.y) < speed ) )
		{
			auto_scroll = false;
		}
	}
}
		
void Screen::Draw()
{
  	DrawFps();
  	display();
}

void Screen::DrawText(sf::Text& text)
{
	pushGLStates();
	draw(text);
	popGLStates();
	     	
}

   
