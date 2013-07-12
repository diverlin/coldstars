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

BaseButton::BaseButton(GUI::eTYPE subtype_id, const std::string& info, void (*pAction)(Player*), TextureOb* textureOb):BaseGuiElement(subtype_id, info, textureOb)
{
	m_TextureOb_additional = nullptr;
	m_TextureOb_mask = nullptr;
		
	m_Alpha = 1.0f;
	
	m_Animation_scale = new AnimationEffect2D(Vec2<float>(0.7, 0.7), Vec2<float>(1.3, 1.3), Vec2<float>(0.02, 0.02), 0, 0, 0);
	
	m_pAction = pAction;
}

BaseButton::~BaseButton()
{
	delete m_Animation_scale;
}

/* virtual override */
void BaseButton::ResetState()
{
	m_Pressed = false;
	m_Lock = false;
	ShadeOff();
}

void BaseButton::LockOn() 
{ 
	m_Lock = true; 
	FullShadeOn();  
};

void BaseButton::LockOff() 
{ 
	m_Lock = false; 
	ShadeOff();
};

void BaseButton::ShadeOn() 
{
	m_Alpha = 0.4f; 
}

void BaseButton::FullShadeOn() 
{
	m_Alpha = 0.05f; 
}

void BaseButton::ShadeOff() 
{
	m_Alpha = 1.0f; 
}      
   
/* virtual override */   		    
void BaseButton::RenderInfo() const
{
	Vec2<float> pos(m_Box.GetCenter().x, m_Box.GetCenter().y);
	drawSimpleColoredTextWithBackground(m_Info, 12, pos, Color4<int>(255, 255, 255, 255));
}

/* virtual override */
void BaseButton::RenderUnique() const
{
	//if (textureOb_mask != nullptr)
   	//{
   		//animation_scale->Update(rect1);
   	//}
   	
	setColor4f(1.0f, 1.0f, 1.0f, m_Alpha);

    if (m_TextureOb)
    {
   	    drawQuad(m_TextureOb, m_Box);
   	}
    
   	if (m_TextureOb_additional)
   	{
   	   	drawQuad(m_TextureOb_additional, m_Box);
   	}
	setColor4f(1.0f, 1.0f, 1.0f, 1.0f);

   	if (m_TextureOb_mask)
   	{
   	   	drawQuad(m_TextureOb_mask, m_Box);
   	}
   		
	if (m_Label != "")
	{
		Vec2<float> pos(m_Box.GetCenter().x, m_Box.GetCenter().y + m_Box.GetSize().y);
		Screen::Instance().DrawText(m_Label, 12, pos);
	}
}
		
