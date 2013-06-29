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

BaseButton::BaseButton(int subtype_id, const std::string& info, void (*pAction)(Player*), TextureOb* textureOb):BaseGuiElement(subtype_id, info, textureOb)
{
	textureOb_additional = nullptr;
	textureOb_mask = nullptr;
		
	alpha = 1.0f;
	lock  = false;
	pressed = false;
	
	animation_scale = new AnimationEffect2D(Vec2<float>(0.7, 0.7), Vec2<float>(1.3, 1.3), Vec2<float>(0.02, 0.02), 0, 0, 0);
	
	this->pAction = pAction;
}

BaseButton::~BaseButton()
{
	delete animation_scale;
}

/* virtual override */
void BaseButton::ResetState()
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
   
/* virtual override */   		    
void BaseButton::RenderInfo() const
{
	Vec2<float> pos(box.GetCenter().x, box.GetCenter().y);
	drawSimpleColoredTextWithBackground(info, 12, pos, Color4<int>(255, 255, 255, 255));
}

/* virtual override */
void BaseButton::RenderUnique() const
{
	//if (textureOb_mask != nullptr)
   	//{
   		//animation_scale->Update(rect1);
   	//}
   	
	setColor4f(1.0f, 1.0f, 1.0f, alpha);

   	drawQuad_inXYPlane(textureOb, box);
   	
   	if (textureOb_additional != nullptr)
   	{
   	   	drawQuad_inXYPlane(textureOb_additional, box);
   	}
	setColor4f(1.0f, 1.0f, 1.0f, 1.0f);

   	if (textureOb_mask != nullptr)
   	{
   	   	drawQuad_inXYPlane(textureOb_mask, box);
   	}
   		
	if (label != "")
	{
		Vec2<float> pos(box.GetCenter().x, box.GetCenter().y + box.GetSize().y );
		Screen::Instance().DrawText(label, 12, pos);
	}
}
		
