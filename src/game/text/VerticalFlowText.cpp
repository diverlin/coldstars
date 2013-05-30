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

#include "VerticalFlowText.hpp"
#include "../common/rand.hpp"
#include "../render/Render.hpp"
#include "../render/Screen.hpp"

VerticalFlowText::VerticalFlowText(const std::string& str, 
					int font_size,
                                        const Vec2<float>& center, 
                                        const Color4<int>& color, 
                                        float collision_radius)
{
        is_alive = true;
        live_time = 70; //TEXT_EXISTANCE_TIME

        this->str = str;
        this->font_size = font_size;
        this->color = color;


        float kof1 = 0.1 * getRandInt(3, 18);
        float kof2 = 0.1 * getRandInt(5, 15);

        pos.x = center.x - collision_radius * kof1;
        pos.y = center.y + collision_radius * kof2;
        
        speed = 2.0;
}

VerticalFlowText::~VerticalFlowText()
{}

void VerticalFlowText::update()
{
        if (is_alive == true)
        {
                pos.y += speed;
                if (speed > 0.5)
                {
                        speed -= 0.1;
                }

                live_time -= 1;
                if (live_time < 0)
                {
                        is_alive = false;
                }
        }
}
                
void VerticalFlowText::Render(const Vec2<float>& scroll_coords) const
{
        if (is_alive == true)
        {
                Screen::Instance().DrawText(str, font_size, pos-scroll_coords, color);
        }
}
 

