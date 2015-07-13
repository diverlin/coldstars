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
#include <Render.hpp>

#include <jeti/Config.hpp>

#include <constants.hpp>
#include <meti/RandUtils.hpp> // remove

#include <iostream>

namespace jeti {

Screen& Screen::Instance()
{
    static Screen instance;
    return instance;
}
    
Screen::Screen()
:
fps(0), 
frames_counter(0), 
last_time(0.0), 
scale(1.0), 
d_scale(0.0)
{}

Screen::~Screen()
{}

void Screen::InitRenderStuff()
{
    Config config;
    int width      = config.width;
    int height     = config.height;
    int bpp        = config.bpp;
    bool vsync     = config.vsync;
    int fps_limit  = config.fps_limit;

    std::string title("coldstars");

    auto_scroll = false;
    
    wrCreateWindowSpecific(width, height, bpp, vsync, fps_limit, title);
    
    glewInit();             
    m_Render.Init(width, height);
    
    rect.Set(0.0, 0.0, width, height);
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
    
    //std::string fps_str = "FPS:" + std::to_string(fps) + " / game_speed: x" + std::to_string(global::get().config().GAME_SPEED);
    //DrawText(fps_str, 14, glm::vec2(100, GetHeight()-10));
    if (meti::getRandInt(0, 30) == 0) std::cout<<"fps="<<fps<<std::endl;
}
    
    
     
void Screen::Resize(int width, int height)
{
    //m_Render.SetOrthogonalProjection(width, height);
    
    //wrResizeSpecific(width, height);
    
    //if (global::get().config().MODERN_EFFECTS == true)
    //{
        //ResizePostEffects(width, height);
    //}
}
    
  
void Screen::MovingBy(const glm::vec2& delta)
{
    rect.MovingBy(delta);
}

void Screen::UpdateInSpace()
{   
    rect.SetBottomLeft(m_Camera.GetPos().x, m_Camera.GetPos().y);
    //if (auto_scroll == true)
    //{
        //glm::vec2 d_pos;
        //float speed = 15.0;
        //get_dPos_ToPoint(rect.center(), target_center, speed, d_pos);
        //MovingBy(d_pos);
        //if ( ( fabs(rect.center().x - target_center.x) < speed ) and ( fabs(rect.center().y - target_center.y) < speed ) )
        //{
            //auto_scroll = false;
        //}
    //}
}
        
void Screen::Draw()
{
    //glPushMatrix();
    //glLoadIdentity();
    //enable_BLEND();
    //TextureOb* texOb = GuiTextureObCollector::Instance().radar_screenrect;
    //Rect rect2(rect);
    ////rect2.Scale(scale);
    //drawTexturedRect(texOb, rect2, -2.0);
    //glPopMatrix();
    
    DrawFps();
    wrDrawSpecific();
}

void  Screen::IncreaseScale() 
{ 
    d_scale = 0.15;
    if (scale < 30.0)
    {
        scale += d_scale;
        
        glm::vec2 center = rect.center();
        float rate = 0.5*d_scale;
        float offset_x = rect.GetWidth()*rate;
        float offset_y = rect.GetHeight()*rate;
        glm::vec2 offset(offset_x, offset_y);
        rect.setCenter(center-offset);
    } 
}

void Screen::DecreaseScale() 
{ 
    d_scale = -0.15;
    if (scale > 0.3)
    {
        scale += d_scale;
        
        glm::vec2 center = rect.center();
        float rate = 0.5*d_scale;
        float offset_x = rect.GetWidth()*rate;
        float offset_y = rect.GetHeight()*rate;
        glm::vec2 offset(offset_x, offset_y);
        
        rect.setCenter(center-offset);
    } 
}

}
   
