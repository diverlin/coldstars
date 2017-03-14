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

Kosmoport::Kosmoport(int id)
:
race_id(race::Type::R0), //wrong
angar(nullptr),
store(nullptr),
shop(nullptr),
goverment(nullptr)    
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
//   core::global::get().entityManager().addToGarbage(angar);
//   core::global::get().entityManager().addToGarbage(store);
//   core::global::get().entityManager().addToGarbage(shop);
//   core::global::get().entityManager().addToGarbage(goverment);
}
       
void Kosmoport::BindAngar(Angar* angar)
{ 
    this->angar= angar; 
    this->angar->SetOwnerKosmoport(this);
}

void Kosmoport::BindStore(Store* store)             
{ 
    this->store = store; 
    this->store->SetOwnerKosmoport(this);    
}

void Kosmoport::BindShop(Shop* shop)                    
{ 
    this->shop = shop; 
    this->shop->SetOwnerKosmoport(this);
}

void Kosmoport::BindGoverment(Goverment* goverment)     
{ 
    this->goverment= goverment; 
    this->goverment->SetOwnerKosmoport(this);
}
                    
/* virtual */
bool Kosmoport::GetPermissionToLand() const
{
          if (angar->GetFreeVehicleSlotTotalNum() > 0) 
        { 
            return true; 
        }
        
        return false;
}
                
/* virtual */
bool Kosmoport::AddVehicle(Vehicle* vehicle)
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
bool Kosmoport::RemoveVehicle(Vehicle* vehicle)
{        
    assert(false);
//    vehicle->parentVehicleSlot()->Release();
    return true;
}


/* virtual */
void Kosmoport::UpdateInStatic()
{
    angar->UpdateInStatic();
}

/* virtual */
std::string Kosmoport::GetDockVehicleStr() const
{
    return angar->GetDockVehicleStr();
}                


void Kosmoport::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{}

void Kosmoport::LoadData(const boost::property_tree::ptree& load_ptree)
{}

void Kosmoport::ResolveData()
{}


void Kosmoport::Save(boost::property_tree::ptree& save_ptree) const
{
//    std::string root = "kosmoport." + std::to_string(id())+".";

//    Base::SaveData(save_ptree, root);
//    Land::SaveData(save_ptree, root);
//    Kosmoport::SaveData(save_ptree, root);
}

void Kosmoport::Load(const boost::property_tree::ptree& load_ptree)
{
//    Base::LoadData(load_ptree);
//    Land::LoadData(load_ptree);
//    Kosmoport::LoadData(load_ptree);
}

void Kosmoport::Resolve()
{
//    Base::ResolveData();
//    Land::ResolveData();
//    Kosmoport::ResolveData();
}
