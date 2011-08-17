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
     bool is_alive;
    
     bool in_SPACE;

     int id, type_id, subtype_id;
     int race_id;
  
     StarSystem* pTo_starsystem;
     Ship* pTo_ship;

     TextureOb* pTo_texOb;
     GLuint texture;
     int w, h;

     int credits;

     // observation/radar
     VEC_pAsteroid_type visible_ASTEROID_pList;
     VEC_pMineral_type visible_MINERAL_pList;
     VEC_pContainer_type visible_CONTAINER_pList;

     VEC_pNpc_type visible_NPC_RANGER_pList;
     VEC_pNpc_type visible_NPC_WARRIOR_pList;
     VEC_pNpc_type visible_NPC_TRADER_pList;
     VEC_pNpc_type visible_NPC_PIRAT_pList;
     VEC_pNpc_type visible_NPC_DIPLOMAT_pList;

     VEC_float_type asteroid_distance_list;
     VEC_float_type mineral_distance_list;
     VEC_float_type container_distance_list;

     VEC_float_type npc_ranger_distance_list;
     VEC_float_type npc_warrior_distance_list;
     VEC_float_type npc_trader_distance_list;
     VEC_float_type npc_pirat_distance_list;
     VEC_float_type npc_diplomat_distance_list;

     See see;
     // observation/radar 

     Kosmoport* pTo_kosmoport;
     Land* pTo_land;

     Skill* pTo_skill; 

      Npc(int _race_id, int _subtype_id, TextureOb* _pTo_faceTexOb);
     ~Npc();
     
     void setShip(Ship* _pTo_ship);
       
     void extractTheMind();        // needs for player

     // AI
     //void setRandomTargetCoord();
     bool needs_task_queue_has_been_changed;

     std::vector<int> QUEST_TASK_queue;
     std::vector<int> NEEDS_TASK_queue;

     void generateQuest();
     void questTaskQueueCreation(); 
     void checkNeedTaskQueueForNewTasks();

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

     void thinkNothing_inStatic(); 
     void thinkCommon_inKosmoport_inStatic();
     void thinkCommon_inLand_inStatic();

     void thinkUnique_inSpace_inStatic();
          void (Npc::*pToFunc_thinkUnique_inSpace_inStatic)();
     void thinkCommon_inSpace_inStatic();

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

     void initQuestTask();

     void insertNeedTaskId(int _task_id);
     void removeNeedTaskId(int _task_id);
     void initNeedTask();


     int active_task_id;
     void taskExecution_inDynamic();
     void taskExecution_inStatic();

     // task section
     bool doNothing();
     void clearAIfuncSequence();    

     //// docking/launching
     bool findAndSetTargetDockingObject();
     void createDockingSequence();
          bool checkDocking();
          bool getDockingPermission();
          bool dockingEvent();

     void createLaunchingSequence();
          bool launchingEvent();
     //// docking/launching

     //// scanning
     Ship* pTo_scanShip;   // move to scan_item
     bool isScanTargetPossible(Ship* _pTo_ship);
     bool setScanTarget(Ship* _pTo_ship);
     bool scanProceeding(); 
     bool removeScanTarget();
     //// scanning
};

#endif 



        
