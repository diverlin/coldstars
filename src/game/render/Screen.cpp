/*
	Copyright (C) ColdStars, Aleksandr Pivovarov <<coldstars8@gmail.com>>
	
	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.
	
	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	
	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

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
    
Screen::Screen():fps(0), frames_counter(0), last_time(0.0)
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
	float now_time = GetElapsedTimeInSeconds();
	if ((now_time - last_time) > 1.0)
	{
		fps = frames_counter;
		frames_counter = 0;
		last_time = now_time;
	}
	else
	{
		frames_counter++;
	}
	
      	std::string fps_str = "FPS:" + int2str(fps) + " / game_speed: x" + int2str(Config::Instance().GAME_SPEED);
	DrawText(fps_str, 14, Vec2<float>(100, GetHeight()-5));
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

void Screen::MovingBy(const Vec2<float>& delta)
{
	rect.MovingBy(delta);
}

void Screen::UpdateInSpace()
{	
	if (auto_scroll == true)
	{
		Vec2<float> d_pos;
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


   
