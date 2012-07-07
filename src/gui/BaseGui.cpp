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
	for (unsigned int i=0; i<button_vec.size(); i++)
	{
		delete button_vec[i];
	}
}	
      		
void BaseGui::RenderButtons() const
{
	glPushMatrix();
	{
		glTranslatef(offset.x, offset.y, 0);
		for (unsigned int i=0; i<button_vec.size(); i++)
		{
			button_vec[i]->Render();
       		}
       	}
       	glPopMatrix();
}

void BaseGui::RenderFocusedButtonInfo(int mxvp, int myvp) const
{
	for (unsigned int i=0; i<button_vec.size(); i++)
	{		
                if (button_vec[i]->CheckInteraction(mxvp - offset.x, myvp - offset.y) == true)
                {
        		button_vec[i]->RenderInfo(offset.x, offset.y);
        		return; break;
        	}
        }
}

