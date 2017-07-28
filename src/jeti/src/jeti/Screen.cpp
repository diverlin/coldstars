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
//#include <jeti/Render.hpp>

#include <client/common/global.hpp>

#include <constants.hpp>
#include <meti/RandUtils.hpp> // remove

#include <iostream>

namespace jeti {

void Screen::init()
{
    Config config;
    int width      = config.width;
    int height     = config.height;
    int bpp        = config.bpp;
    bool vsync     = config.vsync;
    int fps_limit  = config.fps_limit;

    std::string title("coldstars");
    
    wrCreateWindowSpecific(width, height, bpp, vsync, fps_limit, title);
}

//void Screen::updateInSpace()
//{
//    jeti::Camera& camera = client::global::get().camera();
//    m_rect.SetBottomLeft(camera.target().x, camera.target().y);
//    //if (auto_scroll == true)
//    //{
//    //glm::vec2 d_pos;
//    //float speed = 15.0;
//    //get_dPos_ToPoint(rect.center(), target_center, speed, d_pos);
//    //MovingBy(d_pos);
//    //if ( ( fabs(rect.center().x - target_center.x) < speed ) and ( fabs(rect.center().y - target_center.y) < speed ) )
//    //{
//    //auto_scroll = false;
//    //}
//    //}
//}

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
    
    wrDrawSpecific();
}

} // namespace jeti

