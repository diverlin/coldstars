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


#ifndef GUISPACE_H
#define GUISPACE_H

class GuiSpace
{
    	public:
      		GuiSpace(Player*);
       		~GuiSpace();

       		void UpdateMouseInteraction(int, int, int, int);
       		
       		void RenderButtons() const;
       		void RenderFocusedButtonInfo(int, int) const;
       		void RenderText(const vec2f&) const;
       		
       	private:
       		Player* player;
       		
       		std::vector<Button*> button_vec;
       		

};


#endif
