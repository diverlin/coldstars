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


#include "button.hpp"

Button :: Button(TextureOb* _texOb, 
		 int _subtype_id, 
		 float _pos_x, 
		 float _pos_y, 
		 int _w, 
		 int _h, 
		 std::string _info_str)
{
	type_id = GUI::BUTTON::BUTTON_ID;
	subtype_id = _subtype_id;
	
    	texOb = _texOb;
    
    	rect = Rect(_pos_x, _pos_y, _w, _h);
    	info_str = _info_str; 
    	show_info = false; 
}

Button :: ~Button()
{}

void Button :: setShowInfoFlag(bool _show_info)   { show_info = _show_info; }
bool Button :: getShowInfoFlag() const { return show_info; }
Rect Button :: getRect() const         { return rect; }
TextureOb* Button :: getTexOb()        { return texOb; }
int Button :: getTypeId() const        { return subtype_id; }
int Button :: getSubTypeId() const     { return subtype_id; }

bool Button :: interaction(int _x, int _y)
{        
    	float dist = distBetweenPoints(rect.getCenter().x, rect.getCenter().y, _x, _y);
    	if (dist < rect.getWidth()/2)
        	return true;
    	else
        	return false;    
}
    
void Button :: setCenter(int _x, int _y)
{        
     	rect.setCenter((float)_x, (float)_y);
}
   
void Button :: render() const
{
   	drawTexturedRect(texOb, rect, -1);
}

void Button :: renderInfo() const
{
     	drawSimpleText(info_str, 12, rect.getBottomLeft().x - 50, rect.getBottomLeft().y + 30);
}
