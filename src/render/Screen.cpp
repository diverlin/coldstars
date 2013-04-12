#include "Screen.hpp"
#include "../common/myStr.hpp"

#include "../resources/ShaderCollector.hpp"
#include "../render/Render.hpp"
#include "../config/config.hpp"
#include "../common/common.hpp"
#include "../common/rand.hpp"

Screen& Screen::Instance()
{
	static Screen instance;
      	return instance;
}
    
Screen::Screen():fps(0.0), loop_begin_time(0.0)
{}

Screen::~Screen()
{}

void Screen::InitBasic(int width, int height, int bpp, bool vert_sync, const std::string& title)
{	
      	auto_scroll = false;
      	
	wrCreateWindowSpecific(width, height, bpp, vert_sync, title);

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
	if (getRandInt(1, 20) == 1)
	{
		fps = 1.f / (GetElapsedTimeInSeconds() - loop_begin_time);
	}

      	std::string fps_str = "FPS:" + int2str((int)fps) + " / game_speed: x" + int2str(Config::Instance().GAME_SPEED);
	DrawText(fps_str, 14, vec2f(100, GetHeight()-5));
}
    
    
     
void Screen::Resize(int width, int height)
{
	resizeGl(width, height);
	
	wrResizeSpecific(width, height);
	
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
  	wrDrawSpecific();
}


   
