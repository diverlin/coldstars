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

MicroScenarioJump::MicroScenarioJump()
{
	type_id = MICROSCENARIO::JUMP_ID;
}


MicroScenarioJump::~MicroScenarioJump()
{}
		
void MicroScenarioJump::Enter(Npc* npc) const
{	
	npc->GetVehicle()->GetDriveComplex()->SetTarget(npc->GetStateMachine()->GetMicroTaskManager()->GetMicroTask()->GetTarget()->GetStarSystem(), NAVIGATOR_ACTION::KEEP_CLOSE_ID);
	printf("npc_id = %i, is GOING to MicroScenarioJump from ss_id = %i to ss_id = %i\n", npc->GetId(), npc->GetStarSystem()->GetId(), npc->GetStateMachine()->GetMicroTaskManager()->GetMicroTask()->GetTarget()->GetId());
}

void MicroScenarioJump::UpdateInStaticInSpace(Npc* _npc) const
{
	// check if still able to jump
}

void MicroScenarioJump::UpdateInDynamicInSpace(Npc* npc) const
{
     	if (npc->GetVehicle()->GetDriveComplex()->CheckTargetEchievement() == true)
     	{
                npc->GetVehicle()->HyperJumpEvent();
     	        printf("npc id = %i, jumpEvent()\n", npc->GetId());
     	}
}

void MicroScenarioJump::Exit(Npc* npc) const
{
	printf("npc_id = %i, FINISH MicroScenarioJump from ss_id = %i to ss_id = %i\n", npc->GetId(), npc->GetStarSystem()->GetId(), npc->GetStateMachine()->GetMicroTaskManager()->GetMicroTask()->GetTarget()->GetId());
}


std::string MicroScenarioJump::GetDescription(Npc* npc) const
{
	return "JUMP to ss_id = " + int2str( npc->GetStateMachine()->GetMicroTaskManager()->GetMicroTask()->GetTarget()->GetId());
}
