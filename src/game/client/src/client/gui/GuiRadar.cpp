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

#include <core/spaceobject/SpaceObject.hpp>
#include <core/spaceobject/Vehicle.hpp>
#include <core/pilot/Npc.hpp>

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
        
    m_scale = RADAR_SCALE;
}

Radar::~Radar()
{
    delete m_material_bar;
    delete m_material_screenrect;
    delete m_material_range;
}

void Radar::reset()
{
    m_entities.clear();
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
    m_box_range.setCenter(box().center() + meti::vec2(player->npc()->vehicle()->position()) * m_scale);

    // screen rect
    m_box_screenrect.setSize(m_screen_w*m_scale, m_screen_h*m_scale);
    m_box_screenrect.setCenter(box().center() + meti::vec2(client::shortcuts::camera()->position()) * m_scale);

    const MouseData& data_mouse = player->cursor().mouseData();
    if (box().checkInteraction(meti::vec2(data_mouse.screenCoord()))) {
        if (data_mouse.event() == MouseData::Event::LeftButtonPress) {
            client::shortcuts::camera()->setPosition(data_mouse.worldCoord());
        }
    }
}
             
void Radar::add(control::SpaceObject* object)
{
    m_entities.push_back(object);
}

void Radar::addVisible(control::SpaceObject* object, control::Vehicle* vehicle)
{
    if (vehicle->canRadarObject(object)) {
        add(object);
    }
}             
            
void Radar::_renderUnique(const jeti::Render& render, client::Player* player) const
{
    render.drawQuadHUD(*m_material_background, box());
    render.drawQuadHUD(*m_material_bar, box());
    render.drawQuadHUD(*m_material_range, m_box_range);
    render.drawQuadHUD(*m_material_screenrect, m_box_screenrect);

    float size, size_base = 7;
    {         
        for (const auto& entity: m_entities) {
            switch(entity->descriptor()->obType())
            {
                case entity::Type::STAR: {
                    //glBindTexture(GL_TEXTURE_2D, MaterialCollector::get().dot_yellow->model()->texture);
                    size = 2*size_base;
                    break;
                }
                case entity::Type::PLANET: {
                    //glBindTexture(GL_TEXTURE_2D, MaterialCollector::get().dot_blue->model()->texture);
                    size = 1.5*size_base;
                    break;                
                }
                case entity::Type::ASTEROID: {
                    //glBindTexture(GL_TEXTURE_2D, MaterialCollector::get().dot_red->model()->texture);
                    size = 1.25*size_base;
                    break;                
                }
                case entity::Type::WORMHOLE: {
                    //glBindTexture(GL_TEXTURE_2D, MaterialCollector::get().dot_purple->model()->texture);
                    size = 1.5*size_base;
                    break;                
                }
                case entity::Type::VEHICLE: {
                    //glBindTexture(GL_TEXTURE_2D, MaterialCollector::get().dot_green->model()->texture);
                    size = 1*size_base;
                    break;                
                }
            }
            
            //float scale_render = Screen::Instance().GetScale();
            //render.drawParticle(rect.center() + vec2(entity->position()*scale)/scale_render, size);
            //render.drawParticle(m_rect.center() + vec2(entity->position()), size);
        }
    }
}

} // namespace gui
