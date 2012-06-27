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


MacroScenarioStarSystemDefence::MacroScenarioStarSystemDefence() 
{
	type_id = MACROSCENARIO::STARSYSTEMDEFENCE_ID;
}

MacroScenarioStarSystemDefence::~MacroScenarioStarSystemDefence() 
{}

void MacroScenarioStarSystemDefence::UpdateInStatic(Npc* _npc) const
{
	if ( _npc->GetStarSystem() != _npc->GetStateMachine()->GetMacroTaskManager()->GetMacroTask()->GetTarget()->GetStarSystem() )
	{
		if (_npc->GetStateMachine()->GetMicroTaskManager()->GetTarget()->GetStarSystem() != _npc->GetStateMachine()->GetMacroTaskManager()->GetMacroTask()->GetTarget()->GetStarSystem())
		{
			_npc->GetStateMachine()->SetCurrentMicroTask(MICROSCENARIO_JUMP, _npc->GetStateMachine()->GetMacroTaskManager()->GetMacroTask()->GetTarget()->GetStarSystem());
		}
	}
	else
	{
		if ( (_npc->GetStateMachine()->GetMicroTaskManager()->GetScenario() == NULL) or (_npc->GetStateMachine()->GetMicroTaskManager()->GetScenario() != MICROSCENARIO_DESTROY) )
		{
            		_npc->GetObservation()->FindVisibleNpcsInSpaceInStatic();
            	
            		Npc* _target_npc = _npc->GetObservation()->GetClosestNpc(&RACES_GOOD_LIST);
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

std::string MacroScenarioStarSystemDefence::GetDescription(Npc* _npc) const
{
	return "MacroScenarioStarSystemDefence: ss_id = " + int2str(_npc->GetStateMachine()->GetMacroTaskManager()->GetMacroTask()->GetTarget()->GetId());
}
