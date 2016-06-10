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
#include "../../../spaceobjects/Vehicle.hpp"

MicroScenarioExploration::MicroScenarioExploration()
{
    type_id = type::AISCENARIO::MICRO_EXPLORATION_ID;
}

/* virtual */
MicroScenarioExploration::~MicroScenarioExploration()
{}
    
/* virtual */
void MicroScenarioExploration::Enter(Npc* npc) const
{    
    LOG("npc_id=" + std::to_string(npc->id()) + " ENTER MicroScenarioExploration");
}

/* virtual */
void MicroScenarioExploration::UpdateInStaticInSpace(Npc* npc) const
{
    if (npc->GetVehicle()->driveComplex().PathExists() == false)
    {
        glm::vec3 target_pos = meti::getRandXYVec3f(100, 1500, npc->GetVehicle()->center().z);
        npc->GetVehicle()->driveComplex().SetStaticTargetCoords(target_pos);
    }
}

/* virtual */
void MicroScenarioExploration::UpdateInDynamicInSpace(Npc* npc) const
{}

/* virtual */
void MicroScenarioExploration::Exit(Npc* npc) const
{
    LOG("npc_id=" + std::to_string(npc->id()) + " EXIT MicroScenarioExploration");
}

/* virtual */
std::string MicroScenarioExploration::GetDescription(Npc* npc) const
{
    return "MicroScenarioExploration";
}
