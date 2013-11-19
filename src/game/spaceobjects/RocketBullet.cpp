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

#include "RocketBullet.hpp"

#include <common/common.hpp>
#include <common/myStr.hpp>
#include <common/Logger.hpp>
#include <common/constants.hpp>

#include <world/EntityManager.hpp>
#include <world/starsystem.hpp>

#include <effects/particlesystem/DriveEffect.hpp>
#include <effects/particlesystem/ExplosionEffect.hpp>

#include <render/Render.hpp>

#include <text/VerticalFlowText.hpp> 

RocketBullet::RocketBullet(int id)
:
m_Speed(0),
m_DamageRate(1.0),
m_OwnerId(0),
m_Target(nullptr),
m_EffectDrive(nullptr) 
{
    SetId(id);
    SetTypeId(TYPE::ENTITY::BULLET_ID);
    SetSubTypeId(TYPE::ENTITY::ROCKETBULLET_ID);
}

/* virtual */
RocketBullet::~RocketBullet()
{
    #if CREATEDESTROY_LOG_ENABLED == 1
    Logger::Instance().Log("___::~RocketBullet("+int2str(GetId())+")");
    #endif

    delete m_EffectDrive;
}

void RocketBullet::CreateDriveComplexTextureDependedStuff()
{
    GetPoints().addMidLeftPoint();
    GetPoints().addMidFarLeftPoint();
        
    m_EffectDrive = GetNewDriveEffect(GetTextureOb().size_id/2, GetPoints().GetpMidLeft(), GetPoints().GetpMidFarLeft());
}    

void RocketBullet::UpdateInSpace(int time, bool show_effect)
{
    CheckDeath(show_effect);
        
    if (time > 0)
    {
        UpdateOrientation();
            
        if (m_Speed < m_DataBullet.speed_max)
        {
            m_Speed += m_DataBullet.d_speed; 
        } 
                
        if (m_Target != nullptr)
        { 
            float angle; 
            get_dPos_ToPoint(GetCenter(), m_Target->GetCenter(), m_Speed/100.0, GetAppliedForce(), angle);
        
            if (CheckTarget() == true)
            {
                //SetAngleZ(angle);
            }
            else
            {
                m_Target = nullptr;
            }
        }      

        SetCenter(GetCenter() + GetAppliedForce());    

        m_DataBullet.live_time -= 1;
    }
}

bool RocketBullet::CheckTarget() const
{
    if (m_Target->GetAlive() == true)
    {
        if (m_Target->GetPlaceTypeId() == TYPE::PLACE::SPACE_ID)
        {
            if (m_Target->GetStarSystem()->GetId() == GetStarSystem()->GetId())
            {
                return true;
            }
        }
    }
    
    return false;
}

void RocketBullet::CollisionEvent(bool show_effect)
{
    GetDataLife().is_alive = false; 
    GetDataLife().dying_time = -1;
}

/* virtual override final */
void RocketBullet::UpdateInfo()
{
    GetInfo().clear();

    GetInfo().addTitleStr("ROCKET");
    GetInfo().addNameStr("id/ss_id:");          GetInfo().addValueStr( int2str(GetId()) + " / " + int2str(GetStarSystem()->GetId()) );
    GetInfo().addNameStr("armor:");             GetInfo().addValueStr( int2str(GetDataLife().armor) );
    if (m_Target != nullptr) 
    { 
        GetInfo().addNameStr("target_id:");       GetInfo().addValueStr(int2str(m_Target->GetId())); 
    }
}

/* virtual override final */
void RocketBullet::Hit(int damage, bool show_effect)
{
    GetDataLife().armor -= damage;

    if (GetDataLife().armor < 0)
    {
        GetDataLife().is_alive = false;
    }

    if (show_effect == true)
    {
        // improove
        VerticalFlowText* text = new VerticalFlowText(int2str(damage), 12, vec3ToVec2(GetCenter()), COLOR::COLOR4I_RED_LIGHT, GetCollisionRadius());
        GetStarSystem()->Add(text); 
    }
}

/* virtual override final */
void RocketBullet::PostDeathUniqueEvent(bool show_effect)  
{
    if (show_effect == true)
    {
        ExplosionEffect* explosion = getNewExplosionEffect(GetCollisionRadius());
        GetStarSystem()->Add(explosion, GetCenter());                
    }
}

void RocketBullet::RenderInSpace(const Renderer& render, float scale)
{  
    render.DrawQuad(GetTextureOb(), GetActualModelMatrix());

    m_EffectDrive->Update();
    m_EffectDrive->Render(scale, 0.0f);
}


void RocketBullet::SaveDataUniqueRocketBullet(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    save_ptree.put(root+"speed", m_Speed);
    save_ptree.put(root+"owner_id", m_OwnerId);
    if (m_Target != nullptr)     { save_ptree.put(root+"target_id", m_Target->GetId()); }
    else                        { save_ptree.put(root+"target_id", NONE_ID); }
    
    m_DataBullet.SaveData(save_ptree, root);
}

void RocketBullet::LoadDataUniqueRocketBullet(const boost::property_tree::ptree& load_ptree)
{
    m_Speed = load_ptree.get<float>("speed");  
    m_OwnerId = load_ptree.get<int>("owner_id");  
    unresolved_RocketBullet_target_id = load_ptree.get<int>("target_id");  
    
    m_DataBullet.LoadData(load_ptree.get_child("data_bullet"));
}

void RocketBullet::ResolveDataUniqueRocketBullet()
{           
    CreateDriveComplexTextureDependedStuff();
                
    if (unresolved_RocketBullet_target_id != NONE_ID)
    {
        m_Target = (BaseSpaceEntity*)EntityManager::Instance().GetEntityById(unresolved_RocketBullet_target_id);
    }
    
    ((StarSystem*)EntityManager::Instance().GetEntityById(data_unresolved_BaseSpaceEntity.starsystem_id))->AddBullet(this, data_unresolved_Orientation.center, data_unresolved_Orientation.direction); 
}
   
   
/* virtual override final */
void RocketBullet::SaveData(boost::property_tree::ptree& save_ptree) const
{
    const std::string root = "rocketbullet."+int2str(GetId())+".";
    Base::Save(save_ptree, root);
    Orientation::Save(save_ptree, root);
    BaseDrawable::Save(save_ptree, root);
    BaseSpaceEntity::Save((save_ptree, root);
    SaveDataUniqueRocketBullet(save_ptree, root);
}

/* virtual override final */
void RocketBullet::LoadData(const boost::property_tree::ptree& load_ptree)
{
    Base::Load(load_ptree);
    Orientation::Load(load_ptree);
    BaseDrawable::Load(load_ptree);
    BaseSpaceEntity::Load(load_ptree);
    LoadDataUniqueRocketBullet(load_ptree);
}

/* virtual override final */
void RocketBullet::ResolveData()
{
    Base::Resolve();
    Orientation::Resolve();
    BaseDrawable::Resolve();
    BaseSpaceEntity::Resolve();
    ResolveDataUniqueRocketBullet();
}
