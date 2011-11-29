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

class Npc 
{
   	public:
              	Npc(int _race_id, 
              	    IdData, LifeData, 
              	    TextureOb*);
              	    
     		~Npc();
                
   		void setAlive(bool);
   		void setGarbageReady(bool);
   		void setStarSystem(StarSystem*);
   		void setKosmoport(Kosmoport*);
   		void setLand(Land*);
   		void setScanTarget(Ship*);
   		void setPlaceTypeId(int);
   		void setControlledByPlayer(bool);

   		bool getAlive()    const;
   		bool getGarbageReady() const;
   		int getId()        const;
   		int getTypeId()    const;
   		int getSubTypeId() const;
   		int getRaceId()    const;
   		
   		Observation* getObservation() const;
   		
   		StarSystem* getStarSystem() const;
   		StarSystem* getFailBackStarSystem() const;
   		
   		Kosmoport* getKosmoport();
   		Ship* getShip();
   		Skill* getSkill();
   		Ship* getScanShip();
   		int getPlaceTypeId() const;
   		
   		StateMachine* getStateMachine();
   		   		
   		Points* getPoints() const;
   		bool* getpAlive();
   		int* getpPlaceTypeId();
   		float getCollisionRadius();
   		
   		//MacroTaskHolder* getMacroTaskMain() const;
   		//MacroTaskHolder* getMacroTaskSelf() const;
   		//MicroTaskHolder* getMicroTask() const;   		

     		
     		
   		bool getControlledByPlayer()   const;
                unsigned long int getCredits() const;   

   		void bind(Ship*);

		void increaseCredits(int);
		void decreaseCredits(int);
     
     		// AI
     		void update_inSpace_inStatic();     		
     		void update_inSpace_inDynamic();
     		
     		void thinkCommon_inKosmoport_inStatic();
     		void thinkCommon_inLand_inStatic();

     		void update_inDynamic_inSpace();
                //

     		//// scanning
    		bool checkPossibilityToScan(Ship*);
     		bool scanProceeding(); 
     		bool removeScanTarget();
     		//// scanning
     		
     		Planet* getPlanetForDocking();
    		StarSystem* getClosestStarSystem(bool);
    		
                NeedsToDo needsToDo;
                            
               
                void renderInfo(float _pos_x, float _pos_y, float _offset_x = 0.0, float _offset_y = 0.0);
                
                Observation* observation;
                
                void jumpEvent();
                void dockEvent();
                                
   	private:
     		int race_id;
     		unsigned long int credits; 
     		 
     		IdData data_id;
     		LifeData data_life;
     		
   	     	StarSystem* starsystem;
   	     	StarSystem* failback_starsystem;
   	     	
   	     	Kosmoport* kosmoport;
   	     	Land* land;
   	     	
   	     	InfoTable info;

   	     	bool controlled_by_player;
   	     	
   	     	Ship* ship;
   	     	
   	     	Skill* skill; 

   	     	TextureOb* texOb;

     		AiModelBase* ai_model;
     		StateMachine* state_machine;

     		     		
                void asteroidScenario();
                void checkNeeds();
     		     	
     		 	
     		Ship* ship_to_scan;
     		
     		int place_type_id;
     		
     		void updateInfo();     		
     		     		
     		//MacroTaskHolder* macro_task_main;
   		//MacroTaskHolder* macro_task_self;
   		//MicroTaskHolder* micro_task;
 };



Npc* generateNpc(int _race_id, int _subtype_id);


#endif 

