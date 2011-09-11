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
   		bool getAlive() const;
   		int getId() const;
   		int getSubTypeId() const;
   		int getRaceId() const;
   		StarSystem* getStarSystem();
   		Kosmoport* getKosmoport();
   		Ship* getShip();
   		Skill* getSkill();
   		Ship* getScanShip();
   		   		   	   
   		void setInSpace(bool);
   		void setAlive(bool);			
   		void setStarSystem(StarSystem*);
   		void setKosmoport(Kosmoport*);
   		void setLand(Land*);
   		void setShip(Ship*);
   		void setScanTarget(Ship*);

		void addCredits(int);
		void removeCredits(int);

      		Npc(int _race_id, int _subtype_id, TextureOb* _faceTexOb);
     		~Npc();
     
     		void extractTheMind();        // needs for player

     		// AI
     		//void setRandomTargetCoord();
     		void thinkCommon_inKosmoport_inStatic();
     		void thinkCommon_inLand_inStatic();

     		void thinkCommon_inSpace_inStatic();
     		void thinkUnique_inSpace_inStatic();

     		void taskExecution_inDynamic();
    		void taskExecution_inStatic();

     		void clearAIfuncSequence();   
     		

     		//// docking/launching
     		void createDockingSequence();
     		void createLaunchingSequence();
     		//// docking/launching
     		

     		//// scanning
    		bool checkPossibilityToScan(Ship* _ship);
     		bool scanProceeding(); 
     		bool removeScanTarget();
     		//// scanning
     		
   	private:
   	     	bool is_alive;    
     		int race_id;
     		unsigned long int credits;  
     		int id, type_id, subtype_id;
     	
     	     	bool in_SPACE;
   	     		
   	     	StarSystem* starsystem;
   	     	Kosmoport* kosmoport;
   	     	Land* land;
   	     	
   	     	Ship* ship;
   	     	
   	     	Skill* skill; 
   	     	     		
   	     	TextureOb* texOb;
   	     	
   	     	
   	     	// observation/radar
     		std::vector<Asteroid*>  visible_ASTEROID_pList;
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
     		
     		See see;
     		
     		void observeAll_inSpace_inStatic();
          		void observeAsteroids_inSpace_inStatic();
          		void observeMinerals_inSpace_inStatic();
          		void observeContainers_inSpace_inStatic();
          		void observeNpcs_inSpace_inStatic();
               			void observeRangerNpcs_inSpace_inStatic();
               			void observeWarriorNpcs_inSpace_inStatic();
               			void observeTraderNpcs_inSpace_inStatic();
               			void observePiratNpcs_inSpace_inStatic();
               			void observeDiplomatNpcs_inSpace_inStatic();

     		void observe_inPlanet_inStatic();  //inhabited <-> uninhabited
     		// observation/radar 
     		
     		// AI
     		void generateQuest();
     		void questTaskQueueCreation(); 
     		void checkNeedTaskQueueForNewTasks();
     		
     		void initQuestTask();

     		void insertNeedTaskId(int _task_id);
     		void removeNeedTaskId(int _task_id);
     		void initNeedTask();


     		int active_task_id;
     		
     		
     		bool needs_task_queue_has_been_changed;

     		std::vector<int> QUEST_TASK_queue;
     		std::vector<int> NEEDS_TASK_queue;
     		
     		void thinkNothing_inStatic(); 
     		
          	void (Npc::*pToFunc_thinkUnique_inSpace_inStatic)();
     		
     		void thinkUnique_Race0_Ranger_inSpace_inStatic();
     		void thinkUnique_Race0_Warrior_inSpace_inStatic();
     		void thinkUnique_Race0_Trader_inSpace_inStatic();
     		void thinkUnique_Race0_Pirat_inSpace_inStatic();
     		void thinkUnique_Race0_Diplomat_inSpace_inStatic();

     		void thinkUnique_Race1_Ranger_inSpace_inStatic();
     		void thinkUnique_Race1_Warrior_inSpace_inStatic();
     		void thinkUnique_Race1_Trader_inSpace_inStatic();
     		void thinkUnique_Race1_Pirat_inSpace_inStatic();
     		void thinkUnique_Race1_Diplomat_inSpace_inStatic();

    		void thinkUnique_Race2_Ranger_inSpace_inStatic();
     		void thinkUnique_Race2_Warrior_inSpace_inStatic();
     		void thinkUnique_Race2_Trader_inSpace_inStatic();
     		void thinkUnique_Race2_Pirat_inSpace_inStatic();
     		void thinkUnique_Race2_Diplomat_inSpace_inStatic();

     		void thinkUnique_Race3_Ranger_inSpace_inStatic();
     		void thinkUnique_Race3_Warrior_inSpace_inStatic();
     		void thinkUnique_Race3_Trader_inSpace_inStatic();
     		void thinkUnique_Race3_Pirat_inSpace_inStatic();
     		void thinkUnique_Race3_Diplomat_inSpace_inStatic();

     		void thinkUnique_Race4_Ranger_inSpace_inStatic();
     		void thinkUnique_Race4_Warrior_inSpace_inStatic();
     		void thinkUnique_Race4_Trader_inSpace_inStatic();
     		void thinkUnique_Race4_Pirat_inSpace_inStatic();
     		void thinkUnique_Race4_Diplomat_inSpace_inStatic();

     		void thinkUnique_Race6_inSpace_inStatic();
     		void thinkUnique_Race7_inSpace_inStatic();
          		void makeImmediateDecision();
          		
       		std::vector<bool (Npc::*)()> func_inDynamic_queue;
     		std::vector<bool (Npc::*)()> func_inStatic_queue;
     		
     		bool doNothing();
     		// AI
     		
     		
     		//// docking/launching
     		bool findAndSetTargetDockingObject();

          	bool checkDocking();
          	bool getDockingPermission();
          	bool dockingEvent();

          	bool launchingEvent();
     		//// docking/launching
     		     		
     		Ship* scanShip;      		   	
};

#endif 



        
