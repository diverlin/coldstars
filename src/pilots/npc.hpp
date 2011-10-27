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
   		void setAlive(bool);			
   		void setStarSystem(StarSystem*);
   		void setKosmoport(Kosmoport*);
   		void setLand(Land*);
   		void setScanTarget(Ship*);
   		void setPlaceTypeId(int);
   		void setControlledByPlayer(bool);

   		bool getAlive() const;
   		int getId() const;
   		int getTypeId() const;
   		int getSubTypeId() const;
   		int getRaceId() const;
   		StarSystem* getStarSystem();
   		Kosmoport* getKosmoport();
   		Ship* getShip();
   		Skill* getSkill();
   		Ship* getScanShip();
   		int getPlaceTypeId() const;
   		QuestObject* getSelfCareOb();
   		QuestObject* getQuestOb();
   		bool getControlledByPlayer() const;
                unsigned long int getCredits() const;   

   		void bind(Ship*);

		void addCredits(int);
		void removeCredits(int);

      		Npc(int _race_id, int _subtype_id, TextureOb* _faceTexOb);
     		~Npc();
     
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
     		
          	bool launchingEvent();
     		
     		Planet* getPlanetForDocking();
    		
                NeedsToDo needsToDo;
                            
                void setDoNothing();
                                
   	private:
   	     	bool is_alive;    
     		int race_id;
     		unsigned long int credits;  
     		int id, type_id, subtype_id;
     	
   	     	StarSystem* starsystem;
   	     	Kosmoport* kosmoport;
   	     	Land* land;
   	     	

   	     	bool controlled_by_player;
   	     	
   	     	Ship* ship;
   	     	
   	     	Skill* skill; 

   	     	TextureOb* texOb;

                QuestObject* selfcareOb;      // object to safe life
                QuestObject* subSelfcareOb;   // object to safe life
   	     	QuestObject* questOb;         // quest - continius
                QuestObject* subQuestOb;      // task is very short and can be changed very frequently  within quest
                               
   	     	//// observation/radar
     		std::vector<Asteroid*>  visible_ASTEROID_pList;
     		std::vector<Asteroid*>  sorted_visible_ASTEROID_pList;
     		     		
     		std::vector<Mineral*>   visible_MINERAL_pList;
     		std::vector<Container*> visible_CONTAINER_pList;

     		std::vector<Npc*> visible_NPC_RANGER_pList;
     		std::vector<Npc*> visible_NPC_WARRIOR_pList;
     		std::vector<Npc*> visible_NPC_TRADER_pList;
     		std::vector<Npc*> visible_NPC_PIRAT_pList;
     		std::vector<Npc*> visible_NPC_DIPLOMAT_pList;

     		std::vector<float> asteroid_distance_list;
     		std::vector<float> mineral_distance_list;
     		std::vector<float> container_distance_list;

     		std::vector<float> npc_ranger_distance_list;
     		std::vector<float> npc_warrior_distance_list;
     		std::vector<float> npc_trader_distance_list;
     		std::vector<float> npc_pirat_distance_list;
     		std::vector<float> npc_diplomat_distance_list;
     		
     		VisionStatus see;
     		
 		void observeAll_inSpace_inStatic();
     		//void observe_inPlanet_inStatic();  //inhabited <-> uninhabited
                
          	void findVisibleAsteroids_inSpace_inStatic();
          	void findVisibleMinerals_inSpace_inStatic();
          	void findVisibleContainers_inSpace_inStatic();
          	void findVisibleNpcs_inSpace_inStatic();
               	void findVisibleRangerNpcs_inSpace_inStatic();
               	void findVisibleWarriorNpcs_inSpace_inStatic();
               	void findVisibleTraderNpcs_inSpace_inStatic();
               	void findVisiblePiratNpcs_inSpace_inStatic();
               	void findVisibleDiplomatNpcs_inSpace_inStatic();
               			
               	void sortVisibleAsteroids_inSpace_inStatic();
     		//// 
     		
     		//// AI
     		void selfcareResolver();
     		void questResolver();
                
                // scenarios
     		void destroyShipQuestScenario();
     		void liberationStarSystemQuestScenario();
    		
                void checkNeeds();
                
                //
       		bool (Npc::*func_inDynamic_inSpace)();
     		bool doNothing();
                bool jumpingSequence();
          	bool dockingSequence();
     		//
     		     		
     		Ship* scanShip;
     		
     		int place_type_id;
};

#endif 


//void thinkUnique_inSpace_inStatic();
     		
          	//void (Npc::*pToFunc_thinkUnique_inSpace_inStatic)();
     		
     		//void thinkUnique_Race0_Ranger_inSpace_inStatic();
     		//void thinkUnique_Race0_Warrior_inSpace_inStatic();
     		//void thinkUnique_Race0_Trader_inSpace_inStatic();
     		//void thinkUnique_Race0_Pirat_inSpace_inStatic();
     		//void thinkUnique_Race0_Diplomat_inSpace_inStatic();

     		//void thinkUnique_Race1_Ranger_inSpace_inStatic();
     		//void thinkUnique_Race1_Warrior_inSpace_inStatic();
     		//void thinkUnique_Race1_Trader_inSpace_inStatic();
     		//void thinkUnique_Race1_Pirat_inSpace_inStatic();
     		//void thinkUnique_Race1_Diplomat_inSpace_inStatic();

    		//void thinkUnique_Race2_Ranger_inSpace_inStatic();
     		//void thinkUnique_Race2_Warrior_inSpace_inStatic();
     		//void thinkUnique_Race2_Trader_inSpace_inStatic();
     		//void thinkUnique_Race2_Pirat_inSpace_inStatic();
     		//void thinkUnique_Race2_Diplomat_inSpace_inStatic();

     		//void thinkUnique_Race3_Ranger_inSpace_inStatic();
     		//void thinkUnique_Race3_Warrior_inSpace_inStatic();
     		//void thinkUnique_Race3_Trader_inSpace_inStatic();
     		//void thinkUnique_Race3_Pirat_inSpace_inStatic();
     		//void thinkUnique_Race3_Diplomat_inSpace_inStatic();

     		//void thinkUnique_Race4_Ranger_inSpace_inStatic();
     		//void thinkUnique_Race4_Warrior_inSpace_inStatic();
     		//void thinkUnique_Race4_Trader_inSpace_inStatic();
     		//void thinkUnique_Race4_Pirat_inSpace_inStatic();
     		//void thinkUnique_Race4_Diplomat_inSpace_inStatic();

     		//void thinkUnique_Race6_inSpace_inStatic();
     		//void thinkUnique_Race7_inSpace_inStatic();
        
