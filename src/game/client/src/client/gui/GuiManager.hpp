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

#include <client/gui/GuiKosmoport.hpp>
#include <client/gui/GuiSpace.hpp>
#include <client/gui/GuiNatureLand.hpp>

namespace gui {

class GuiSkill;
class GuiGalaxyMap;

class GuiManager
{
public:
    static GuiManager& get();
    ~GuiManager();

    void SetPlayer(client::Player*);

    GuiKosmoport& kosmoport() { return m_kosmoport; }
    GuiSpace& space() { return m_space; }

    GuiVehicle* vehicle() const { return m_vehicle; }
    GuiGalaxyMap* galaxy() const { return m_galaxymap; }

    void updateSessionInSpace();
    void runSessionInKosmoport(const MouseData&);
    void runSessionInNatureLand(const MouseData&);

    void enterKosmoport();
    void quitKosmoport();

    void enterSpace();
    void quitSpace();

    bool updateMouseInteractionWithScanVehicle(const MouseData&);
    void renderScanVehicle(const MouseData&, bool show_skill = true) const;

    void pressEventMBL_onGuiElement(gui::type);
    void resetEventOnGuiElement(gui::type);
    BaseGuiElement* element(gui::type) const;

private:
    GuiManager();
    GuiManager(const GuiManager&) = delete;
    GuiManager& operator=(const GuiManager&) = delete;

    std::vector<int> m_commands;

    client::Player* m_player = nullptr;

    GuiKosmoport m_kosmoport;
    GuiSpace m_space;
    GuiNatureLand m_natureland;

    // shared guis
    GuiVehicle* m_vehicle = nullptr;
    GuiGalaxyMap* m_galaxymap = nullptr;

    GuiSkills* m_skills = nullptr;
    Slider* m_slider = nullptr;
};

} // namespace gui
