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
              	Npc(int _race_id, IdData _data_id, TextureOb* _faceTexOb);
     		~Npc();
                
   		void setAlive(bool);
   		void setStarSystem(StarSystem*);
   		void setKosmoport(Kosmoport*);
   		void setLand(Land*);
   		void setScanTarget(Ship*);
   		void setPlaceTypeId(int);
   		void setControlledByPlayer(bool);

   		bool getAlive()    const;
   		int getId()        const;
   		int getTypeId()    const;
   		int getSubTypeId() const;
   		int getRaceId()    const;
   		StarSystem* getStarSystem();
   		Kosmoport* getKosmoport();
   		Ship* getShip();
   		Skill* getSkill();
   		Ship* getScanShip();
   		int getPlaceTypeId() const;
   		QuestObject* getSelfCareOb();
   		QuestObject* getQuestOb();
   		bool getControlledByPlayer()   const;
                unsigned long int getCredits() const;   

   		void bind(Ship*);

		void addCredits(int);
		void removeCredits(int);
     
     		// AI
     		//void setRandomTargetCoord();
     		void thinkCommon_inSpace_inStatic();
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
    		StarSystem* getCloseSafeStarSystem();
    		
                NeedsToDo needsToDo;
                            
                void setDoNothing();
                                
   	private:
   	     	bool is_alive;    
     		int race_id;
     		unsigned long int credits;  
     		IdData data_id;
     		
   	     	StarSystem* starsystem;
   	     	Kosmoport* kosmoport;
   	     	Land* land;
   	     	

   	     	bool controlled_by_player;
   	     	
   	     	Ship* ship;
   	     	
   	     	Skill* skill; 

   	     	TextureOb* texOb;

                QuestObject* selfcareOb;      // object to safe life
                QuestObject* subSelfcareOb;   // object to safe life
                
                QuestObject* grabOb;      
                QuestObject* subGrabOb;   
                
   	     	QuestObject* questOb;         // quest - continius
                QuestObject* subQuestOb;      // task is very short and can be changed very frequently  within quest
                     
                Observation* observation;
   	     	
     		void selfcareResolver();
     		void questResolver();
                
                // scenarios (performes in static)
                void grabbingScenario();
                void asteroidScenario();
                
     		void destroyShipQuestScenario();
     		void liberationStarSystemQuestScenario();
    		//
    		
                void checkNeeds();
                void generateSelfCare();
                void generateQuest();
                
                // Tracking and they events
                bool jumpTracking();
          	bool dockTracking();
                bool grabTracking();
                
                void jumpEvent();
                void dockEvent();
     		//
     		     		
     		Ship* ship_to_scan;
     		
     		int place_type_id;
 };



Npc* generateNpc(int _race_id, int _subtype_id);


#endif 

