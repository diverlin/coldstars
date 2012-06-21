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
{}

MacroScenarioStarSystemLiberation::~MacroScenarioStarSystemLiberation() 
{}

void MacroScenarioStarSystemLiberation::UpdateInStatic(Npc* _npc) const
{
	if ( _npc->GetStarSystem()->GetId() != _npc->GetStateMachine()->GetCurrentMacroTask()->GetTarget()->GetId() )
	{
		//if (_npc->getMicroTask()->GetTarget()->getObId() != _npc->getMacroTaskMain()->GetTarget()->GetStarSystem()->GetId())
		{
			_npc->GetStateMachine()->SetCurrentMicroTask(MICROSCENARIO_JUMP, _npc->GetStateMachine()->GetCurrentMacroTask()->GetTarget()->GetStarSystem());
		}
	}
	else
	{
		if (_npc->GetStateMachine()->GetCurrentMicroTask()->GetTarget()->GetTypeId() != ENTITY::NPC_ID)
		{
			Npc* _target_npc = _npc->GetStarSystem()->GetRandNpc(&RACES_EVIL_LIST);
			if (_target_npc != NULL)
			{
				_npc->GetStateMachine()->SetCurrentMicroTask(MICROSCENARIO_DESTROY, _target_npc);
			}
			else
			{
				//explore
			}
		}
	}        
}

std::string MacroScenarioStarSystemLiberation::GetDescription(Npc* _npc) const
{
	return "MacroScenarioStarSystemLiberation: ss_id = " + int2str(_npc->GetStateMachine()->GetCurrentMacroTask()->GetTarget()->GetId());
}
