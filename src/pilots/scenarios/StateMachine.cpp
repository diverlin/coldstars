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
	current_macroTask  = new TaskHolder();		
	//previous_macroTask = new TaskHolder();

	current_microTask  = new TaskHolder();		
	//previous_microTask = new TaskHolder();
	
	npc_owner = npc;
}
		
StateMachine::~StateMachine() 
{
	delete current_macroTask;		
	//delete previous_macroTask;

	delete current_microTask;		
	//delete previous_microTask;
}
		
void StateMachine::UpdateInStatic()
{
	if (current_macroTask->GetScenario() != NULL)
	{
	 	current_macroTask->GetScenario()->UpdateInStatic(npc_owner);
	}
	
	if (current_microTask->GetScenario() != NULL)
	{
	 	current_microTask->GetScenario()->UpdateInStatic(npc_owner);
	}
}

void StateMachine::UpdateInDynamic()
{
	if (current_microTask->GetScenario() != NULL)
	{
	 	current_microTask->GetScenario()->UpdateInDynamic(npc_owner);
	}
}
	
		
void StateMachine::SetCurrentMacroTask(BaseScenario* _new_state, BaseGameEntity* _target)
{
	//if (previous_macroTask->GetScenario() != NULL)
	//{
		//previous_macroTask->GetScenario()->Exit(npc_owner);
	//}

	//previous_macroTask->set(current_macroTask->GetScenario(), current_macroTask->GetTarget());
	current_macroTask->Set(_new_state, _target);
	
	if (current_macroTask->GetScenario() != NULL)
	{
		current_macroTask->GetScenario()->Enter(npc_owner);
	}
}

				
void StateMachine::SetCurrentMicroTask(BaseScenario* _new_state,  BaseGameEntity* _target)
{
	//if (previous_microTask->GetScenario() != NULL)
	//{
		//previous_microTask->GetScenario()->Exit(npc_owner);
	//}

	//previous_microTask->set(current_microTask->GetScenario(), current_microTask->GetTarget());
	current_microTask->Set(_new_state, _target);
	
	if (current_microTask->GetScenario() != NULL)
	{
		current_microTask->GetScenario()->Enter(npc_owner);
	}
}

void StateMachine::ForceReset()
{
	current_macroTask->SetResult(FAIL_ID);		
	//previous_macroTask->SetResult(FAIL_ID);
		
	current_microTask->SetResult(FAIL_ID);		
	//previous_microTask->SetResult(FAIL_ID);	
}



