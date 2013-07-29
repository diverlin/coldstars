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


#include "BaseGuiElement.hpp"
#include <common/constants.hpp>
#include <render/Render.hpp>
#include <common/Logger.hpp>

#include <render/AnimationEffect2D.hpp>


std::map<GUI::TYPE, BaseGuiElement*> BaseGuiElement::static_gui_element_map;

   
BaseGuiElement::BaseGuiElement(GUI::TYPE subtype_id, const std::string& info, TextureOb* textureOb)
:
m_Subtype_id(subtype_id),
m_Lock(false),
m_Pressed(false),
m_Show(true),
m_Root(true),
m_TextureOb(textureOb),
m_Info(info),
m_AnimationProgram(nullptr)
{}

/* virtual */
BaseGuiElement::~BaseGuiElement()
{
	for (std::vector<BaseGuiElement*>::iterator it=m_Child_vec.begin(); it!=m_Child_vec.end(); it++)
	{
		delete *it;
	}
    
    delete m_AnimationProgram;
}	
 
void BaseGuiElement::DeleteAnimationProgram()
{
    if (m_AnimationProgram != nullptr)
    {
        delete m_AnimationProgram;
        m_AnimationProgram = nullptr;
    }
}

      	
BaseGuiElement* BaseGuiElement::GetGuiElement(GUI::TYPE request_subtype_id) const
{
	std::map<GUI::TYPE, BaseGuiElement*>::const_iterator it = static_gui_element_map.find(request_subtype_id);
	if (it != static_gui_element_map.cend())
	{
		return it->second;
	}
	
	return nullptr;
}   
	
void BaseGuiElement::PressEventMBL_onGuiElement(GUI::TYPE subtype_id)
{
	BaseGuiElement* button = GetGuiElement(subtype_id);
	if (button != nullptr)
	{
		button->OnPressEventMBL(m_Player);
	}
}	

void BaseGuiElement::ResetStateEventOnGuiElement(GUI::TYPE subtype_id)
{
	BaseGuiElement* button = GetGuiElement(subtype_id);
	if (button != nullptr)
	{
		button->ResetState();
	}
}	
			
/* virtual */
void BaseGuiElement::ResetState()
{
	m_Pressed = false;
	m_Lock = false;
}

void BaseGuiElement::AddChild(BaseGuiElement* child, const Vec2<float>& offset) 
{ 
	child->SetOffset(offset);
	child->SetRoot(false);
	
	m_Child_vec.push_back(child); 
	static_gui_element_map.insert(std::make_pair(child->GetSubTypeId(), child));
}
		
BaseGuiElement* BaseGuiElement::UpdateMouseInteraction(const Vec2<float>& mouse_pos)
{
	if (!m_Show)
	{
		return nullptr;
	}
	
	BaseGuiElement* child_interacted = nullptr;
	for (const auto &child : m_Child_vec)
	{
		child_interacted = child->UpdateMouseInteraction(mouse_pos);
		if (child_interacted)
		{
			return child_interacted;
		}
	}
	
	if (!m_Root)
	{	
		if (m_Box.CheckInteraction(mouse_pos) == true)
		{
			return this;
		}
	}
     	
	return nullptr;
}

void BaseGuiElement::UpdateGeometry(const Vec2<float>& parent_offset, const Vec2<float>& parent_scale)
{
	if (!m_Show)
	{
		return;
	}
	
	Vec2<float> next_offset = parent_offset + m_Offset;
	Vec2<float> next_scale = parent_scale * m_Box.GetScale();

    m_Box.SetCenter(next_offset);
    m_Box.SetScale(next_scale);
			
	for (auto &child : m_Child_vec)
	{
		child->UpdateGeometry(next_offset, next_scale);
	}
}

void BaseGuiElement::Update(Player* player)
{
	if (!m_Show)
	{
		return;
	}
    
    if (m_Root)
    {
        UpdateGeometry(m_Offset, Vec2<float>(1,1));
    }
	
    UpdateCommon(player);
    UpdateUnique(player);
}
 
/* virtual */
void BaseGuiElement::UpdateUnique(Player*)
{}

void BaseGuiElement::UpdateCommon(Player* player)
{
    for (auto &child : m_Child_vec)
	{      
        child->Update(player);
	}
	
    if (m_AnimationProgram != nullptr)
   	{    
   		m_AnimationProgram->Update(m_Box);
   	}
}

void BaseGuiElement::Render(Player* player) const
{
	if (!m_Show)
	{
		return;
	}
	
    if (m_Root)
    {
        resetRenderTransformation();
    }
    
	enable_BLEND();
	{
		RenderUnique(player);
		RenderCommon(player);
	}
	disable_BLEND();
}

/* virtual */
void BaseGuiElement::RenderUnique(Player* player) const
{
	if (m_TextureOb)
	{
		drawQuad(m_TextureOb, m_Box);
   	}
}

void BaseGuiElement::RenderCommon(Player* player) const
{
   	for (const auto &gui_element : m_Child_vec)
	{
		gui_element->Render(player);
	}
}
