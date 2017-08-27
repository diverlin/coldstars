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

#include "Sector.hpp"
#include <core/world/starsystem.hpp>
#include <core/world/galaxy.hpp>
#include <core/manager/EntityManager.hpp>
#include <core/common/constants.hpp>
#include <core/common/Global.hpp>
#include <common/common.hpp>
#include <meti/RandUtils.hpp>
#include <core/pilot/Npc.hpp>

#include <core/struct/StarSystemsConditionData.hpp>

#include <core/model/world/starsystem.hpp>

#include <ceti/serialization/macro.hpp>


namespace model {

Sector::Sector(int_t descriptor_id)
{
    setDescriptor(descriptor_id);
}

Sector::Sector(const std::string& data)
{
    MACRO_READ_SERIALIZED_DATA
}

std::string
Sector::data() const
{
    MACRO_SAVE_SERIALIZED_DATA
}

bool Sector::operator==(const Sector& rhs) const {
    if (m_position != rhs.m_position) {
        return false;
    }

    bool result = isEqual(m_starsystems, rhs.m_starsystems);
    return result;
}

bool Sector::operator!=(const Sector& rhs) const {
    return !(*this == rhs);
}

} // namespace model

