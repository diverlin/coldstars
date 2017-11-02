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

#include "GuiRadar.hpp"
#include <client/resources/GuiTextureObCollector.hpp>
#include <client/pilot/Player.hpp>
#include <client/session/Shortcuts.hpp>

#include <core/spaceobject/ALL>
#include <core/pilot/Npc.hpp>
#include <core/world/starsystem.hpp>


#include <jeti/Screen.hpp>
#include <jeti/Camera.hpp>
#include <jeti/Render.hpp>

#include <meti/VectorUtils.hpp>


namespace gui {

Radar::Radar()
{
    _setGroup(gui::type::GUI_RADAR);
    
    m_material_background = new jeti::control::Material(MaterialCollector::get().radar_background);
    m_material_bar = new jeti::control::Material(MaterialCollector::get().radar_bar);
    m_material_screenrect = new jeti::control::Material(MaterialCollector::get().radar_screenrect);
    m_material_range = new jeti::control::Material(MaterialCollector::get().radar_range);
    m_material_dot = new jeti::control::Material(MaterialCollector::get().dot);

    m_entitiesMesh = new jeti::Mesh();

    m_size_base = 7;

    m_color_star = glm::vec4(1.0f, 1.0f, 0.5f, 1.0f);
    m_color_planet = glm::vec4(1.0f, 0.5f, 1.0f, 1.0f);
    m_color_asteroid = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    m_color_wormhole = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    m_color_vehicle = glm::vec4(0.5f, 1.0f, 1.0f, 1.0f);

    m_size_star = 2.0f*m_size_base;
    m_size_planet = 1.5f*m_size_base;
    m_size_asteroid = 1.25f*m_size_base;
    m_size_wormhole = 1.5f*m_size_base;
    m_size_vehicle = 1.0f*m_size_base;

    m_scale = RADAR_SCALE;
}

Radar::~Radar()
{
    delete m_material_background;
    delete m_material_bar;
    delete m_material_screenrect;
    delete m_material_range;
    delete m_material_dot;
}

void Radar::__reset()
{
    m_entities.clear();

    m_positions.clear();
    m_colors.clear();
    m_sizes.clear();
}

void Radar::_updateUnique(client::Player* player)
{
    int screen_w = client::shortcuts::screen()->width();
    int screen_h = client::shortcuts::screen()->height();

    // main gui frame
    box().setSize(RADAR_FRAME_SIZE, RADAR_FRAME_SIZE);
    box().setCenter(screen_w/2 - box().size().x, -screen_h/2 + box().size().y);

    // range mark on radar gui
    float range = player->npc()->vehicle()->properties().radar;
    m_box_range.setSize(range*m_scale, range*m_scale);
    m_box_range.setCenter(box().center() + meti::to_vec2(player->npc()->vehicle()->position()) * m_scale);

    // screen rect
    m_box_screenrect.setSize(screen_w*m_scale, screen_h*m_scale);
    m_box_screenrect.setCenter(box().center() + meti::to_vec2(client::shortcuts::camera()->position()) * m_scale);


    // fill with entitites
    __reset();
    control::StarSystem* starsystem = player->npc()->vehicle()->starsystem();
    for (auto* star: starsystem->stars()) {
        __add(star);
    }
    for (auto* planet: starsystem->planets()) {
        __add(planet);
    }
    for (auto* asteroid: starsystem->asteroids()) {
        __add(asteroid);
    }
    for (auto* vehicle: starsystem->vehicles()) {
        __add(vehicle);
    }

    // TODO: to be fixed
    const MouseData& data_mouse = player->cursor().mouseData();
    if (box().checkInteraction(meti::to_vec2(data_mouse.screenCoord()))) {
        if (data_mouse.event() == MouseData::Event::LeftButtonPress) {
            client::shortcuts::camera()->setPosition(data_mouse.worldCoord());
        }
    }
}
             
void Radar::__add(control::SpaceObject* object)
{
    m_entities.push_back(object);

    float scale_render = 1.0f; // TODO

    glm::vec3 position = meti::to_vec3(box().center()) + object->position()*m_scale/scale_render;
    m_positions.push_back(position);
    switch(object->descriptor()->obType())
    {
    case entity::Type::STAR: {
        m_colors.push_back(m_color_star);
        m_sizes.push_back(m_size_star);
        break;
    }
    case entity::Type::PLANET: {
        m_colors.push_back(m_color_planet);
        m_sizes.push_back(m_size_planet);
        break;
    }
    case entity::Type::ASTEROID: {
        m_colors.push_back(m_color_asteroid);
        m_sizes.push_back(m_size_asteroid);
        break;
    }
    case entity::Type::WORMHOLE: {
        m_colors.push_back(m_color_wormhole);
        m_sizes.push_back(m_size_wormhole);
        break;
    }
    case entity::Type::SHIP: {
        m_colors.push_back(m_color_vehicle);
        m_sizes.push_back(m_size_vehicle);
        break;
    }
    default:
        assert(false);
        break;
    }
}

void Radar::__addVisible(control::SpaceObject* object, control::Vehicle* vehicle)
{
    if (vehicle->canRadarObject(object)) {
        __add(object);
    }
}             
            
void Radar::_renderUnique(const jeti::Render& render, client::Player* player) const
{
    render.drawQuadHUD(*m_material_background, box());
    render.drawQuadHUD(*m_material_bar, box());
    render.drawQuadHUD(*m_material_range, m_box_range);
    render.drawQuadHUD(*m_material_screenrect, m_box_screenrect);

    if (m_positions.size()) {
        m_entitiesMesh->fillPointVertices(m_positions, m_colors, m_sizes);
        render.drawParticlesForHUD(*m_entitiesMesh, *m_material_dot);
    }
}

} // namespace gui
