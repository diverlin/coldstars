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

#include "MicroScenarioExploration.hpp"
#include "../../../common/constants.hpp"
#include <ceti/Logger.hpp>
//#include <ceti/StringUtils.hpp>
#include <meti/RandUtils.hpp>
#include <core/spaceobject/Vehicle.hpp>

MicroScenarioExploration::MicroScenarioExploration()
{
    setTypeId(ai::type::MICRO_EXPLORATION);
}

/* virtual */
MicroScenarioExploration::~MicroScenarioExploration()
{}
    
/* virtual */
void MicroScenarioExploration::enter(Npc* npc) const
{    
    assert(false);
    //LOG("npc_id=" + std::to_string(npc->id()) + " ENTER MicroScenarioExploration");
}

/* virtual */
void MicroScenarioExploration::UpdateInStaticInSpace(Npc* npc) const
{
    assert(false);
    //    if (npc->vehicle()->driveComplex().PathExists() == false)
//    {
//        glm::vec3 target_pos = meti::getRandXYVec3f(100, 1500, npc->vehicle()->position().z);
//        npc->vehicle()->driveComplex().SetStaticTargetCoords(target_pos);
//    }
}

/* virtual */
void MicroScenarioExploration::UpdateInDynamicInSpace(Npc* npc) const
{}

/* virtual */
void MicroScenarioExploration::exit(Npc* npc) const
{
    assert(false);
    //LOG("npc_id=" + std::to_string(npc->id()) + " EXIT MicroScenarioExploration");
}

/* virtual */
std::string MicroScenarioExploration::GetDescription(Npc* npc) const
{
    return "MicroScenarioExploration";
}
