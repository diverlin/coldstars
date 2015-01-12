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

#include "BaseLand.hpp"
#include "../world/EntityManager.hpp"
#include "../common/constants.hpp"
#include "../spaceobjects/Planet.hpp"
#include "../spaceobjects/SpaceStation.hpp"
#include "../spaceobjects/BaseSpaceEntity.hpp"

BaseLand::BaseLand():owner(nullptr)
{}

/* virtual */
BaseLand::~BaseLand()
{}


void BaseLand::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    save_ptree.put(root+"data_unresolved_BaseLand.owner_id", owner->id());
}

void BaseLand::LoadData(const boost::property_tree::ptree& load_ptree)
{
    data_unresolved_BaseLand.owner_id = load_ptree.get<int>("data_unresolved_BaseLand.owner_id");
}

void BaseLand::ResolveData()
{
    Base* owner = EntityManager::Instance().GetEntityById(data_unresolved_BaseLand.owner_id);
    switch(owner->typeId())
    {
        case TYPE::ENTITY::PLANET_ID:
        {
            ((Planet*)owner)->BindLand(this);
            break;
        }

        case TYPE::ENTITY::VEHICLE_ID:
        {
            if (owner->subTypeId() == TYPE::ENTITY::SPACESTATION_ID)
            {
                ((SpaceStation*)owner)->BindLand(this);
            }
            break;
        }
    }
}
