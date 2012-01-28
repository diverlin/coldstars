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


class MacroTaskHolder
{
	public:
		MacroTaskHolder();
		~MacroTaskHolder();
		
		template <typename TARGET_TYPE>
		void set(MacroScenarioBase*, TARGET_TYPE*);

		bool getValid() const;		
		MacroScenarioBase* getScenario() const;
		TargetObject*      getTarget() const;	
		
		void reset();
				
	private:
		MacroScenarioBase*     scenario;
		TargetObject* target;	
		
		bool is_valid;
};


class MicroTaskHolder
{
	public:
		MicroTaskHolder();
		~MicroTaskHolder();
	
		template <typename TARGET_TYPE>
		void set(MicroScenarioBase*, TARGET_TYPE*);
	
		bool getValid() const;
		MicroScenarioBase*  getScenario() const;
		TargetObject*       getTarget() const;
		
		void reset();
			
	private:
		MicroScenarioBase*     scenario;
		TargetObject* target;	
		
		bool is_valid;
};


class StateMachine
{
	public:
		StateMachine(Npc*);
		~StateMachine();

		template <typename TARGET_TYPE>
		void setCurrentMicroTask(MicroScenarioBase*, TARGET_TYPE*);
		template <typename TARGET_TYPE>
		void setCurrentMacroTask(MacroScenarioBase*, TARGET_TYPE*);
		
		MacroTaskHolder* getCurrentMacroTask() const;
		MacroTaskHolder* getPreviousMacroTask() const;	
		
		MicroTaskHolder* getCurrentMicroTask() const;
		MicroTaskHolder* getPreviousMicroTask() const;		
				
		void update_inDynamic();			
		void update_inStatic();	
		
		void reset();

	private:
		Npc* npc_owner;
		
		MacroTaskHolder* current_macroTask;		
		MacroTaskHolder* previous_macroTask;

		MicroTaskHolder* current_microTask;		
		MicroTaskHolder* previous_microTask;
}; 


#endif 
     
