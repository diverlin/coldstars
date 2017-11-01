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

#include <client/gui/GuiRadar.hpp>
#include "../gui/GuiVehicle.hpp"
#include "../gui/GuiVehicle2.hpp"

class Renderer;

namespace gui {

class Vehicle;
class GuiSkills;
class GuiGalaxyMap;
class Slider;

class Space : public Base
{
public:
    Space();
    ~Space();

    bool initialized() const { return m_initialized; }

    //GuiVehicle2& GetGuiVehicleTarget() { return gui_vehicle_target; };

    void bindSharedGuis(GuiGalaxyMap*, Vehicle*, GuiSkills*, Slider*);
    void unbindSharedGuis();

    void resize(int, int);
    void buttonsAction(client::Player*) const;

    void renderText(const glm::vec2&) const;

    void enterGalaxyMap();
    void exitGalaxyMap();

    void enterGuiScan();
    void exitGuiScan();

protected:
    void _updateUnique(client::Player*) override final;
    void _renderUnique(const jeti::Render&, client::Player*) const override final;


private:
    bool m_initialized = false;

    GuiGalaxyMap* m_galaxymapShared = nullptr;
    //GuiVehicle*   gui_vehicle_scan_shared = nullptr;
    GuiSkills*    m_skillsShared = nullptr;
    Slider*       m_sliderShared = nullptr;

    bool updateMouseInteractionWithPreciseWeaponTarget(const MouseData&);
};

} // namespace gui
