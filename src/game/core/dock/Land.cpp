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

#include "Land.hpp"

#include <common/Global.hpp>
#include <managers/EntityManager.hpp>

#include "../common/constants.hpp"
#include "../spaceobjects/Planet.hpp"
#include "../spaceobjects/SpaceStation.hpp"
#include "../spaceobjects/SpaceObject.hpp"

Land::Land():owner(nullptr)
{}

/* virtual */
Land::~Land()
{}


void Land::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    save_ptree.put(root+"data_unresolved_Land.owner_id", owner->id());
}

void Land::LoadData(const boost::property_tree::ptree& load_ptree)
{
    data_unresolved_Land.owner_id = load_ptree.get<int>("data_unresolved_Land.owner_id");
}

void Land::ResolveData()
{
//    Base* owner = global::get().entityManager().get(data_unresolved_Land.owner_id);
//    switch(owner->type())
//    {
//        case type::entity::PLANET_ID:
//        {
//            ((control::Planet*)owner)->BindLand(this);
//            break;
//        }

//        case type::entity::VEHICLE_ID:
//        {
//            if (owner->subtype() == type::entity::SPACESTATION_ID)
//            {
//                ((SpaceStation*)owner)->BindLand(this);
//            }
//            break;
//        }
//    }
}
