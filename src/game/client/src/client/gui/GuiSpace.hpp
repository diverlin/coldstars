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

#ifndef GUISPACE_HPP
#define GUISPACE_HPP

#include "BaseGuiElement.hpp"

#include "../gui/GuiRadar.hpp"
#include "../gui/GuiVehicle.hpp"
#include "../gui/GuiVehicle2.hpp"

class GuiVehicle;
class GuiSkills;
class GuiGalaxyMap;
class Slider;
class Renderer;

class GuiSpace : public BaseGuiElement
{
    public:
        GuiSpace();
        ~GuiSpace();
        
        bool GetInitDone() const { return init_done; };
        
        //GuiVehicle2& GetGuiVehicleTarget() { return gui_vehicle_target; };
        
        void BindSharedGuis(GuiGalaxyMap*, GuiVehicle*, GuiSkills*, Slider*);
        void UnbindSharedGuis();
        
        virtual void UpdateUnique(Player*) override final;
                                        
        void Resize(int, int);
        void ButtonsAction(Player*) const;
        
        virtual void RenderUnique(const jeti::Renderer&, Player*) const override final;
                
        void RenderText(const glm::vec2&) const;
        
        void EnterGalaxyMap();
        void ExitGalaxyMap();
        
        void EnterGuiScan();
        void ExitGuiScan();
        
    private:
        bool init_done;
        
        GuiGalaxyMap* gui_galaxymap_shared;  
        //GuiVehicle*   gui_vehicle_scan_shared;
        GuiSkills*    gui_skills_shared;
        Slider*       slider_shared;
        
        bool UpdateMouseInteractionWithPreciseWeaponTarget(const MouseData&);  
};

#endif
