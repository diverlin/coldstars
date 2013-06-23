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

BaseGuiElement::BaseGuiElement(int subtype_id, const std::string& info, TextureOb* textureOb):
textureOb(textureOb),
subtype_id(subtype_id),
info(info)
{
	type_id = GUI::BUTTON::BUTTON_ID;
}

BaseGuiElement::~BaseGuiElement()
{
	for (std::vector<BaseGuiElement*>::iterator it = child_vec.begin(); it!=child_vec.end(); it++)
	{
		delete *it;
	}
}	
      		
bool BaseGuiElement::UpdateMouseInteraction(const MouseData& data_mouse)
{
	for (std::vector<BaseGuiElement*>::iterator it=child_vec.begin(); it!=child_vec.end(); it++)
	{
		BaseGuiElement gui_element = **it;
		gui_element.Update();
		if (gui_element.GetBox().CheckInteraction(data_mouse.mx - center.x, data_mouse.my - center.y))
		{
			if (data_mouse.left_click == true)
			{
				//gui_element.PressEvent();
			}
			return true;
		}
	}
     	
	return false;
}
		       		
void BaseGuiElement::Render() const
{
	glPushMatrix();
	{
		glTranslatef(center.x, center.y, 0);
		for (std::vector<BaseGuiElement*>::const_iterator it = child_vec.begin(); it!=child_vec.end(); it++)
		{
			BaseGuiElement gui_element = **it;
			gui_element.Render();
		}
	}
	glPopMatrix();
}

void BaseGuiElement::RenderInfo(const MouseData& data_mouse) const
{
	for (std::vector<BaseGuiElement*>::const_iterator it = child_vec.begin(); it!=child_vec.end(); it++)
	{	
		BaseGuiElement gui_element = **it;
		if (gui_element.GetBox().CheckInteraction(data_mouse.mx - center.x, data_mouse.my - center.y))
		{
			//gui_element.RenderInfo(center.x, center.y);
			return; break;
		}
	}
}

