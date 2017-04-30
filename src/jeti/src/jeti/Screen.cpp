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
#include <jeti/Camera.hpp>

#include <jeti/Config.hpp>

#include <client/common/global.hpp>

#include <constants.hpp>
#include <meti/RandUtils.hpp> // remove

#include <iostream>

namespace jeti {

Screen::Screen()
{}

Screen::~Screen()
{}

void Screen::init()
{
    Config config;
    int width      = config.width;
    int height     = config.height;
    int bpp        = config.bpp;
    bool vsync     = config.vsync;
    int fps_limit  = config.fps_limit;

    std::string title("coldstars");

    m_autoScroll = false;
    
    wrCreateWindowSpecific(width, height, bpp, vsync, fps_limit, title);

    m_rect.set(0.0, 0.0, width, height);
    m_data.resize(width, height);
}

void Screen::__drawFps()
{    
    float now_time = elapsedSeconds();
    if ((now_time - m_lastTime) > 1.0) {
        m_fps = m_framesCounter;
        m_framesCounter = 0;
        m_lastTime = now_time;
    } else {
        m_framesCounter++;
    }
    
    //std::string fps_str = "FPS:" + std::to_string(fps) + " / game_speed: x" + std::to_string(core::global::get().config().GAME_SPEED);
    //DrawText(fps_str, 14, glm::vec2(100, GetHeight()-10));
    if (meti::getRandInt(30) == 0) std::cout<<"fps="<<m_fps<<std::endl;
}



void Screen::resize(int width, int height)
{
    //m_Render.SetOrthogonalProjection(width, height);
    
    //wrResizeSpecific(width, height);
    
    //if (core::global::get().config().MODERN_EFFECTS == true)
    //{
    //ResizePostEffects(width, height);
    //}
}


void Screen::move(const glm::vec2& delta)
{
    m_rect.MovingBy(delta);
}

void Screen::updateInSpace()
{   
    jeti::Camera& camera = client::global::get().camera();
    m_rect.SetBottomLeft(camera.lookTo().x, camera.lookTo().y);
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

void Screen::draw()
{
    //glPushMatrix();
    //glLoadIdentity();
    //enable_BLEND();
    //TextureOb* texOb = GuiTextureObCollector::Instance().radar_screenrect;
    //Rect rect2(rect);
    ////rect2.Scale(scale);
    //drawTexturedRect(texOb, rect2, -2.0);
    //glPopMatrix();
    
    __drawFps();
    wrDrawSpecific();
}

void  Screen::increaseScale()
{ 
    m_deltaScale = SCALE_STEP;
    if (m_data.scale < SCALE_MAX) {
        m_data.scale += m_deltaScale;
        
        glm::vec2 center = m_rect.center();
        float rate = 0.5 * m_deltaScale;
        float offset_x = m_rect.width()*rate;
        float offset_y = m_rect.height()*rate;
        glm::vec2 offset(offset_x, offset_y);
        m_rect.setCenter(center-offset);
    }
}

void Screen::decreaseScale()
{ 
    m_deltaScale = -SCALE_STEP;
    if (m_data.scale > SCALE_MIN) {
        m_data.scale += m_deltaScale;
        
        glm::vec2 center = m_rect.center();
        float rate = 0.5 * m_deltaScale;
        float offset_x = m_rect.width()*rate;
        float offset_y = m_rect.height()*rate;
        glm::vec2 offset(offset_x, offset_y);
        
        m_rect.setCenter(center-offset);
    }
}

} // namespace jeti

