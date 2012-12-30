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
#include "../gui/GuiVehicle2.hpp"
#include "../gui/GuiSkill.hpp"
#include "../gui/GuiKosmoport.hpp"
#include "../gui/GuiAngar.hpp"
#include "../gui/GuiStore.hpp"
#include "../gui/GuiShop.hpp"
#include "../gui/GuiGoverment.hpp"
#include "../gui/GuiSpace.hpp"
#include "../gui/GuiGalaxyMap.hpp"
#include "../gui/GuiNatureLand.hpp"
				
class GuiManager
{
   	public:
      		GuiManager();
      		~GuiManager();

		void SetPlayer(Player*);

                bool GetShowGuiGalaxyMap() const { return show_gui_galaxymap; };

		GuiRadar& GetGuiRadar() { return gui_radar; };
		GuiVehicle& GetGuiVehicleScan() { return gui_vehicle_scan; };
		GuiVehicle2& GetGuiVehiclePlayer() { return gui_vehicle_player; };
		GuiVehicle2& GetGuiVehicleTarget() { return gui_vehicle_target; };
		GuiSkill& GetGuiSkill() { return gui_skill; };

		bool UpdateInSpace(const MouseData&);
		void RenderInSpace(const MouseData&);
		
		bool RunSessionInKosmoport(const MouseData&);
		bool RunSessionInNatureLand(const MouseData&);
                
                void EnterGalaxyMapInSpace();
                void ExitGalaxyMapInSpace();
                
                void EnterGuiScanInSpace();
                void EnterGuiScanInAngar();
                void ExitGuiScan();
                
                void EnterGuiAngarScreen();
                void ExitGuiAngarScreen();
               
		void EnterGuiStoreScreen();
                void ExitGuiStoreScreen();
                                
                void EnterGuiShopScreen();
                void ExitGuiShopScreen();

                void EnterGuiGalaxyMapScreen();
                void ExitGuiGalaxyMapScreen();
                
                void EnterGuiGovermentScreen();
                void ExitGuiGovermentScreen();
                
                void ExitCurrentScreen();
                                
      	private:
      		Player* player;

		bool show_gui_galaxymap;                                                                                
        	bool show_gui_scan;
        	bool show_gui_radar;

      		GuiVehicle 	gui_vehicle_scan;
      		GuiVehicle2 	gui_vehicle_player;
      		GuiVehicle2 	gui_vehicle_target;
      		GuiSkill   	gui_skill;
      		GuiKosmoport 	gui_kosmoport;
      		GuiAngar 	gui_angar;
                GuiStore 	gui_store;
                GuiShop        	gui_shop;
                GuiGoverment    gui_goverment;
      		GuiSpace     	gui_space;      
		GuiGalaxyMap    gui_galaxymap;
       		GuiRadar 	gui_radar;
       		GuiNatureLand 	gui_natureland;

       		Slider slider;  

     		bool UpdateMouseInteractionWithScanVehicle(const MouseData&, bool allow_full_control = false);     		
     		bool UpdateMouseInteractionWithPreciseWeaponTarget(const MouseData&);   
     		
     		void RenderScanVehicle(const MouseData&, bool show_skill = true) const;
};



#endif
