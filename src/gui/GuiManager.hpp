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

class GuiSkill;
class GuiGalaxyMap;

#include "../gui/GuiKosmoport.hpp"
#include "../gui/GuiSpace.hpp"
#include "../gui/GuiNatureLand.hpp"

class GuiManager
{
   	public:
      		GuiManager();
      		~GuiManager();

		void SetPlayer(Player*);

                GuiKosmoport& GetGuiKosmoport() { return gui_kosmoport; };
                GuiSpace& GetGuiSpace() { return gui_space; };
                
		GuiVehicle* GetGuiVehicleScan() const { return gui_vehicle_scan; };
                GuiGalaxyMap* GetGuiGalaxyMap() const { return gui_galaxymap; };

                bool RunSessionInSpace(const MouseData&);                                
                bool RunSessionInKosmoport(const MouseData&);
		bool RunSessionInNatureLand(const MouseData&);
                
                void EnterGuiKosmoport();
                void ExitGuiKosmoport();                
               
                void EnterGuiSpace();
                void ExitGuiSpace(); 
                
                bool UpdateMouseInteractionWithScanVehicle(const MouseData&, bool allow_full_control = false);     		
     		void RenderScanVehicle(const MouseData&, bool show_skill = true) const;  
                                
      	private:
      		Player* player;
                
      		GuiKosmoport 	gui_kosmoport;
      		GuiSpace     	gui_space;
       		GuiNatureLand 	gui_natureland;

                // shared guis
      		GuiVehicle* 	gui_vehicle_scan;
                GuiSkill*   	gui_skill;
                GuiGalaxyMap*   gui_galaxymap;
       		Slider*         slider;  
};



#endif
