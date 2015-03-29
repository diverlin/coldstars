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

#include <meti/RandUtils.hpp>

#include "../slots/ItemSlot.hpp"

#include <common/Global.hpp>
#include <managers/EntitiesManager.hpp>

NatureLand::NatureLand(int id)
{
    setId(id);
    setTypeId(TYPE::ENTITY::NATURELAND_ID);
}

/* virtual */
NatureLand::~NatureLand()
{}

/* virtual */ 
void NatureLand::putChildrenToGarbage() const
{
    for (unsigned int i=0; i<VEHICLE_vec.size(); i++) {
        global::get().entitiesManager().AddToGarbage(VEHICLE_vec[i]);
    }

    for (unsigned int i=0; i<item_slot_vec.size(); i++) {
        global::get().entitiesManager().AddToGarbage(item_slot_vec[i]);
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
            item_slot_vec[i]->SetPosition(glm::vec2(meti::getRandInt(0, 100), meti::getRandInt(0, 100)));
            
            return true;
        }
    }
    
    return false;
}


/* virtual */
bool NatureLand::AddVehicle(Vehicle* vehicle)
{
    vehicle->setPlaceTypeId(TYPE::PLACE::NATURELAND_ID); 
    vehicle->SetLand(this);
    
    VEHICLE_vec.push_back(vehicle);
    
    if (vehicle->starsystem() == nullptr) // used if vehicle added directly after creation
    {
            vehicle->setStarSystem(owner->starsystem());
    }
    return true;
}

/*virtual */
bool NatureLand::RemoveVehicle(Vehicle* vehicle)
{       
        for (unsigned int i=0; i<VEHICLE_vec.size(); i++) 
        {
                if (VEHICLE_vec[i]->id() == vehicle->id())
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
                   str += "_" + std::to_string(VEHICLE_vec[i]->id());
        }

        return str;
}
              
/* virtual override final */
void NatureLand::Save(boost::property_tree::ptree& save_ptree) const
{
    const std::string root = "natureland."+std::to_string(id())+".";
    Base::SaveData(save_ptree, root);
    Land::SaveData(save_ptree, root);
    NatureLand::SaveData(save_ptree, root);
}

/* virtual override final */
void NatureLand::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
    Land::LoadData(load_ptree);
    NatureLand::LoadData(load_ptree);
}

/* virtual override final */
void NatureLand::Resolve()
{
    Base::ResolveData();
    Land::ResolveData();
    NatureLand::ResolveData();
}


void NatureLand::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    //save_ptree.put(root+"data_unresolved_NatureLand.textureOb_background_path", textureOb_background->GetMaterial().texture_path);
}

void NatureLand::LoadData(const boost::property_tree::ptree& load_ptree)
{
    data_unresolved_NatureLand.textureOb_background_path = load_ptree.get<std::string>("data_unresolved_NatureLand.textureOb_background_path");
}

void NatureLand::ResolveData()
{
    //textureOb_background = TextureCollector::Instance().GetTextureObByPath(data_unresolved_NatureLand.textureOb_background_path);
}