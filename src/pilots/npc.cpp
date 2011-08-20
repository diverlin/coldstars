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


#include "npc.h"

Npc :: Npc(int _race_id, int _subtype_id, TextureOb* _pTo_texOb)
{ 
    is_alive = true;

    in_SPACE = false;

    type_id = NPC_ID;
    subtype_id = _subtype_id;
    id = g_ENTITY_ID_GENERATOR.returnNextId(); 
      
    pTo_texOb = _pTo_texOb;
    texture = pTo_texOb->texture;
    w = pTo_texOb->w;
    h = pTo_texOb->h;

    pTo_ship = NULL;

    race_id = _race_id;

    pTo_skill = new Skill();

    if (race_id == RACE_0_ID)
    {  
       if (subtype_id == RANGER_ID)
          pToFunc_thinkUnique_inSpace_inStatic = &Npc::thinkUnique_Race0_Ranger_inSpace_inStatic;
       if (subtype_id == WARRIOR_ID)
          pToFunc_thinkUnique_inSpace_inStatic = &Npc::thinkUnique_Race0_Warrior_inSpace_inStatic;
       if (subtype_id == TRADER_ID)
          pToFunc_thinkUnique_inSpace_inStatic = &Npc::thinkUnique_Race0_Trader_inSpace_inStatic;
       if (subtype_id == PIRAT_ID)
          pToFunc_thinkUnique_inSpace_inStatic = &Npc::thinkUnique_Race0_Pirat_inSpace_inStatic;
       if (subtype_id == DIPLOMAT_ID)
          pToFunc_thinkUnique_inSpace_inStatic = &Npc::thinkUnique_Race0_Diplomat_inSpace_inStatic;
    }

    if (race_id == RACE_1_ID)
    { 
       if (subtype_id == RANGER_ID)
          pToFunc_thinkUnique_inSpace_inStatic = &Npc::thinkUnique_Race1_Ranger_inSpace_inStatic;
       if (subtype_id == WARRIOR_ID)
          pToFunc_thinkUnique_inSpace_inStatic = &Npc::thinkUnique_Race1_Warrior_inSpace_inStatic;
       if (subtype_id == TRADER_ID)
          pToFunc_thinkUnique_inSpace_inStatic = &Npc::thinkUnique_Race1_Trader_inSpace_inStatic;
       if (subtype_id == PIRAT_ID)
          pToFunc_thinkUnique_inSpace_inStatic = &Npc::thinkUnique_Race1_Pirat_inSpace_inStatic;
       if (subtype_id == DIPLOMAT_ID)
          pToFunc_thinkUnique_inSpace_inStatic = &Npc::thinkUnique_Race1_Diplomat_inSpace_inStatic;
    }

    if (race_id == RACE_2_ID)
    { 
       if (subtype_id == RANGER_ID)
          pToFunc_thinkUnique_inSpace_inStatic = &Npc::thinkUnique_Race2_Ranger_inSpace_inStatic;
       if (subtype_id == WARRIOR_ID)
          pToFunc_thinkUnique_inSpace_inStatic = &Npc::thinkUnique_Race2_Warrior_inSpace_inStatic;
       if (subtype_id == TRADER_ID)
          pToFunc_thinkUnique_inSpace_inStatic = &Npc::thinkUnique_Race2_Trader_inSpace_inStatic;
       if (subtype_id == PIRAT_ID)
          pToFunc_thinkUnique_inSpace_inStatic = &Npc::thinkUnique_Race2_Pirat_inSpace_inStatic;
       if (subtype_id == DIPLOMAT_ID)
          pToFunc_thinkUnique_inSpace_inStatic = &Npc::thinkUnique_Race2_Diplomat_inSpace_inStatic;
    }

    if (race_id == RACE_3_ID)
    { 
       if (subtype_id == RANGER_ID)
          pToFunc_thinkUnique_inSpace_inStatic = &Npc::thinkUnique_Race3_Ranger_inSpace_inStatic;
       if (subtype_id == WARRIOR_ID)
          pToFunc_thinkUnique_inSpace_inStatic = &Npc::thinkUnique_Race3_Warrior_inSpace_inStatic;
       if (subtype_id == TRADER_ID)
          pToFunc_thinkUnique_inSpace_inStatic = &Npc::thinkUnique_Race3_Trader_inSpace_inStatic;
       if (subtype_id == PIRAT_ID)
          pToFunc_thinkUnique_inSpace_inStatic = &Npc::thinkUnique_Race3_Pirat_inSpace_inStatic;
       if (subtype_id == DIPLOMAT_ID)
          pToFunc_thinkUnique_inSpace_inStatic = &Npc::thinkUnique_Race3_Diplomat_inSpace_inStatic;
    }

    if (race_id == RACE_4_ID)
    { 
       if (subtype_id == RANGER_ID)
          pToFunc_thinkUnique_inSpace_inStatic = &Npc::thinkUnique_Race4_Ranger_inSpace_inStatic;
       if (subtype_id == WARRIOR_ID)
          pToFunc_thinkUnique_inSpace_inStatic = &Npc::thinkUnique_Race4_Warrior_inSpace_inStatic;
       if (subtype_id == TRADER_ID)
          pToFunc_thinkUnique_inSpace_inStatic = &Npc::thinkUnique_Race4_Trader_inSpace_inStatic;
       if (subtype_id == PIRAT_ID)
          pToFunc_thinkUnique_inSpace_inStatic = &Npc::thinkUnique_Race4_Pirat_inSpace_inStatic;
       if (subtype_id == DIPLOMAT_ID)
          pToFunc_thinkUnique_inSpace_inStatic = &Npc::thinkUnique_Race4_Diplomat_inSpace_inStatic;
    }

    if (race_id == RACE_6_ID)
       pToFunc_thinkUnique_inSpace_inStatic = &Npc::thinkUnique_Race6_inSpace_inStatic;
    if (race_id == RACE_7_ID)
       pToFunc_thinkUnique_inSpace_inStatic = &Npc::thinkUnique_Race7_inSpace_inStatic;

    credits = 1000;
    needs_task_queue_has_been_changed = false;
}
    
Npc :: ~Npc()
{}  
    



void Npc :: setShip(Ship* _pTo_ship)
{
    pTo_ship = _pTo_ship;

    pTo_ship->pTo_npc_owner = this;
    //pTo_ship->owner_type_id = this->type_id;

    pTo_ship->pTo_starsystem = pTo_starsystem;
}


//void Npc :: setRandomTargetCoord()
//{
     //if (pTo_ship->direction_list_END == true) 
     //{   
        //pTo_ship->pTo_navigator->setStaticTargetCoords(randIntInRange(0,800), randIntInRange(0,800));  
     //} 
//}

void Npc :: extractTheMind()
{
     pToFunc_thinkUnique_inSpace_inStatic = &Npc::thinkNothing_inStatic;
     // player take action
}





//////////// AI
void Npc :: generateQuest()
{}

void Npc :: questTaskQueueCreation()
{}



void Npc :: checkNeedTaskQueueForNewTasks()
{
     if (needs_task_queue_has_been_changed == true)
     {
        clearAIfuncSequence();
        initNeedTask();
        needs_task_queue_has_been_changed = false; 
     }
}



void Npc :: observeAll_inSpace_inStatic()
{
     observeAsteroids_inSpace_inStatic();
     observeMinerals_inSpace_inStatic();
     observeContainers_inSpace_inStatic();

     observeNpcs_inSpace_inStatic();
}

          void Npc :: observeAsteroids_inSpace_inStatic()
          {
               see.ASTEROID  = false;
               visible_ASTEROID_pList.clear();
               asteroid_distance_list.clear();

               for (unsigned int ai = 0; ai < pTo_starsystem->ASTEROID_pList.size(); ai++)
               {    
                   float ship_asteroid_dist = lengthBetweenPoints(pTo_ship->points.center_x, pTo_ship->points.center_y, pTo_starsystem->ASTEROID_pList[ai]->points.center_x, pTo_starsystem->ASTEROID_pList[ai]->points.center_y);
                   if (ship_asteroid_dist < pTo_ship->radius)
                   {
                      visible_ASTEROID_pList.push_back(pTo_starsystem->ASTEROID_pList[ai]);
                      asteroid_distance_list.push_back(ship_asteroid_dist);
                      see.ASTEROID = true;
                   } 
               }
          }


          void Npc :: observeMinerals_inSpace_inStatic()
          {
               see.MINERAL   = false;
               visible_MINERAL_pList.clear();
               mineral_distance_list.clear();

               for (unsigned int mi = 0; mi < pTo_starsystem->MINERAL_pList.size(); mi++)
               {    float ship_mineral_dist = lengthBetweenPoints(pTo_ship->points.center_x, pTo_ship->points.center_y, pTo_starsystem->MINERAL_pList[mi]->points.center_x, pTo_starsystem->MINERAL_pList[mi]->points.center_y);
                    if (ship_mineral_dist < pTo_ship->radius)
                    {
                       visible_MINERAL_pList.push_back(pTo_starsystem->MINERAL_pList[mi]);
                       mineral_distance_list.push_back(ship_mineral_dist);
                       see.MINERAL = true;
                    } 
               }
          }

          void Npc :: observeContainers_inSpace_inStatic()
          {
               see.CONTAINER   = false;
               visible_CONTAINER_pList.clear();
               container_distance_list.clear();

               for (unsigned int ci = 0; ci < pTo_starsystem->CONTAINER_pList.size(); ci++)
               {    float ship_container_dist = lengthBetweenPoints(pTo_ship->points.center_x, pTo_ship->points.center_y, pTo_starsystem->CONTAINER_pList[ci]->points.center_x, pTo_starsystem->CONTAINER_pList[ci]->points.center_y);
                    if (ship_container_dist < pTo_ship->radius)
                    {
                       visible_CONTAINER_pList.push_back(pTo_starsystem->CONTAINER_pList[ci]);
                       container_distance_list.push_back(ship_container_dist);
                       see.CONTAINER = true;
                    } 
               }

          }

          void Npc :: observeNpcs_inSpace_inStatic()
          {
               observeRangerNpcs_inSpace_inStatic();
               observeWarriorNpcs_inSpace_inStatic();
               observeTraderNpcs_inSpace_inStatic();
               observePiratNpcs_inSpace_inStatic();
               observeDiplomatNpcs_inSpace_inStatic();
          }
               void Npc :: observeRangerNpcs_inSpace_inStatic()
               {
                    see.RANGER = false;
                    visible_NPC_RANGER_pList.clear();
                    npc_ranger_distance_list.clear();

                    for (unsigned int nri = 0; nri < pTo_starsystem->NPC_RANGER_pList.size(); nri++)
                    {    float dist = lengthBetweenPoints(pTo_ship->points.center_x, pTo_ship->points.center_y, pTo_starsystem->NPC_RANGER_pList[nri]->pTo_ship->points.center_x, pTo_starsystem->NPC_RANGER_pList[nri]->pTo_ship->points.center_y);
                         if (dist < pTo_ship->radius)
                         {
                            visible_NPC_RANGER_pList.push_back(pTo_starsystem->NPC_RANGER_pList[nri]);
                            npc_ranger_distance_list.push_back(dist);
                            see.RANGER = true;
                         } 
                    }
               }

               void Npc :: observeWarriorNpcs_inSpace_inStatic()
               {
                    see.WARRIOR = false;
                    visible_NPC_WARRIOR_pList.clear();
                    npc_warrior_distance_list.clear();

                    for (unsigned int nwi = 0; nwi < pTo_starsystem->NPC_WARRIOR_pList.size(); nwi++)
                    {    float dist = lengthBetweenPoints(pTo_ship->points.center_x, pTo_ship->points.center_y, pTo_starsystem->NPC_WARRIOR_pList[nwi]->pTo_ship->points.center_x, pTo_starsystem->NPC_WARRIOR_pList[nwi]->pTo_ship->points.center_y);
                         if (dist < pTo_ship->radius)
                         {
                            visible_NPC_WARRIOR_pList.push_back(pTo_starsystem->NPC_WARRIOR_pList[nwi]);
                            npc_warrior_distance_list.push_back(dist);
                            see.WARRIOR = true;
                         } 
                    }
               } 

               void Npc :: observeTraderNpcs_inSpace_inStatic()
               {
                    see.TRADER = false;
                    visible_NPC_TRADER_pList.clear();
                    npc_trader_distance_list.clear();

                    for (unsigned int nti = 0; nti < pTo_starsystem->NPC_TRADER_pList.size(); nti++)
                    {    float dist = lengthBetweenPoints(pTo_ship->points.center_x, pTo_ship->points.center_y, pTo_starsystem->NPC_TRADER_pList[nti]->pTo_ship->points.center_x, pTo_starsystem->NPC_TRADER_pList[nti]->pTo_ship->points.center_y);
                         if (dist < pTo_ship->radius)
                         {
                            visible_NPC_TRADER_pList.push_back(pTo_starsystem->NPC_TRADER_pList[nti]);
                            npc_trader_distance_list.push_back(dist);
                            see.TRADER = true;
                         } 
                    }
               }

               void Npc :: observePiratNpcs_inSpace_inStatic()
               {
                    see.PIRAT = false;
                    visible_NPC_PIRAT_pList.clear();
                    npc_pirat_distance_list.clear();

                    for (unsigned int npi = 0; npi < pTo_starsystem->NPC_PIRAT_pList.size(); npi++)
                    {    float dist = lengthBetweenPoints(pTo_ship->points.center_x, pTo_ship->points.center_y, pTo_starsystem->NPC_PIRAT_pList[npi]->pTo_ship->points.center_x, pTo_starsystem->NPC_PIRAT_pList[npi]->pTo_ship->points.center_y);
                         if (dist < pTo_ship->radius)
                         {
                            visible_NPC_PIRAT_pList.push_back(pTo_starsystem->NPC_PIRAT_pList[npi]);
                            npc_pirat_distance_list.push_back(dist);
                            see.PIRAT = true;
                         } 
                    }
               }

               void Npc :: observeDiplomatNpcs_inSpace_inStatic()
               {
                    see.DIPLOMAT = false;
                    visible_NPC_DIPLOMAT_pList.clear();
                    npc_diplomat_distance_list.clear();

                    for (unsigned int ndi = 0; ndi < pTo_starsystem->NPC_DIPLOMAT_pList.size(); ndi++)
                    {    float dist = lengthBetweenPoints(pTo_ship->points.center_x, pTo_ship->points.center_y, pTo_starsystem->NPC_DIPLOMAT_pList[ndi]->pTo_ship->points.center_x, pTo_starsystem->NPC_DIPLOMAT_pList[ndi]->pTo_ship->points.center_y);
                         if (dist < pTo_ship->radius)
                         {
                            visible_NPC_DIPLOMAT_pList.push_back(pTo_starsystem->NPC_DIPLOMAT_pList[ndi]);
                            npc_diplomat_distance_list.push_back(dist);
                            see.DIPLOMAT = true;
                         } 
                    }
               }


void Npc :: observe_inPlanet_inStatic()
{}


void Npc :: thinkNothing_inStatic()
{
     // player take action
}



void Npc :: thinkCommon_inKosmoport_inStatic()
{
     pTo_ship->reloadAllWeapons();

     if (in_SPACE == false)
     { 
        printf("npc_id=%i,  insertNeedTaskId(LAUNCHING_task_id)\n", id);
        insertNeedTaskId(LAUNCHING_task_id);   // debug
     }

     checkNeedTaskQueueForNewTasks();
}

void Npc :: thinkCommon_inLand_inStatic()
{
     pTo_ship->reloadAllWeapons();

     if (in_SPACE == false)
     { 
        printf("npc_id=%i,  insertNeedTaskId(LAUNCHING_task_id)\n", id);
        insertNeedTaskId(LAUNCHING_task_id);   // debug
     }

     checkNeedTaskQueueForNewTasks();
}


void Npc :: thinkUnique_inSpace_inStatic()
{
     (this->*pToFunc_thinkUnique_inSpace_inStatic)();
}

void Npc :: thinkCommon_inSpace_inStatic()
{
     pTo_ship->reloadAllWeapons();
     pTo_ship->pTo_navigator->updateTargetCoords();


     if ( (in_SPACE == true) && (active_task_id != LANDING_task_id) )                           // debug
     { 
        findAndSetTargetDockingObject();  // depending on purpouse
        insertNeedTaskId(LANDING_task_id);        
     }

     checkNeedTaskQueueForNewTasks();
}

// Race 0
void Npc :: thinkUnique_Race0_Ranger_inSpace_inStatic()
{
     observeAll_inSpace_inStatic();

     //makeImmediateDecision();    
}

void Npc :: thinkUnique_Race0_Warrior_inSpace_inStatic()
{
     thinkUnique_Race0_Ranger_inSpace_inStatic();
}

void Npc :: thinkUnique_Race0_Trader_inSpace_inStatic()
{
     thinkUnique_Race0_Ranger_inSpace_inStatic();
}

void Npc :: thinkUnique_Race0_Pirat_inSpace_inStatic()
{
     thinkUnique_Race0_Ranger_inSpace_inStatic();
}

void Npc :: thinkUnique_Race0_Diplomat_inSpace_inStatic()
{
     thinkUnique_Race0_Ranger_inSpace_inStatic();
}


// Race 1
void Npc :: thinkUnique_Race1_Ranger_inSpace_inStatic()
{
     thinkUnique_Race0_Ranger_inSpace_inStatic();
}

void Npc :: thinkUnique_Race1_Warrior_inSpace_inStatic()
{
     thinkUnique_Race0_Ranger_inSpace_inStatic();
}

void Npc :: thinkUnique_Race1_Trader_inSpace_inStatic()
{
     thinkUnique_Race0_Ranger_inSpace_inStatic();
}

void Npc :: thinkUnique_Race1_Pirat_inSpace_inStatic()
{
     thinkUnique_Race0_Ranger_inSpace_inStatic();
}

void Npc :: thinkUnique_Race1_Diplomat_inSpace_inStatic()
{
     thinkUnique_Race0_Ranger_inSpace_inStatic();
}



// Race 2
void Npc :: thinkUnique_Race2_Ranger_inSpace_inStatic()
{
     thinkUnique_Race0_Ranger_inSpace_inStatic();
}

void Npc :: thinkUnique_Race2_Warrior_inSpace_inStatic()
{
     thinkUnique_Race0_Ranger_inSpace_inStatic();
}

void Npc :: thinkUnique_Race2_Trader_inSpace_inStatic()
{
     thinkUnique_Race0_Ranger_inSpace_inStatic();
}

void Npc :: thinkUnique_Race2_Pirat_inSpace_inStatic()
{
     thinkUnique_Race0_Ranger_inSpace_inStatic();
}

void Npc :: thinkUnique_Race2_Diplomat_inSpace_inStatic()
{
     thinkUnique_Race0_Ranger_inSpace_inStatic();
}


// Race 3
void Npc :: thinkUnique_Race3_Ranger_inSpace_inStatic()
{
     thinkUnique_Race0_Ranger_inSpace_inStatic();
}

void Npc :: thinkUnique_Race3_Warrior_inSpace_inStatic()
{
     thinkUnique_Race0_Ranger_inSpace_inStatic();
}

void Npc :: thinkUnique_Race3_Trader_inSpace_inStatic()
{
     thinkUnique_Race0_Ranger_inSpace_inStatic();
}

void Npc :: thinkUnique_Race3_Pirat_inSpace_inStatic()
{
     thinkUnique_Race0_Ranger_inSpace_inStatic();
}

void Npc :: thinkUnique_Race3_Diplomat_inSpace_inStatic()
{
     thinkUnique_Race0_Ranger_inSpace_inStatic();
}


// Race 4
void Npc :: thinkUnique_Race4_Ranger_inSpace_inStatic()
{
     thinkUnique_Race0_Ranger_inSpace_inStatic();
}

void Npc :: thinkUnique_Race4_Warrior_inSpace_inStatic()
{
     thinkUnique_Race0_Ranger_inSpace_inStatic();
}

void Npc :: thinkUnique_Race4_Trader_inSpace_inStatic()
{
     thinkUnique_Race0_Ranger_inSpace_inStatic();
}

void Npc :: thinkUnique_Race4_Pirat_inSpace_inStatic()
{
     thinkUnique_Race0_Ranger_inSpace_inStatic();
}

void Npc :: thinkUnique_Race4_Diplomat_inSpace_inStatic()
{
     thinkUnique_Race0_Ranger_inSpace_inStatic();
}

// Race 6
void Npc :: thinkUnique_Race6_inSpace_inStatic()
{
     for (unsigned int ki = 0; ki < pTo_starsystem->SHIP_pList.size(); ki ++)
     {
         if (pTo_starsystem->SHIP_pList[ki]->returnOwnerRaceId() != race_id)
         { 
            pTo_ship->pTo_navigator->setTargetShip(pTo_starsystem->SHIP_pList[ki]);
            pTo_ship->setWeaponsToShipTarget(pTo_starsystem->SHIP_pList[ki], true, true, true, true, true);
            break;
         }
     }
}

// Race 7
void Npc :: thinkUnique_Race7_inSpace_inStatic()
{
     thinkUnique_Race6_inSpace_inStatic();
}



void Npc :: makeImmediateDecision()
{
    if (see.ASTEROID == true)
    {  
        int a_index = -1;
        float dist = asteroid_distance_list[0];

        for(unsigned int i = 0; i < visible_ASTEROID_pList.size(); i++)
           if (asteroid_distance_list[i] < dist)
           {
               dist = asteroid_distance_list[i];
               a_index = i;
           } 
        //printf("closest asteroid at =%f\n", dist);
        if (a_index != -1) 
           pTo_ship->setWeaponsToAsteroidTarget(visible_ASTEROID_pList[a_index], true, true, true, true, true);
    }            
}



void Npc :: insertNeedTaskId(int _task_id)
{
     NEEDS_TASK_queue.insert(NEEDS_TASK_queue.begin(), _task_id); 
     needs_task_queue_has_been_changed = true;
}

void Npc :: removeNeedTaskId(int _task_id)
{
     NEEDS_TASK_queue.erase(NEEDS_TASK_queue.begin()); 
     needs_task_queue_has_been_changed = true;
}

void Npc :: initNeedTask()
{
     if ( NEEDS_TASK_queue.size() != 0 )
     {
        active_task_id = NEEDS_TASK_queue[0];

        if (active_task_id == HYPER_JUMP_task_id)
        {
            //self.hyperJumpTaskInit()
            //return self.hyperJumpTaskExecution_inDynamic, self.hyperJumpTaskExecution_inStatic 
        }

        if (active_task_id == LANDING_task_id)
        {
            createDockingSequence();
        }

        if (active_task_id == LAUNCHING_task_id)
        {
            //createLaunchingSequence(); 
            printf("npc_id = %i, launchingEvent()\n", id);
            launchingEvent();
        }

        if (active_task_id == GRABBING_MINERAL_task_id)
        {
            //self.grabbingMineralTaskInit()
            //return self.grabbingTaskExecution_inDynamic, self.grabbingTaskExecution_inStatic
        }
 
        if (active_task_id == GRABBING_CONTAINER_task_id)
        { 
            //self.grabbingContainerTaskInit()
            //return self.grabbingTaskExecution_inDynamic, self.grabbingTaskExecution_inStatic
        }
        //   print '===set active', self.name, self.returnCurTaskStr(self.active_task_id)
     }

     else
     {
        initQuestTask();
     }
}




void Npc :: initQuestTask()
{
     if (QUEST_TASK_queue.size() != 0)
     {
        active_task_id = QUEST_TASK_queue[0];

        if (active_task_id == DESTROY_ALIEN_task_id)
        {
            //destroyAlienTaskInit()
            //    return self.destroyAlienTaskExecution_inDynamic, self.destroyAlienTaskExecution_inStatic
        }
     
        if (active_task_id == AREST_REQUEST_task_id)
        {
            //arestRequestTaskInit()
            //    return self.arestRequestTaskExecution_inDynamic, self.arestRequestTaskExecution_inStatic
        }

        if (active_task_id == TERROR_REQUEST_task_id)
        { 
            //   self.terrorRequestTaskInit()
            //   return self.terrorRequestTaskExecution_inDynamic, self.terrorRequestTaskExecution_inStatic
        }

        if (active_task_id == FIRE_LOW_task_id)
        {
                //self.fireLowTaskInit()
                //return self.fireLowTaskExecution_inDynamic, self.fireLowTaskExecution_inStatic
        } 
        
        if (active_task_id == FIRE_HIGH_task_id)
        {
           //     self.fireHighTaskInit()
           //     return self.fireHighTaskExecution_inDynamic, self.fireHighTaskExecution_inStatic
        }        
           //print '===set active', self.name, self.returnCurTaskStr(active_task_id)
     }
     else
     {
        generateQuest();
     }
}

void Npc :: taskExecution_inDynamic()
{
     if (func_inDynamic_queue.size() != 0)
     { 
        bool function_done = (this->*func_inDynamic_queue[0])();
        if (function_done == true) 
           func_inDynamic_queue.erase(func_inDynamic_queue.begin());
     }
}

void Npc :: taskExecution_inStatic()
{
     if (func_inStatic_queue.size() != 0)
     { 
        bool function_done = (this->*func_inStatic_queue[0])();
        if (function_done == true) 
           func_inStatic_queue.erase(func_inStatic_queue.begin());
     }
}



//// *********** DOCKING/LAUNCH ***********
// DOCKING
void Npc :: createDockingSequence()
{
     func_inDynamic_queue.push_back(&Npc::checkDocking);
     func_inDynamic_queue.push_back(&Npc::getDockingPermission);
     func_inDynamic_queue.push_back(&Npc::dockingEvent);
}


bool Npc :: findAndSetTargetDockingObject()
{
     printf("npc_id = %i, findAndSetTargetDockingObject()\n", id);

     Planet* pTo_target_planet = pTo_starsystem->returnClosestPlanet(pTo_ship->points.center_x, pTo_ship->points.center_y);  // improve
     pTo_ship->pTo_navigator->setTargetPlanet(pTo_target_planet);

     return true; 
}

bool Npc :: checkDocking()
{
     return pTo_ship->checkDocking();
}


bool Npc :: getDockingPermission()
{
     return pTo_ship->getDockingPermission();
}


bool Npc :: dockingEvent()
{
     if (pTo_ship->dockingEvent() == true)
     {
         removeNeedTaskId(LANDING_task_id);
         return true;
     }
     return false;
}

// LAUNCHING
void Npc :: createLaunchingSequence()
{
     func_inDynamic_queue.push_back(&Npc::launchingEvent);
}

bool Npc :: launchingEvent()
{
     return pTo_ship->launchingEvent();
}
//// *********** DOCKING/LAUNCH ***********


//// *********** SCANNING ***********
bool Npc :: isScanTargetPossible(Ship* _pTo_ship)
{
     if (pTo_ship->id == _pTo_ship->id)    // selfscan is possible all time
        return true;
 
     if (pTo_ship->ableTo.SCAN == true) 
        if (_pTo_ship->protector_slot.getEquipedStatus() == true)
           if (pTo_ship->scaner_slot.getScanerEquipment()->scan >= _pTo_ship->protector_slot.getProtectorEquipment()->protection) 
              return true;

     return false;
}

bool Npc :: setScanTarget(Ship* _pTo_ship)
{
     pTo_scanShip = _pTo_ship;
     return true;
}

bool Npc :: scanProceeding()
{
     return true;
}

bool Npc :: removeScanTarget()
{
     pTo_scanShip = NULL;
     return true;
}
//// *********** SCANNING ***********



bool Npc :: doNothing()
{
    return false;
}


void Npc :: clearAIfuncSequence()
{
      func_inDynamic_queue.clear();
      func_inStatic_queue.clear();
}

       
