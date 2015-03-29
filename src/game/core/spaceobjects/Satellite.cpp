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
#include <meti/RandUtils.hpp>
//#include <ceti/StringUtils.hpp>
#include "../common/Logger.hpp"
#include "../common/Global.hpp"
#include "../world/starsystem.hpp"
//#include "../effects/Shield.hpp"
#include "../slots/ItemSlot.hpp"
#include "../parts/WeaponComplex.hpp"
#include "../pilots/Npc.hpp"

Satellite::Satellite(int id)
{        
    setId(id);
    setTypeId(TYPE::ENTITY::VEHICLE_ID);
    setSubTypeId(TYPE::ENTITY::SATELLITE_ID);
    
    setMass(meti::getRandInt(ENTITY::SATELLITE::MASS_MIN, ENTITY::SATELLITE::MASS_MAX));
}

/* virtual */
Satellite::~Satellite() 
{
    #if CREATEDESTROY_LOG_ENABLED == 1
    Logger::Instance().Log("___::~Satellite("+std::to_string(id())+")");
    #endif
}

void Satellite::BindParent(const SpaceObject* const parent)
{
    setParent(parent);
    m_Orbit.CalcPath(2*1.1*parent->collisionRadius(), 1.0, meti::getRandBool());
}
        
void Satellite::UpdateInSpace(int time, bool show_effect)
{
    checkDeath(show_effect);
//    UpdateRenderStuff();
    if (time > 0)
    {
        m_Orbit.UpdatePosition();

        //printf("sat orbit =%f,%f\n", orbit->getPosition().x, orbit->getPosition().y);
        //if (parent != nullptr)
        //{        
            glm::vec3 new_pos;
            new_pos.x = parent()->center().x + m_Orbit.GetPosition().x;
            new_pos.y = parent()->center().y + m_Orbit.GetPosition().y;
            new_pos.z = parent()->center().z;
            setCenter(new_pos);
            updateOrientation();
        //}
        //else
        //{
            //points.setCenter(orbit->getPosition());
        //}
        
        GetComplexWeapon().Fire(time, GetOwnerNpc()->GetSkills().GetAttackNormalized(), show_effect);
    }
}

//void Satellite::UpdateInfo()
//{
//    GetInfo().clear();

//    GetInfo().addTitleStr("SATELLITE");

//    //GetInfo().addNameStr("id/ss_id:");  GetInfo().addValueStr(std::to_string(id()) + " / " + std::to_string(starsystem->id()));
//    GetInfo().addNameStr("id:");          GetInfo().addValueStr(std::to_string(id()));
//    GetInfo().addNameStr("mass:");        GetInfo().addValueStr(std::to_string(mass()));
//    GetInfo().addNameStr("pos:");         GetInfo().addValueStr( meti::str(center()) );
//}
            
//void Satellite::UpdateRenderStuff()
//{
//    GetComplexProtector().GetShieldEffect()->Update();
//    updateOrientation();
//}

//void Satellite::RenderInSpace(const jeti::Renderer& render, float scale)
//{
//    RenderKorpus(render);
    
//    //if (GetDataKorpus().draw_turrels == true)
//    //{
//        //GetComplexWeapon().RenderTurrels();
//    //}

//    //if (GetComplexProtector().GetProtectorSlot()->GetItem() != nullptr)
//    //{
//        //RenderShieldEffect(1.0 - GetColor().a);
//        //starsystem()->RestoreSceneColor();
//    //}
//}

//void Satellite::RenderAtPlanet(const jeti::Renderer& render)
//{
//    RenderKorpus(render);
    
//    //if (GetDataKorpus().draw_turrels == true)
//    //{
//        //GetComplexWeapon().RenderTurrels();
//    //}
//}


void Satellite::SaveData(boost::property_tree::ptree&, const std::string&) const
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" Satellite("+std::to_string(id())+")::SaveData", SAVELOAD_LOG_DIP);
    #endif
}

void Satellite::LoadData(const boost::property_tree::ptree&)
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" Satellite("+std::to_string(id())+")::LoadData", SAVELOAD_LOG_DIP);
    #endif
}

void Satellite::ResolveData()
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" Satellite("+std::to_string(id())+")::ResolveData", SAVELOAD_LOG_DIP);
    #endif
}

/*virtual*/
void Satellite::Save(boost::property_tree::ptree& save_ptree) const
{
    const std::string root = "satellite."+std::to_string(id())+".";

    Base::SaveData(save_ptree, root);
    //Orientation::SaveData(save_ptree, root);
//    BaseDrawable::SaveData(save_ptree, root);
    SpaceObject::SaveData(save_ptree, root);
    Vehicle::SaveData(save_ptree, root);
    Satellite::SaveData(save_ptree, root);
}

/*virtual*/
void Satellite::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
//    Orientation::LoadData(load_ptree);
//    BaseDrawable::LoadData(load_ptree);
    SpaceObject::LoadData(load_ptree);
    Vehicle::LoadData(load_ptree);
    Satellite::LoadData(load_ptree);
}

/*virtual*/
void Satellite::Resolve()
{
    Base::ResolveData();
//    Orientation::ResolveData();
//    BaseDrawable::ResolveData();
    SpaceObject::ResolveData();
    Vehicle::ResolveData();
    Satellite::ResolveData();
}
