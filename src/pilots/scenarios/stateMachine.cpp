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



MacroTaskHolder :: MacroTaskHolder()
{
	is_valid = false;
	
	scenario = NULL;
	target   = new TargetObject(NULL);
}

MacroTaskHolder :: ~MacroTaskHolder()
{
	delete target;
}

template <typename TARGET_TYPE>
void MacroTaskHolder :: set(MacroScenarioBase* _scenario, TARGET_TYPE* _target)
{
	is_valid = true;
	
	scenario = _scenario;
	target->setObject(_target);
}

bool MacroTaskHolder :: getValid() const { return is_valid; }
MacroScenarioBase* MacroTaskHolder :: getScenario()   const { return scenario; }
TargetObject*  MacroTaskHolder :: getTarget() const { return target; }	
	
void MacroTaskHolder :: reset()
{
	is_valid = false;
	
	target->reset();
	//scenario->reset();
}




MicroTaskHolder :: MicroTaskHolder()
{
	is_valid = false;
	
	scenario = NULL;
	target   = new TargetObject(NULL);
}

MicroTaskHolder :: ~MicroTaskHolder()
{
	delete target;
}

MicroScenarioBase* MicroTaskHolder :: getScenario()   const { return scenario; }
TargetObject*  MicroTaskHolder :: getTarget() const { return target; }	
	
template <typename TARGET_TYPE>
void MicroTaskHolder :: set(MicroScenarioBase* _scenario, TARGET_TYPE* _target)
{
	scenario = _scenario;
	target->setObject(_target);
}




StateMachine :: StateMachine(Npc* _npc) 
{
	current_macroTask  = new MacroTaskHolder();		
	previous_macroTask = new MacroTaskHolder();

	current_microTask  = new MicroTaskHolder();		
	previous_microTask = new MicroTaskHolder();
	
	npc_owner = _npc;
}
		
StateMachine :: ~StateMachine() 
{
	delete current_macroTask;		
	delete previous_macroTask;

	delete current_microTask;		
	delete previous_microTask;
}


MacroTaskHolder* StateMachine :: getCurrentMacroTask() const  { return current_macroTask; }
MacroTaskHolder* StateMachine :: getPreviousMacroTask() const { return previous_macroTask; }	
		
MicroTaskHolder* StateMachine :: getCurrentMicroTask() const  { return current_microTask; }
MicroTaskHolder* StateMachine :: getPreviousMicroTask() const { return previous_microTask; }	
		
		
void StateMachine :: update_inStatic()
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

void StateMachine :: update_inDynamic()
{
	if (current_microTask->getScenario() != NULL)
	{
	 	current_microTask->getScenario()->update_inDynamic(npc_owner);
	}
}


		
template <typename TARGET_TYPE>					
void StateMachine :: setCurrentMacroTask(MacroScenarioBase* _new_state,  TARGET_TYPE* _target)
{
	if (previous_macroTask->getScenario() != NULL)
	{
		previous_macroTask->getScenario()->exit(npc_owner);
	}

	//previous_macroTask->set(current_macroTask->getScenario(), current_macroTask->getTarget());
	current_macroTask->set(_new_state, _target);
	
	if (current_macroTask->getScenario() != NULL)
	{
		current_macroTask->getScenario()->enter(npc_owner);
	}
}

		
template <typename TARGET_TYPE>					
void StateMachine :: setCurrentMicroTask(MicroScenarioBase* _new_state,  TARGET_TYPE* _target)
{
	if (previous_microTask->getScenario() != NULL)
	{
		previous_microTask->getScenario()->exit(npc_owner);
	}

	//previous_microTask->set(current_microTask->getScenario(), current_microTask->getTarget());
	current_microTask->set(_new_state, _target);
	
	if (current_microTask->getScenario() != NULL)
	{
		current_microTask->getScenario()->enter(npc_owner);
	}
}





