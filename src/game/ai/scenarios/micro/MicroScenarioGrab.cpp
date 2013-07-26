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
#include "../../../common/Logger.hpp"
#include "../../../common/myStr.hpp"
#include "../../../spaceobjects/Vehicle.hpp"
#include "../../../ai/StateMachine.hpp"

#include "../../../items/equipment/GrappleEquipment.hpp"
#include "../../../slots/ItemSlot.hpp"
#include "../../../pilots/Npc.hpp"

#include "../../../world/starsystem.hpp"

MicroScenarioGrab::MicroScenarioGrab()
{
	type_id = TYPE::AISCENARIO::MICRO_GRAB_ID;
}

/* virtual */
MicroScenarioGrab::~MicroScenarioGrab()
{}

/* virtual */		
void MicroScenarioGrab::Enter(Npc* npc) const
{
	npc->GetVehicle()->GetComplexDrive().SetTarget(npc->GetStateMachine().GetMicroTaskManager().GetTarget(), NAVIGATOR_ACTION::COLLECTING_ID);
	
        #if AISCENARIO_LOG_ENABLED == 1 
	Logger::Instance().Log("npc_id="+int2str(npc->GetId())+" ENTER MicroScenarioGrab"); 
	#endif   	 
}

/* virtual */
bool MicroScenarioGrab::Validate(Npc* npc) const
{
        // shortcut
        BaseSpaceEntity* target = npc->GetStateMachine().GetMicroTaskManager().GetTarget();
        
        // check if equipment is able to perform current task
        bool euipment_is_ok = false;
        if (npc->GetVehicle()->GetSlotGrapple()->GetItem() != nullptr)
        {
                if (npc->GetVehicle()->GetSlotGrapple()->GetGrappleEquipment()->GetFunctioning() == true)
                {
                        euipment_is_ok = true;
                }
        }
        
        // check if target is ok
        bool target_is_ok = npc->GetVehicle()->GetSlotGrapple()->CheckTargetPure(target);
        
	if ( (euipment_is_ok == true) and (target_is_ok == true) )
        {
                return true;
        }

        return false;
}

/* virtual */
void MicroScenarioGrab::UpdateInStaticInSpace(Npc* npc) const
{
	BaseSpaceEntity* target = npc->GetStateMachine().GetMicroTaskManager().GetTarget();
	if (npc->GetVehicle()->GetSlotGrapple()->CheckTarget(target) == true)
	{
       		npc->GetVehicle()->GetSlotGrapple()->GetGrappleEquipment()->AddTarget(target);
       	}
}

/* virtual */
void MicroScenarioGrab::UpdateInDynamicInSpace(Npc* npc) const
{}

/* virtual */
void MicroScenarioGrab::Exit(Npc* npc) const
{
        #if AISCENARIO_LOG_ENABLED == 1 
	Logger::Instance().Log("npc_id="+int2str(npc->GetId())+" EXIT MicroScenarioGrab"); 
	#endif    
}

/* virtual */
std::string MicroScenarioGrab::GetDescription(Npc* npc) const 
{
	return "MicroScenarioGrab ob_id = " + int2str(npc->GetStateMachine().GetMicroTaskManager().GetTarget()->GetId());
}
