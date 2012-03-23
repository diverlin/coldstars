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


MacroScenarioStarSystemDefence :: MacroScenarioStarSystemDefence() 
{}

MacroScenarioStarSystemDefence :: ~MacroScenarioStarSystemDefence() 
{}

void MacroScenarioStarSystemDefence :: update_inStatic(Npc* _npc) const
{
	if ( _npc->getStarSystem() != _npc->getStateMachine()->getCurrentMacroTask()->getTarget()->getStarSystem() )
	{
		if (_npc->getStateMachine()->getCurrentMicroTask()->getTarget()->getStarSystem() != _npc->getStateMachine()->getCurrentMacroTask()->getTarget()->getStarSystem())
		{
			_npc->getStateMachine()->setCurrentMicroTask(g_MICROSCENARIO_JUMP, _npc->getStateMachine()->getCurrentMacroTask()->getTarget()->getStarSystem());
		}
	}
	else
	{
		if ( (_npc->getStateMachine()->getCurrentMicroTask()->getScenario() != g_MICROSCENARIO_DESTROY) or (_npc->getStateMachine()->getCurrentMicroTask()->getValid() == false) )
		{
            		_npc->getObservation()->findVisibleNpcs_inSpace_inStatic();
            	
            		Npc* _target_npc = _npc->getObservation()->getClosestNpc(&RACES_GOOD_LIST);
            		if (_target_npc != NULL)
            		{
				_npc->getStateMachine()->setCurrentMicroTask(g_MICROSCENARIO_DESTROY, _target_npc);
			}
			else
			{
				//explore
			}
		}
	}
}

std::string MacroScenarioStarSystemDefence :: getDescription(Npc* _npc) const
{
	return "MacroScenarioStarSystemDefence: ss_id = " + int2str(_npc->getStateMachine()->getCurrentMacroTask()->getTarget()->getId());
}
