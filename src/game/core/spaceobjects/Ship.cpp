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

//#include <ceti/StringUtils.hpp>
#include <common/Logger.hpp>

#include <world/starsystem.hpp>

#include <effects/Shield.hpp>

#include <items/equipment/GrappleEquipment.hpp>

#include <slots/ItemSlot.hpp>
#include <slots/VehicleSlot.hpp>

#include <pilots/Npc.hpp>

#include <jeti/TextureOb.hpp>


Ship::Ship(int id)
{
    setId(id);
    setTypeId(TYPE::ENTITY::VEHICLE_ID);
    setSubTypeId(TYPE::ENTITY::SHIP_ID);
}

/* virtual override final */
Ship::~Ship()
{
    #if CREATEDESTROY_LOG_ENABLED == 1
    Logger::Instance().Log("___::~Ship("+std::to_string(id())+")");
    #endif
} 


///* virtual override final */
//void Ship::UpdateInfo()
//{
//    GetInfo().clear();

//    GetInfo().addTitleStr("SHIP");
//    if (starsystem())    { GetInfo().addNameStr("id/ss_id:"); GetInfo().addValueStr( std::to_string(id()) + " / " + std::to_string(starsystem()->id()) ); }
//    else                     { GetInfo().addNameStr("id:");       GetInfo().addValueStr( std::to_string(id()) ); }
//    // alpitodorender GetInfo().addNameStr("race:");          GetInfo().addValueStr( getRaceStr(GetTextureOb().GetAssociation().race_id) );
//    GetInfo().addNameStr("class:");         GetInfo().addValueStr( getStr(subSubTypeId()) );
//    GetInfo().addNameStr("armor/max:");     GetInfo().addValueStr( std::to_string(dataLife().armor) + "/" + std::to_string(GetDataKorpus().armor) );
////    alpitodorender GetInfo().addNameStr("size id:");       GetInfo().addValueStr( std::to_string(GetTextureOb().GetData().size_id) );
//    GetInfo().addNameStr("space/free:");    GetInfo().addValueStr( std::to_string(GetDataKorpus().space) + "/" + std::to_string(GetProperties().free_space) );
//    GetInfo().addNameStr("mass:");          GetInfo().addValueStr( std::to_string(mass()) );
//    GetInfo().addNameStr("speedx100:");     GetInfo().addValueStr( std::to_string(GetProperties().speed*100) );
//    GetInfo().addNameStr("speed dmx100:");  GetInfo().addValueStr( std::to_string(mass()*MASS_DECREASE_SPEED_RATE*100));
//    GetInfo().addNameStr("energy:");        GetInfo().addValueStr( std::to_string(GetProperties().energy) );
//    GetInfo().addNameStr("temp.:");         GetInfo().addValueStr( std::to_string(GetDataKorpus().temperature) );
//    GetInfo().addNameStr("radar:");         GetInfo().addValueStr( std::to_string(GetProperties().radar) );
//    GetInfo().addNameStr("protect:");       GetInfo().addValueStr( std::to_string(GetProperties().protection) );
//    GetInfo().addNameStr("repair:");        GetInfo().addValueStr( std::to_string(GetProperties().repair) );
//    GetInfo().addNameStr("scan:");          GetInfo().addValueStr( std::to_string(GetProperties().scan) );
//    GetInfo().addNameStr("price:");         GetInfo().addValueStr( std::to_string(GetDataKorpus().price) );
//    GetInfo().addNameStr("pos:");           GetInfo().addValueStr( meti::str(center()) );
        
//    if (GetProperties().grab_radius > 0)
//    {
//        std::string grab_str = GetSlotGrapple()->GetGrappleEquipment()->GetTargetStr();
//        if (grab_str.size() > 0)
//        {
//            GetInfo().addNameStr("grab_id:");           GetInfo().addValueStr( grab_str );
//        }
//    }

//    //info.addNameStr("attackR:");           info.addValueStr( boost::lexical_cast<std::string>(propetries.attack_rate_normalized) );
//    //info.addNameStr("defenceR:");           info.addValueStr( boost::lexical_cast<std::string>(propetries.defence_rate_normalized) );
//}

/* virtual override final */
void Ship::UpdateInSpace(int time, bool show_effect)
{   
    checkDeath(show_effect);
    GetComplexProtector().GetShieldEffect()->Update();
GetComplexDrive().UpdatePosition(); // debug
            
    if (time > 0)
    {
        UpdateSpecialAction();
        
        GetOwnerNpc()->UpdateInSpace(time, show_effect);
        updateOrientation();   
        GetComplexWeapon().Fire(time, GetOwnerNpc()->GetSkills().GetAttackNormalized(), show_effect);
        
        if (GetProperties().speed > 0) 
        { 
            GetComplexDrive().UpdatePosition();
        }
        
        UpdateGrappleMicroProgram_inDynamic();
    }
}

//void Ship::RenderInSpace(const jeti::Renderer& render, float scale)
//{
//    //if (GetProperties().grab_radius > 0)
//    //{
//        //RenderGrabTrail(render);
//    //}
        
//    RenderKorpus(render);
    
//    //if (GetDataKorpus().draw_turrels == true)
//    //{
//        //GetComplexWeapon().RenderTurrels();
//    //}
    
//    //if (GetProperties().speed > 0)
//    //{
//        //RenderDriveEffect(scale , 1.0 - GetColor().a);
//        //starsystem()->RestoreSceneColor();
//    //}
    
////    if (GetProperties().shield_effect_enabled == true)
////    {
////        RenderShieldEffect(render, 1.0f - GetColor().a);
////    }
//}

//void Ship::RenderAtPlanet(const jeti::Renderer& render, const glm::vec3& center)
//{
//    setCenter(center);
//    //SetAngleZ(0);
//    updateOrientation();
    
//    RenderKorpus(render);
    
//    if (GetDataKorpus().draw_turrels == true)
//    {
//        GetComplexWeapon().RenderTurrels();
//    }
//}

void Ship::SaveData(boost::property_tree::ptree&, const std::string&) const
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" Ship("+std::to_string(id())+")::SaveData", SAVELOAD_LOG_DIP);
    #endif
}

void Ship::LoadData(const boost::property_tree::ptree&)
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" Ship("+std::to_string(id())+")::LoadData", SAVELOAD_LOG_DIP);
    #endif
}

void Ship::ResolveData()
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" Ship("+std::to_string(id())+")::ResolveData", SAVELOAD_LOG_DIP);
    #endif
}

/* virtual override final */
void Ship::Save(boost::property_tree::ptree& save_ptree) const
{
    const std::string root = "ship."+std::to_string(id())+".";

    Base::SaveData(save_ptree, root);
    Orientation::SaveData(save_ptree, root);
    //BaseDrawable::SaveData(save_ptree, root);
    SpaceObject::SaveData(save_ptree, root);
    Vehicle::SaveData(save_ptree, root);
    Ship::SaveData(save_ptree, root);
}

/* virtual override final */
void Ship::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
    Orientation::LoadData(load_ptree);
//    BaseDrawable::LoadData(load_ptree);
    SpaceObject::LoadData(load_ptree);
    Vehicle::LoadData(load_ptree);
    Ship::LoadData(load_ptree);
}

/* virtual override final */
void Ship::Resolve()
{
    Base::ResolveData();
    Orientation::ResolveData();
//    BaseDrawable::ResolveData();
    SpaceObject::ResolveData();
    Vehicle::ResolveData();
    Ship::ResolveData();
}
