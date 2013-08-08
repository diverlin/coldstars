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

#include "Satellite.hpp"
#include "../common/rand.hpp"
#include "../common/myStr.hpp"
#include "../common/Logger.hpp"
#include "../world/EntityManager.hpp"
#include "../world/starsystem.hpp"
#include "../effects/Shield.hpp"
#include "../slots/ItemSlot.hpp"
#include "../parts/WeaponComplex.hpp"
#include "../pilots/Npc.hpp"

Satellite::Satellite(int id)
{        
    SetId(id);
    SetTypeId(TYPE::ENTITY::VEHICLE_ID);
    SetSubTypeId(TYPE::ENTITY::SATELLITE_ID);
    
    SetMass(getRandInt(ENTITY::SATELLITE::MASS_MIN, ENTITY::SATELLITE::MASS_MAX));
}

/* virtual */
Satellite::~Satellite() 
{
    #if CREATEDESTROY_LOG_ENABLED == 1
    Logger::Instance().Log("___::~Satellite("+int2str(GetId())+")");
    #endif
}

void Satellite::BindParent(const BaseSpaceEntity* const parent)
{
    SetParent(parent);
    m_Orbit.CalcPath(2*1.1*parent->GetCollisionRadius(), 1.0, getRandBool());
}
        
void Satellite::UpdateInSpace(int time, bool show_effect)
{
    CheckDeath(show_effect);
    UpdateRenderStuff(); 
    if (time > 0)
    {
        m_Orbit.UpdatePosition();

        //printf("sat orbit =%f,%f\n", orbit->getPosition().x, orbit->getPosition().y);
        //if (parent != nullptr)
        //{        
            Vec3<float> new_pos;
            new_pos.x = GetParent()->GetCenter().x + m_Orbit.GetPosition().x;
            new_pos.y = GetParent()->GetCenter().y + m_Orbit.GetPosition().y;
            new_pos.z = GetParent()->GetCenter().z;
            SetCenter(new_pos);
            UpdateOrientation();
        //}
        //else
        //{
            //points.SetCenter(orbit->getPosition());
        //}
        
        GetComplexWeapon().Fire(time, GetOwnerNpc()->GetSkills().GetAttackNormalized(), show_effect);
    }
}

void Satellite::UpdateInfo()
{
    GetInfo().clear();

    GetInfo().addTitleStr("SATELLITE");

    //GetInfo().addNameStr("id/ss_id:");  GetInfo().addValueStr(int2str(GetId()) + " / " + int2str(starsystem->GetId()));
    GetInfo().addNameStr("id:");          GetInfo().addValueStr(int2str(GetId()));
    GetInfo().addNameStr("mass:");        GetInfo().addValueStr(int2str(GetMass()));
    GetInfo().addNameStr("pos:");         GetInfo().addValueStr( str(GetCenter()) );
}
            
void Satellite::UpdateRenderStuff()
{
    GetComplexProtector().GetShieldEffect()->Update();    
    UpdateOrientation();
}

void Satellite::RenderInSpace(float scale)
{   
    UpdateRenderAnimation();
        
    RenderKorpus();
    
    if (GetDataKorpus().draw_turrels == true)
    {
        GetComplexWeapon().RenderTurrels();
    }

    if (GetComplexProtector().GetProtectorSlot()->GetItem() != nullptr)
    {
        RenderShieldEffect(1.0 - GetColor().a); 
    }
}

void Satellite::RenderAtPlanet() const
{
    RenderKorpus();
    
    if (GetDataKorpus().draw_turrels == true)
    {
        GetComplexWeapon().RenderTurrels();
    }
}        


void Satellite::SaveDataUniqueSatellite(boost::property_tree::ptree&, const std::string&) const
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" Satellite("+int2str(GetId())+")::SaveDataUniqueSatellite", SAVELOAD_LOG_DIP);
    #endif
}

void Satellite::LoadDataUniqueSatellite(const boost::property_tree::ptree&)
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" Satellite("+int2str(GetId())+")::LoadDataUniqueSatellite", SAVELOAD_LOG_DIP);
    #endif
}

void Satellite::ResolveDataUniqueSatellite()
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" Satellite("+int2str(GetId())+")::ResolveDataUniqueSatellite", SAVELOAD_LOG_DIP);
    #endif
}

/*virtual*/
void Satellite::SaveData(boost::property_tree::ptree& save_ptree) const
{
    const std::string root = "satellite."+int2str(GetId())+".";
    SaveDataUniqueBase(save_ptree, root);
    SaveDataUniqueOrientation(save_ptree, root);
    SaveDataUniqueBaseDrawable(save_ptree, root);
    SaveDataUniqueBaseSpaceEntity(save_ptree, root);
    SaveDataUniqueVehicle(save_ptree, root);
    SaveDataUniqueSatellite(save_ptree, root);
}

/*virtual*/
void Satellite::LoadData(const boost::property_tree::ptree& load_ptree)
{
    LoadDataUniqueBase(load_ptree);
    LoadDataUniqueOrientation(load_ptree);
    LoadDataUniqueBaseDrawable(load_ptree);
    LoadDataUniqueBaseSpaceEntity(load_ptree);
    LoadDataUniqueVehicle(load_ptree);
    LoadDataUniqueSatellite(load_ptree);
}

/*virtual*/
void Satellite::ResolveData()
{
    ResolveDataUniqueBase();
    ResolveDataUniqueOrientation();
    ResolveDataUniqueBaseDrawable();
    ResolveDataUniqueBaseSpaceEntity();
    ResolveDataUniqueVehicle();
    ResolveDataUniqueSatellite();
}

