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


#include "starsystem.hpp"
#include <world/Sector.hpp>

#include <meti/VectorUtils.hpp>

#include <core/builder/spaceobject/WormHoleBuilder.hpp>
#include <core/builder/spaceobject/ShipBuilder.hpp>
#include <core/builder/pilot/NpcBuilder.hpp>

#include <ceti/Logger.hpp>
#include <ceti/Collision.hpp>
#include <math/rand.hpp>
//#include <ceti/StringUtils.hpp>

#include <common/Global.hpp>
#include <core/manager/EntityManager.hpp>
#include <common/Config.hpp>

//#include <jeti/Render.hpp>

#include <core/slot/ItemSlot.hpp>
#include <core/item/other/Bomb.hpp>

#include <core/spaceobject/ALL>

//#include <client/pilot/Player.hpp>
#include <core/pilot/Npc.hpp>

//#include <client/effect/DistantNebulaEffect.hpp>
//#include <client/effect/DistantStarEffect.hpp>
//#include <client/effect/lazerTrace.hpp>
//#include <jeti/particlesystem/ExplosionEffect.hpp>

//#include <client/text/VerticalFlowText.hpp>

//#include <client/gui/GuiManager.hpp>
//#include <client/gui/GuiRadar.hpp>

#include <descriptor/RaceDescriptors.hpp>
#include <core/manager/DescriptorManager.hpp>

//#include <jeti/Mesh.hpp>
#include <meti/RandUtils.hpp>

//int Starsystem::m_counter = 0;


namespace model {

StarSystemModel::StarSystemModel(int_t descriptor_id, int_t ob_id)
{
    setId(ob_id);
    setDescriptor(descriptor_id);

    m_status = int(ENTITY::STARSYSTEM::CONDITION::SAFE);
}

StarSystemModel::StarSystemModel(const std::string& data)
{
    MACRO_READ_SERIALIZED_DATA
}

std::string
StarSystemModel::data() const
{
    MACRO_SAVE_SERIALIZED_DATA
}

bool StarSystemModel::operator==(const StarSystemModel& rhs) const
{
    return (data() == rhs.data());
}

bool StarSystemModel::operator!=(const StarSystemModel& rhs) const
{
    return !(*this == rhs);
}

} // namespace model

