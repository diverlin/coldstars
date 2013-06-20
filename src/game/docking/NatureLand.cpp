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

#include "NatureLand.hpp"
#include "../spaceobjects/Vehicle.hpp"
#include "../common/constants.hpp"
#include "../common/myStr.hpp"
#include "../common/rand.hpp"
#include "../resources/TextureManager.hpp"
#include "../resources/textureOb.hpp"

#include "../slots/ItemSlot.hpp"
#include "../garbage/EntityGarbage.hpp"

NatureLand::NatureLand(int id)
{
	data_id.id = id;
	data_id.type_id = ENTITY::NATURELAND_ID;
}

/* virtual */
NatureLand::~NatureLand()
{}

/* virtual */ 
void NatureLand::PutChildsToGarbage() const
{
    	for (unsigned int i=0; i<VEHICLE_vec.size(); i++)
    	{
    		EntityGarbage::Instance().Add(VEHICLE_vec[i]);
    	}

    	for (unsigned int i=0; i<item_slot_vec.size(); i++)
    	{
    		EntityGarbage::Instance().Add(item_slot_vec[i]);
    	}
    		
}

//// ******* TRANSITION ******* 
bool NatureLand::CanAcceptNewItem() const
{
	for (unsigned int i=0; i<item_slot_vec.size(); i++)
	{
		if (item_slot_vec[i]->GetItem() == nullptr)
		{
			return true;
		}
	}
	
	return false;
}
                
void NatureLand::AddItemSlot(ItemSlot* item_slot)
{
	item_slot->SetOwner(this);
	item_slot_vec.push_back(item_slot);
}

bool NatureLand::AddItem(BaseItem* item)
{
	for (unsigned int i=0; i<item_slot_vec.size(); i++)
	{
		if (item_slot_vec[i]->GetItem() == nullptr)
		{
			item_slot_vec[i]->InsertItem(item);
			item_slot_vec[i]->SetPosition(Vec2<float>(getRandInt(0, 100), getRandInt(0, 100)));
			
			return true;
		}
	}
	
	return false;
}


/* virtual */
bool NatureLand::AddVehicle(Vehicle* vehicle)
{
       	vehicle->SetPlaceTypeId(data_id.type_id); 
       	vehicle->SetLand(this);
       	
        VEHICLE_vec.push_back(vehicle);
        
        if (vehicle->GetStarSystem() == nullptr) // used if vehicle added directly after creation
        {
                vehicle->SetStarSystem(owner->GetStarSystem());
        }
        return true;
}

/*virtual */
bool NatureLand::RemoveVehicle(Vehicle* vehicle)
{       
        for (unsigned int i=0; i<VEHICLE_vec.size(); i++) 
        {
                if (VEHICLE_vec[i]->GetId() == vehicle->GetId())
                {
                        VEHICLE_vec.erase(VEHICLE_vec.begin() + i);
                        return true;
                }
        }
        
        return false;
}


/* virtual */
bool NatureLand::GetPermissionToLand() const
{
       	return true;
}

/* virtual */
void NatureLand::UpdateInStatic()
{}  

/*virtual*/
std::string NatureLand::GetDockVehicleStr() const
{
	std::string str;
        for (unsigned int i=0; i<VEHICLE_vec.size(); i++)
        {
               	str += "_" + int2str(VEHICLE_vec[i]->GetId());
        }

        return str;
}
              
/*virtual*/
void NatureLand::SaveData(boost::property_tree::ptree& save_ptree) const
{
	const std::string root = "natureland."+int2str(data_id.id)+".";
        SaveDataUniqueBase(save_ptree, root);
	SaveDataUniqueBaseLand(save_ptree, root);
	SaveDataUniqueNatureLand(save_ptree, root);
}

/*virtual*/
void NatureLand::LoadData(const boost::property_tree::ptree& load_ptree)
{
        LoadDataUniqueBase(load_ptree);
	LoadDataUniqueBaseLand(load_ptree);
	LoadDataUniqueNatureLand(load_ptree);
}

/*virtual*/
void NatureLand::ResolveData()
{
        ResolveDataUniqueBase();
	ResolveDataUniqueBaseLand();
	ResolveDataUniqueNatureLand();
}


void NatureLand::SaveDataUniqueNatureLand(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
	save_ptree.put(root+"data_unresolved_NatureLand.textureOb_background_path", textureOb_background->path);
}

void NatureLand::LoadDataUniqueNatureLand(const boost::property_tree::ptree& load_ptree)
{
	data_unresolved_NatureLand.textureOb_background_path = load_ptree.get<std::string>("data_unresolved_NatureLand.textureOb_background_path");
}

void NatureLand::ResolveDataUniqueNatureLand()
{
	textureOb_background = TextureManager::Instance().GetTextureObByPath(data_unresolved_NatureLand.textureOb_background_path);
}
