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

#include "MicroScenarioLaunching.hpp"
#include "../../../common/constants.hpp"
#include <ceti/Logger.hpp>
//#include <ceti/StringUtils.hpp>
#include "../../../spaceobjects/Vehicle.hpp"
#include "../../../pilots/Npc.hpp"

MicroScenarioLaunching::MicroScenarioLaunching()
{
    setTypeId(type::AISCENARIO::MICRO_LAUNCHING_ID);
}

/* virtual */
MicroScenarioLaunching::~MicroScenarioLaunching()
{}
        
/* virtual */
void MicroScenarioLaunching::enter(Npc* npc) const
{
    LOG("npc_id=" + std::to_string(npc->id()) + " ENTER MicroScenarioLaunching");
}

/* virtual */
bool MicroScenarioLaunching::Validate(Npc* npc) const
{
    if (npc->vehicle()->place() != type::place::KOSMOS)
    {
        return true;
    }

    return false;
}

/* virtual */        
void MicroScenarioLaunching::UpdateInStaticInSpace(Npc* npc) const
{}

/* virtual */
void MicroScenarioLaunching::UpdateInDynamicInSpace(Npc* npc) const
{}

/* virtual */
void MicroScenarioLaunching::UpdateInStaticInDock(Npc* npc) const
{
    //npc->GetVehicle()->LaunchingEvent();
    //npc->GetVehicle()->SetSpecialActionId(SPECIAL_ACTION::INITIATE_LAUNCHING_ID);
}

/* virtual */
void MicroScenarioLaunching::exit(Npc* npc) const 
{
    LOG("npc_id=" + std::to_string(npc->id()) + " EXIT MicroScenarioLaunching");
}

/* virtual */
std::string MicroScenarioLaunching::GetDescription(Npc* _npc) const
{
    return "MicroScenarioLaunching";
}
