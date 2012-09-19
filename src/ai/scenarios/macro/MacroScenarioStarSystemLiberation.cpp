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
#include "../../../ai/StateMachine.hpp"
#include "../../../ai/MicroTask.hpp"
#include "../../../spaceobjects/Vehicle.hpp"

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
	#if AISCENARIO_LOG_ENABLED == 1 
	Logger::Instance().Log("npc_id=" + int2str(npc->GetId()) + " ENTER MacroScenarioStarSystemLiberation");
	#endif
}

/*virtual*/
void MacroScenarioStarSystemLiberation::UpdateInStaticInSpace(Npc* npc) const
{
	StarSystem* target_starsystem = npc->GetStateMachine()->GetMacroTaskManager()->GetMacroTask()->GetTarget()->GetStarSystem();
	if (npc->GetStarSystem()->GetId() != target_starsystem->GetId())
	{
		if (npc->GetStateMachine()->GetMicroTaskManager()->GetMicroTask()->GetScenarioTypeId() != MICROSCENARIO::JUMP_ID)
		{
			MicroTask* microtask = new MicroTask(MICROSCENARIO::JUMP_ID, target_starsystem);
			npc->GetStateMachine()->SetCurrentMicroTask(microtask);
			
			return;
		}
	}
	else
	{
		if (target_starsystem->GetConditionId() != ENTITY::STARSYSTEM::CONDITION::SAFE_ID)
		{
			if (npc->GetStateMachine()->GetMicroTaskManager()->GetMicroTask()->GetScenarioTypeId() != MICROSCENARIO::DESTROY_ID)
			{
				Vehicle* target_vehicle = npc->GetObservation().GetRandVisibleVehicle(RaceInformationCollector::Instance().RACES_EVIL_vec);
				if (target_vehicle != NULL)
				{
					MicroTask* microtask = new MicroTask(MICROSCENARIO::DESTROY_ID, target_vehicle);
					npc->GetStateMachine()->SetCurrentMicroTask(microtask);
					
					return;
				}
				else
				{
					MicroTask* microtask = new MicroTask(MICROSCENARIO::EXPLORATION_ID);
					npc->GetStateMachine()->SetCurrentMicroTask(microtask);
					
					return;
				}
			}
		}
		//else
		//{
			//npc->GetStateMachine()->GetMacroTaskManager()->GetMacroTask()->SetResult(SUCCESS_ID);
			//return;
		//}
	}        
}

/*virtual*/
void MacroScenarioStarSystemLiberation::Exit(Npc* npc) const
{
	#if AISCENARIO_LOG_ENABLED == 1 
	Logger::Instance().Log("npc_id=" + int2str(npc->GetId()) + " EXIT MacroScenarioStarSystemLiberation");
	#endif
}

/*virtual*/
std::string MacroScenarioStarSystemLiberation::GetDescription(Npc* npc) const
{
	return "MacroScenarioStarSystemLiberation: ss_id = " + int2str(npc->GetStateMachine()->GetMacroTaskManager()->GetMacroTask()->GetTarget()->GetId());
}
