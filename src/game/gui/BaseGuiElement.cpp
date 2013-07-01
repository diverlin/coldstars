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
#include "../common/constants.hpp"
#include "../render/MyGl.hpp"
#include "../render/Render.hpp"
#include "../common/Logger.hpp"

std::map<int, BaseGuiElement*> BaseGuiElement::static_gui_element_map;

BaseGuiElement::BaseGuiElement(int subtype_id, const std::string info, TextureOb* textureOb, BaseGuiElement* parent):
subtype_id(subtype_id),
info(info),
textureOb(textureOb),
parent(parent),
show(true),
root(true)
{
	scale.Set(1.0, 1.0, 1.0);
}

BaseGuiElement::~BaseGuiElement()
{
	for (std::vector<BaseGuiElement*>::iterator it = child_vec.begin(); it!=child_vec.end(); it++)
	{
		delete *it;
	}
}	
      	
BaseGuiElement* BaseGuiElement::GetGuiElement(int request_subtype_id) const
{
	std::map<int, BaseGuiElement*>::const_iterator it = static_gui_element_map.find(request_subtype_id);
	if (it != static_gui_element_map.cend())
	{
		return it->second;
	}
	
	return nullptr;
}   
	
void BaseGuiElement::PressEventOnGuiElement(int subtype_id)
{
	BaseGuiElement* button = GetGuiElement(subtype_id);
	if (button != nullptr)
	{
		button->PressEvent(player);
	}
	#if GUI_LOG_ENABLED == 1
	else
	{
		Logger::Instance().Log("BaseGuiElement::PressEventOnGuiElement, unknown subtype_id", GUI_LOG_DIP);
	}
	#endif

}	

void BaseGuiElement::ResetStateEventOnGuiElement(int subtype_id)
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
	pressed = false;
	lock = false;
}

void BaseGuiElement::AddChild(BaseGuiElement* child, const Vec3<float>& offset) 
{ 
	child->SetParent(this);
	child->SetOffset(offset);
	child->SetRoot(false);
	
	child_vec.push_back(child); 
	static_gui_element_map.insert(std::make_pair(child->GetSubTypeId(), child));
}
		
BaseGuiElement* BaseGuiElement::UpdateMouseInteraction(const Vec2<float>& mouse_pos)
{
	if (!show)
	{
		return nullptr;
	}
	
	BaseGuiElement* child_element = nullptr;
	for (auto &child : child_vec)
	{
		child_element = child->UpdateMouseInteraction(mouse_pos);
		if (child_element != nullptr)
		{
			return child_element;
		}
	}
	
	if (!root)
	{	
		if (box.CheckInteraction(mouse_pos) == true)
		{
			return this;
		}
	}
     	
	return nullptr;
}

void BaseGuiElement::UpdateGeometry(const Vec3<float>& parent_offset, const Vec3<float>& parent_scale)
{
	if (!show)
	{
		return;
	}
	
	Vec3<float> next_offset = offset*scale + parent_offset*parent_scale;
	Vec3<float> next_scale = parent_scale*scale;
	box.SetCenter(next_offset);
	box.SetScale(next_scale);
			
	for (auto &child : child_vec)
	{
		child->UpdateGeometry(next_offset, next_scale);
	}
}
 
void BaseGuiElement::Render() const
{
	if (!show)
	{
		return;
	}
	
	enable_BLEND();
	{
		RenderUnique();
		RenderCommon();
	}
	disable_BLEND();
}

/* virtual */
void BaseGuiElement::RenderUnique() const
{
	if (textureOb != nullptr)
	{
		drawNotScaledQuad(textureOb, box);
   	}
}

void BaseGuiElement::RenderCommon() const
{
   	for (auto &gui_element : child_vec)
	{
		gui_element->Render();
	}
}
