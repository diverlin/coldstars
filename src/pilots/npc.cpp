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


#include "npc.hpp"

bool Npc :: launchingEventPlayer() { launchingEvent(); }
     		

void Npc :: setAlive(bool _alive) 		   { is_alive = _alive; }
void Npc :: setStarSystem(StarSystem* _starsystem) { starsystem = _starsystem; }
void Npc :: setKosmoport(Kosmoport* _kosmoport)    { kosmoport = _kosmoport; }
void Npc :: setLand(Land* _land)   		   { land = _land; }
void Npc :: setScanTarget(Ship* _ship)             { scanShip = _ship; }
void Npc :: setPlaceTypeId(int _place_type_id)     { place_type_id = _place_type_id; /*if (ship != NULL) ship->setPlaceTypeId(_place_type_id); */ }

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
QuestObject* Npc :: getQuestOb()   { return questOb; }
   		
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
    	is_alive = true;

    	type_id = NPC_ID;
    	subtype_id = _subtype_id;
    	id = g_ENTITY_ID_GENERATOR.returnNextId(); 
      
    	texOb = _texOb;

    	race_id = _race_id;



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
    	//needs_task_queue_has_been_changed = false;
    
    
        ship       = NULL;
    	kosmoport  = NULL;
    	land       = NULL;
    	starsystem = NULL;
    	
    	func_inDynamic = &Npc::doNothing;
    	
    	
	place_type_id = NONE_ID; // fake
	
	skill = new Skill();
	questOb = new QuestObject(this);
}
    
Npc :: ~Npc()
{}  
    


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
}   		QuestObject* getQuestOb();





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


void Npc :: observe_inPlanet_inStatic()
{}


void Npc :: thinkNothing_inStatic()
{
     	// player take action
}



void Npc :: thinkCommon_inKosmoport_inStatic()
{   		
     	ship->reloadAllWeapons();

     	//if (place_type_id == KOSMOPORT_TYPE_ID)
     	//{ 
        	//printf("npc_id=%i,  insertNeedTaskId(LAUNCHING_task_id)\n", id);
        	//insertNeedTaskId(LAUNCHING_task_id);   // debug
     	//}
}

void Npc :: thinkCommon_inLand_inStatic()
{
     	ship->reloadAllWeapons();

     	//if (place_type_id == LAND_ID)
     	//{ 
        	//printf("npc_id=%i,  insertNeedTaskId(LAUNCHING_task_id)\n", id);
        	//insertNeedTaskId(LAUNCHING_task_id);   // debug
     	//}
}


void Npc :: thinkUnique_inSpace_inStatic()
{
     	(this->*pToFunc_thinkUnique_inSpace_inStatic)();
}

void Npc :: thinkCommon_inSpace_inStatic()
{
     	ship->reloadAllWeapons();
     	
	if (see.ASTEROID == true)
	{
		ship->weapon_selector.setAll(false);
		ship->selectWeapons();
		ship->resetDeselectedWeaponTargets();
		
		ship->weapon_selector.setAll(true);
		ship->selectWeapons();
		//printf("TARGET => ship_id, asteroid id = %i/%i\n", ship->getId(), sorted_visible_ASTEROID_pList[0]->getId());
                ship->setWeaponsTarget(sorted_visible_ASTEROID_pList[0]);	
	}

	if (questOb->getExist() == true)
	{
		if (questOb->getTypeId() == NPC_ID)
		{
			ship->getNavigator()->setTargetShip(questOb->getNpc()->getShip(), randIntInRange(30, 100));
			if (questOb->getActionId() == DESTROY_TASK_ID)
			{
			 	ship->weapon_selector.setAll(true);
			        ship->selectWeapons();
                   		ship->setWeaponsTarget(questOb->getNpc()->getShip());
			}
		}
	}
	
	
     	//{	 
        	//Planet* _target_planet = getPlanetForDocking();  // depending on purpouse
	       	//ship->getNavigator()->setTargetPlanet(_target_planet); 
        //}
        
        ship->getNavigator()->updateDynamicTargetCoords();
}

// Race 0
void Npc :: thinkUnique_Race0_Ranger_inSpace_inStatic()
{
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
{   		QuestObject* getQuestOb();
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
     	thinkUnique_Race0_Ranger_inSpace_inStatic();
     	//for (unsigned int ki = 0; ki < starsystem->SHIP_inSPACE_vec.size(); ki ++)
     	//{
         	//if (starsystem->SHIP_inSPACE_vec[ki]->getNpc()->getRaceId() != race_id)
         	//{
         	        //ship->getNavigator()->setTargetShip(starsystem->SHIP_inSPACE_vec[ki], randIntInRange(30, 100));
         	            		 
		 	//ship->weapon_selector.setAll(true);
            		//ship->selectWeapons();
            		//ship->setWeaponsTarget(starsystem->SHIP_inSPACE_vec[ki]);
            		//break;
         	//}
     	//}
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
        	{ 
           		ship->selectWeapons();
           		ship->setWeaponsTarget(visible_ASTEROID_pList[a_index]);
        	}   
    	}            
}



void Npc :: update_inDynamic_inSpace()
{
	(this->*func_inDynamic)();
}



//// *********** DOCKING/LAUNCH ***********
// DOCKING

Planet* Npc :: getPlanetForDocking()
{
     	printf("npc_id = %i, getPlanetForDocking()\n", id);

     	Planet* _target_planet = starsystem->getClosestPlanet(ship->getPoints()->getCenter());  // improove
     	return _target_planet;
}

bool Npc :: checkDocking()
{
     	return ship->getNavigator()->checkEchievement();
}


bool Npc :: getDockingPermission()
{
     	return ship->getNavigator()->getDockingPermission();
}


bool Npc :: dockingEvent()
{
     	if (ship->dockingEvent() == true)
     	{
         	return true;
     	}
     	return false;
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



       
