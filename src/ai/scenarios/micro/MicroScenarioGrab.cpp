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

MicroScenarioGrab::MicroScenarioGrab()
{
	type_id = MICROSCENARIO::GRAB_ID;
}

/* virtual */
MicroScenarioGrab::~MicroScenarioGrab()
{}

/* virtual */		
void MicroScenarioGrab::Enter(Npc* npc) const
{
	npc->GetVehicle()->GetDriveComplex().SetTarget(npc->GetStateMachine().GetMicroTaskManager().GetTarget(), NAVIGATOR_ACTION::COLLECTING_ID);
	
        #if AISCENARIO_LOG_ENABLED == 1 
	Logger::Instance().Log("npc_id="+int2str(npc->GetId())+" ENTER MicroScenarioGrab"); 
	#endif   	 
}

/* virtual */
bool MicroScenarioGrab::Validate(Npc* npc) const
{
	if (npc->GetStateMachine().GetMicroTaskManager().GetTarget()->GetPlaceTypeId() == ENTITY::PLACE_SPACE_ID)
	{
		return true;
	}
	
	return false;
}

/* virtual */
void MicroScenarioGrab::UpdateInStaticInSpace(Npc* npc) const
{
	BaseSpaceEntity* target = npc->GetStateMachine().GetMicroTaskManager().GetTarget();
	if (npc->GetVehicle()->GetGrappleSlot()->CheckTarget(target) == true)
	{
       		npc->GetVehicle()->GetGrappleSlot()->GetGrappleEquipment()->AddTarget(target);
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
