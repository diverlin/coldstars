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

#include "MicroScenarioGrab.hpp"
#include "../../../common/constants.hpp"
#include <ceti/Logger.hpp>
//#include <ceti/StringUtils.hpp>
#include "../../../spaceobjects/Vehicle.hpp"
#include "../../../ai/StateMachine.hpp"

#include "../../../item/equipment/Grapple.hpp"
#include "../../../slots/ItemSlot.hpp"
#include "../../../pilots/Npc.hpp"

#include "../../../world/starsystem.hpp"

MicroScenarioGrab::MicroScenarioGrab()
{
    type_id = type::AISCENARIO::MICRO_GRAB_ID;
}

/* virtual */
MicroScenarioGrab::~MicroScenarioGrab()
{}

/* virtual */        
void MicroScenarioGrab::Enter(Npc* npc) const
{
    npc->GetVehicle()->driveComplex().SetTarget(npc->GetStateMachine().GetMicroTaskManager().GetTarget(), NAVIGATOR_ACTION::COLLECTING_ID);
    
    LOG("npc_id="+std::to_string(npc->id())+" ENTER MicroScenarioGrab");
}

/* virtual */
bool MicroScenarioGrab::Validate(Npc* npc) const
{   
    // check equipment
    STATUS equipment_status = npc->GetVehicle()->CheckGrabStatus();
    
    if (equipment_status != STATUS::ITEM_OK)
    {
        return false;
    }
    
    // check target
    SpaceObject* target = npc->GetStateMachine().GetMicroTaskManager().GetTarget();     // shortcut
    STATUS target_status = npc->GetVehicle()->grappleSlot()->checkTargetPure(target);
        
    if ( (equipment_status == STATUS::ITEM_OK) and (target_status == STATUS::TARGET_OK) )
    {
        return true;
    }

    return false;
}

/* virtual */
void MicroScenarioGrab::UpdateInStaticInSpace(Npc* npc) const
{
    SpaceObject* target = npc->GetStateMachine().GetMicroTaskManager().GetTarget();
    if (npc->GetVehicle()->grappleSlot()->checkTarget(target) == STATUS::TARGET_OK)
    {
        npc->GetVehicle()->grappleSlot()->grappleEquipment()->AddTarget(target);
    }
}

/* virtual */
void MicroScenarioGrab::UpdateInDynamicInSpace(Npc* npc) const
{}

/* virtual */
void MicroScenarioGrab::Exit(Npc* npc) const
{
    LOG("npc_id="+std::to_string(npc->id())+" EXIT MicroScenarioGrab");
}

/* virtual */
std::string MicroScenarioGrab::GetDescription(Npc* npc) const 
{
    return "MicroScenarioGrab ob_id = " + std::to_string(npc->GetStateMachine().GetMicroTaskManager().GetTarget()->id());
}
