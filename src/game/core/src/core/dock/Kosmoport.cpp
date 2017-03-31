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

#include "Kosmoport.hpp" 
#include <core/spaceobject/Vehicle.hpp>
//#include <ceti/StringUtils.hpp>
#include "../common/constants.hpp"
#include <common/Global.hpp>
#include <core/manager/EntityManager.hpp>

#include "../dock/Angar.hpp"
#include "../dock/Store.hpp"
#include "../dock/Shop.hpp"
#include "../dock/Goverment.hpp"

#include <core/slot/VehicleSlot.hpp>

namespace control {

Kosmoport::Kosmoport(int id)
{
    assert(false);
    //    setId(id);
    //    setTypeId(entity::Type::KOSMOPORT);
}

/* virtual */
Kosmoport::~Kosmoport()
{}

/* virtual */
void Kosmoport::putChildrenToGarbage() const
{
    assert(false);
    //   EntityManager::get().addToGarbage(angar);
    //   EntityManager::get().addToGarbage(store);
    //   EntityManager::get().addToGarbage(shop);
    //   EntityManager::get().addToGarbage(goverment);
}

void Kosmoport::bindAngar(Angar* angar)
{ 
    m_angar= angar;
    m_angar->setKosmoport(this);
}

void Kosmoport::bindStore(Store* store)
{ 
    m_store = store;
    m_store->setKosmoport(this);
}

void Kosmoport::bindShop(Shop* shop)
{ 
    m_shop = shop;
    m_shop->setKosmoport(this);
}

void Kosmoport::bindGoverment(Goverment* goverment)
{ 
    m_goverment= goverment;
    m_goverment->setKosmoport(this);
}

/* virtual */
bool Kosmoport::isAllowedToLand() const
{
    if (m_angar->freeVehicleSlotTotalNum() > 0) {
        return true;
    }

    return false;
}

/* virtual */
bool Kosmoport::add(Vehicle* vehicle)
{        
    assert(false);
    //    vehicle->setPlaceTypeId(type::place::KOSMOPORT);
    //    angar->AddVehicle(vehicle);
    
    //    vehicle->setLand(this);
    //    if (!vehicle->starsystem()) {
    //        // TODO
    //        //vehicle->setStarSystem(m_owner->starsystem());
    //    }

    return true;
}

//* virtual */
bool Kosmoport::remove(Vehicle* vehicle)
{        
    assert(false);
    //    vehicle->parentVehicleSlot()->Release();
    return true;
}


/* virtual */
void Kosmoport::updateInStatic()
{
    m_angar->updateInStatic();
}

/* virtual */
std::string Kosmoport::vehiclesStr() const
{
    return m_angar->vehiclesStr();
}                


//void Kosmoport::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
//{}

//void Kosmoport::LoadData(const boost::property_tree::ptree& load_ptree)
//{}

//void Kosmoport::ResolveData()
//{}


//void Kosmoport::Save(boost::property_tree::ptree& save_ptree) const
//{
////    std::string root = "kosmoport." + std::to_string(id())+".";

////    Base::SaveData(save_ptree, root);
////    Land::SaveData(save_ptree, root);
////    Kosmoport::SaveData(save_ptree, root);
//}

//void Kosmoport::Load(const boost::property_tree::ptree& load_ptree)
//{
////    Base::LoadData(load_ptree);
////    Land::LoadData(load_ptree);
////    Kosmoport::LoadData(load_ptree);
//}

//void Kosmoport::Resolve()
//{
////    Base::ResolveData();
////    Land::ResolveData();
////    Kosmoport::ResolveData();
//}

} // namespace control
