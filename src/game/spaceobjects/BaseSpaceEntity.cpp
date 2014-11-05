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
#include "../resources/MeshCollector.hpp"
#include "../resources/TextureCollector.hpp"
#include "../resources/GuiTextureObCollector.hpp"
#include "../common/constants.hpp"
#include <math/rand.hpp>
#include "../common/common.hpp"
#include "../common/myStr.hpp"
#include "../world/EntityManager.hpp"
#include "../world/starsystem.hpp"
#include "../text/VerticalFlowText.hpp" 
#include "../common/Logger.hpp"
#include <jeti/Render.hpp>
#include <jeti/animations/BaseAnimationRotation.hpp>

#include <jeti/Screen.hpp>


BaseSpaceEntity::BaseSpaceEntity():
m_Starsystem(nullptr), 
m_PlaceTypeId(TYPE::PLACE::NONE_ID), 
m_Mass(0), 
m_GiveExpirience(0),
m_Parent(nullptr)
{}

/* virtual override */
BaseSpaceEntity::~BaseSpaceEntity()
{
    #if CREATEDESTROY_LOG_ENABLED == 1
    Logger::Instance().Log("___::~BaseSpaceEntity("+int2str(GetId())+")");
    #endif
}

void BaseSpaceEntity::ApplyImpulse(const glm::vec3& force_dir, float strength)
{
    m_AppliedForce += force_dir * strength;
}

/* virtual */
void BaseSpaceEntity::Hit(int damage, bool show_effect)
{
    m_DataLife.armor -= damage;
    if (m_DataLife.armor <= 0)
    {
        m_DataLife.is_alive = false; 
        m_DataLife.dying_time -= 3;
    }

    if (show_effect == true)
    {    
        VerticalFlowText* text = new VerticalFlowText(int2str(damage), 12, vec3ToVec2(GetCenter()), COLOR::COLOR4I_RED_LIGHT, GetCollisionRadius());
        m_Starsystem->Add(text); 
    }

}

void BaseSpaceEntity::SilentKill()
{
    m_DataLife.is_alive      = false;  
    m_DataLife.garbage_ready = true;
}

void BaseSpaceEntity::CheckDeath(bool show_effect)
{
    if (m_DataLife.is_alive == false)
    {
        m_DataLife.dying_time--;
        if (m_DataLife.dying_time < 0)
        {
            if (m_DataLife.garbage_ready == false)
            {   
                PostDeathUniqueEvent(show_effect);
                m_DataLife.garbage_ready = true;
            }
        }
    }  
}

/* virtual */        
void BaseSpaceEntity::RenderInfoInSpace(const jeti::Renderer&, const glm::vec2& scroll_coords, float scale)
{ 
    UpdateInfo(); // virtual
    glm::vec2 pos(GetCenter().x - scroll_coords.x, GetCenter().y - scroll_coords.y);
    jeti::drawInfoIn2Column(m_Info.title_list, m_Info.value_list, pos/scale);
}

void BaseSpaceEntity::RenderInfo(const glm::vec2& center)
{ 
    UpdateInfo(); // virtual
    jeti::drawInfoIn2Column(m_Info.title_list, m_Info.value_list, center);
}
    
void BaseSpaceEntity::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" BaseSpaceEntity("+int2str(GetId())+")::Save(", SAVELOAD_LOG_DIP);
    #endif
    
    save_ptree.put(root+"data_life.is_alive",   m_DataLife.is_alive);
    save_ptree.put(root+"data_life.armor",      m_DataLife.armor);
    save_ptree.put(root+"data_life.life_time",  m_DataLife.life_time);
    save_ptree.put(root+"data_life.dying_time", m_DataLife.dying_time);

    save_ptree.put(root+"mass", m_Mass);


    if (m_Parent) save_ptree.put(root+"data_unresolved_BaseSpaceEntity.parent_id", m_Parent->GetId());
    else        save_ptree.put(root+"data_unresolved_BaseSpaceEntity.parent_id", NONE_ID);

    if (m_Starsystem)    save_ptree.put(root+"data_unresolved_BaseSpaceEntity.starsystem_id", m_Starsystem->GetId());
    else            save_ptree.put(root+"data_unresolved_BaseSpaceEntity.starsystem_id", NONE_ID);
        
    save_ptree.put(root+"place_type_id", (int)m_PlaceTypeId);
}



void BaseSpaceEntity::LoadData(const boost::property_tree::ptree& load_ptree)
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" BaseSpaceEntity("+int2str(GetId())+")::LoadData", SAVELOAD_LOG_DIP);
    #endif
    
    m_DataLife.is_alive   = load_ptree.get<bool>("data_life.is_alive");
    m_DataLife.armor      = load_ptree.get<int>("data_life.armor");
    m_DataLife.life_time  = load_ptree.get<int>("data_life.life_time");
    m_DataLife.dying_time = load_ptree.get<int>("data_life.dying_time");

    m_Mass = load_ptree.get<int>("mass");

    m_PlaceTypeId = (TYPE::PLACE)load_ptree.get<int>("place_type_id");    
    
    data_unresolved_BaseSpaceEntity.parent_id     = load_ptree.get<int>("data_unresolved_BaseSpaceEntity.parent_id");            
    data_unresolved_BaseSpaceEntity.starsystem_id = load_ptree.get<int>("data_unresolved_BaseSpaceEntity.starsystem_id");
}

void BaseSpaceEntity::ResolveData()
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" BaseSpaceEntity("+int2str(GetId())+")::ResolveData", SAVELOAD_LOG_DIP);
    #endif    
    
    if (data_unresolved_BaseSpaceEntity.parent_id != NONE_ID)
    {
        m_Parent = (BaseSpaceEntity*)EntityManager::Instance().GetEntityById(data_unresolved_BaseSpaceEntity.parent_id);
    }

    if (data_unresolved_BaseSpaceEntity.starsystem_id != NONE_ID)
    {
        m_Starsystem = (StarSystem*)EntityManager::Instance().GetEntityById(data_unresolved_BaseSpaceEntity.starsystem_id);
    }
}
