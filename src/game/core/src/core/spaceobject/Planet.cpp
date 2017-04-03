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

//#include <ceti/StringUtils.hpp>
#include <ceti/Logger.hpp>
  
#include <dock/Kosmoport.hpp>

#include <common/Global.hpp>
#include <core/world/starsystem.hpp>

#include <core/model/spaceobject/Planet.hpp>
#include <core/spaceobject/Vehicle.hpp>

#include <core/manager/EntityManager.hpp>


namespace control {

Planet::Planet(descriptor::Planet* descr, model::Planet* model)
    :
      Planetoid(descr, model)
    , m_descriptor_planet(descr)
    , m_model_planet(model)
{}

Planet::~Planet()
{}

/* virtual override final */
void
Planet::putChildrenToGarbage() const
{
    //global::get().entityManager().addToGarbage(m_model->land);
}

int
Planet::radius() const
{
    return model()->radius();
}

void
Planet::bindLand(Land* land)
{
    m_land = land;
    land->setOwner(this);
    model()->setLand(land->id());
}

//void Planet::addVehicle(Vehicle* vehicle)
//{
//    if (!vehicle->starsystem()) {
//        vehicle->setStarSystem(starsystem());
//    }
        
//    land()->AddVehicle(vehicle);
//}

void Planet::updateInSpace(int time, bool show_effect)
{      
    if (time > 0) {
        _updatePosition();
    }
}

void Planet::updateInSpaceInStatic()
{
    std::cout<<"WARNING: implement land please"<<std::endl;
    //land()->UpdateInStatic();
}

///* virtual override final */
//void Planet::UpdateInfo()
//{
//    GetInfo().clear();
    
//    GetInfo().addTitleStr("PLANET");
//    GetInfo().addNameStr("id/ss_id:");    GetInfo().addValueStr(std::to_string(id()) + " / " + std::to_string(starsystem()->id()));
//    GetInfo().addNameStr("armor:");        GetInfo().addValueStr(std::to_string(dataLife().armor));
//    GetInfo().addNameStr("population:");  GetInfo().addValueStr(std::to_string(m_Population));
//    GetInfo().addNameStr("dock_veh:");    GetInfo().addValueStr(m_Land->GetDockVehicleStr());
//    GetInfo().addNameStr("pos:");         GetInfo().addValueStr( meti::str(center()) );
//}

void Planet::_postDeathUniqueEvent(bool)
{}

} // namespace control





//Planet::Planet(int id)
//{
//    setId(id);
//    setTypeId(entity::Type::PLANET);
//}

//Planet::~Planet()
//{}

//void Planet::_postDeathUniqueEvent(bool)
//{}

///* virtual override final */
//void Planet::putChildrenToGarbage() const
//{
//    //global::get().entityManager().addToGarbage(m_model->land);
//}

//void Planet::BindLand(Land* land)
//{
//    m_land = land;
//    m_land->SetOwner(this);
//    setSubTypeId(m_land->type());
//}

//void Planet::AddVehicle(Vehicle* vehicle) const
//{
//    if (vehicle->starsystem() == nullptr) {
//        vehicle->setStarSystem(starsystem());
//    }

//    m_land->AddVehicle(vehicle);

//}

//void Planet::UpdateInSpace(int time, bool show_effect)
//{
//    if (time > 0) {
//        _updatePosition();
//    }
//}

//void Planet::UpdateInSpaceInStatic()
//{
//    m_land->UpdateInStatic();
//}

////void Planet::Render_NEW(const jeti::Renderer& render)
////{
////    //alpitodorender render.DrawMeshLightNormalMap(mesh(), textureOb(), actualModelMatrix());
////    for (BaseDecor* decor : m_Decorations)
////    {
////        decor->Render(render, center());
////    }
////}

//void Planet::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
//{
//    LOG(" Planet("+std::to_string(id())+")::SaveData");

//    //SaveManager::Instance().Put(root+"race_id", race_id);
//    save_ptree.put(root+"population", m_population);
//}

//void Planet::LoadData(const boost::property_tree::ptree& load_ptree)
//{
//    LOG(" Planet("+std::to_string(id())+")::LoadData");

//    //race_id = SaveManager::Instance().Get<int>(root+"race_id");
//    m_population = load_ptree.get<unsigned int>("population");
//}

//void Planet::ResolveData()
//{
//    LOG(" Planet("+std::to_string(id())+")::ResolveData");

//    ((Starsystem*)EntityManager::get().getEntity(data_unresolved_SpaceObject.starsystem_id))->add(this, parent(), data_unresolved_Planetoid.orbit_it);
//}

///* virtual override final */
//void Planet::Save(boost::property_tree::ptree& save_ptree) const
//{
//    std::string root = "planet." + std::to_string(id())+".";

//    Base::SaveData(save_ptree, root);
//    //Orientation::SaveData(save_ptree, root);
//    SpaceObject::SaveData(save_ptree, root);
//    Planetoid::SaveData(save_ptree, root);
//    Planet::SaveData(save_ptree, root);
//}

///* virtual override final */
//void Planet::Load(const boost::property_tree::ptree& load_ptree)
//{
//    Base::LoadData(load_ptree);
//   // Orientation::LoadData(load_ptree);
//    SpaceObject::LoadData(load_ptree);
//    Planetoid::LoadData(load_ptree);
//    Planet::LoadData(load_ptree);
//}

///* virtual override final */
//void Planet::Resolve()
//{
//    Base::ResolveData();
//    //Orientation::ResolveData();
//    SpaceObject::ResolveData();
//    Planetoid::ResolveData();
//    Planet::ResolveData();
//}
