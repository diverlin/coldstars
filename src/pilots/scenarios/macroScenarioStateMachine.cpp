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


MacroScenarioStateMachine :: MacroScenarioStateMachine(Npc* _npc) 
{
	current_state  = NULL;
	previous_state = NULL;
	
	npc_owner = _npc;
}
		
MacroScenarioStateMachine :: ~MacroScenarioStateMachine() 
{}

void MacroScenarioStateMachine :: update_inStatic()
{
	if (current_state != NULL)
	{
	 	current_state->update_inStatic(npc_owner);
	}
}

template <typename TARGET_TYPE>					
void MacroScenarioStateMachine :: setCurrentState(MacroScenarioBase* _new_state,  TARGET_TYPE* _target)
{
	if (previous_state != NULL)
	{
		previous_state->exit(npc_owner);
	}
	previous_state = current_state;
	current_state = _new_state;
	
	if (current_state != NULL)
	{
		npc_owner->getMicroTask()->getTarget()->setObject(_target);
		current_state->enter(npc_owner);
	}
}

//void MacroScenarioStateMachine :: update_inDynamic()
//{
	//if (current_state != NULL)
	//{
	 	//current_state->update_inDynamic(npc_owner);
	//}
//}

MacroScenarioBase* MacroScenarioStateMachine :: getCurrentState() const { return current_state; }
		

//void MicroScenarioStateMachine :: revertPreviousState()
//{
	//current_state = previous_state;
//}

void MacroScenarioStateMachine :: reset()
{
	current_state  = NULL;
	previous_state = NULL;
}

std::string MacroScenarioStateMachine :: getCurrentStateDescription() const
{
	return current_state->getDescription(npc_owner);
}
