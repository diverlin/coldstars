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

#include "MicroScenarioJump.hpp"
#include "../../../common/constants.hpp"
#include "../../../common/Logger.hpp"
#include "../../../common/myStr.hpp"
#include "../../../spaceobjects/Vehicle.hpp"

#include "../../../world/starsystem.hpp"
#include "../../../ai/StateMachine.hpp"
#include "../../../pilots/Npc.hpp"

MicroScenarioJump::MicroScenarioJump()
{
	type_id = MICROSCENARIO::JUMP_ID;
}

/* virtual */
MicroScenarioJump::~MicroScenarioJump()
{}
		
/* virtual */
void MicroScenarioJump::Enter(Npc* npc) const
{	
	npc->GetVehicle()->GetDriveComplex().SetTarget(npc->GetStateMachine()->GetMicroTaskManager()->GetMicroTask()->GetTarget()->GetStarSystem(), NAVIGATOR_ACTION::KEEP_CLOSE_ID);
        
        #if AISCENARIO_LOG_ENABLED == 1 
	Logger::Instance().Log("npc_id="+int2str(npc->GetId())+" ENTER MicroScenarioJump"); 
	#endif    
}

/* virtual */
bool MicroScenarioJump::Validation(Npc* npc) const
{
	if (npc->GetVehicle()->GetStarSystem()->GetId() != npc->GetStateMachine()->GetMicroTaskManager()->GetMicroTask()->GetTarget()->GetStarSystem()->GetId())
	{
		return true;
	}
	
	return false;
}

/* virtual */
void MicroScenarioJump::UpdateInStaticInSpace(Npc* npc) const
{
	// check if still able to jump
}

/* virtual */
void MicroScenarioJump::UpdateInDynamicInSpace(Npc* npc) const
{
     	if (npc->GetVehicle()->GetDriveComplex().CheckTargetEchievement() == true)
     	{
     		if (npc->GetVehicle()->GetSpecialActionId() != SPECIAL_ACTION::INITIATE_JUMPIN_ID)
     		{
     			npc->GetVehicle()->SetSpecialActionId(SPECIAL_ACTION::INITIATE_JUMPIN_ID);
     		}
     	}
}

/* virtual */
void MicroScenarioJump::Exit(Npc* npc) const
{
        #if AISCENARIO_LOG_ENABLED == 1 
	Logger::Instance().Log("npc_id="+int2str(npc->GetId())+" EXIT MicroScenarioJump"); 
	#endif   
}

/* virtual */
std::string MicroScenarioJump::GetDescription(Npc* npc) const
{
	return "JUMP to ss_id = " + int2str( npc->GetStateMachine()->GetMicroTaskManager()->GetMicroTask()->GetTarget()->GetId());
}
