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

#include "MacroScenarioStarSystemLiberation.hpp"
#include "../../../common/constants.hpp"
#include "../../../common/Logger.hpp"
#include "../../../common/myStr.hpp"
#include "../../../world/starsystem.hpp"

MacroScenarioStarSystemLiberation::MacroScenarioStarSystemLiberation() 
{
	type_id = MACROSCENARIO::STARSYSTEMLIBERATION_ID;
}

/*virtual*/
MacroScenarioStarSystemLiberation::~MacroScenarioStarSystemLiberation() 
{}

/*virtual*/
void MacroScenarioStarSystemLiberation::Enter(Npc* npc) const
{	
	Logger::Instance().Log("npc_id=" + int2str(npc->GetId()) + ", enter MacroScenarioStarSystemLiberation");
}

/*virtual*/
void MacroScenarioStarSystemLiberation::UpdateInStatic(Npc* npc) const
{
	if (npc->GetStarSystem()->GetId() != npc->GetStateMachine()->GetMacroTaskManager()->GetMacroTask()->GetTarget()->GetId() )
	{
		if (npc->GetStateMachine()->GetMicroTaskManager()->GetMicroTask()->GetScenarioTypeId() != MICROSCENARIO::JUMP_ID)
		{
			MicroTask* microtask = new MicroTask(MICROSCENARIO::JUMP_ID, npc->GetStateMachine()->GetMacroTaskManager()->GetMacroTask()->GetTarget()->GetStarSystem());
			npc->GetStateMachine()->SetCurrentMicroTask(microtask);
		}
	}
	else
	{
		if (npc->GetStateMachine()->GetMacroTaskManager()->GetMacroTask()->GetTarget()->GetStarSystem()->GetCaptured() == true)
		{
			if (npc->GetStateMachine()->GetMicroTaskManager()->GetMicroTask()->GetScenarioTypeId() != MICROSCENARIO::DESTROY_ID)
			{
				Vehicle* target_vehicle = npc->GetStarSystem()->GetRandomVehicle(&RaceInformationCollector.RACES_EVIL_vec);
				if (target_vehicle != NULL)
				{
					MicroTask* microtask = new MicroTask(MICROSCENARIO::DESTROY_ID, target_vehicle);
					npc->GetStateMachine()->SetCurrentMicroTask(microtask);
				}
				else
				{
					//MicroTask* microtask = new MicroTask(target_vehicle, MICROSCENARIO::EXPLORE_ID);
					//npc->GetStateMachine()->SetCurrentMicroTask(microtask);
				}
			}
		}
		else
		{
			npc->GetStateMachine()->GetMacroTaskManager()->GetMacroTask()->SetResult(SUCCESS_ID);
			return;
		}
	}        
}

/*virtual*/
void MacroScenarioStarSystemLiberation::Exit(Npc* npc) const
{
	Logger::Instance().Log("npc_id=" + int2str(npc->GetId()) + ", exit MacroScenarioStarSystemLiberation");
}

/*virtual*/
std::string MacroScenarioStarSystemLiberation::GetDescription(Npc* npc) const
{
	return "MacroScenarioStarSystemLiberation: ss_id = " + int2str(npc->GetStateMachine()->GetMacroTaskManager()->GetMacroTask()->GetTarget()->GetId());
}
