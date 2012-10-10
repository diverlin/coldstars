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
    
Screen::Screen()
{}

Screen::~Screen()
{}

void Screen::InitBasic(int width, int height, int bpp, bool vert_sync, const std::string& title)
{	
      	this->bpp = bpp;
      	this->vert_sync = vert_sync;
      	auto_scroll = false;
      	
      	render_window.Create(sf::VideoMode(width, height, bpp), title);
      	render_window.SetFramerateLimit(Config::Instance().FPS_LIMIT); 
    	render_window.UseVerticalSync(vert_sync);
    	render_window.PreserveOpenGLStates(true);
    	 	
      	initGl(width, height);
      	
      	rect.Set(0.0, 0.0, width, height);
}

void Screen::InitPostEffects(int width, int height)
{
 	fbo0.Create();
	fbo1.Create();	
	fbo2.Create();
	fbo3.Create();
	
	bloom.Create(ShaderCollector::Instance().blur, ShaderCollector::Instance().extractbright, ShaderCollector::Instance().combine);
	
	ResizePostEffects(width, height);
}
	       	
void Screen::DrawFps()
{
	float fps = 1.f / render_window.GetFrameTime();
      	sf::String _str(std::string("FPS:" + boost::lexical_cast<std::string>( (int)fps) +" / GAMESPEED: x" + boost::lexical_cast<std::string>( Config::Instance().GAMESPEED) ), font, 14);
      	_str.SetColor(sf::Color(255, 255, 255));
      	_str.SetPosition(100, 15);
      	render_window.Draw(_str);
}
    
    
     
void Screen::Resize(int width, int height)
{
	resizeGl(width, height);
	
	view.SetFromRect(sf::FloatRect(0, 0, width, height));
	render_window.SetView(view);	
	render_window.SetSize(width, height);
	
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
		float speed = 30.0;
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
  	render_window.Display();
}



   
