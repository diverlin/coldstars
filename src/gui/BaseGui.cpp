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



BaseGui::BaseGui()
{}


BaseGui::~BaseGui()
{
	for (std::map<int, BaseButton*>::iterator iterator = button_map.begin(); iterator!=button_map.end(); iterator++)
	{
		delete iterator->second;
	}
}	
      		
BaseButton* BaseGui::GetButton(int request_subtype_id) const
{
	for (std::map<int, BaseButton*>::const_iterator iterator = button_map.begin(); iterator!=button_map.end(); iterator++)
	{
		if (iterator->first == request_subtype_id)
		{
			return iterator->second; 
		}
	}
	
	return NULL;
} 
      

bool BaseGui::UpdateButtonsMouseInteraction(int mxvp, int myvp, int lmb, int rmb)
{
	for (std::map<int, BaseButton*>::iterator iterator = button_map.begin(); iterator!=button_map.end(); iterator++)
	{
		iterator->second->Update();
        	if (iterator->second->CheckInteraction(mxvp, myvp) == true)
        	{
           		if (lmb == true)
           		{
       				iterator->second->PressEvent();
           		}
           		return true;
        	}
     	}
     	
     	return false;
}
		       		
void BaseGui::RenderButtons() const
{
	glPushMatrix();
	{
		glTranslatef(offset.x, offset.y, 0);
		for (std::map<int, BaseButton*>::const_iterator iterator = button_map.begin(); iterator!=button_map.end(); iterator++)
		{
			iterator->second->Render();
       		}
       	}
       	glPopMatrix();
}

void BaseGui::RenderFocusedButtonInfo(int mxvp, int myvp) const
{
	for (std::map<int, BaseButton*>::const_iterator iterator = button_map.begin(); iterator!=button_map.end(); iterator++)
	{	
                if (iterator->second->CheckInteraction(mxvp - offset.x, myvp - offset.y) == true)
                {
        		iterator->second->RenderInfo(offset.x, offset.y);
        		return; break;
        	}
        }
}

