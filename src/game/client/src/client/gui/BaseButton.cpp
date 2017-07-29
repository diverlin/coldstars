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
#include <common/constants.hpp>
#include <client/common/global.hpp>
#include <ceti/Collision.hpp>
#include <jeti/Render.hpp>
#include <jeti/Screen.hpp>


BaseButton::BaseButton(gui::type type_id, gui::type subtype_id, const std::string& info, void (*pAction)(Player*), jeti::control::Material* textureOb)
:
BaseGuiElement(type_id, subtype_id, info, textureOb),
m_Alpha(1.0f),
m_TextureOb_additional(nullptr),
m_TextureOb_mask(nullptr),    
m_pAction(pAction)
{}

BaseButton::~BaseButton()
{}

/* virtual override */
void BaseButton::ResetState()
{
    SetPressed(false);
    ShadeOff();
}

void BaseButton::LockOn() 
{ 
    SetLocked(true); 
    FullShadeOn();  
};

void BaseButton::LockOff() 
{ 
    SetLocked(false); 
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
void BaseButton::RenderInfo(const jeti::Render&) const
{
    jeti::drawColoredTextWithBackground(GetInfo(), 12, GetBox().center(), glm::ivec4(255, 255, 255, 255));
}

/* virtual override */
void BaseButton::RenderUnique(const jeti::Render& render, Player*) const
{      
    //setColor4f(1.0f, 1.0f, 1.0f, m_Alpha);
    
    if (HasTextureOb() == true)
    {
        render.drawQuad(textureOb(), GetBox());
    }
    
    if (m_TextureOb_additional != nullptr)
    {
        render.drawQuad(*m_TextureOb_additional, GetBox());
    }
    //setColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    
    if (m_TextureOb_mask)
    {
        render.drawQuad(*m_TextureOb_mask, GetBox());
    }
    
    if (GetLabel() != "")
    {
        glm::vec2 pos(GetBox().center().x, GetBox().center().y + GetBox().size().y);
        client::global::get().screen().drawText(GetLabel(), 12, pos);
    }
}
        
