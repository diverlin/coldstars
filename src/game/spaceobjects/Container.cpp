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

#include "Container.hpp"

#include <common/common.hpp>
#include <common/myStr.hpp>
#include <common/Logger.hpp>

#include <world/EntityManager.hpp>
#include <world/starsystem.hpp>

#include <render/Render.hpp>

#include <effects/particlesystem/ExplosionEffect.hpp>

#include <garbage/EntityGarbage.hpp>

#include <slots/ItemSlot.hpp>
#include <items/BaseItem.hpp>


Container::Container(int id)
:
m_ItemSlot(nullptr),
m_Velocity(0)    
{
    SetId(id);
    SetTypeId(TYPE::ENTITY::CONTAINER_ID);
}

/* virtual */   
Container::~Container()
{
    #if CREATEDESTROY_LOG_ENABLED == 1
    Logger::Instance().Log("___::~Container("+int2str(GetId())+")");
    #endif
}

/* virtual override final */
void Container::PutChildsToGarbage() const
{
    EntityGarbage::Instance().Add(m_ItemSlot);
}
            
void Container::BindItemSlot(ItemSlot* item_slot) 
{ 
    m_ItemSlot = item_slot; 
    m_ItemSlot->SetOwner(this); 
}

/* virtual override final */
void Container::UpdateInfo()  
{
    GetInfo().clear();
    GetInfo().addTitleStr("CONTAINER");
    GetInfo().addNameStr("id/ss_id:");    GetInfo().addValueStr(int2str(GetId()) + " / " + int2str(GetStarSystem()->GetId()));
    GetInfo().addNameStr("armor:");       GetInfo().addValueStr(int2str(GetDataLife().armor));
    GetInfo().addNameStr("pos:");         GetInfo().addValueStr( str(GetCenter()) );
}        
 
/* virtual override final */           
void Container::RenderInfoInSpace(const Renderer& render, const glm::vec2& scroll_coords, float zoom)
{
    UpdateInfo();
    glm::vec2 pos(GetCenter().x - scroll_coords.x, GetCenter().y - scroll_coords.y);
    pos /= zoom;
    drawInfoIn2Column(GetInfo().title_list, GetInfo().value_list, pos);
    
    pos.x += 300;
    m_ItemSlot->GetItem()->RenderInfo(render, pos);
}
 
/* virtual override final */   
void Container::PostDeathUniqueEvent(bool show_effect)
{
    if (m_ItemSlot->GetItem()->GetTypeId() == TYPE::ENTITY::BOMB_ID)
    {
        GetStarSystem()->BombExplosionEvent(this, show_effect);  
    }
    else
    {
        if (show_effect == true)
        {
            ExplosionEffect* explosion = getNewExplosionEffect(GetCollisionRadius());
            GetStarSystem()->Add(explosion, GetCenter()); 
        }
    }
}

void Container::UpdateInSpace(int time, bool show_effect)
{
    CheckDeath(show_effect);         
    if (time > 0)
    {
        SetCenter(GetCenter() + GetAppliedForce());
        GetAppliedForce() *= 0.99;
    }
}
               
void Container::Render2D(const Renderer& render)
{ 
    render.DrawQuad(GetTextureOb(), GetActualModelMatrix());
}

void Container::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const    
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" Container("+int2str(GetId())+")::SaveData()", SAVELOAD_LOG_DIP);
    #endif
    
    save_ptree.put(root+"target_pos.x", m_TargetPos.x);
    save_ptree.put(root+"target_pos.y", m_TargetPos.y);

    save_ptree.put(root+"velocity", m_Velocity);
}

void Container::LoadData(const boost::property_tree::ptree& load_ptree)
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" Container("+int2str(GetId())+")::LoadData()", SAVELOAD_LOG_DIP);
    #endif
    
    m_TargetPos.x   = load_ptree.get<float>("target_pos.x");
    m_TargetPos.y   = load_ptree.get<float>("target_pos.y");
    
    m_Velocity = load_ptree.get<float>("velocity");
}

void Container::ResolveData()
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" Container("+int2str(GetId())+")::ResolveData()", SAVELOAD_LOG_DIP);
    #endif
    
    ((StarSystem*)EntityManager::Instance().GetEntityById(data_unresolved_BaseSpaceEntity.starsystem_id))->AddContainer(this, data_unresolved_Orientation.center); 
}        

/* virtual override final */
void Container::Save(boost::property_tree::ptree& save_ptree) const
{
    const std::string root = "container." + int2str(GetId()) + ".";

    Base::SaveData(save_ptree, root);
    Orientation::SaveData(save_ptree, root);
    BaseDrawable::SaveData(save_ptree, root);
    BaseSpaceEntity::SaveData(save_ptree, root);
    Container::SaveData(save_ptree, root);
}

/* virtual override final */
void Container::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
    Orientation::LoadData(load_ptree);
    BaseDrawable::LoadData(load_ptree);
    BaseSpaceEntity::LoadData(load_ptree);
    Container::LoadData(load_ptree);
}
    
/* virtual override final */    
void Container::Resolve()
{
    Base::ResolveData();
    Orientation::ResolveData();
    BaseDrawable::ResolveData();
    BaseSpaceEntity::ResolveData();
    Container::ResolveData();
}
