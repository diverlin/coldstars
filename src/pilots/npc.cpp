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
void Npc :: setScanTarget(Ship* _ship)             { ship_to_scan = _ship; }
void Npc :: setPlaceTypeId(int _place_type_id)     { place_type_id = _place_type_id; /*if (ship != NULL) ship->setPlaceTypeId(_place_type_id); */ }
void Npc :: setControlledByPlayer(bool _controlled_by_player) { controlled_by_player = _controlled_by_player; }
   		
bool Npc :: getAlive() const 	   { return is_alive; }
int Npc :: getId() const	   { return data_id.id; }
int Npc :: getTypeId() const	   { return data_id.type_id; }
int  Npc :: getSubTypeId() const   { return data_id.subtype_id; }
int Npc :: getRaceId() const	   { return race_id; }
StarSystem* Npc :: getStarSystem() { return starsystem; }
Kosmoport* Npc :: getKosmoport()   { return kosmoport; }
Ship* Npc :: getShip() 	 	   { return ship; }
Skill* Npc :: getSkill() 	   { return skill; }	
Ship* Npc :: getScanShip()	   { return ship_to_scan; }	
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

void Npc :: addCredits(int _credits)    { credits += _credits; }
void Npc :: removeCredits(int _credits) { credits -= _credits; }

		
Npc :: Npc(int _race_id, IdData _data_id, TextureOb* _texOb)
{ 
    	is_alive = true;

      
    	texOb = _texOb;

    	race_id = _race_id;
    	
    	controlled_by_player = false;

    	credits = 1000;
   	
   	data_id = _data_id;
   	
    	
	place_type_id = NONE_ID; 


        ship       = NULL;
    	kosmoport  = NULL;
    	land       = NULL;
    	starsystem = NULL;
    		
	skill = new Skill();

	selfcareOb     = new QuestObject();
	subSelfcareOb  = new QuestObject();
        
        grabOb         = new QuestObject();
        subGrabOb      = new QuestObject();
        
	questOb        = new QuestObject();
        subQuestOb     = new QuestObject();
        
        observation = new Observation(this);
}
    
Npc :: ~Npc()
{
        delete skill;
        
	delete selfcareOb;
	delete subSelfcareOb;
        
        delete grabOb;
        delete subGrabOb;
        
	delete questOb;
	delete subQuestOb;
        
        delete observation;
}  
    


//void Npc :: setRandomTargetCoord()
//{
     //if (pTo_ship->direction_list_END == true) 
     //{   
        //pTo_ship->pTo_navigator->setStaticTargetCoords(getRandInt(0,800), getRandInt(0,800));  
     //} 
//}





void Npc :: thinkCommon_inKosmoport_inStatic()
{   		
	if (needsToDo.REPAIR_KORPUS == true)
	{
                ship->repair();
		needsToDo.REPAIR_KORPUS = false;
	}	
	
	
	// if all things are DONE
	ship->getNavigator()->getTargetPlanet()->addToLaunchingQueue(this);

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
        bool busy = false;
        
	observation->observeAll_inSpace_inStatic();  
        
	selfcareOb->validation();
	subSelfcareOb->validation();
        
        if (ship->ableTo.GRAB == true)
        {
                ship->grapple_slot.getGrappleEquipment()->validationTargets();  
        }
        
        if ( (observation->see.MINERAL == false) or (ship->ableTo.GRAB == false) )
        {
                if (grabOb->getActionId() == GRABBING_TASK_ID)
                {
                        grabOb->reset();
                }
        }

	questOb->validation();
	subQuestOb->validation();       
       
        if ( (race_id != RACE_6_ID) or (race_id != RACE_7_ID) )
        {
                checkNeeds();    
        }
       
        //// generator
        if ( (observation->see.MINERAL == true) and (ship->ableTo.GRAB == true) )
        {
                if (grabOb->getActionId() != GRABBING_TASK_ID)                
                {
                	printf("npc_id =%i, grabOb set GRABBING_TASK_ID\n", data_id.id);
                        grabOb->setTask(starsystem, GRABBING_TASK_ID);
                }
        }
       
  
        
        if (selfcareOb->getExist() == false)
	{
	        if ( (needsToDo.REPAIR_KORPUS == true) and (selfcareOb->getActionId() != SELFCARE_TASK_ID) )
	        {
                	//generateSelfCare();
                }
        }
         
       	if (questOb->getExist() == false)
	{
                //generateQuest();
        }
        ////
        
	if (observation->see.ASTEROID == true)
	{
                asteroidScenario();
	}
                        
             
        if ( (grabOb->getExist() == true) and (busy == false) )
        {
                if (grabOb->getActionId() == GRABBING_TASK_ID)
                {
                        grabbingScenario();                        
                        busy = true;
                }
        }

        
        if ( (selfcareOb->getExist() == true) and (busy == false) )
        {                            
                selfcareResolver(); 
                busy = true;   
        }
        

        if ( (questOb->getExist() == true) and (busy == false) )
        {
                questResolver();
                busy = true;  
        }

	ship->getNavigator()->updateDynamicTargetCoord();
}


void Npc :: generateSelfCare()
{
        selfcareOb->setTask(getCloseSafeStarSystem(), SELFCARE_TASK_ID); 
}



void Npc :: generateQuest()
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



void Npc :: asteroidScenario()
{
        ship->weapon_selector.setAll(false);
        ship->selectWeapons();
        ship->resetDeselectedWeaponTargets();

        ship->weapon_selector.setAll(true);
        ship->selectWeapons();
        ship->setWeaponsTarget(observation->sorted_visible_ASTEROID_vec[0]);
                
        //printf("TARGET => ship_id, asteroid id = %i/%i\n", ship->getId(), sorted_visible_ASTEROID_pList[0]->getId());
}


void Npc :: grabbingScenario()
{
        if ( starsystem->getId() != grabOb->getStarSystem()->getId() )
	{
		if (ship->getNavigator()->getFollowingTypeId() != STARSYSTEM_ID)
		{
                        ship->getNavigator()->setTarget(grabOb->getStarSystem()); 
                        
			printf("npc_id =%i navigate StarSystem id =%i, reason = GRAB HUNTING\n", data_id.id, grabOb->getStarSystem()->getId() );   // debug
                }
       	}
        else
        {        
                ship->getNavigator()->setStaticTargetCoords(observation->sorted_visible_MINERAL_vec[0]->getPoints()->getCenter(), 30.0);
        
                for (unsigned int i = 0; i < observation->sorted_visible_MINERAL_vec.size(); i++)
                {                	
                        float dist = distBetweenCenters(ship->getPoints()->getCenter(), observation->sorted_visible_MINERAL_vec[i]->getPoints()->getCenter());
                        printf("npc_id =%i,, dist/radius=%f,%i\n ", data_id.id, dist, ship->grapple_slot.getGrappleEquipment()->getRadius() );  
                        if (dist < ship->grapple_slot.getGrappleEquipment()->getRadius())
                        {                                       
                                ship->grapple_slot.getGrappleEquipment()->add(observation->sorted_visible_MINERAL_vec[i]);  
                                printf("npc_id =%i, mineral_id = %i ADDED // total vec.size()%i\n", data_id.id, observation->sorted_visible_MINERAL_vec[i]->getId(), ship->grapple_slot.getGrappleEquipment()->target_vec.size());                                              
                        }
                        else
                        {
                                break;
                        }
                }
        }
}


void Npc :: destroyShipQuestScenario()
{
	if ( starsystem->getId() != questOb->getStarSystem()->getId() )
	{
		if (ship->getNavigator()->getFollowingTypeId() != STARSYSTEM_ID)
		{                               
       			ship->getNavigator()->setTarget(questOb->getStarSystem()); 
       			
			printf("npc_id =%i navigate StarSystem id =%i, reason = DESTROY SHIP HUNTING\n", data_id.id, questOb->getStarSystem()->getId() );   // debug
       		}
       	}
	else
	{
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
		if (ship->getNavigator()->getFollowingTypeId() != STARSYSTEM_ID)
		{                         
       			ship->getNavigator()->setTarget(questOb->getStarSystem());
       			
			printf("npc_id =%i navigate StarSystem id =%i, reason = LIBERATION THIS SYSTEM\n", data_id.id, questOb->getStarSystem()->getId() );   // debug
       		}
	}
	else
	{
		if (subQuestOb->getActionId() != DESTROY_SHIP_QUEST_ID)
		{
			subQuestOb->setTask(questOb->getStarSystem()->getEvilNpc(ship->getPoints()->getCenter()), DESTROY_SHIP_QUEST_ID);
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
       	if (selfcareOb->getStarSystem()->getId() != starsystem->getId())
	{
		if (ship->getNavigator()->getFollowingTypeId() != STARSYSTEM_ID)
		{       
       			ship->getNavigator()->setTarget(selfcareOb->getStarSystem());
       			
       			printf("npc_id =%i navigate StarSystem id =%i, reason = SELF_CARE\n", data_id.id, selfcareOb->getStarSystem()->getId() );   // debug
       		}
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
        		ship->getNavigator()->setTarget(subSelfcareOb->getPlanet());
		}              
        }
}


void Npc :: questResolver()
{
	if (questOb->getObTypeId() == NPC_ID)
	{
		if (questOb->getActionId() == DESTROY_SHIP_QUEST_ID)
		{
			destroyShipQuestScenario();
		}
	}

	if (questOb->getObTypeId() == STARSYSTEM_ID)
	{	
		if (questOb->getActionId() == LIBERATION_STARSYSTEM_QUEST_ID)
		{ 
			liberationStarSystemQuestScenario();
		}
	}
}




void Npc :: update_inDynamic_inSpace()
{
     	//printf("npc_id = %i update_inDynamic_inSpace \n", id);
     	if (ship->getNavigator()->getFollowingTypeId() == STARSYSTEM_ID)
     	{
		jumpTracking();
	}
	
	if (ship->getNavigator()->getFollowingTypeId() == PLANET_ID)
	{
	        dockTracking();
	}

	if (ship->ableTo.GRAB == true) // think how to optimize this
	{
       		grabTracking();        	
        }
}





bool Npc :: dockTracking()
{
     	if (ship->getNavigator()->checkEchievement() == true)
     	{
     		if (ship->getNavigator()->getDockingPermission() == true)
     		{
     		     	dockEvent();
                        return true;
     		}
     		else
     		{
     			// wait or reset
     		}
     	}
        
        return true;
}


bool Npc :: jumpTracking()
{
     	if (ship->getNavigator()->checkEchievement() == true)
     	{
                jumpEvent();
                return true;
     	}
     	
     	return false;
}

bool Npc :: grabTracking()
{
        for (unsigned int i = 0; i < ship->grapple_slot.getGrappleEquipment()->target_vec.size(); i++)
        {
        	ship->grapple_slot.getGrappleEquipment()->target_vec[i]->externalManipulation(ship->getPoints()->getCenter());
        }        
}



void Npc:: jumpEvent()
{
        printf("npc id = %i, jumpEvent()\n", data_id.id);
	ship->jumpEvent();
}


void Npc:: dockEvent()
{
        printf("npc id = %i, dockEvent()\n", data_id.id);
	ship->dockEvent();
}








Planet* Npc :: getPlanetForDocking()
{
     	printf("npc_id = %i, getPlanetForDocking()\n", data_id.id);

     	Planet* _target_planet = starsystem->getClosestPlanet(ship->getPoints()->getCenter());  // improove
     	return _target_planet;
}


StarSystem* Npc :: getCloseSafeStarSystem()
{
 	if (starsystem->getCapturedFlag() == false)
        {
        	return starsystem;
        }
        else
        {
        	StarSystem* _target_starsystem = starsystem;   // HACK, find close safe starsystem instead
		return _target_starsystem;
        }
}



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
     	ship_to_scan = NULL;
     	return true;
}
//// *********** SCANNING ***********

     



Npc* generateNpc(int _race_id, int _subtype_id)
{
	IdData data_id;
    	data_id.id         = g_NPC_ID_GENERATOR.getNextId(); 
    	data_id.type_id    = NPC_ID;
    	data_id.subtype_id = _subtype_id;
    	
       	TextureOb* texOb_face  = g_TEXTURE_MANAGER.returnPointerToRandomFaceTexObWithFolloingAttributes(_race_id);
	Npc* npc = new Npc(_race_id, data_id, texOb_face);
	
	return npc;
}


