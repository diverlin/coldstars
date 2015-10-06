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

#include "SpaceStation.hpp"
#include <math/rand.hpp>
//#include <ceti/StringUtils.hpp>
#include <ceti/Logger.hpp>

#include <common/Global.hpp>
#include <managers/EntitiesManager.hpp>
#include <world/starsystem.hpp>

#include <dock/Kosmoport.hpp>

//#include <effects/Shield.hpp>

#include <slots/ItemSlot.hpp>

#include <pilots/Npc.hpp>



SpaceStation::SpaceStation(int id)
: 
m_Land(nullptr)
{      
    setId(id);
    setTypeId(TYPE::ENTITY::VEHICLE_ID);
    setSubTypeId(TYPE::ENTITY::SPACESTATION_ID);
}

/* virtual */
SpaceStation::~SpaceStation() 
{
    Logger::Instance().Log("___::~SpaceStation("+std::to_string(id())+")");
}    
 
/* virtual override final */
void SpaceStation::putChildrenToGarbage() const 
{
    global::get().entitiesManager().addToGarbage(m_Land);
    GetOwnerNpc()->SetAlive(false);
    global::get().entitiesManager().addToGarbage(GetOwnerNpc());
    
    for(unsigned int i=0; i<m_SlotTotal_vec.size(); i++)
    {
        global::get().entitiesManager().addToGarbage(m_SlotTotal_vec[i]);
    }
}

void SpaceStation::BindLand(Land* land)               
{
    m_Land = land;
    m_Land->SetOwner(this);
}
 
/* virtual override final */          
void SpaceStation::UpdateInSpace(int time, bool show_effect)
{
    checkDeath(show_effect);
    if (time > 0)
    {
        GetComplexWeapon().Fire(time, GetOwnerNpc()->GetSkills().GetAttackNormalized(), show_effect);
    }
}

///* virtual override final */
//void SpaceStation::UpdateInfo()
//{
//    GetInfo().clear();

//    GetInfo().addTitleStr("StarBase" + getStr(subTypeId()));

//    GetInfo().addNameStr("id/ss_id:");    GetInfo().addValueStr(std::to_string(id()) + " / " + std::to_string(starsystem()->id()));
//    GetInfo().addNameStr("id:");          GetInfo().addValueStr(std::to_string(id()));
//    GetInfo().addNameStr("mass:");        GetInfo().addValueStr(std::to_string(mass()));
//    GetInfo().addNameStr("pos:");         GetInfo().addValueStr( meti::str(center()) );
//}

//void SpaceStation::UpdateRenderStuff_2D()
//{
//    //points.update();
//    GetComplexProtector().GetShieldEffect()->Update();
    
//    //if (ableTo.DRIVE == true)
//    //{
//        //drive_trail->update();
//    //}
//}

//void SpaceStation::RenderInSpace(const jeti::Renderer& render, float scale)
//{
//    //UpdateRenderStuff_2D();
        
//    RenderKorpus(render);
        
//    //if (GetVehicleDescriptor().draw_turrels == true)
//    //{
//        //GetComplexWeapon().RenderTurrels();
//    //}
    
//    //if (GetComplexProtector().GetProtectorSlot()->item() != nullptr)
//    //{
//        //RenderShieldEffect(1.0 - color().a);
//        //starsystem()->RestoreSceneColor();
//    //}
//}

void SpaceStation::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    Logger::Instance().Log(" SpaceStation("+std::to_string(id())+")::SaveData", SAVELOAD_LOG_DIP);
}

void SpaceStation::LoadData(const boost::property_tree::ptree& load_ptree)
{
    Logger::Instance().Log(" SpaceStation("+std::to_string(id())+")::LoadData", SAVELOAD_LOG_DIP);
}

void SpaceStation::ResolveData()
{
    Logger::Instance().Log(" SpaceStation("+std::to_string(id())+")::ResolveData", SAVELOAD_LOG_DIP);
}


/* virtual override final */
void SpaceStation::Save(boost::property_tree::ptree& save_ptree) const
{
    const std::string root = "spacestation."+std::to_string(id())+".";

    Base::SaveData(save_ptree, root);
    //Orientation::SaveData(save_ptree, root);
//    BaseDrawable::SaveData(save_ptree, root);
    SpaceObject::SaveData(save_ptree, root);
    Vehicle::SaveData(save_ptree, root);
    SpaceStation::SaveData(save_ptree, root);
}

/* virtual override final */
void SpaceStation::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
    //Orientation::LoadData(load_ptree);
//    BaseDrawable::LoadData(load_ptree);
    SpaceObject::LoadData(load_ptree);
    Vehicle::LoadData(load_ptree);
    SpaceStation::LoadData(load_ptree);
}

/* virtual override final */
void SpaceStation::Resolve()
{
    Base::ResolveData();
    //Orientation::ResolveData();
//    BaseDrawable::ResolveData();
    SpaceObject::ResolveData();
    Vehicle::ResolveData();
    SpaceStation::ResolveData();
}
