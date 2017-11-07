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

namespace jeti {
class Render;
} // namespace jeti

namespace client {
class Player;
} // namespace client

namespace gui {

class GuiSkill;
class GuiGalaxyMap;

class Manager
{
public:
    static Manager& get();
    ~Manager();

    void setPlayer(client::Player* player) { m_player = player; }

    GuiKosmoport& kosmoport() { return m_kosmoport; }
    Space& space() { return m_space; }

    Vehicle* vehicle() const { return m_vehicle; }
    GuiGalaxyMap* galaxy() const { return m_galaxymap; }

    void update(client::Player*);
    void render(jeti::Render&, client::Player*);

//    void runSessionInSpace(jeti::Render& render, client::Player* player);
    void runSessionInKosmoport(const MouseData&);
    void runSessionInNatureLand(const MouseData&);

    void enterScan(client::Player* player);
    void exitScan(client::Player* player);

    void enterKosmoport();
    void quitKosmoport();

    void enterSpace();
    void quitSpace();

    bool updateMouseInteractionWithScanVehicle(const MouseData&);
    void renderScanVehicle(const MouseData&, bool show_skill = true) const;

    void pressEventMBL_onGuiElement(Type);
    void resetEventOnGuiElement(Type);
    Base* element(Type) const;

private:
    Manager();
    Manager(const Manager&) = delete;
    Manager& operator=(const Manager&) = delete;

    std::vector<int> m_commands;

    client::Player* m_player = nullptr;

    GuiKosmoport m_kosmoport;
    Space m_space;
    GuiNatureLand m_natureland;

    // shared guis
    Vehicle* m_vehicle = nullptr;
    GuiGalaxyMap* m_galaxymap = nullptr;

    GuiSkills* m_skills = nullptr;
    Slider* m_slider = nullptr;

    void __updateInSpace(client::Player*);
    void __renderInSpace(jeti::Render&, client::Player*);
};

} // namespace gui
