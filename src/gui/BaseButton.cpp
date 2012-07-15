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


#include "BaseButton.hpp"

BaseButton::BaseButton(TextureOb* textureOb, 
		 int subtype_id, 
		 int pos_x, 
		 int pos_y, 
		 int w, 
		 int h, 
		 std::string info)
{
	type_id = GUI::BUTTON::BUTTON_ID;
	
    	this->textureOb = textureOb;
	this->subtype_id = subtype_id;
    	this->info = info; 

	textureOb_additional = NULL;
	
	alpha = 1.0f;
	lock  = false;
	pressed = false;
	
    	rect.Set(pos_x, pos_y, w, h);
}

BaseButton::~BaseButton()
{}

bool BaseButton::CheckInteraction(int x, int y)
{        
    	float dist = distBetweenPoints(rect.GetCenter(), x, y);
    	if (dist < rect.GetWidth()/2)
        	return true;
    	else
        	return false;    
}
    
void BaseButton::SetCenter(int x, int y)
{        
     	rect.SetCenter((float)x, (float)y);
}

void BaseButton::Reset()
{
	pressed = false;
	ShadeOff();
}

void BaseButton::LockOn() 
{ 
	lock = true; 
	FullShadeOn();  
};

void BaseButton::LockOff() 
{ 
	lock = false; 
	ShadeOff();
};

void BaseButton::ShadeOn() 
{
	alpha = 0.4f; 
}

void BaseButton::FullShadeOn() 
{
	alpha = 0.05f; 
}

void BaseButton::ShadeOff() 
{
	alpha = 1.0f; 
}       		
         		
void BaseButton::Render() const
{
	glColor4f(1.0f, 1.0f, 1.0f, alpha);
   	drawTexturedRect(textureOb, rect, -1);
   	if (textureOb_additional != NULL)
   	{
   		drawTexturedRect(textureOb_additional, rect, -1);   	
   	}
}

//void BaseButton::RenderWithTitle(const std::string& title, int offset_x, int offset_y) const
//{
	//Render();
     	//drawSimpleText(info, 12, rect.GetBottomLeft().x  + offset_x, rect.GetBottomLeft().y + offset_y);
//}

void BaseButton::RenderInfo(int offset_x, int offset_y) const
{
     	drawSimpleText(info, 12, rect.GetBottomLeft().x - 50 + offset_x, rect.GetBottomLeft().y + 30 + offset_y);
}
