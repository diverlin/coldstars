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


#ifndef STATEMACHINE_H
#define STATEMACHINE_H


class StateMachine
{
	public:
		StateMachine(Npc*);
		~StateMachine();

		void SetCurrentMicroTask(BaseScenario*, BaseGameEntity*);
		void SetCurrentMacroTask(BaseScenario*, BaseGameEntity*);
		
		TaskHolder* GetCurrentMacroTask() const { return current_macroTask; };
		//TaskHolder* GetPreviousMacroTask() const { return previous_macroTask; };	
		
		TaskHolder* GetCurrentMicroTask() const { return current_microTask; };
		//TaskHolder* GetPreviousMicroTask() const { return previous_microTask; };		
				
		void UpdateInDynamic();			
		void UpdateInStatic();	
		
		void ForceReset();

	private:
		Npc* npc_owner;
		
		TaskHolder* current_macroTask;		
		//TaskHolder* previous_macroTask;

		TaskHolder* current_microTask;		
		//TaskHolder* previous_microTask;
}; 


#endif 
     
