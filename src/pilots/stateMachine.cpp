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


StateMachine :: StateMachine(Npc* _npc) 
{
	current_state  = NULL;
	previous_state = NULL;
	
	npc = _npc;
	
	done = false;
}
		
StateMachine :: ~StateMachine() 
{}

void StateMachine :: update_inStatic()
{
	 current_state->update_inStatic(npc);
}

void StateMachine :: update_inDynamic()
{
	 current_state->update_inDynamic(npc);
}
					
void StateMachine :: setCurrentState(StateBase* _new_state)
{
	if (previous_state != NULL)
	{
		previous_state->exit(npc);
	}
	previous_state = current_state;
	current_state = _new_state;
	
	current_state->enter(npc);
}

void StateMachine :: revertPreviousState()
{
	current_state = previous_state;
}
