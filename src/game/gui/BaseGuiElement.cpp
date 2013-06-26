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
#include "MouseData.hpp"
#include "../common/constants.hpp"
#include "../render/MyGl.hpp"
#include "../render/Render.hpp"
#include "../pilots/Player.hpp"

std::map<int, BaseGuiElement*> BaseGuiElement::static_gui_element_map;

BaseGuiElement::BaseGuiElement(int subtype_id, const std::string info, TextureOb* textureOb, BaseGuiElement* parent):
subtype_id(subtype_id),
info(info),
textureOb(textureOb),
parent(parent)
{}

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
	
/* virtual */
void BaseGuiElement::Reset()
{
	pressed = false;
	lock = false;
}

void BaseGuiElement::AddChild(BaseGuiElement* child, const Vec3<float>& offset) 
{ 
	child->SetParent(this);
	child->SetOffset(offset);

	child_vec.push_back(child); 
	static_gui_element_map.insert(std::make_pair(child->GetSubTypeId(), child));
}
		
bool BaseGuiElement::UpdateMouseInteraction(const MouseData& data_mouse)
{
	for (auto &gui_element : child_vec)
	{
		gui_element->Update();
		if (gui_element->GetBox().CheckInteraction(data_mouse.mx, data_mouse.my))
		{
			bool child_interaction = false;
			for (auto &child : child_vec)
			{
				child_interaction = child->UpdateMouseInteraction(data_mouse);
			}
		
			if (child_interaction == false)
			{
				if (data_mouse.left_click == true)
				{
					gui_element->PressEvent(player);
					return true;
				}
			}
		}
	}
     	
	return false;
}

void BaseGuiElement::UpdateGeometry(const Vec3<float>& parent_offset)
{
	Vec3<float> res_offset = offset + parent_offset;
	box.SetCenter(res_offset);
	//box.SetSize(parent->GetBox().GetSize());
	
	for (auto &gui_element : child_vec)
	{
		gui_element->UpdateGeometry(res_offset);
	}
}
 
void BaseGuiElement::Render() const
{
	enable_BLEND();
		RenderUnique();
		RenderCommon();
	disable_BLEND();
}

/* virtual */
void BaseGuiElement::RenderUnique() const
{
	if (textureOb != nullptr)
	{
		drawQuad_inXYPlane(textureOb, box.GetSize(), box.GetCenter(), box.GetAngle().z);
   	}
}

void BaseGuiElement::RenderCommon() const
{
   	for (auto &gui_element : child_vec)
	{
		gui_element->Render();
	}
}

void BaseGuiElement::RenderChildInfo(const MouseData& data_mouse) const
{
	for (auto &gui_element : child_vec)
	{	
		if (gui_element->GetBox().CheckInteraction(data_mouse.mx, data_mouse.my))
		{
			//gui_element->RenderInfo(center.x, center.y);
			return; break;
		}
	}
}

	
