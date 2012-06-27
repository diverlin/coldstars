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



StateMachine::StateMachine(Npc* npc) 
{
	macrotask_holder  = new MacroTaskHolder();		
	microtask_holder  = new MicroTaskHolder();		
	
	npc_owner = npc;
}
		
StateMachine::~StateMachine() 
{
	delete macrotask_holder;		
	delete microtask_holder;		
}
		
void StateMachine::UpdateInStatic()
{
	if (macrotask_holder->GetScenario() != NULL) { macrotask_holder->GetScenario()->UpdateInStatic(npc_owner); }
	if (microtask_holder->GetScenario() != NULL) { microtask_holder->GetScenario()->UpdateInStatic(npc_owner); }
}

void StateMachine::UpdateInDynamic()
{
	if (microtask_holder->GetScenario() != NULL)
	{
	 	microtask_holder->GetScenario()->UpdateInDynamic(npc_owner);
	}
}
	
		
void StateMachine::SetCurrentMacroTask(MacroTask* macrotask)
{
	if (macrotask_holder->GetScenario() != NULL)
	{
		//macrotask_holder->GetScenario()->Exit(npc_owner);
	}
	
	//macrotask_holder->Set(target, new_scenario);
	//macrotask_holder->GetScenario()->Enter(npc_owner);
}

				
void StateMachine::SetCurrentMicroTask(BaseScenario* new_scenario, BaseGameEntity* target)
{
	if (microtask_holder->GetScenario() != NULL)
	{
		microtask_holder->GetScenario()->Exit(npc_owner);
	}
	
	microtask_holder->Set(new_scenario, target);
	microtask_holder->GetScenario()->Enter(npc_owner);
}

void StateMachine::ForceReset()
{
	macrotask_holder->SetResult(FAIL_ID);		
	microtask_holder->SetResult(FAIL_ID);		
}



