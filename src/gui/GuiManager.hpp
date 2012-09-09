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

#include "../gui/GuiRadar.hpp"
#include "../gui/GuiVehicle.hpp"
#include "../gui/GuiSkill.hpp"
#include "../gui/GuiKosmoport.hpp"
#include "../gui/GuiAngar.hpp"
#include "../gui/GuiStore.hpp"
#include "../gui/GuiShop.hpp"
#include "../gui/GuiSpace.hpp"
#include "../gui/GuiMap.hpp"
				
class GuiManager
{
   	public:
      		GuiManager();
      		~GuiManager();

		void SetPlayer(Player*);
		
		bool RunSession(const MouseData&);
		GuiRadar& GetGuiRadar() { return gui_radar; };
		GuiVehicle& GetGuiVehicle() { return gui_vehicle; };
		      		
      	private:
      		Player* player;
      		
      		GuiVehicle 	gui_vehicle;
      		GuiSkill   	gui_skill;
      		GuiKosmoport 	gui_kosmoport;
      		GuiAngar 	gui_angar;
                GuiStore 	gui_store;
                GuiShop        	gui_shop;
      		GuiSpace     	gui_space;      
		GuiMap       	gui_map;      		
       		GuiRadar 	gui_radar;
       		
       		Slider slider;     
       		
     		bool UpdateMouseInteractionWithScanVehicle(const MouseData&, Vehicle*, bool allow_full_control = false);     		
     		bool UpdateMouseInteractionWithScanVehicleAsWeaponTarget(const MouseData&, Vehicle*);   
     		
     		void RenderScanVehicle(const MouseData&, Vehicle*, bool show_skill = true) const;  	
};



#endif
