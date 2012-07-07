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


#include "Button.hpp"

Button::Button(TextureOb* textureOb, 
		 int subtype_id, 
		 int pos_x, 
		 int pos_y, 
		 int w, 
		 int h, 
		 std::string info_str)
{
	type_id = GUI::BUTTON::BUTTON_ID;
	
	this->subtype_id = subtype_id;
    	this->textureOb = textureOb;
    	this->info_str = info_str; 

	alpha = 1.0f;
	lock = false;
	
    	rect.Set(pos_x, pos_y, w, h);
}

Button::~Button()
{}

bool Button::CheckInteraction(int x, int y)
{        
    	float dist = distBetweenPoints(rect.GetCenter(), x, y);
    	if (dist < rect.GetWidth()/2)
        	return true;
    	else
        	return false;    
}
    
void Button::SetCenter(int x, int y)
{        
     	rect.SetCenter((float)x, (float)y);
}
   
void Button::Update()
{
	if (lock == false)
	{
		if (alpha < 1.0f)
		{
			alpha += 0.01f;
		}
		else
		{
			alpha = 1.0f;
		}
	}
}
          		
void Button::Render() const
{

	glColor4f(1.0f, 1.0f, 1.0f, alpha);
   	drawTexturedRect(textureOb, rect, -1);
}

void Button::RenderInfo(int offset_x, int offset_y) const
{
     	drawSimpleText(info_str, 12, rect.GetBottomLeft().x - 50 + offset_x, rect.GetBottomLeft().y + 30 + offset_y);
}
