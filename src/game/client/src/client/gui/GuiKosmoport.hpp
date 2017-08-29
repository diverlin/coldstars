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

#pragma once

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

    void SetPlayer(client::Player*);
    void BindKosmoport(control::Kosmoport*);
    void UnbindKosmoport();

    void BindSharedGuis(GuiGalaxyMap*, GuiVehicle*, GuiSkills*, Slider*);
    void UnbindSharedGuis();

    void EnterGuiScanInAngar();
    void ExitGuiScan();

    void EnterGuiStoreScreen();
    void ExitGuiStoreScreen();

    bool GetInitDone() const { return init_done; }

    void ButtonsAction();

    bool Update(const MouseData&);
    void Render(const MouseData&);

    void EnterGuiAngarScreen();

private:
    bool init_done;

    int active_screen_id;

    control::Kosmoport* m_kosmoport = nullptr;

    GuiAngar m_gui_angar;
    GuiStore m_gui_store;
    GuiShop m_gui_shop;
    GuiGoverment m_gui_goverment;

    GuiGalaxyMap* m_gui_galaxymap_shared = nullptr;
    GuiVehicle* m_gui_vehicle_scan_shared = nullptr;
    GuiSkills* m_gui_skills_shared = nullptr;
    Slider* m_slider_shared = nullptr;


    void ExitGuiAngarScreen();

    void EnterGuiShopScreen();
    void ExitGuiShopScreen();

    void EnterGuiGalaxyMapScreen();
    void ExitGuiGalaxyMapScreen();

    void EnterGuiGovermentScreen();
    void ExitGuiGovermentScreen();

    void ExitCurrentScreen();
};


