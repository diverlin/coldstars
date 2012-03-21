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

class Npc : public SpaceObjectBase
{
   	public:
              	Npc(int _race_id, 
              	    IdData, LifeData, 
              	    TextureOb*);
              	    
     		virtual ~Npc();
                
   		void setAlive(bool);
   		void setGarbageReady(bool);
   		void setLand(LandBase*);
   		void setScanTarget(VehicleBase*);
   		void setControlledByPlayer(bool);
   		void setUpperControl(bool);
   		

   		int getRaceId()    const;
   		
   		Observation* getObservation() const;
   		
   		StarSystem* getFailBackStarSystem() const;
   		
   		Kosmoport* getKosmoport();
   		VehicleBase* getVehicle();
   		VehicleBase* getScanTarget();
   		Skill* getSkill();

   		
   		StateMachine* getStateMachine();   		   		
   		
   		LandBase* getLand() const; 
   		    		
                unsigned long int getCredits() const;   

   		void bind(VehicleBase*);

		void increaseCredits(int);
		void decreaseCredits(int);
     
     		// AI
     		void update_inSpace_inStatic();     		
     		void update_inSpace(int, bool);
     		
     		void thinkCommon_inKosmoport_inStatic();
     		void thinkCommon_inLand_inStatic();

     		void update_inDynamic(int, bool);
                //

     		//// scanning
    		bool checkPossibilityToScan(VehicleBase*);
     		bool scanProceeding(); 
     		void resetScanTarget();
     		//// scanning
     		
     		Planet* getPlanetForDocking();
    		StarSystem* getClosestStarSystem(bool);
    		
                NeedsToDo needsToDo;
                            
               
                void renderInfo(float _pos_x, float _pos_y, float _offset_x, float _offset_y);
               
                void jumpEvent();
                void dockEvent();
                                
   	private:
     		int race_id;
     		unsigned long int credits; 
     		bool upper_control;

   	     	StarSystem* failback_starsystem;
   	     	
   	     	LandBase* land;
   	     	     		     		
   	     	VehicleBase* vehicle;
   	     	
   	     	Skill* skill; 


     		AiModelBase* ai_model;
     		StateMachine* state_machine;
   		     	
     		 	
     		VehicleBase* vehicle_to_scan;
     		
                Observation* observation;

                void asteroidScenario();
                void checkNeeds();
                                    		
     		void updateInfo();     	
     		virtual void postDeathUniqueEvent(bool);	
 };



Npc* getNewNpc(int _race_id, int _subtype_id);


#endif 

