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



VerticalFlowText :: VerticalFlowText(std::string _str, 
                                     vec2f _center, 
                                     Color4i _color, 
                                     float _collision_radius)
{
        is_alive = true;
        live_time = 70; //TEXT_EXISTANCE_TIME

        str = _str;
        color = _color;


        float kof1 = 0.1 * getRandInt(3, 18);
        float kof2 = 0.1 * getRandInt(5, 15);

        pos.x = _center.x - _collision_radius * kof1;
        pos.y = _center.y + _collision_radius * kof2;
        
        speed = 2.0;
}

VerticalFlowText :: ~VerticalFlowText()
{}


bool VerticalFlowText :: GetAlive() const { return is_alive; }
		

void VerticalFlowText :: update()
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
                
void VerticalFlowText :: render(vec2f scroll_coords) const
{
        if (is_alive == true)
        {
                drawSimpleColoredText(str, pos, color, scroll_coords);
        }
}
 








InfoTable :: InfoTable()
{}

InfoTable :: ~InfoTable()
{}

void InfoTable :: clear()
{
    	title_list.clear();
    	value_list.clear();
}

void InfoTable :: addTitleStr(std::string _str)
{
	title_list.push_back(_str);
}

void InfoTable :: addNameStr(std::string _str)
{
	title_list.push_back(_str);
}

void InfoTable :: addValueStr(std::string _str)
{
	value_list.push_back(_str);
}
