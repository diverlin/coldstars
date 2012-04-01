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

#ifndef NPC_H
#define NPC_H

class Npc : public BaseGameEntity
{
   	public:
              	Npc(int _race_id, 
              	    IdData, LifeData, 
              	    TextureOb*);
              	    
     		virtual ~Npc();    		
     		
		void SetGarbageReady(bool garbage_ready)      { data_life.garbage_ready = garbage_ready; }
		void SetAlive(bool alive) 		      { data_life.is_alive = alive; }
		void SetLand(LandBase* land)   		      { this->land = land; };
		void SetScanTarget(Vehicle* vehicle_to_scan)  { this->vehicle_to_scan = vehicle_to_scan; };
		void SetUpperControl(bool upper_control)      { this->upper_control = upper_control; };

		int GetRaceId() 		const { return race_id; };
		StarSystem* GetFailBackStarSystem() const { return failback_starsystem; };
		Vehicle* GetVehicle()           const { return vehicle; };
		Skill* GetSkill() 	        const { return skill; };
		Vehicle* GetScanTarget()        const { return vehicle_to_scan; };	
		Observation* GetObservation()   const { return observation; };
		unsigned long int GetCredits()  const { return credits; };   
		StateMachine* GetStateMachine() const { return state_machine; };
		LandBase* GetLand()             const { return land; };

   		void Bind(Vehicle*);

		void IncreaseCredits(int);
		void DecreaseCredits(int);
     
     		// AI
     		void Update_inSpace_inStatic();     		
     		void Update_inSpace(int, bool);
     		
     		void ThinkCommon_inKosmoport_inStatic();
     		void ThinkCommon_inLand_inStatic();

     		void Update_inDynamic(int, bool);
                //

     		//// scanning
    		bool CheckPossibilityToScan(Vehicle*);
     		bool ScanProceeding(); 
     		void ResetScanTarget();
     		//// scanning
     		
     		Planet* GetPlanetForDocking();
    		StarSystem* GetClosestStarSystem(bool);
    		
                NeedsToDo needsToDo;
               
                void RenderInfo(float _pos_x, float _pos_y, float _offset_x, float _offset_y);
                               
   	private:
     		int race_id;
     		unsigned long int credits; 
     		bool upper_control;

   	     	StarSystem* failback_starsystem;
   	     	
   	     	LandBase* land;
   	     	     		     		
   	     	Vehicle* vehicle;
   	     	
   	     	Skill* skill; 


     		AiModelBase* ai_model;
     		StateMachine* state_machine;
   		     	
     		 	
     		Vehicle* vehicle_to_scan;
     		
                Observation* observation;

                void AsteroidScenario();
                void CheckNeeds();
                                    		
     		void UpdateInfo();     	
     		virtual void PostDeathUniqueEvent(bool);	
 };



Npc* getNewNpc(int _race_id, int _subtype_id);


#endif 

