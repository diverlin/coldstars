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

namespace control {
class SpaceObject;
class Vehicle;
} // namespace model

namespace jeti {
class Render;
}

namespace gui {

class Radar : public Base
{
public:
    Radar();
    virtual ~Radar() override final;
    
    void resize(int, int);

    void reset();

    void add(control::SpaceObject*);
    void addVisible(control::SpaceObject*, control::Vehicle*);

protected:
    virtual void _updateUnique(client::Player*) override final;
    virtual void _renderUnique(const jeti::Render&, client::Player*) const override final;

private:
    const float RADAR_FRAME_SIZE = 120;
    const float RADAR_SCALE = 1/50.0;

    float m_scale = 1.0f;

    jeti::control::Material* m_material_background = nullptr;
    jeti::control::Material* m_material_bar = nullptr;
    jeti::control::Material* m_material_screenrect = nullptr;
    jeti::control::Material* m_material_range = nullptr;

    int m_screen_w = 0;
    int m_screen_h = 0;

    ceti::Box2D m_box_screenrect;
    ceti::Box2D m_box_range;

    std::vector<control::SpaceObject*> m_entities;
};

} // namespace gui
