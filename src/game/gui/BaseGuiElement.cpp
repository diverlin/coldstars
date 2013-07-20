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

std::map<GUI::eTYPE, BaseGuiElement*> BaseGuiElement::static_gui_element_map;

BaseGuiElement::BaseGuiElement(GUI::eTYPE subtype_id, const std::string& info, TextureOb* textureOb, BaseGuiElement* parent):
m_Subtype_id(subtype_id),
m_Info(info),
m_TextureOb(textureOb),
//m_Parent(parent),
m_Show(true),
m_Root(true),
m_Lock(false),
m_Pressed(false)
{
	m_Scale.Set(1.0, 1.0, 1.0);
}

/* virtual */
BaseGuiElement::~BaseGuiElement()
{
	for (std::vector<BaseGuiElement*>::iterator it=m_Child_vec.begin(); it!=m_Child_vec.end(); it++)
	{
		delete *it;
	}
}	
      	
BaseGuiElement* BaseGuiElement::GetGuiElement(GUI::eTYPE request_subtype_id) const
{
	std::map<GUI::eTYPE, BaseGuiElement*>::const_iterator it = static_gui_element_map.find(request_subtype_id);
	if (it != static_gui_element_map.cend())
	{
		return it->second;
	}
	
	return nullptr;
}   
	
void BaseGuiElement::PressEventOnGuiElement(GUI::eTYPE subtype_id)
{
	BaseGuiElement* button = GetGuiElement(subtype_id);
	if (button != nullptr)
	{
		button->PressEvent(m_Player);
	}
	#if GUI_LOG_ENABLED == 1
	else
	{
		Logger::Instance().Log("BaseGuiElement::PressEventOnGuiElement, unknown subtype_id", GUI_LOG_DIP);
	}
	#endif

}	

void BaseGuiElement::ResetStateEventOnGuiElement(GUI::eTYPE subtype_id)
{
	BaseGuiElement* button = GetGuiElement(subtype_id);
	if (button != nullptr)
	{
		button->ResetState();
	}
	#if GUI_LOG_ENABLED == 1
	else
	{
		Logger::Instance().Log("BaseGuiElement::ResetEventOnGuiElement, unknown subtype_id", GUI_LOG_DIP);
	}
	#endif
}	
			
/* virtual */
void BaseGuiElement::ResetState()
{
	m_Pressed = false;
	m_Lock = false;
}

void BaseGuiElement::AddChild(BaseGuiElement* child, const Vec3<float>& offset) 
{ 
	//child->SetParent(this);
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

void BaseGuiElement::UpdateGeometry(const Vec3<float>& parent_offset, const Vec3<float>& parent_scale)
{
	if (!m_Show)
	{
		return;
	}
	
	Vec3<float> next_offset = m_Offset*m_Scale + parent_offset*parent_scale;
	Vec3<float> next_scale = parent_scale*m_Scale;
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
        UpdateGeometry(Vec3<float>(0,0,0), Vec3<float>(1,1,1));
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
		RenderCommon(player);
		RenderUnique(player);
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
