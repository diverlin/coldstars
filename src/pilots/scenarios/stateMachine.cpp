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
		
void StateMachine::update_inStatic()
{
	if (current_macroTask->getScenario() != NULL)
	{
	 	current_macroTask->getScenario()->update_inStatic(npc_owner);
	}
	
	if (current_microTask->getScenario() != NULL)
	{
	 	current_microTask->getScenario()->update_inStatic(npc_owner);
	}
}

void StateMachine::update_inDynamic()
{
	if (current_microTask->getScenario() != NULL)
	{
	 	current_microTask->getScenario()->update_inDynamic(npc_owner);
	}
}
	
		
void StateMachine::setCurrentMacroTask(ScenarioBase* _new_state, BaseGameEntity* _target)
{
	//if (previous_macroTask->getScenario() != NULL)
	//{
		//previous_macroTask->getScenario()->exit(npc_owner);
	//}

	//previous_macroTask->set(current_macroTask->getScenario(), current_macroTask->getTarget());
	current_macroTask->set(_new_state, _target);
	
	if (current_macroTask->getScenario() != NULL)
	{
		current_macroTask->getScenario()->enter(npc_owner);
	}
}

				
void StateMachine::setCurrentMicroTask(ScenarioBase* _new_state,  BaseGameEntity* _target)
{
	//if (previous_microTask->getScenario() != NULL)
	//{
		//previous_microTask->getScenario()->exit(npc_owner);
	//}

	//previous_microTask->set(current_microTask->getScenario(), current_microTask->getTarget());
	current_microTask->set(_new_state, _target);
	
	if (current_microTask->getScenario() != NULL)
	{
		current_microTask->getScenario()->enter(npc_owner);
	}
}

void StateMachine::reset()
{
	current_macroTask->reset();		
	//previous_macroTask->reset();

	current_microTask->reset();		
	//previous_microTask->reset();
}



