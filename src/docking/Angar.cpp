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

#include "Angar.hpp"
#include "Kosmoport.hpp"
#include "../common/EntityManager.hpp"
#include "../common/myStr.hpp"
#include "../common/Logger.hpp"
#include "../spaceobjects/Vehicle.hpp"
#include "../slots/VehicleSlot.hpp" 
#include "../slots/ItemSlot.hpp" 
#include "../pilots/Npc.hpp"

#include "../garbage/EntityGarbage.hpp"
#include "../items/BaseItem.hpp"

Angar::Angar(int id)
{
	data_id.id = id;
	data_id.type_id = ENTITY::ANGAR_ID;
	
	price_fuel = PRICE_FUEL;
}

Angar::~Angar()
{        
        #if CREATEDESTROY_LOG_ENABLED == 1
	Logger::Instance().Log("___::~Angar(), id="+int2str(GetId()));
	#endif
}

void Angar::PutChildsToGarbage() const
{
	for(unsigned int i=0; i<vehicle_total_slot_vec.size(); i++)
	{
		vehicle_total_slot_vec[i]->PutChildsToGarbage();
		EntityGarbage::Instance().Add(vehicle_total_slot_vec[i]);
	}

	for(unsigned int i=0; i<item_slot_vec.size(); i++)
	{
		item_slot_vec[i]->PutChildsToGarbage();
		EntityGarbage::Instance().Add(item_slot_vec[i]);
	}
}
       
void Angar::AddVehicleSlot(VehicleSlot* vehicle_slot) 
{ 
	vehicle_slot->SetOwner(this);
        
        if (vehicle_slot->GetSubTypeId() == ENTITY::VEHICLE_MILITARY_SLOT_ID)
        {
                vehicle_military_slot_vec.push_back(vehicle_slot);
        }
        
        if (vehicle_slot->GetSubTypeId() == ENTITY::VEHICLE_VISITORS_SLOT_ID)
	{
                vehicle_visitors_slot_vec.push_back(vehicle_slot);     
        }
        
        vehicle_total_slot_vec.push_back(vehicle_slot); 
};

   
void Angar::AddItemSlot(ItemSlot* item_slot)
{
        item_slot->SetOwner(this);
        item_slot_vec.push_back(item_slot); 
}
  
bool Angar::RepairItem(Npc* npc, BaseItem* item) const
{
	int price = item->GetPrice() * REPAIR_ITEM_PRICE_RATE;
	if (npc->WithdrawCredits(price) == true)
	{
		item->RepairEvent();
	}
}
                         
void Angar::Ai() const
{
        for (unsigned int i=0; i<vehicle_visitors_slot_vec.size(); i++)
        {
                if (vehicle_visitors_slot_vec[i]->GetVehicle() != NULL)
                {
                	if (vehicle_visitors_slot_vec[i]->GetVehicle()->GetOwnerNpc() != NULL)
                	{
                        	vehicle_visitors_slot_vec[i]->GetVehicle()->GetOwnerNpc()->MindInKosmoport();
                	}
               	}
        }
}
                                                
int Angar::GetFreeVehicleSlotTotalNum() const
{
        int sum_free = 0;
        for (unsigned int i=0; i<vehicle_visitors_slot_vec.size(); i++)
        {
                if (vehicle_visitors_slot_vec[i]->GetVehicle() == NULL)
                {
                        sum_free++;
                }
        }
        return sum_free; 
}

bool Angar::AddVehicle(Vehicle* vehicle)
{
        if (vehicle->GetSubSubTypeId() == ENTITY::WARRIOR_ID)
        {        
                for (unsigned int i=0; i<vehicle_military_slot_vec.size(); i++)
                {
                        if (vehicle_military_slot_vec[i]->GetVehicle() == NULL)
                        {
                                vehicle_military_slot_vec[i]->InsertVehicle(vehicle);
                                return true;
                        }
                }
        }  
        else
        {        
                for (unsigned int i=0; i<vehicle_visitors_slot_vec.size(); i++)
                {
                        if (vehicle_visitors_slot_vec[i]->GetVehicle() == NULL)
                        {
                                vehicle_visitors_slot_vec[i]->InsertVehicle(vehicle);
                                return true;
                        }
                }
        }  
        
        return false;        
}

std::string Angar::GetDockVehicleStr() const
{
	std::string str;
        for (unsigned int i=0; i<vehicle_military_slot_vec.size(); i++)
        {
                if (vehicle_military_slot_vec[i]->GetVehicle() != NULL)
                {
                	str += "_m" + int2str(vehicle_military_slot_vec[i]->GetVehicle()->GetId());
                }
        }
        
        for (unsigned int i=0; i<vehicle_visitors_slot_vec.size(); i++)
        {
                if (vehicle_visitors_slot_vec[i]->GetVehicle() != NULL)
                {
                	str += "_v" + int2str(vehicle_visitors_slot_vec[i]->GetVehicle()->GetId());
                }
        }
        
        return str;
}
                

void Angar::SaveDataUniqueAngar(boost::property_tree::ptree& save_ptree, const std::string& root) const
{}

void Angar::LoadDataUniqueAngar(const boost::property_tree::ptree& load_ptree)
{}

void Angar::ResolveDataUniqueAngar()
{
	((Kosmoport*)EntityManager::Instance().GetEntityById(data_unresolved_Room.owner_kosmoport_id))->BindAngar(this); 
}


void Angar::SaveData(boost::property_tree::ptree& save_ptree) const
{
	std::string root = "angar." + int2str(GetId())+".";
	SaveDataUniqueBase(save_ptree, root);
	SaveDataUniqueRoom(save_ptree, root);
	SaveDataUniqueAngar(save_ptree, root);
}

void Angar::LoadData(const boost::property_tree::ptree& load_ptree)
{
	LoadDataUniqueBase(load_ptree);
	LoadDataUniqueRoom(load_ptree);
	LoadDataUniqueAngar(load_ptree);
}

void Angar::ResolveData()
{
	ResolveDataUniqueBase();
	ResolveDataUniqueRoom();
	ResolveDataUniqueAngar();
}

