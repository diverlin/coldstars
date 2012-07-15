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


#ifndef GUIMANAGER_H
#define GUIMANAGER_H

class GuiManager
{
   	public:
      		GuiManager(Player*);
      		~GuiManager();

		bool RunSession(int, int, bool, bool);
      		
      	private:
      		Player* player;
      		
      		GuiVehicle* 	gui_vehicle;
      		GuiSkill*   	gui_skill;
      		GuiKosmoport* 	gui_kosmoport;
      		GuiAngar* 	gui_angar;
                GuiStore* 	gui_store;
      		GuiSpace*     	gui_space;      
		GuiMap*       	gui_map;    

     		bool UpdateMouseInteractionWithScanVehicle(int, int, int, int, Vehicle*, bool allow_full_control = false);     		
     		void RenderScanVehicle(Vehicle*, int, int, bool show_skill = true) const;  	
};



#endif
