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

#ifndef GUIKOSMOPORT_H
#define GUIKOSMOPORT_H

#include "BaseGuiElement.hpp"
#include "../gui/GuiAngar.hpp"
#include "../gui/GuiStore.hpp"
#include "../gui/GuiShop.hpp"
#include "../gui/GuiGoverment.hpp"

class GuiVehicle;
class GuiSkills;
class GuiGalaxyMap;
class Slider;

class GuiKosmoport : public BaseGuiElement
{
        public:
               GuiKosmoport();
               ~GuiKosmoport();
                                
                void SetPlayer(Player*);
                void BindKosmoport(Kosmoport*);
                void UnbindKosmoport();
                
                void BindSharedGuis(GuiGalaxyMap*, GuiVehicle*, GuiSkills*, Slider*);
                void UnbindSharedGuis();                
          
                void EnterGuiScanInAngar();
                void ExitGuiScan();
                                
                void EnterGuiStoreScreen();
                void ExitGuiStoreScreen();
                
                bool GetInitDone() const { return init_done; };
                
                void ButtonsAction();
                                
                bool Update(const MouseData&);
                void Render(const MouseData&);
                
                                void EnterGuiAngarScreen();
                                
        private:
                bool init_done;                                                                             
                                
                int active_screen_id; 
                
                Kosmoport* kosmoport;
                                
              GuiAngar     gui_angar;
                GuiStore     gui_store;
                GuiShop            gui_shop;
                GuiGoverment    gui_goverment;  
              
                GuiGalaxyMap* gui_galaxymap_shared;  
                GuiVehicle*   gui_vehicle_scan_shared;
                GuiSkills*    gui_skills_shared;
                Slider*       slider_shared;
                

                void ExitGuiAngarScreen();
                                
                void EnterGuiShopScreen();
                void ExitGuiShopScreen();

                void EnterGuiGalaxyMapScreen();
                void ExitGuiGalaxyMapScreen();
                
                void EnterGuiGovermentScreen();
                void ExitGuiGovermentScreen();
                
                void ExitCurrentScreen();
};


#endif 
