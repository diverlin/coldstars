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
    int screen_w = client::shortcuts::screen()->width();
    int screen_h = client::shortcuts::screen()->height();
    resize(screen_w, screen_h);
}

Radar::~Radar()
{
    delete m_material_bar;
    delete m_material_screenrect;
    delete m_material_range;
}

void Radar::resize(int screen_w, int screen_h)
{
    m_rect.set(0, 0, 250, 250);
}
         
void Radar::resetData()
{
    m_entities.clear();
}

/*virtual final*/ 
void Radar::_updateUnique(client::Player* player)
{
    float range_diameter = 2*player->npc()->vehicle()->properties().radar;
    box().setSize(range_diameter, range_diameter);
    box().setCenter(0, 800);

//    m_screenrect.set(m_rect.center() + client::shortcuts::screen()->bottomLeftScreenWC() * scale, (int)(client::shortcuts::screen()->width() * scale), (int)(client::shortcuts::screen()->height() * scale));
//    const MouseData& data_mouse = player->cursor().mouseData();
//    if (m_rect.CheckRoundInteraction(data_mouse.pos_screencoord, /*radius=*/70.0) == true)
//    {
//        if (data_mouse.left_press == true)
//        {
//            glm::vec2 new_global_coord( ( data_mouse.pos_screencoord.x - m_rect.center().x - m_screenrect.width()/2)/scale, ( data_mouse.pos_screencoord.y - m_rect.center().y - m_screenrect.height()/2)/scale);
//            //client::shortcuts::screen()->setBottomLeftScreenWC(new_global_coord);
//        }
//    }
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
            
/* virtual override final */
void Radar::_renderUnique(const jeti::Render& render, client::Player* player) const
{
    m_material_background->load();
    render.drawQuadHUD(*m_material_background, box());
//    /range_rect.setCenter(rect.center() + meti::vec2(player->GetNpc()->vehicle()->position()) * scale);
    
//    drawTexturedRect(textureOb_background, rect, -2.0);
//    drawTexturedRect(textureOb_bar, rect, -2.0);
//    drawTexturedRect(textureOb_screenrect, screenrect, -2.0);
//    drawTexturedRect(textureOb_range, range_rect, -2.0);
          return;
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
