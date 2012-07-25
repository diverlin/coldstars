#include "Screen.hpp"
#include <boost/lexical_cast.hpp>

#include "../render/Glsl.hpp"


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
      	
      	render_window.Create(sf::VideoMode(width, height, bpp), title);
      	render_window.SetFramerateLimit(Config::Instance().FPS_LIMIT); 
    	render_window.UseVerticalSync(vert_sync);
    	render_window.PreserveOpenGLStates(true);
    	 	
      	initGl(width, height);
}

void Screen::InitPostEffects(int width, int height)
{
 	fbo0.Create();
	fbo1.Create();	
	fbo2.Create();
	fbo3.Create();
	
	bloom.Create(ShadersPack::Instance().blur, ShadersPack::Instance().extractbright, ShadersPack::Instance().combine);
	
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
	bottomLeft_globalCoord += delta;
	UpdateTopRightGlobalCoord();
}

void Screen::UpdateTopRightGlobalCoord()
{
	topRight_globalCoord.Set(bottomLeft_globalCoord.x + render_window.GetWidth(), bottomLeft_globalCoord.y + render_window.GetHeight());
}

void Screen::Draw()
{
  	DrawFps();
  	render_window.Display();
}



   
