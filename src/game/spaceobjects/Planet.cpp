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


#include "Planet.hpp"

#include <common/myStr.hpp>
#include <common/Logger.hpp>
  
#include <dock/Kosmoport.hpp>

#include <effects/BaseDecor.hpp>

#include <world/EntityManager.hpp>
#include <world/starsystem.hpp>

#include <spaceobjects/Vehicle.hpp>

#include <garbage/EntityGarbage.hpp>

#include <jeti/Render.hpp>


Planet::Planet(int id)
:
m_Land(nullptr),
m_Population(0)
{    
    SetId(id);
    SetTypeId(TYPE::ENTITY::PLANET_ID);
}

/* virtual */
Planet::~Planet()
{
    #if CREATEDESTROY_LOG_ENABLED == 1
    Logger::Instance().Log("___::~Planet("+int2str(GetId())+")");
    #endif
   
//    for (BaseDecor* decor : m_Decorations)
//    {
//        delete decor;
//    }
//    m_Decorations.clear();
}

/* virtual override final */
void Planet::PutChildsToGarbage() const
{
    EntityGarbage::Instance().Add(m_Land);
}

void Planet::BindLand(BaseLand* land)
{
    m_Land = land;
    m_Land->SetOwner(this);
    SetSubTypeId(land->GetTypeId());
}

void Planet::AddVehicle(Vehicle* vehicle) const
{
    if (vehicle->GetStarSystem() == nullptr)
    {
        vehicle->SetStarSystem(GetStarSystem());
    }
    
    m_Land->AddVehicle(vehicle);

}

void Planet::UpdateInSpace(int time, bool show_effect)
{      
    if (time > 0)
    {
        UpdatePosition();
    }
}

void Planet::UpdateInSpaceInStatic()
{
    m_Land->UpdateInStatic();
}

/* virtual override final */
void Planet::UpdateInfo()
{
    GetInfo().clear();
    
    GetInfo().addTitleStr("PLANET");
    GetInfo().addNameStr("id/ss_id:");    GetInfo().addValueStr(int2str(GetId()) + " / " + int2str(GetStarSystem()->GetId()));
    GetInfo().addNameStr("armor:");        GetInfo().addValueStr(int2str(GetDataLife().armor));
    GetInfo().addNameStr("population:");  GetInfo().addValueStr(int2str(m_Population));
    GetInfo().addNameStr("dock_veh:");    GetInfo().addValueStr(m_Land->GetDockVehicleStr());
    GetInfo().addNameStr("pos:");         GetInfo().addValueStr( str(GetCenter()) );
}

void Planet::PostDeathUniqueEvent(bool)
{}

//void Planet::Render_NEW(const Renderer& render)
//{
//    //alpitodorender render.DrawMeshLightNormalMap(GetMesh(), GetTextureOb(), GetActualModelMatrix());
//    for (BaseDecor* decor : m_Decorations)
//    {
//        decor->Render(render, GetCenter());
//    }
//}

void Planet::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" Planet("+int2str(GetId())+")::SaveData", SAVELOAD_LOG_DIP);
    #endif
    
    //SaveManager::Instance().Put(root+"race_id", race_id);
    save_ptree.put(root+"population", m_Population);
}

void Planet::LoadData(const boost::property_tree::ptree& load_ptree)
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" Planet("+int2str(GetId())+")::LoadData", SAVELOAD_LOG_DIP);
    #endif
    
    //race_id = SaveManager::Instance().Get<int>(root+"race_id");
    m_Population = load_ptree.get<unsigned int>("population");    
}

void Planet::ResolveData()
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" Planet("+int2str(GetId())+")::ResolveData", SAVELOAD_LOG_DIP);
    #endif
    
    ((StarSystem*)EntityManager::Instance().GetEntityById(data_unresolved_BaseSpaceEntity.starsystem_id))->Add(this, GetParent(), data_unresolved_BasePlanet.orbit_it); 
}

/* virtual override final */
void Planet::Save(boost::property_tree::ptree& save_ptree) const        
{
    std::string root = "planet." + int2str(GetId())+".";

    Base::SaveData(save_ptree, root);
    Orientation::SaveData(save_ptree, root);
    BaseSpaceEntity::SaveData(save_ptree, root);
    BasePlanet::SaveData(save_ptree, root);
    Planet::SaveData(save_ptree, root);
}

/* virtual override final */
void Planet::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
    Orientation::LoadData(load_ptree);
    BaseSpaceEntity::LoadData(load_ptree);
    BasePlanet::LoadData(load_ptree);
    Planet::LoadData(load_ptree);
}

/* virtual override final */
void Planet::Resolve()
{
    Base::ResolveData();
    Orientation::ResolveData();
    BaseSpaceEntity::ResolveData();
    BasePlanet::ResolveData();
    Planet::ResolveData();
}
