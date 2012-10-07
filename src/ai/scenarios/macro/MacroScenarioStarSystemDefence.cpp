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
#include "../../Task.hpp"
#include "../../../world/starsystem.hpp"
#include "../../../ai/StateMachine.hpp"

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
	#if AISCENARIO_LOG_ENABLED == 1 
	Logger::Instance().Log("npc_id=" + int2str(npc->GetId()) + " ENTER MacroScenarioStarSystemDefence");
	#endif
}

/*virtual*/
void MacroScenarioStarSystemDefence::UpdateInStaticInSpace(Npc* npc) const
{
	StarSystem* target_starsystem = target_starsystem = npc->GetStateMachine().GetMacroTaskManager().GetTarget()->GetStarSystem();
	if (npc->GetStarSystem()->GetId() != target_starsystem->GetId())
	{
		if (npc->GetStateMachine().GetMicroTaskManager().GetTask().GetScenarioTypeId() != MICROSCENARIO::JUMP_ID)
		{
			Task microtask(MICROSCENARIO::JUMP_ID, target_starsystem->GetId());
			npc->GetStateMachine().SetCurrentMicroTask(microtask);
			
			return;
		}
	}
	else
	{
		if (target_starsystem->GetConditionId() != ENTITY::STARSYSTEM::CONDITION::CAPTURED_ID)
		{
			if (npc->GetStateMachine().GetMicroTaskManager().GetTask().GetScenarioTypeId() != MICROSCENARIO::DESTROY_ID)
			{       	
			        Vehicle* target_vehicle = npc->GetObservation().GetRandVisibleVehicle(RaceInformationCollector::Instance().RACES_GOOD_vec);
            			if (target_vehicle != NULL)
            			{
            				Task microtask(MICROSCENARIO::DESTROY_ID, target_vehicle->GetId());
					npc->GetStateMachine().SetCurrentMicroTask(microtask);
					
					return;
				}
				else
				{
					Task microtask(MICROSCENARIO::EXPLORATION_ID, NONE_ID);
					npc->GetStateMachine().SetCurrentMicroTask(microtask);
					
					return;
				}
			}
		}
	}
}

/*virtual*/
void MacroScenarioStarSystemDefence::Exit(Npc* npc) const
{
	#if AISCENARIO_LOG_ENABLED == 1 
	Logger::Instance().Log("npc_id=" + int2str(npc->GetId()) + " EXIT MacroScenarioStarSystemDefence");
	#endif
}


/*virtual*/
std::string MacroScenarioStarSystemDefence::GetDescription(Npc* npc) const
{
	return "MacroScenarioStarSystemDefence: ss_id = " + int2str(npc->GetStateMachine().GetMacroTaskManager().GetTarget()->GetId());
}
