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

#include "BaseSpaceEntity.hpp"
//#include "../common/constants.hpp"
#include <math/rand.hpp>
#include "../world/EntityManager.hpp"
#include "../world/starsystem.hpp"
#include "../common/Logger.hpp"


BaseSpaceEntity::BaseSpaceEntity():
    m_starsystem(nullptr),
    m_placeTypeId(TYPE::PLACE::NONE_ID),
    m_mass(0),
    m_expirienceToGive(0),
    m_parent(nullptr)
{}

/* virtual override */
BaseSpaceEntity::~BaseSpaceEntity()
{
#if CREATEDESTROY_LOG_ENABLED == 1
    Logger::Instance().Log("___::~BaseSpaceEntity("+std::to_string(id())+")");
#endif
}

void BaseSpaceEntity::addImpulse(const glm::vec3& force_dir, float strength)
{
    m_externalForce += force_dir * strength;
}

/* virtual */
void BaseSpaceEntity::hit(int damage, bool show_effect)
{
    m_dataLife.armor -= damage;
    if (m_dataLife.armor <= 0) {
        m_dataLife.is_alive = false;
        m_dataLife.dying_time -= 3;
    }

    if (show_effect == true) {
//        VerticalFlowText* text = new VerticalFlowText(std::to_string(damage), 12, meti::vec2(center()), COLOR::COLOR4I_RED_LIGHT, collisionRadius());
//        m_starsystem->Add(text);
    }

}

void BaseSpaceEntity::killSilently()
{
    m_dataLife.is_alive      = false;
    m_dataLife.garbage_ready = true;
}

void BaseSpaceEntity::checkDeath(bool show_effect)
{
    if (m_dataLife.is_alive == false)
    {
        m_dataLife.dying_time--;
        if (m_dataLife.dying_time < 0)
        {
            if (m_dataLife.garbage_ready == false)
            {
                postDeathUniqueEvent(show_effect);
                m_dataLife.garbage_ready = true;
            }
        }
    }
}

///* virtual */
//void BaseSpaceEntity::RenderInfoInSpace(const jeti::Renderer&, const glm::vec2& scroll_coords, float scale)
//{
//    UpdateInfo(); // virtual
//    glm::vec2 pos(center().x - scroll_coords.x, center().y - scroll_coords.y);
//    jeti::drawInfoIn2Column(m_Info.title_list, m_Info.value_list, pos/scale);
//}

//void BaseSpaceEntity::RenderInfo(const glm::vec2& center)
//{
//    UpdateInfo(); // virtual
//    jeti::drawInfoIn2Column(m_Info.title_list, m_Info.value_list, center);
//}

void BaseSpaceEntity::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
#if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" BaseSpaceEntity("+std::to_string(id())+")::Save(", SAVELOAD_LOG_DIP);
#endif
    
    save_ptree.put(root+"data_life.is_alive",   m_dataLife.is_alive);
    save_ptree.put(root+"data_life.armor",      m_dataLife.armor);
    save_ptree.put(root+"data_life.life_time",  m_dataLife.life_time);
    save_ptree.put(root+"data_life.dying_time", m_dataLife.dying_time);

    save_ptree.put(root+"mass", m_mass);


    if (m_parent) save_ptree.put(root+"data_unresolved_BaseSpaceEntity.parent_id", m_parent->id());
    else        save_ptree.put(root+"data_unresolved_BaseSpaceEntity.parent_id", NONE_ID);

    if (m_starsystem)    save_ptree.put(root+"data_unresolved_BaseSpaceEntity.starsystem_id", m_starsystem->id());
    else            save_ptree.put(root+"data_unresolved_BaseSpaceEntity.starsystem_id", NONE_ID);

    save_ptree.put(root+"place_type_id", (int)m_placeTypeId);
}



void BaseSpaceEntity::LoadData(const boost::property_tree::ptree& load_ptree)
{
#if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" BaseSpaceEntity("+std::to_string(id())+")::LoadData", SAVELOAD_LOG_DIP);
#endif
    
    m_dataLife.is_alive   = load_ptree.get<bool>("data_life.is_alive");
    m_dataLife.armor      = load_ptree.get<int>("data_life.armor");
    m_dataLife.life_time  = load_ptree.get<int>("data_life.life_time");
    m_dataLife.dying_time = load_ptree.get<int>("data_life.dying_time");

    m_mass = load_ptree.get<int>("mass");

    m_placeTypeId = (TYPE::PLACE)load_ptree.get<int>("place_type_id");
    
    data_unresolved_BaseSpaceEntity.parent_id     = load_ptree.get<int>("data_unresolved_BaseSpaceEntity.parent_id");
    data_unresolved_BaseSpaceEntity.starsystem_id = load_ptree.get<int>("data_unresolved_BaseSpaceEntity.starsystem_id");
}

void BaseSpaceEntity::ResolveData()
{
#if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" BaseSpaceEntity("+std::to_string(id())+")::ResolveData", SAVELOAD_LOG_DIP);
#endif
    
    if (data_unresolved_BaseSpaceEntity.parent_id != NONE_ID) {
        m_parent = (BaseSpaceEntity*)EntityManager::Instance().GetEntityById(data_unresolved_BaseSpaceEntity.parent_id);
    }
    if (data_unresolved_BaseSpaceEntity.starsystem_id != NONE_ID) {
        m_starsystem = (StarSystem*)EntityManager::Instance().GetEntityById(data_unresolved_BaseSpaceEntity.starsystem_id);
    }
}
