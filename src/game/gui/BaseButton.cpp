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
#include "../common/constants.hpp"
#include "../common/Collision.hpp"
#include "../render/Render.hpp"
#include "../render/Screen.hpp"
#include "../render/AnimationEffect2D.hpp"

BaseButton::BaseButton(TextureOb* textureOb, int subtype_id, const std::string& info)
{
	type_id = GUI::BUTTON::BUTTON_ID;
	
    	this->textureOb = textureOb;
	this->subtype_id = subtype_id;
    	this->info = info; 

	textureOb_additional = NULL;
	textureOb_mask = NULL;
		
	alpha = 1.0f;
	lock  = false;
	pressed = false;
	
	animation_scale = new AnimationEffect2D(Vec2<float>(0.7, 0.7), Vec2<float>(1.3, 1.3), Vec2<float>(0.02, 0.02), 0, 0, 0);
}

BaseButton::~BaseButton()
{
	delete animation_scale;
}


void BaseButton::Reset()
{
	pressed = false;
	lock = false;
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
       		    
void BaseButton::RenderInfo(int gui_offset_x, int gui_offset_y) const
{
	Vec2<float> pos(box.GetCenter().x+gui_offset_x, box.GetCenter().y+gui_offset_y);
	drawSimpleColoredTextWithBackground(info, 12, pos, Color4<int>(255, 255, 255, 255));
}

void BaseButton::Render(int offset_x, int offset_y) const
{
	//if (textureOb_mask != NULL)
   	//{
   		//animation_scale->Update(rect1);
   	//}
   	
	setColor4f(1.0f, 1.0f, 1.0f, alpha);

   	drawQuad_inXYPlane(textureOb, box.GetSize(), box.GetCenter(), box.GetAngle().z);
   	
   	if (textureOb_additional != NULL)
   	{
   	   	drawQuad_inXYPlane(textureOb_additional, box.GetSize(), box.GetCenter(), box.GetAngle().z);
   	}
	setColor4f(1.0f, 1.0f, 1.0f, 1.0f);

   	if (textureOb_mask != NULL)
   	{
   	   	drawQuad_inXYPlane(textureOb_mask, box.GetSize(), box.GetCenter(), box.GetAngle().z);
   	}
   		
	if (label != "")
	{
		Vec2<float> pos(box.GetCenter().x + offset_x, box.GetCenter().y + box.GetSize().y + offset_y);
		Screen::Instance().DrawText(label, 12, pos);
	}
}
		
