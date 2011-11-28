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

void Npc :: setGarbageReady(bool _garbage_ready)   { data_life.garbage_ready = _garbage_ready; }
void Npc :: setAlive(bool _alive) 		   { data_life.is_alive = _alive; }
void Npc :: setStarSystem(StarSystem* _starsystem) { starsystem = _starsystem; }
void Npc :: setKosmoport(Kosmoport* _kosmoport)    { kosmoport = _kosmoport; }
void Npc :: setLand(Land* _land)   		   { land = _land; }
void Npc :: setScanTarget(Ship* _ship)             { ship_to_scan = _ship; }
void Npc :: setPlaceTypeId(int _place_type_id)     { place_type_id = _place_type_id; /*if (ship != NULL) ship->setPlaceTypeId(_place_type_id); */ }
void Npc :: setControlledByPlayer(bool _controlled_by_player) { controlled_by_player = _controlled_by_player; }

bool Npc :: getGarbageReady() const { return data_life.garbage_ready; }   		
bool Npc :: getAlive() const 	   { return data_life.is_alive; }
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

QuestObject* Npc :: getQuestOb()   { return questOb; }
QuestObject* Npc :: getTaskOb()   { return taskOb; }

bool Npc :: getControlledByPlayer() const { return controlled_by_player; }
unsigned long int Npc :: getCredits() const { return credits; }   
StateMachine* Npc :: getStateMachine() {return state_machine; }

void Npc :: bind(Ship* _ship) 	           
{ 
	ship = _ship; 
	ship->setNpc(this); 
	ship->setStarSystem(starsystem);  //???	
} 	

void Npc :: increaseCredits(int _credits) { credits += _credits; }
void Npc :: decreaseCredits(int _credits) { credits -= _credits; }

		
Npc :: Npc(int _race_id, IdData _data_id, LifeData _data_life, TextureOb* _texOb)
{ 
   	data_id = _data_id;
   	data_life = _data_life;	

      
    	texOb = _texOb;

    	race_id = _race_id;
    	
    	controlled_by_player = false;

    	credits = 1000;
   	
   	
	place_type_id = NONE_ID; 


        ship       = NULL;
    	kosmoport  = NULL;
    	land       = NULL;
    	starsystem = NULL;
    		
	skill = new Skill();

	questOb        = new QuestObject();
        taskOb 	       = new QuestObject();
        
        observation = new Observation(this);
        
        state_machine = new StateMachine(this);
}
    
Npc :: ~Npc()
{
        delete skill;
      
	delete questOb;
	delete taskOb;
        
        delete observation;
        
        delete state_machine;
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
        
       
        
        //if ( (observation->see.MINERAL == false) or (ship->ableTo.GRAB == false) )
        //{
                //if (grabOb->getActionId() == GRABBING_TASK_ID)
                //{
                        //grabOb->reset();
                //}
        //}
        
        ship->grapple_slot.getGrappleEquipment()->validationTargets(); 
                

	questOb->validation();
       
        if ( (race_id != RACE_6_ID) or (race_id != RACE_7_ID) )
        {
                checkNeeds();    
        }
       
       	state_machine
        ////// generator
        //if ( (observation->see.MINERAL == true) and (ship->ableTo.GRAB == true) )
        //{
                //if (grabOb->getActionId() != GRABBING_TASK_ID)                
                //{
                	//printf("npc_id =%i, grabOb set GRABBING_TASK_ID\n", data_id.id);
                        //grabOb->setTask(starsystem, GRABBING_TASK_ID);
                //}
        //}
       
  
        
        //if (selfcareOb->getExist() == false)
	//{
	        //if ( (needsToDo.REPAIR_KORPUS == true) and (selfcareOb->getActionId() != SELFCARE_TASK_ID) )
	        //{
                	////generateSelfCare();
                //}
        //}
         
       	//if (questOb->getExist() == false)
	//{
                //generateQuest();
        //}
        ////
        
	if (observation->see.ASTEROID == true)
	{
                asteroidScenario();
	}
                        
             
        //if ( (grabOb->getExist() == true) and (busy == false) )
        //{
                //if (grabOb->getActionId() == GRABBING_TASK_ID)
                //{
                        ////grabScenario();                        
                        //busy = true;
                //}
        //}

        
        //if ( (selfcareOb->getExist() == true) and (busy == false) )
        //{                            
                //selfcareResolver(); 
                //busy = true;   
        //}
        

        if ( (questOb->getExist() == true) and (busy == false) )
        {
                questResolver();
                busy = true;  
        }
}


void Npc :: generateSelfCare()
{
        //selfcareOb->setTask(getCloseSafeStarSystem(), SELFCARE_TASK_ID); 
}



void Npc :: generateQuest()
{
        if ((race_id != RACE_6_ID) or (race_id != RACE_7_ID))
        {
                //destroyShipQuestGenerator(this);
                //liberationStarSystemQuestGenerator(this);
        }
        else
        {
                //questEvilGenerator(this);    
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
        ship->setWeaponsTarget(observation->visible_ASTEROID_vec[0].asteroid);
                
        //printf("TARGET => ship_id, asteroid id = %i/%i\n", ship->getId(), sorted_visible_ASTEROID_pList[0]->getId());
}


//void Npc :: grabScenario()
//{
        //if ( starsystem->getId() != grabOb->getStarSystem()->getId() )
	//{
		//if (ship->getNavigator()->getTargetTypeId() != STARSYSTEM_ID)
		//{
                        //ship->getNavigator()->forceJump(grabOb->getStarSystem()); 
                        
			//printf("npc_id =%i navigate StarSystem id =%i, reason = GRAB HUNTING\n", data_id.id, grabOb->getStarSystem()->getId() );   // debug
                //}
       	//}
        //else
        //{        
        	//vec2f offset_target = getRandVec(30, 60);
                //ship->getNavigator()->setStaticTargetCoords(observation->visible_MINERAL_vec[0].mineral->getPoints()->getCenter() + offset_target);
                
                //// debug
                ////observation->printVisibleMineralInformation();
                //// debug
                
                //for (unsigned int i = 0; i < observation->visible_MINERAL_vec.size(); i++)
                //{                	
                        //if (observation->visible_MINERAL_vec[i].dist < ship->grapple_slot.getGrappleEquipment()->getRadius())
                        //{                                       
                                //ship->grapple_slot.getGrappleEquipment()->add(observation->visible_MINERAL_vec[i].mineral);
                        //}
                        //else
                        //{
                                //break;
                        //}
                //}
        //}
//}


//void Npc :: destroyShipQuestScenario()
//{
	//if ( starsystem->getId() != questOb->getStarSystem()->getId() )
	//{
		//if (ship->getNavigator()->getTargetTypeId() != STARSYSTEM_ID)
		//{                               
       			//ship->getNavigator()->forceJump(questOb->getStarSystem()); 
       			
			//printf("npc_id =%i navigate StarSystem id =%i, reason = DESTROY SHIP HUNTING\n", data_id.id, questOb->getStarSystem()->getId() );   // debug
       		//}
       	//}
	//else
	//{
		//ship->weapon_selector.setAll(true);
		//ship->selectWeapons();
		//ship->setWeaponsTarget(questOb->getNpc()->getShip());
                      
                //int _dist_close = questOb->getNpc()->getShip()->getCollisionRadius();  
                //int _dist_far = 2 * _dist_close;
                                                
		//ship->getNavigator()->setTarget(questOb->getNpc()->getShip(), getRandInt(_dist_close, _dist_far) );
	//}
//}


//void Npc :: liberationStarSystemQuestScenario()
//{
	//if ( starsystem->getId() != questOb->getStarSystem()->getId() )
	//{
		//if (ship->getNavigator()->getTargetTypeId() != STARSYSTEM_ID)
		//{                         
       			//ship->getNavigator()->forceJump(questOb->getStarSystem());
       			
			//printf("npc_id =%i navigate StarSystem id =%i, reason = LIBERATION THIS SYSTEM\n", data_id.id, questOb->getStarSystem()->getId() );   // debug
       		//}
	//}
	//else
	//{
		//if (subQuestOb->getActionId() != DESTROY_SHIP_QUEST_ID)
		//{
			//subQuestOb->setTask(questOb->getStarSystem()->getEvilNpc(ship->getPoints()->getCenter()), DESTROY_SHIP_QUEST_ID);
		//}

		//ship->weapon_selector.setAll(true);
		//ship->selectWeapons();
		//ship->setWeaponsTarget(subQuestOb->getNpc()->getShip());
                      
                //int _dist_close = subQuestOb->getNpc()->getShip()->getCollisionRadius();  
                //int _dist_far = 2 * _dist_close;
                                                
		//ship->getNavigator()->setTarget(subQuestOb->getNpc()->getShip(), getRandInt(_dist_close, _dist_far) );
	//}
//}


//void Npc :: selfcareResolver()
//{       
       	//if (selfcareOb->getStarSystem()->getId() != starsystem->getId())
	//{
		//if (ship->getNavigator()->getTargetTypeId() != STARSYSTEM_ID)
		//{       
       			//ship->getNavigator()->forceJump(selfcareOb->getStarSystem());
       			
       			//printf("npc_id =%i navigate StarSystem id =%i, reason = SELF_CARE\n", data_id.id, selfcareOb->getStarSystem()->getId() );   // debug
       		//}
        //}
        //else
        //{
		//if (subSelfcareOb->getActionId() != LANDING_TASK_ID)
		//{
			//Planet* _target_planet = getPlanetForDocking();  // depending on purpouse
			//subSelfcareOb->setTask(_target_planet, LANDING_TASK_ID);
		//}
		//else
		//{
        		//ship->getNavigator()->setTarget(subSelfcareOb->getPlanet(), DOCKING_NAVIGATOR_ACTION_ID);
		//}              
        //}
//}


void Npc :: questResolver()
{
	if (questOb->getObTypeId() == NPC_ID)
	{
		//if (questOb->getActionId() == DESTROY_SHIP_QUEST_ID)
		//{
			//destroyShipQuestScenario();
		//}
	}

	if (questOb->getObTypeId() == STARSYSTEM_ID)
	{	
		//if (questOb->getActionId() == LIBERATION_STARSYSTEM_QUEST_ID)
		//{ 
			//liberationStarSystemQuestScenario();
		//}
	}
}




void Npc :: update_inDynamic_inSpace()
{
     	//printf("npc_id = %i update_inDynamic_inSpace \n", id);
     	if (ship->getNavigator()->getTargetTypeId() == STARSYSTEM_ID)
     	{
		//jumpTracking();
	}
	
	if (ship->getNavigator()->getTargetTypeId() == PLANET_ID)
	{
	        //dockTracking();
	}

	if (ship->ableTo.GRAB == true) // think how to optimize this
	{
       		//grabTracking();        	
        }
}





//bool Npc :: dockTracking()
//{
     	//if (ship->getNavigator()->checkEchievement() == true)
     	//{
     		//if (ship->getNavigator()->getDockingPermission() == true)
     		//{
     		     	//dockEvent();
                        //return true;
     		//}
     		//else
     		//{
     			//// wait or reset
     		//}
     	//}
        
        //return true;
//}


//bool Npc :: jumpTracking()
//{
     	//if (ship->getNavigator()->checkEchievement() == true)
     	//{
                //jumpEvent();
                //return true;
     	//}
     	
     	//return false;
//}

//void Npc :: grabTracking()
//{
        //ship->grapple_slot.getGrappleEquipment()->validationTargets();  
                
        //for (unsigned int i = 0; i < ship->grapple_slot.getGrappleEquipment()->target_vec.size(); i++)
        //{	//printf("blablabla\n");
                //if (ship->grapple_slot.getGrappleEquipment()->target_vec[i]->getValid() == true)
                //{
                	////printf("blablabla\n");
                       	//ship->grapple_slot.getGrappleEquipment()->target_vec[i]->moveExternalyToPosition(ship->getPoints()->getCenter());        	
       	
        		//float dist = distBetweenPoints(ship->getPoints()->getCenter(), *ship->grapple_slot.getGrappleEquipment()->target_vec[i]->getpCenter() ); 
        		//if (dist < ship->getCollisionRadius()/10)
        		//{
        			//if (ship->grapple_slot.getGrappleEquipment()->target_vec[i]->getObTypeId() == MINERAL_ID)
        			//{
        				//GoodsPack* _goodsPack = createGoodsPack(MINERAL_ID, vec2f (0, 0));
        				//_goodsPack->increase(ship->grapple_slot.getGrappleEquipment()->target_vec[i]->getMineral()->getMass());
        				//ItemSlot* _slot = ship->getEmptyOtsecSlot();
        				//if (_slot != NULL)
        				//{
        					//_slot->insertGoods(_goodsPack);
        					//starsystem->killMineralById(ship->grapple_slot.getGrappleEquipment()->target_vec[i]->getObId());   
        					//ship->grapple_slot.getGrappleEquipment()->target_vec[i]->reset();
        				//}			
        			//}
        			
        			//if (ship->grapple_slot.getGrappleEquipment()->target_vec[i]->getObTypeId() == CONTAINER_ID)
        			//{
        				//starsystem->removeContainer(ship->grapple_slot.getGrappleEquipment()->target_vec[i]->getObId());
        			//}
        		//}
        	//}
        //}                 
        
//}



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


StarSystem* Npc :: getClosestFriendlyStarSystem()
{
 	if (starsystem->getCaptured() == false)
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




void Npc :: updateInfo()
{
	info.clear();

    	info.addTitleStr("NPC");
    	info.addNameStr("id/ss_id:");           info.addValueStr( int2str(data_id.id) + " / "  + int2str(starsystem->getId()) );
    	info.addNameStr("race:");   		info.addValueStr( returnRaceStringByRaceId(texOb->race_id) ); 
    	
    	//if (grabOb->getExist() == true)
    	//{   	
    	//info.addNameStr("grabOb:");   		info.addValueStr( ship->grapple_slot.getGrappleEquipment()->getTargetStr() ); 
    	//}
    	//if (selfcareOb->getExist() == true)
    	//{   	
    	//info.addNameStr("selfcareOb:");   	info.addValueStr( "" ); 
    	//}
    	if (questOb->getExist() == true)
    	{   	
    	info.addNameStr("questOb:");   		info.addValueStr( "" ); 
    	}
}



void Npc :: renderInfo(float _pos_x, float _pos_y, float _offset_x, float _offset_y)
{  
        updateInfo();
     	drawInfoIn2Column(&info.title_list, &info.value_list, _pos_x + 190, _pos_y);
}
     



Npc* generateNpc(int _race_id, int _subtype_id)
{
	IdData data_id;
    	data_id.id         = g_NPC_ID_GENERATOR.getNextId(); 
    	data_id.type_id    = NPC_ID;
    	data_id.subtype_id = _subtype_id;
    	
    	LifeData data_life;
    	
       	TextureOb* texOb_face  = g_TEXTURE_MANAGER.returnPointerToRandomFaceTexObWithFolloingAttributes(_race_id);
	Npc* npc = new Npc(_race_id, data_id, data_life, texOb_face);
	
	return npc;
}


