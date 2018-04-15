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

namespace core {
namespace control {
class SpaceObject;
class Vehicle;
} // namespace core
} // namespace core

namespace jeti {
class Mesh;
class Render;
}

namespace gui {

const float RADAR_FRAME_SIZE = 120;

class Radar : public Base
{
public:
    Radar(const glm::vec2&);
    virtual ~Radar() override final;

protected:
    virtual void _updateUnique(client::Player*) override final;
    virtual void _renderUnique(const jeti::Render&, client::Player*) const override final;

private:
    const float RADAR_SCALE = 1/40.0;

    glm::vec4 m_color_star;
    glm::vec4 m_color_planet;
    glm::vec4 m_color_asteroid;
    glm::vec4 m_color_wormhole;
    glm::vec4 m_color_vehicle;

    float m_size_base = 0;
    float m_size_star= 0;
    float m_size_planet = 0;
    float m_size_asteroid = 0;
    float m_size_wormhole = 0;
    float m_size_vehicle = 0;

    float m_scale = 1.0f;

    jeti::control::Material* m_material_background = nullptr;
    jeti::control::Material* m_material_bar = nullptr;
    jeti::control::Material* m_material_screenrect = nullptr;
    jeti::control::Material* m_material_range = nullptr;
    jeti::control::Material* m_material_dot = nullptr;

    ceti::Box2D m_box_screenrect;
    ceti::Box2D m_box_range;

    std::vector<core::control::SpaceObject*> m_entities;
    jeti::Mesh* m_entitiesMesh = nullptr;

    std::vector<glm::vec3> m_positions;
    std::vector<glm::vec4> m_colors;
    std::vector<float> m_sizes;

    void __reset();

    void __add(core::control::SpaceObject*);
    void __addVisible(core::control::SpaceObject*, core::control::Vehicle*);
};

} // namespace gui
