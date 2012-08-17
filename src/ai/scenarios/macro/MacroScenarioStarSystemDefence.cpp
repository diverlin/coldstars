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

#include "MacroScenarioStarSystemDefence.hpp"
#include "../../../pilots/Npc.hpp"
#include "../../../spaceobjects/Vehicle.hpp"
#include "../../../common/constants.hpp"
#include "../../../common/Logger.hpp"
#include "../../../common/myStr.hpp"
#include "../../MicroTask.hpp"
#include "../../../world/starsystem.hpp"

MacroScenarioStarSystemDefence::MacroScenarioStarSystemDefence() 
{
	type_id = MACROSCENARIO::STARSYSTEMDEFENCE_ID;
}

/*virtual*/
MacroScenarioStarSystemDefence::~MacroScenarioStarSystemDefence() 
{}

/*virtual*/
void MacroScenarioStarSystemDefence::Enter(Npc* npc) const
{	
	Logger::Instance().Log("npc_id=" + int2str(npc->GetId()) + ", enter MacroScenarioStarSystemDefence");
}

/*virtual*/
void MacroScenarioStarSystemDefence::UpdateInStatic(Npc* npc) const
{
	if (npc->GetStateMachine()->GetMicroTaskManager()->GetMicroTask()->GetScenarioTypeId() != MICROSCENARIO::JUMP_ID)
	{
		if (npc->GetStateMachine()->GetMicroTaskManager()->GetMicroTask()->GetScenarioTypeId() != MICROSCENARIO::JUMP_ID)
		{
			MicroTask* microtask = new MicroTask(MICROSCENARIO::JUMP_ID, npc->GetStateMachine()->GetMacroTaskManager()->GetMacroTask()->GetTarget()->GetStarSystem());
			npc->GetStateMachine()->SetCurrentMicroTask(microtask);
		}
	}
	else
	{
		if (npc->GetStateMachine()->GetMicroTaskManager()->GetMicroTask()->GetScenarioTypeId() != MICROSCENARIO::DESTROY_ID)
		{       	
            		Vehicle* target_vehicle = npc->GetObservation().GetClosestVehicle(&RaceInformationCollector.RACES_GOOD_vec);
            		if (target_vehicle != NULL)
            		{
            			MicroTask* microtask = new MicroTask(MICROSCENARIO::DESTROY_ID, target_vehicle);
				npc->GetStateMachine()->SetCurrentMicroTask(microtask);
			}
			else
			{
				//MicroTask* microtask = new MicroTask(target_vehicle, MICROSCENARIO::EXPLORE_ID);
				//npc->GetStateMachine()->SetCurrentMicroTask(microtask);
				//explore
			}
		}
	}
}

/*virtual*/
void MacroScenarioStarSystemDefence::Exit(Npc* npc) const
{
	Logger::Instance().Log("npc_id=" + int2str(npc->GetId()) + ", exit MacroScenarioStarSystemDefence");
}


/*virtual*/
std::string MacroScenarioStarSystemDefence::GetDescription(Npc* npc) const
{
	return "MacroScenarioStarSystemDefence: ss_id = " + int2str(npc->GetStateMachine()->GetMacroTaskManager()->GetMacroTask()->GetTarget()->GetId());
}
