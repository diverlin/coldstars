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

void Npc :: setAlive(bool _alive) 		   { is_alive = _alive; }
void Npc :: setStarSystem(StarSystem* _starsystem) { starsystem = _starsystem; }
void Npc :: setKosmoport(Kosmoport* _kosmoport)    { kosmoport = _kosmoport; }
void Npc :: setLand(Land* _land)   		   { land = _land; }
void Npc :: setScanTarget(Ship* _ship)             { scanShip = _ship; }
void Npc :: setPlaceTypeId(int _place_type_id)     { place_type_id = _place_type_id; /*if (ship != NULL) ship->setPlaceTypeId(_place_type_id); */ }
void Npc :: setControlledByPlayer(bool _controlled_by_player) { controlled_by_player = _controlled_by_player; }
   		
bool Npc :: getAlive() const 	   { return is_alive; }
int Npc :: getId() const	   { return id; }
int Npc :: getTypeId() const	   { return type_id; }
int  Npc :: getSubTypeId() const   { return subtype_id; }
int Npc :: getRaceId() const	   { return race_id; }
StarSystem* Npc :: getStarSystem() { return starsystem; }
Kosmoport* Npc :: getKosmoport()   { return kosmoport; }
Ship* Npc :: getShip() 	 	   { return ship; }
Skill* Npc :: getSkill() 	   { return skill; }	
Ship* Npc :: getScanShip()	   { return scanShip; }	
int Npc :: getPlaceTypeId() const  { return place_type_id; }
QuestObject* Npc :: getSelfCareOb()    { return selfcareOb; }
QuestObject* Npc :: getQuestOb()   { return questOb; }
bool Npc :: getControlledByPlayer() const { return controlled_by_player; }
unsigned long int Npc :: getCredits() const { return credits; }   


void Npc :: bind(Ship* _ship) 	           
{ 
	ship = _ship; 
	ship->setNpc(this); 
	ship->setStarSystem(starsystem);  //???	
} 	

void Npc :: addCredits(int _credits) { credits += _credits; }
void Npc :: removeCredits(int _credits) { credits -= _credits; }

		
Npc :: Npc(int _race_id, int _subtype_id, TextureOb* _texOb)
{ 
    	id = g_NPC_ID_GENERATOR.getNextId(); 
    	type_id = NPC_ID;
    	subtype_id = _subtype_id;

    	is_alive = true;

      
    	texOb = _texOb;

    	race_id = _race_id;
    	
    	controlled_by_player = false;

    	credits = 1000;
   	
    	func_inDynamic_inSpace = &Npc::doNothing;
    	
    	
	place_type_id = NONE_ID; // fake


        ship       = NULL;
    	kosmoport  = NULL;
    	land       = NULL;
    	starsystem = NULL;
    		
	skill = new Skill();

	selfcareOb     = new QuestObject();
	subSelfcareOb  = new QuestObject();
	questOb        = new QuestObject();
        subQuestOb     = new QuestObject();
}
    
Npc :: ~Npc()
{
	delete selfcareOb;
	delete subSelfcareOb;
	delete questOb;
	delete subQuestOb;
}  
    


//void Npc :: setRandomTargetCoord()
//{
     //if (pTo_ship->direction_list_END == true) 
     //{   
        //pTo_ship->pTo_navigator->setStaticTargetCoords(getRandInt(0,800), getRandInt(0,800));  
     //} 
//}


//////////// AI
void Npc :: observeAll_inSpace_inStatic()
{
     	findVisibleAsteroids_inSpace_inStatic();
     	sortVisibleAsteroids_inSpace_inStatic();

     	findVisibleMinerals_inSpace_inStatic();
     	findVisibleContainers_inSpace_inStatic();

     	findVisibleNpcs_inSpace_inStatic();
}

void Npc :: findVisibleAsteroids_inSpace_inStatic()
{
	see.ASTEROID  = false;
        visible_ASTEROID_pList.clear();
        asteroid_distance_list.clear();

        for (unsigned int ai = 0; ai < starsystem->ASTEROID_vec.size(); ai++)
        {    
        	float ship_asteroid_dist = distBetweenCenters(ship->getPoints()->getCenter(), starsystem->ASTEROID_vec[ai]->getPoints()->getCenter());
                if (ship_asteroid_dist < ship->propetries.radius)
                {
                	visible_ASTEROID_pList.push_back(starsystem->ASTEROID_vec[ai]);
                      	asteroid_distance_list.push_back(ship_asteroid_dist);
                      	see.ASTEROID = true;
                } 
        }
}


void Npc :: sortVisibleAsteroids_inSpace_inStatic()
{
	sorted_visible_ASTEROID_pList.clear();
	
	for (unsigned int i = 0; i<visible_ASTEROID_pList.size(); i++)
	{
		int i_min = 0;
		float min = asteroid_distance_list[i];
		
		for (unsigned int j = i; j<visible_ASTEROID_pList.size(); j++)
		{	
        		if ( asteroid_distance_list[j] < min )
        		{
        			i_min = j;
        			min = asteroid_distance_list[j];
        		}
        	}
        	sorted_visible_ASTEROID_pList.push_back(visible_ASTEROID_pList[i_min]);        	
        }
}

void Npc :: findVisibleMinerals_inSpace_inStatic()
{
	see.MINERAL   = false;
        visible_MINERAL_pList.clear();
        mineral_distance_list.clear();

        for (unsigned int mi = 0; mi < starsystem->MINERAL_vec.size(); mi++)
        {    
         	float ship_mineral_dist = distBetweenCenters(ship->getPoints()->getCenter(), starsystem->MINERAL_vec[mi]->getPoints()->getCenter());
               	if (ship_mineral_dist < ship->propetries.radius)
              	{
               		visible_MINERAL_pList.push_back(starsystem->MINERAL_vec[mi]);
               		mineral_distance_list.push_back(ship_mineral_dist);
              		see.MINERAL = true;
               	} 
        }
}


void Npc :: findVisibleContainers_inSpace_inStatic()
{
	see.CONTAINER   = false;
        visible_CONTAINER_pList.clear();
        container_distance_list.clear();

        for (unsigned int ci = 0; ci < starsystem->CONTAINER_vec.size(); ci++)
        {    
        	float ship_container_dist = distBetweenCenters(ship->getPoints()->getCenter(), starsystem->CONTAINER_vec[ci]->getPoints()->getCenter());
                if (ship_container_dist < ship->propetries.radius)
                {
                	visible_CONTAINER_pList.push_back(starsystem->CONTAINER_vec[ci]);
                	container_distance_list.push_back(ship_container_dist);
                	see.CONTAINER = true;
                } 
    	}

}


void Npc ::findVisibleNpcs_inSpace_inStatic()
{
	findVisibleRangerNpcs_inSpace_inStatic();
        findVisibleWarriorNpcs_inSpace_inStatic();
        findVisibleTraderNpcs_inSpace_inStatic();
        findVisiblePiratNpcs_inSpace_inStatic();
        findVisibleDiplomatNpcs_inSpace_inStatic();
}


void Npc :: findVisibleRangerNpcs_inSpace_inStatic()
{
	see.RANGER = false;
        visible_NPC_RANGER_pList.clear();
        npc_ranger_distance_list.clear();

        for (unsigned int nri = 0; nri < starsystem->NPC_RANGER_inSPACE_vec.size(); nri++)
        {    
        	float dist = distBetweenCenters(ship->getPoints()->getCenter(), starsystem->NPC_RANGER_inSPACE_vec[nri]->ship->getPoints()->getCenter());
                if (dist < ship->propetries.radius)
                {
                	visible_NPC_RANGER_pList.push_back(starsystem->NPC_RANGER_inSPACE_vec[nri]);
                        npc_ranger_distance_list.push_back(dist);
                        see.RANGER = true;
               	} 
       }
}


void Npc :: findVisibleWarriorNpcs_inSpace_inStatic()
{
	see.WARRIOR = false;
        visible_NPC_WARRIOR_pList.clear();
        npc_warrior_distance_list.clear();

        for (unsigned int nwi = 0; nwi < starsystem->NPC_WARRIOR_inSPACE_vec.size(); nwi++)
        {    
        	float dist = distBetweenCenters(ship->getPoints()->getCenter(), starsystem->NPC_WARRIOR_inSPACE_vec[nwi]->ship->getPoints()->getCenter());
               	if (dist < ship->propetries.radius)
              	{
               		visible_NPC_WARRIOR_pList.push_back(starsystem->NPC_WARRIOR_inSPACE_vec[nwi]);
              		npc_warrior_distance_list.push_back(dist);
               		see.WARRIOR = true;
              	} 
        }
} 


void Npc :: findVisibleTraderNpcs_inSpace_inStatic()
{
       see.TRADER = false;
       visible_NPC_TRADER_pList.clear();
       npc_trader_distance_list.clear();

       for (unsigned int nti = 0; nti < starsystem->NPC_TRADER_inSPACE_vec.size(); nti++)
       {    
       		float dist = distBetweenCenters(ship->getPoints()->getCenter(), starsystem->NPC_TRADER_inSPACE_vec[nti]->ship->getPoints()->getCenter());
               	if (dist < ship->propetries.radius)
               	{
               		visible_NPC_TRADER_pList.push_back(starsystem->NPC_TRADER_inSPACE_vec[nti]);
               		npc_trader_distance_list.push_back(dist);
               		see.TRADER = true;
              	} 
       }
}


void Npc :: findVisiblePiratNpcs_inSpace_inStatic()
{
     	see.PIRAT = false;
        visible_NPC_PIRAT_pList.clear();
        npc_pirat_distance_list.clear();

        for (unsigned int npi = 0; npi < starsystem->NPC_PIRAT_inSPACE_vec.size(); npi++)
        {    
       		float dist = distBetweenCenters(ship->getPoints()->getCenter(), starsystem->NPC_PIRAT_inSPACE_vec[npi]->ship->getPoints()->getCenter());
               	if (dist < ship->propetries.radius)
               	{
               		visible_NPC_PIRAT_pList.push_back(starsystem->NPC_PIRAT_inSPACE_vec[npi]);
               		npc_pirat_distance_list.push_back(dist);
               		see.PIRAT = true;
               	} 
       }
}


void Npc :: findVisibleDiplomatNpcs_inSpace_inStatic()
{
 	see.DIPLOMAT = false;
        visible_NPC_DIPLOMAT_pList.clear();
        npc_diplomat_distance_list.clear();

        for (unsigned int ndi = 0; ndi < starsystem->NPC_DIPLOMAT_inSPACE_vec.size(); ndi++)
        {    
         	float dist = distBetweenCenters(ship->getPoints()->getCenter(), starsystem->NPC_DIPLOMAT_inSPACE_vec[ndi]->ship->getPoints()->getCenter());
               	if (dist < ship->propetries.radius)
               	{
               		visible_NPC_DIPLOMAT_pList.push_back(starsystem->NPC_DIPLOMAT_inSPACE_vec[ndi]);
               		npc_diplomat_distance_list.push_back(dist);
               		see.DIPLOMAT = true;
              	} 
        }
}


//void Npc :: observe_inPlanet_inStatic()
//{}




void Npc :: thinkCommon_inKosmoport_inStatic()
{   		
	if (needsToDo.REPAIR_KORPUS == true)
	{
                ship->repair();
		needsToDo.REPAIR_KORPUS = false;
	}	
	
	
	// if all things are DONE
	ship->getNavigator()->getTargetPlanet()->addToLaunchingQueue(this);
	func_inDynamic_inSpace = &Npc::doNothing;
	
	selfcareOb->reset();
	subSelfcareOb->reset();
}

void Npc :: thinkCommon_inLand_inStatic()
{}


//void Npc :: thinkUnique_inSpace_inStatic()
//{
     	//(this->*pToFunc_thinkUnique_inSpace_inStatic)();
//}

void Npc :: thinkCommon_inSpace_inStatic()
{   	
	selfcareOb->validation();
	subSelfcareOb->validation();
		
	subQuestOb->validation();
	questOb->validation();

	observeAll_inSpace_inStatic();  
        
        if ((race_id != RACE_6_ID) or (race_id != RACE_7_ID))
        {
                checkNeeds();           
        }
        
	// emmidiate danger reaction
	if (see.ASTEROID == true)
	{
		ship->weapon_selector.setAll(false);
		ship->selectWeapons();
		ship->resetDeselectedWeaponTargets();
		
		ship->weapon_selector.setAll(true);
		ship->selectWeapons();		
                ship->setWeaponsTarget(sorted_visible_ASTEROID_pList[0]);
                
                //printf("TARGET => ship_id, asteroid id = %i/%i\n", ship->getId(), sorted_visible_ASTEROID_pList[0]->getId());
	}
	
	
	
	selfcareResolver();
		
	
	if ( (selfcareOb->getExist() == false) and (questOb->getExist() == false) )
	{
                if ((race_id != RACE_6_ID) or (race_id != RACE_7_ID))
                {
                        //destroyShipQuestGenerator(this);
                        liberationStarSystemQuestGenerator(this);
                }
                else
                {
                        questEvilGenerator(this);    
                }
        }
                
        if ( (selfcareOb->getExist() == false) and (questOb->getExist() == true) )
	{
		questResolver();
	}	
	
	
	ship->getNavigator()->updateDynamicTargetCoord();
	
}

void Npc :: checkNeeds()
{
        if (ship->getArmor() < 0.5*ship->data_korpus.armor)   // move to ship
	{
		needsToDo.REPAIR_KORPUS = true;
	}
        else
        {
		needsToDo.REPAIR_KORPUS = false;                
        }

        // check conditions of all items here and set REPAIR_EQUIPMENT flag accordingly
        needsToDo.REPAIR_EQUIPMENT = false;
        
        // check bak
   	needsToDo.GET_FUEL = false;
        
        // check if rockets are ended
   	needsToDo.GET_BULLETS = false;
        
        // check credits
        needsToDo.GET_CREDITS = false;
        
   	// ???
        needsToDo.BUY = false;
        
        // check otsec and free space        
   	needsToDo.SELL = false;        
}



void Npc :: destroyShipQuestScenario()
{
	if ( starsystem->getId() != questOb->getStarSystem()->getId() )
	{
		printf("npc_id =%i setTarget(StarSystem()_id =%i\n", id, questOb->getStarSystem()->getId() );
      		func_inDynamic_inSpace = &Npc::jumpingSequence;
                                        
       		ship->getNavigator()->setTarget(questOb->getStarSystem()); 
       	}
	else
	{
		func_inDynamic_inSpace = &Npc::doNothing;

		ship->weapon_selector.setAll(true);
		ship->selectWeapons();
		ship->setWeaponsTarget(questOb->getNpc()->getShip());
                      
                int _dist_close = questOb->getNpc()->getShip()->getCollisionRadius();  
                int _dist_far = 2 * _dist_close;
                                                
		ship->getNavigator()->setTarget(questOb->getNpc()->getShip(), getRandInt(_dist_close, _dist_far) );
	}
}


void Npc :: liberationStarSystemQuestScenario()
{
	if ( starsystem->getId() != questOb->getStarSystem()->getId() )
	{
		printf("npc_id =%i setTarget(StarSystem()_id =%i\n", id, questOb->getStarSystem()->getId() );
      		func_inDynamic_inSpace = &Npc::jumpingSequence;
                                        
       		ship->getNavigator()->setTarget(questOb->getStarSystem());
	}
	else
	{
		func_inDynamic_inSpace = &Npc::doNothing;

		if (subQuestOb->getActionId() != DESTROY_SHIP_QEST_ID)
		{
			subQuestOb->setTask(questOb->getStarSystem()->getEvilNpc(ship->getPoints()->getCenter()), DESTROY_SHIP_QEST_ID);
		}

		ship->weapon_selector.setAll(true);
		ship->selectWeapons();
		ship->setWeaponsTarget(subQuestOb->getNpc()->getShip());
                      
                int _dist_close = subQuestOb->getNpc()->getShip()->getCollisionRadius();  
                int _dist_far = 2 * _dist_close;
                                                
		ship->getNavigator()->setTarget(subQuestOb->getNpc()->getShip(), getRandInt(_dist_close, _dist_far) );
	}
}


void Npc :: selfcareResolver()
{                 
        if ( (needsToDo.REPAIR_KORPUS == true) and (selfcareOb->getActionId() != SELFCARE_TASK_ID) )
	{
               	if (starsystem->getCapturedFlag() == false)
               	{
               		selfcareOb->setTask(starsystem, SELFCARE_TASK_ID);
               	}
               	else
              	{
        		//hjump to near safety ss
        		StarSystem* _target_starsystem = starsystem;
        		selfcareOb->setTask(_target_starsystem, SELFCARE_TASK_ID);
        	}
	}
        
        
        if (selfcareOb->getExist() == true)
        {
        	if (selfcareOb->getStarSystem()->getId() != starsystem->getId())
		{
			printf("npc_id =%i setTarget(StarSystem()_id =%i\n", id, selfcareOb->getStarSystem()->getId() );
      			func_inDynamic_inSpace = &Npc::jumpingSequence;
                	                        
       			ship->getNavigator()->setTarget(selfcareOb->getStarSystem());
        	}
        	else
        	{
			if (subSelfcareOb->getActionId() != LANDING_TASK_ID)
			{
				Planet* _target_planet = getPlanetForDocking();  // depending on purpouse
				subSelfcareOb->setTask(_target_planet, LANDING_TASK_ID);
			}
			else
			{
				func_inDynamic_inSpace = &Npc::dockingSequence;
        			ship->getNavigator()->setTarget(subSelfcareOb->getPlanet());
			}        	        
        	}
        }
}


void Npc :: questResolver()
{
	if (questOb->getTypeId() == NPC_ID)
	{
		if (questOb->getActionId() == DESTROY_SHIP_QEST_ID)
		{
			destroyShipQuestScenario();
		}
	}
	
	if (questOb->getTypeId() == STARSYSTEM_ID)
	{	
		if (questOb->getActionId() == LIBERATION_STARSYSTEM_QUEST_ID)
		{			     
			liberationStarSystemQuestScenario();
		}
	}
}




void Npc :: update_inDynamic_inSpace()
{
	(this->*func_inDynamic_inSpace)();
}



//// *********** DOCKING/LAUNCH ***********
// DOCKING

Planet* Npc :: getPlanetForDocking()
{
     	printf("npc_id = %i, getPlanetForDocking()\n", id);

     	Planet* _target_planet = starsystem->getClosestPlanet(ship->getPoints()->getCenter());  // improove
     	return _target_planet;
}


bool Npc :: dockingSequence()
{
     	if (ship->getNavigator()->checkEchievement() == true)
     	{
     		if (ship->getNavigator()->getDockingPermission() == true)
     		{
     		     	ship->dockingEvent();     			
     		}
     		else
     		{
     			// wait or reset
     		}
     	}
        
        return true;
}


bool Npc :: jumpingSequence()
{
     	if (ship->getNavigator()->checkEchievement() == true)
     	{
                ship->jumpingEvent();
     	}
        
        return true;
}


bool Npc :: launchingEvent()
{
     	return ship->launchingEvent();
}
//// *********** DOCKING/LAUNCH ***********


//// *********** SCANNING ***********
bool Npc :: checkPossibilityToScan(Ship* _ship)
{
     	if (ship->getId() == _ship->getId())    // selfscan is possible all time
     	{
        	return true;
        }
 
     	if (ship->ableTo.SCAN == true) 
     	{
        	if (_ship->protector_slot.getEquipedStatus() == true)
        	{
           		if (ship->scaner_slot.getScanerEquipment()->getScan() >= _ship->protector_slot.getProtectorEquipment()->getProtection()) 
              		{
              			return true;
              		}
              	}
        }

     	return false;
}


bool Npc :: scanProceeding()
{
     	return true;
}

bool Npc :: removeScanTarget()
{
     	scanShip = NULL;
     	return true;
}
//// *********** SCANNING ***********



bool Npc :: doNothing()
{
    	return false;
}


void Npc :: setDoNothing()
{
        func_inDynamic_inSpace = &Npc::doNothing;
}
       



























//// Race 0
//void Npc :: thinkUnique_Race0_Ranger_inSpace_inStatic()
//{

//}

//void Npc :: thinkUnique_Race0_Warrior_inSpace_inStatic()
//{
     	//thinkUnique_Race0_Ranger_inSpace_inStatic();
//}

//void Npc :: thinkUnique_Race0_Trader_inSpace_inStatic()
//{
     	//thinkUnique_Race0_Ranger_inSpace_inStatic();
//}

//void Npc :: thinkUnique_Race0_Pirat_inSpace_inStatic()
//{
     	//thinkUnique_Race0_Ranger_inSpace_inStatic();
//}

//void Npc :: thinkUnique_Race0_Diplomat_inSpace_inStatic()
//{
     	//thinkUnique_Race0_Ranger_inSpace_inStatic();
//}


//// Race 1
//void Npc :: thinkUnique_Race1_Ranger_inSpace_inStatic()
//{
     	//thinkUnique_Race0_Ranger_inSpace_inStatic();
//}

//void Npc :: thinkUnique_Race1_Warrior_inSpace_inStatic()
//{
     	//thinkUnique_Race0_Ranger_inSpace_inStatic();
//}

//void Npc :: thinkUnique_Race1_Trader_inSpace_inStatic()
//{
     	//thinkUnique_Race0_Ranger_inSpace_inStatic();
//}

//void Npc :: thinkUnique_Race1_Pirat_inSpace_inStatic()
//{
     	//thinkUnique_Race0_Ranger_inSpace_inStatic();
//}

//void Npc :: thinkUnique_Race1_Diplomat_inSpace_inStatic()
//{
     	//thinkUnique_Race0_Ranger_inSpace_inStatic();
//}



//// Race 2
//void Npc :: thinkUnique_Race2_Ranger_inSpace_inStatic()
//{
     	//thinkUnique_Race0_Ranger_inSpace_inStatic();
//}

//void Npc :: thinkUnique_Race2_Warrior_inSpace_inStatic()
//{
     	//thinkUnique_Race0_Ranger_inSpace_inStatic();
//}

//void Npc :: thinkUnique_Race2_Trader_inSpace_inStatic()
//{
     	//thinkUnique_Race0_Ranger_inSpace_inStatic();
//}

//void Npc :: thinkUnique_Race2_Pirat_inSpace_inStatic()
//{
     	//thinkUnique_Race0_Ranger_inSpace_inStatic();
//}

//void Npc :: thinkUnique_Race2_Diplomat_inSpace_inStatic()
//{
     	//thinkUnique_Race0_Ranger_inSpace_inStatic();
//}


//// Race 3
//void Npc :: thinkUnique_Race3_Ranger_inSpace_inStatic()
//{
     	//thinkUnique_Race0_Ranger_inSpace_inStatic();
//}

//void Npc :: thinkUnique_Race3_Warrior_inSpace_inStatic()
//{
     	//thinkUnique_Race0_Ranger_inSpace_inStatic();
//}

//void Npc :: thinkUnique_Race3_Trader_inSpace_inStatic()
//{
     	//thinkUnique_Race0_Ranger_inSpace_inStatic();
//}

//void Npc :: thinkUnique_Race3_Pirat_inSpace_inStatic()
//{   		
     	//thinkUnique_Race0_Ranger_inSpace_inStatic();
//}

//void Npc :: thinkUnique_Race3_Diplomat_inSpace_inStatic()
//{
     	//thinkUnique_Race0_Ranger_inSpace_inStatic();
//}


//// Race 4
//void Npc :: thinkUnique_Race4_Ranger_inSpace_inStatic()
//{
     	//thinkUnique_Race0_Ranger_inSpace_inStatic();
//}

//void Npc :: thinkUnique_Race4_Warrior_inSpace_inStatic()
//{
     	//thinkUnique_Race0_Ranger_inSpace_inStatic();
//}

//void Npc :: thinkUnique_Race4_Trader_inSpace_inStatic()
//{
     	//thinkUnique_Race0_Ranger_inSpace_inStatic();
//}

//void Npc :: thinkUnique_Race4_Pirat_inSpace_inStatic()
//{
     	//thinkUnique_Race0_Ranger_inSpace_inStatic();
//}

//void Npc :: thinkUnique_Race4_Diplomat_inSpace_inStatic()
//{
     	//thinkUnique_Race0_Ranger_inSpace_inStatic();
//}

//// Race 6
//void Npc :: thinkUnique_Race6_inSpace_inStatic()
//{
     	////thinkUnique_Race0_Ranger_inSpace_inStatic();
        
     	////for (unsigned int ki = 0; ki < starsystem->SHIP_inSPACE_vec.size(); ki ++)
     	////{
         	////if (starsystem->SHIP_inSPACE_vec[ki]->getNpc()->getRaceId() != race_id)
         	////{
         	        ////ship->getNavigator()->setTargetShip(starsystem->SHIP_inSPACE_vec[ki], getRandInt(30, 100));
         	            		 
		 	////ship->weapon_selector.setAll(true);
            		////ship->selectWeapons();
            		////ship->setWeaponsTarget(starsystem->SHIP_inSPACE_vec[ki]);
            		////break;
         	////}
     	////}
//}

//// Race 7
//void Npc :: thinkUnique_Race7_inSpace_inStatic()
//{
     	//thinkUnique_Race6_inSpace_inStatic();
//}
