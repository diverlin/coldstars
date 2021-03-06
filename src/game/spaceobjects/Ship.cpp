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


#include "Ship.hpp"

#include <common/myStr.hpp>
#include <common/Logger.hpp>

#include <world/starsystem.hpp>

#include <effects/Shield.hpp>

#include <items/equipment/GrappleEquipment.hpp>

#include <slots/ItemSlot.hpp>
#include <slots/VehicleSlot.hpp>

#include <pilots/Npc.hpp>

#include <render/Render.hpp>

#include <resources/textureOb.hpp>


Ship::Ship(int id)
{
    SetId(id);
    SetTypeId(TYPE::ENTITY::VEHICLE_ID);
    SetSubTypeId(TYPE::ENTITY::SHIP_ID);
}

/* virtual override final */
Ship::~Ship()
{
    #if CREATEDESTROY_LOG_ENABLED == 1
    Logger::Instance().Log("___::~Ship("+int2str(GetId())+")");
    #endif
} 


/* virtual override final */
void Ship::UpdateInfo()
{
    GetInfo().clear();

    GetInfo().addTitleStr("SHIP");
    if (GetStarSystem())    { GetInfo().addNameStr("id/ss_id:"); GetInfo().addValueStr( int2str(GetId()) + " / " + int2str(GetStarSystem()->GetId()) ); }
    else                     { GetInfo().addNameStr("id:");       GetInfo().addValueStr( int2str(GetId()) ); }
    GetInfo().addNameStr("race:");          GetInfo().addValueStr( getRaceStr(GetTextureOb().GetAssociation().race_id) ); 
    GetInfo().addNameStr("class:");         GetInfo().addValueStr( getEntityTypeStr(GetSubSubTypeId()) );         
    GetInfo().addNameStr("armor/max:");     GetInfo().addValueStr( int2str(GetDataLife().armor) + "/" + int2str(GetDataKorpus().armor) );
    GetInfo().addNameStr("size id:");       GetInfo().addValueStr( int2str(GetTextureOb().GetData().size_id) );
    GetInfo().addNameStr("space/free:");    GetInfo().addValueStr( int2str(GetDataKorpus().space) + "/" + int2str(GetProperties().free_space) );
    GetInfo().addNameStr("mass:");          GetInfo().addValueStr( int2str(GetMass()) );
    GetInfo().addNameStr("speedx100:");     GetInfo().addValueStr( int2str(GetProperties().speed*100) );
    GetInfo().addNameStr("speed dmx100:");  GetInfo().addValueStr( int2str(GetMass()*MASS_DECREASE_SPEED_RATE*100));
    GetInfo().addNameStr("energy:");        GetInfo().addValueStr( int2str(GetProperties().energy) );
    GetInfo().addNameStr("temp.:");         GetInfo().addValueStr( int2str(GetDataKorpus().temperature) );
    GetInfo().addNameStr("radar:");         GetInfo().addValueStr( int2str(GetProperties().radar) );
    GetInfo().addNameStr("protect:");       GetInfo().addValueStr( int2str(GetProperties().protection) );
    GetInfo().addNameStr("repair:");        GetInfo().addValueStr( int2str(GetProperties().repair) );
    GetInfo().addNameStr("scan:");          GetInfo().addValueStr( int2str(GetProperties().scan) );
    GetInfo().addNameStr("price:");         GetInfo().addValueStr( int2str(GetDataKorpus().price) );
    GetInfo().addNameStr("pos:");           GetInfo().addValueStr( str(GetCenter()) );
        
    if (GetProperties().grab_radius > 0)
    {
        std::string grab_str = GetSlotGrapple()->GetGrappleEquipment()->GetTargetStr();
        if (grab_str.size() > 0)
        {
            GetInfo().addNameStr("grab_id:");           GetInfo().addValueStr( grab_str ); 
        }
    }

    //info.addNameStr("attackR:");           info.addValueStr( boost::lexical_cast<std::string>(propetries.attack_rate_normalized) );    
    //info.addNameStr("defenceR:");           info.addValueStr( boost::lexical_cast<std::string>(propetries.defence_rate_normalized) );    
}

/* virtual override final */
void Ship::UpdateInSpace(int time, bool show_effect)
{   
    CheckDeath(show_effect);
    GetComplexProtector().GetShieldEffect()->Update();
GetComplexDrive().UpdatePosition(); // debug
            
    if (time > 0)
    {
        UpdateSpecialAction();
        
        GetOwnerNpc()->UpdateInSpace(time, show_effect);
        UpdateOrientation();   
        GetComplexWeapon().Fire(time, GetOwnerNpc()->GetSkills().GetAttackNormalized(), show_effect);
        
        if (GetProperties().speed > 0) 
        { 
            GetComplexDrive().UpdatePosition();
        }
        
        UpdateGrappleMicroProgram_inDynamic();
    }
}

void Ship::RenderInSpace(const Renderer& render, float scale)
{   
    //if (GetProperties().grab_radius > 0)
    //{
        //RenderGrabTrail(render);
    //}
        
    RenderKorpus(render);
    
    //if (GetDataKorpus().draw_turrels == true)
    //{
        //GetComplexWeapon().RenderTurrels();
    //}
    
    //if (GetProperties().speed > 0)
    //{
        //RenderDriveEffect(scale , 1.0 - GetColor().a);
        //GetStarSystem()->RestoreSceneColor();
    //}
    
    if (GetProperties().shield_effect_enabled == true)
    {
        RenderShieldEffect(render, 1.0f - GetColor().a); 
    }
}

void Ship::RenderAtPlanet(const Renderer& render, const glm::vec3& center)
{
    SetCenter(center);
    //SetAngleZ(0);
    UpdateOrientation();
    
    RenderKorpus(render);
    
    if (GetDataKorpus().draw_turrels == true)
    {
        GetComplexWeapon().RenderTurrels();
    }
}        

void Ship::SaveData(boost::property_tree::ptree&, const std::string&) const
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" Ship("+int2str(GetId())+")::SaveData", SAVELOAD_LOG_DIP);
    #endif
}

void Ship::LoadData(const boost::property_tree::ptree&)
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" Ship("+int2str(GetId())+")::LoadData", SAVELOAD_LOG_DIP);
    #endif
}

void Ship::ResolveData()
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" Ship("+int2str(GetId())+")::ResolveData", SAVELOAD_LOG_DIP);
    #endif
}

/* virtual override final */
void Ship::Save(boost::property_tree::ptree& save_ptree) const
{
    const std::string root = "ship."+int2str(GetId())+".";

    Base::SaveData(save_ptree, root);
    Orientation::SaveData(save_ptree, root);
    BaseDrawable::SaveData(save_ptree, root);
    BaseSpaceEntity::SaveData(save_ptree, root);
    Vehicle::SaveData(save_ptree, root);
    Ship::SaveData(save_ptree, root);
}

/* virtual override final */
void Ship::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
    Orientation::LoadData(load_ptree);
    BaseDrawable::LoadData(load_ptree);
    BaseSpaceEntity::LoadData(load_ptree);
    Vehicle::LoadData(load_ptree);
    Ship::LoadData(load_ptree);
}

/* virtual override final */
void Ship::Resolve()
{
    Base::ResolveData();
    Orientation::ResolveData();
    BaseDrawable::ResolveData();
    BaseSpaceEntity::ResolveData();
    Vehicle::ResolveData();
    Ship::ResolveData();
}
