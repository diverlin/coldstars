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


MacroScenarioStarSystemLiberation::MacroScenarioStarSystemLiberation() 
{
	type_id = MACROSCENARIO::STARSYSTEMLIBERATION_ID;
}

MacroScenarioStarSystemLiberation::~MacroScenarioStarSystemLiberation() 
{}

void MacroScenarioStarSystemLiberation::UpdateInStatic(Npc* npc) const
{
	if (npc->GetStarSystem()->GetId() != npc->GetStateMachine()->GetMacroTaskManager()->GetMacroTask()->GetTarget()->GetId() )
	{
		//if (npc->getMicroTask()->GetTarget()->getObId() != npc->getMacroTaskMain()->GetTarget()->GetStarSystem()->GetId())
		{
			MicroTask* microtask = new MicroTask(npc->GetStateMachine()->GetMacroTaskManager()->GetMacroTask()->GetTarget()->GetStarSystem(), MICROSCENARIO::JUMP_ID);
			npc->GetStateMachine()->SetCurrentMicroTask(microtask);
		}
	}
	else
	{
		if (npc->GetStateMachine()->GetMicroTaskManager()->GetMicroTask()->GetTarget()->GetTypeId() != ENTITY::NPC_ID)
		{
			Vehicle* _target_vehicle = npc->GetStarSystem()->GetRandomVehicle(&RACES_EVIL_LIST);
			if (_target_vehicle != NULL)
			{
				MicroTask* microtask = new MicroTask(_target_vehicle, MICROSCENARIO::DESTROY_ID);
				npc->GetStateMachine()->SetCurrentMicroTask(microtask);
			}
			else
			{
				//explore
			}
		}
	}        
}

std::string MacroScenarioStarSystemLiberation::GetDescription(Npc* npc) const
{
	return "MacroScenarioStarSystemLiberation: ss_id = " + int2str(npc->GetStateMachine()->GetMacroTaskManager()->GetMacroTask()->GetTarget()->GetId());
}
