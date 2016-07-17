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


#ifndef GUIMANAGER_HPP
#define GUIMANAGER_HPP

class GuiSkill;
class GuiGalaxyMap;

#include <gui/GuiKosmoport.hpp>
#include <gui/GuiSpace.hpp>
#include <gui/GuiNatureLand.hpp>


class GuiManager
{
    public:
        static GuiManager& Instance();
        ~GuiManager();
        
        void SetPlayer(Player*);
        
        GuiKosmoport& GetGuiKosmoport() { return gui_kosmoport; };
        GuiSpace& GetGuiSpace() { return gui_space; };
        
        GuiVehicle* GetGuiVehicleScan() const { return gui_vehicle_scan; };
        GuiGalaxyMap* GetGuiGalaxyMap() const { return gui_galaxymap; };
                
        void UpdateSessionInSpace();                                
        void RunSessionInKosmoport(const MouseData&);
        void RunSessionInNatureLand(const MouseData&);

        void EnterGuiKosmoport();
        void ExitGuiKosmoport();                
        
        void EnterGuiSpace();
        void ExitGuiSpace(); 
        
        bool UpdateMouseInteractionWithScanVehicle(const MouseData&);             
        void RenderScanVehicle(const MouseData&, bool show_skill = true) const;  
            
        void PressEventMBL_onGuiElement(type::GUI);
        void ResetEventOnGuiElement(type::GUI);
        BaseGuiElement* GetGuiElement(type::GUI) const;
                
    private:
        GuiManager();
        GuiManager(const GuiManager&) = delete;
        GuiManager& operator=(const GuiManager&) = delete;
        
        std::vector<int> command_vec;
        
        Player* player;
        
        GuiKosmoport     gui_kosmoport;
        GuiSpace         gui_space;
        GuiNatureLand     gui_natureland;
        
        // shared guis
        GuiVehicle*     gui_vehicle_scan;
        GuiGalaxyMap*   gui_galaxymap;
        
        GuiSkills*       gui_skills;
        Slider*         slider;  
};
  
#endif
