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

#include "BaseSlot.hpp"
#include "../common/constants.hpp"
//#include <ceti/StringUtils.hpp>
#include <ceti/Logger.hpp>

#include <common/Global.hpp>
#include <core/manager/EntityManager.hpp>

#include <core/spaceobject/Vehicle.hpp>


namespace slot {

control::Vehicle*
BaseSlot::vehicleOwner() const {
    control::Vehicle* vehicle = static_cast<control::Vehicle*>(m_owner);
    assert(vehicle);
    return vehicle;
}

} // namespace slot

//BaseSlot::BaseSlot()
//:
//m_selected(false),
//m_textureOb(nullptr),
//m_owner(nullptr)
//{}

///* virtual */
//BaseSlot::~BaseSlot()
//{
////    LOG("___::~BaseSlot("+std::to_string(id())+")");
//}
                
//void BaseSlot::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
//{
//    assert(false);
////    LOG(" BaseSlot("+std::to_string(id())+")::SaveData");
        
////    if (m_owner) { save_ptree.put(root+"unresolved.owner_id", m_owner->id()); }
////    else       { save_ptree.put(root+"unresolved.owner_id", NONE); }
    
////    save_ptree.put(root+"position.x", m_position.x);
////    save_ptree.put(root+"position.y", m_position.y);
//}

//void BaseSlot::LoadData(const boost::property_tree::ptree& load_ptree)
//{
//    assert(false);
////    LOG(" BaseSlot("+std::to_string(id())+")::LoadData");
       
////    unresolved_BaseSlot.owner_id = load_ptree.get<int>("unresolved.owner_id");
////    m_position = glm::vec2(load_ptree.get<int>("position.x"), load_ptree.get<int>("position.y"));

//}

//void BaseSlot::ResolveData()
//{
//    assert(false);
////    LOG(" BaseSlot("+std::to_string(id())+")::ResolveData");
    
////    if (unresolved_BaseSlot.owner_id != NONE) {
////        //m_owner = EntityManager::get().getEntity(unresolved_BaseSlot.owner_id);
////    }
//}


