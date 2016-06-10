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
//#include <ceti/StringUtils.hpp>
#include <ceti/Logger.hpp>
#include <common/constants.hpp>

#include <common/Global.hpp>
#include <managers/EntityManager.hpp>
#include <world/starsystem.hpp>

//#include <jeti/particlesystem/DriveEffect.hpp>
//#include <jeti/particlesystem/ExplosionEffect.hpp>

//#include <text/VerticalFlowText.hpp>



RocketBullet::RocketBullet(int id)
:
m_Speed(0),
m_DamageRate(1.0),
m_OwnerId(0),
m_Target(nullptr),
m_EffectDrive(nullptr) 
{
    setId(id);
    setTypeId(type::ENTITY::BULLET_ID);
    setSubTypeId(type::ENTITY::ROCKETBULLET_ID);
}

/* virtual */
RocketBullet::~RocketBullet()
{
    LOG("___::~RocketBullet("+std::to_string(id())+")");

    delete m_EffectDrive;
}

void RocketBullet::CreateDriveComplexTextureDependedStuff()
{
    points().addMidLeftPoint();
    points().addMidFarLeftPoint();
        
    //alpitodorender m_EffectDrive = GetNewDriveEffect(textureOb().GetData().size_id/2, points().GetpMidLeft(), points().GetpMidFarLeft());
}    

void RocketBullet::UpdateInSpace(int time, bool show_effect)
{
    _checkDeath(show_effect);
        
    if (time > 0)
    {
        updateOrientation();
            
        if (m_Speed < m_DataBullet.speed_max)
        {
            m_Speed += m_DataBullet.d_speed; 
        } 
                
        if (m_Target != nullptr)
        { 
            float angle; 
            get_dPos_ToPoint(center(), m_Target->center(), m_Speed/100.0, _externalForce(), angle);
        
            if (CheckTarget() == true)
            {
                //SetAngleZ(angle);
            }
            else
            {
                m_Target = nullptr;
            }
        }      

        setCenter(center() + _externalForce());    

        m_DataBullet.live_time -= 1;
    }
}

bool RocketBullet::CheckTarget() const
{
    if (m_Target->isAlive() == true)
    {
        if (m_Target->placeTypeId() == type::place::KOSMOS)
        {
            if (m_Target->starsystem()->id() == starsystem()->id())
            {
                return true;
            }
        }
    }
    
    return false;
}

void RocketBullet::CollisionEvent(bool show_effect)
{
    _dataLife().is_alive = false; 
    _dataLife().dying_time = -1;
}

///* virtual override final */
//void RocketBullet::UpdateInfo()
//{
//    GetInfo().clear();

//    GetInfo().addTitleStr("ROCKET");
//    GetInfo().addNameStr("id/ss_id:");          GetInfo().addValueStr( std::to_string(id()) + " / " + std::to_string(starsystem()->id()) );
//    GetInfo().addNameStr("armor:");             GetInfo().addValueStr( std::to_string(dataLife().armor) );
//    if (m_Target != nullptr)
//    {
//        GetInfo().addNameStr("target_id:");       GetInfo().addValueStr(std::to_string(m_Target->id()));
//    }
//}

/* virtual override final */
void RocketBullet::hit(int damage)
{
    SpaceObject::hit(damage);

    //if (show_effect == true)
    {
        // improove
//        VerticalFlowText* text = new VerticalFlowText(std::to_string(damage), 12, meti::vec2(center()), COLOR::COLOR4I_RED_LIGHT, collisionRadius());
//        starsystem()->Add(text);
    }
}

/* virtual override final */
void RocketBullet::_postDeathUniqueEvent(bool show_effect)  
{
    if (show_effect == true)
    {
//        jeti::ExplosionEffect* explosion = jeti::getNewExplosionEffect(collisionRadius());
//        starsystem()->Add(explosion, center());
    }
}

//void RocketBullet::RenderInSpace(const Renderer& render, float scale)
//{
//    //alpitodorender render.DrawQuad(textureOb(), actualModelMatrix());

//    m_EffectDrive->Update();
//    m_EffectDrive->Render(scale, 0.0f);
//}


void RocketBullet::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    save_ptree.put(root+"speed", m_Speed);
    save_ptree.put(root+"owner_id", m_OwnerId);
    if (m_Target != nullptr)     { save_ptree.put(root+"target_id", m_Target->id()); }
    else                        { save_ptree.put(root+"target_id", NONE_ID); }
    
    m_DataBullet.Save(save_ptree, root);
}

void RocketBullet::LoadData(const boost::property_tree::ptree& load_ptree)
{
    m_Speed = load_ptree.get<float>("speed");  
    m_OwnerId = load_ptree.get<int>("owner_id");  
    unresolved_RocketBullet_target_id = load_ptree.get<int>("target_id");  
    
    m_DataBullet.Load(load_ptree.get_child("data_bullet"));
}

void RocketBullet::ResolveData()
{           
    CreateDriveComplexTextureDependedStuff();
                
    if (unresolved_RocketBullet_target_id != NONE_ID)
    {
        m_Target = (SpaceObject*)global::get().entityManager().get(unresolved_RocketBullet_target_id);
    }
    
    ((Starsystem*)global::get().entityManager().get(data_unresolved_SpaceObject.starsystem_id))->add(this, data_unresolved_Orientation.center, data_unresolved_Orientation.direction);
}
   
   
/* virtual override final */
void RocketBullet::Save(boost::property_tree::ptree& save_ptree) const
{
    const std::string root = "rocketbullet."+std::to_string(id())+".";

    Base::SaveData(save_ptree, root);
    //Orientation::SaveData(save_ptree, root);
//    BaseDrawable::SaveData(save_ptree, root);
    SpaceObject::SaveData(save_ptree, root);
    RocketBullet::SaveData(save_ptree, root);
}

/* virtual override final */
void RocketBullet::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
    //Orientation::LoadData(load_ptree);
//    BaseDrawable::LoadData(load_ptree);
    SpaceObject::LoadData(load_ptree);
    RocketBullet::LoadData(load_ptree);
}

/* virtual override final */
void RocketBullet::Resolve()
{
    Base::ResolveData();
    //Orientation::ResolveData();
//    BaseDrawable::ResolveData();
    SpaceObject::ResolveData();
    RocketBullet::ResolveData();
}
