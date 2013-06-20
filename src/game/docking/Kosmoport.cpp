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
#include "../spaceobjects/Vehicle.hpp"
#include "../common/myStr.hpp"
#include "../common/constants.hpp"

#include "../docking/Angar.hpp"
#include "../docking/Store.hpp"
#include "../docking/Shop.hpp"
#include "../docking/Goverment.hpp"

#include "../garbage/EntityGarbage.hpp"
#include "../slots/VehicleSlot.hpp"

Kosmoport::Kosmoport(int id) 
{
	data_id.id = id;
	data_id.type_id = ENTITY::KOSMOPORT_ID;
	race_id = RACE::R0_ID; //wrong
	
	angar     = nullptr;
        store     = nullptr;
        shop      = nullptr;
        goverment = nullptr;
}

/* virtual */
Kosmoport::~Kosmoport()
{}

/* virtual */
void Kosmoport::PutChildsToGarbage() const
{
	EntityGarbage::Instance().Add(angar);
	EntityGarbage::Instance().Add(store);
	EntityGarbage::Instance().Add(shop);
	EntityGarbage::Instance().Add(goverment);
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
        vehicle->SetPlaceTypeId(data_id.type_id); 
        angar->AddVehicle(vehicle);  
        
        vehicle->SetLand(this);        
        if (vehicle->GetStarSystem() == nullptr) // used if vehicle added directly after creation
        {
                vehicle->SetStarSystem(owner->GetStarSystem());
        }
              
        return true;
}

//* virtual */
bool Kosmoport::RemoveVehicle(Vehicle* vehicle)
{        
    	vehicle->GetParentVehicleSlot()->Release();
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


void Kosmoport::SaveDataUniqueKosmoport(boost::property_tree::ptree& save_ptree, const std::string& root) const
{}

void Kosmoport::LoadDataUniqueKosmoport(const boost::property_tree::ptree& load_ptree)
{}

void Kosmoport::ResolveDataUniqueKosmoport()
{}


void Kosmoport::SaveData(boost::property_tree::ptree& save_ptree) const
{
	std::string root = "kosmoport." + int2str(GetId())+".";
	SaveDataUniqueBase(save_ptree, root);
	SaveDataUniqueBaseLand(save_ptree, root);
	SaveDataUniqueKosmoport(save_ptree, root);
}

void Kosmoport::LoadData(const boost::property_tree::ptree& load_ptree)
{
	LoadDataUniqueBase(load_ptree);
	LoadDataUniqueBaseLand(load_ptree);
	LoadDataUniqueKosmoport(load_ptree);
}

void Kosmoport::ResolveData()
{
	ResolveDataUniqueBase();
	ResolveDataUniqueBaseLand();
	ResolveDataUniqueKosmoport();
}
