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
#include <core/spaceobject/Vehicle.hpp>
#include "../common/constants.hpp"

#include <meti/RandUtils.hpp>

#include <core/slot/ItemSlot.hpp>

#include <common/Global.hpp>
#include <core/manager/EntityManager.hpp>

#include <core/descriptor/dock/NatureLand.hpp>
#include <core/model/dock/NatureLand.hpp>

namespace control {

NatureLand::NatureLand(model::NatureLand* model, descriptor::NatureLand* descr)
    :
      Land(model, descr)
    , m_model_natureland(model)
    , m_descriptor_natureland(descr)

{}

/* virtual */
NatureLand::~NatureLand()
{}

/* virtual */ 
void NatureLand::putChildrenToGarbage() const
{
    assert(false);
//    for (unsigned int i=0; i<VEHICLE_vec.size(); i++) {
//       EntityManager::get().addToGarbage(VEHICLE_vec[i]);
//    }

//    for (unsigned int i=0; i<item_slot_vec.size(); i++) {
//       EntityManager::get().addToGarbage(item_slot_vec[i]);
//    }
}

//// ******* TRANSITION ******* 
bool NatureLand::canAcceptNewItem() const
{
    for (slot::Item* slot: m_itemslots) {
        if (!slot->item()) {
            return true;
        }
    }
    
    return false;
}
                
void NatureLand::add(slot::Item* item_slot)
{
    assert(false);
//    item_slot->setOwner(this);
//    item_slot_vec.push_back(item_slot);
}

bool NatureLand::add(control::Item* item)
{
    for (slot::Item* slot: m_itemslots) {
        if (!slot->item()) {
            slot->insert(item);
            slot->setPosition(glm::vec2(meti::getRandInt(100), meti::getRandInt(100)));
            return true;
        }
    }    
    return false;
}


/* virtual */
bool NatureLand::add(Vehicle* vehicle)
{
    assert(false);
//    vehicle->setPlaceTypeId(type::place::LAND);
//    vehicle->setLand(this);
    
//    VEHICLE_vec.push_back(vehicle);
    
//    // used if vehicle added directly after creation
//    if (!vehicle->starsystem()) {
//        // TODO
//        //vehicle->setStarSystem(m_owner->starsystem());
//    }
    return true;
}

/*virtual */
bool NatureLand::remove(Vehicle* vehicle)
{       
    for (unsigned int i=0; i<m_vehicles.size(); i++)
    {
        assert(false);
//        if (VEHICLE_vec[i]->id() == vehicle->id())
//        {
//            VEHICLE_vec.erase(VEHICLE_vec.begin() + i);
//            return true;
//        }
    }

    return false;
}


/* virtual */
bool NatureLand::isAllowedToLand() const
{
           return true;
}

/* virtual */
void NatureLand::updateInStatic()
{}  

/*virtual*/
std::string NatureLand::vehiclesStr() const
{
    std::string str;
    for (unsigned int i=0; i<m_vehicles.size(); i++)
    {
        assert(false);
        //str += "_" + std::to_string(VEHICLE_vec[i]->id());
    }

    return str;
}

///* virtual override final */
//void NatureLand::Save(boost::property_tree::ptree& save_ptree) const
//{
////    const std::string root = "natureland."+std::to_string(id())+".";
////    Base::SaveData(save_ptree, root);
////    Land::SaveData(save_ptree, root);
////    NatureLand::SaveData(save_ptree, root);
//}

///* virtual override final */
//void NatureLand::Load(const boost::property_tree::ptree& load_ptree)
//{
////    Base::LoadData(load_ptree);
////    Land::LoadData(load_ptree);
////    NatureLand::LoadData(load_ptree);
//}

///* virtual override final */
//void NatureLand::Resolve()
//{
////    Base::ResolveData();
////    Land::ResolveData();
////    NatureLand::ResolveData();
//}


//void NatureLand::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
//{
//    //save_ptree.put(root+"data_unresolved_NatureLand.textureOb_background_path", textureOb_background->GetMaterial().texture_path);
//}

//void NatureLand::LoadData(const boost::property_tree::ptree& load_ptree)
//{
//    data_unresolved_NatureLand.textureOb_background_path = load_ptree.get<std::string>("data_unresolved_NatureLand.textureOb_background_path");
//}

//void NatureLand::ResolveData()
//{
//    //textureOb_background = TextureCollector::Instance().GetTextureObByPath(data_unresolved_NatureLand.textureOb_background_path);
//}

} // namespace control
