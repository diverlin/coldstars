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
void Npc :: setUpperControl(bool upper_control) { this->upper_control = upper_control; }

bool Npc :: getGarbageReady() const { return data_life.garbage_ready; }   		
bool Npc :: getAlive() const 	   { return data_life.is_alive; }
int Npc :: getId() const	   { return data_id.id; }
int Npc :: getTypeId() const	   { return data_id.type_id; }
int  Npc :: getSubTypeId() const   { return data_id.subtype_id; }
int Npc :: getRaceId() const	   { return race_id; }
StarSystem* Npc :: getStarSystem() const { return starsystem; }
StarSystem* Npc :: getFailBackStarSystem() const { return failback_starsystem; }
Kosmoport* Npc :: getKosmoport()   { return kosmoport; }
Ship* Npc :: getShip() 	 	   { return ship; }
Skill* Npc :: getSkill() 	   { return skill; }	
Ship* Npc :: getScanShip()	   { return ship_to_scan; }	
int Npc :: getPlaceTypeId() const  { return place_type_id; }
Observation* Npc :: getObservation() const { return observation; }


//MacroTaskHolder* Npc :: getMacroTaskMain() const { return macro_task_main; }
//MacroTaskHolder* Npc :: getMacroTaskSelf() const { return macro_task_self; }
//MicroTaskHolder* Npc :: getMicroTask() const { return micro_task; }
   		
//bool Npc :: getControlledByPlayer() const { return controlled_by_player; }
unsigned long int Npc :: getCredits() const { return credits; }   
StateMachine* Npc :: getStateMachine() {return state_machine; }



Points* Npc :: getPoints() const    { return ship->getPoints(); }
bool* Npc :: getpAlive()       { return &data_life.is_alive; }
int* Npc :: getpPlaceTypeId()  { return &place_type_id; }
float Npc :: getCollisionRadius() { return ship->getCollisionRadius(); }
   		
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
    	
    	upper_control = false;

    	credits = 1000;
   	
   	
	place_type_id = NONE_ID; 


        ship       = NULL;
    	kosmoport  = NULL;
    	land       = NULL;
    	starsystem = NULL;
    	
    	failback_starsystem = NULL;
    	    		
	skill = new Skill();
        
        //macro_task_main = new MacroTaskHolder();
   	//macro_task_self = new MacroTaskHolder();
  	//micro_task = new MicroTaskHolder();
   		
        observation = new Observation(this);

        state_machine = new StateMachine(this);        
        
        // depending on type        
        if (( race_id == RACE_6_ID) or ( race_id == RACE_7_ID) )
        {
                ai_model = g_AIMODEL_CONQUEROR;
        }
        else
        {
       		ai_model = g_AIMODEL_RANGER;        
        }
}
    
Npc :: ~Npc()
{
        delete skill;
      
        delete observation;

        delete state_machine;        
}  
    


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




void Npc :: update_inSpace_inStatic()
{
	ship->getWeaponComplex()->prepareWeapons();
        ship->grapple_slot.getGrappleEquipment()->validationTargets();
        ship->droidRepair();
        // drive work, energy and so on
               	     		
	if (upper_control == false)
	{
        	checkNeeds();
                
		observation->observeAll_inSpace_inStatic();  
         
        
        	// place model here
		ai_model->update_inStatic(this);
		//
        
       
		if (observation->see.ASTEROID == true)
		{
                	asteroidScenario();
		}
             

       		state_machine->update_inStatic();                 
        }

        ship->getNavigator()->update_inSpace_inStatic();
}


void Npc :: update_inSpace_inDynamic()
{
        //	macroTask_stateMachine->update_inDynamic(); // is it needed ?
       	state_machine->update_inDynamic();
}     	





void Npc :: checkNeeds()
{
        if (ship->getArmor() < 0.5*ship->data_korpus.armor)   // move to ship
	{
		needsToDo.REPAIR_KORPUS = true;
		//if (quest_self != g_QUEST_SELF_SAFETY)
		//{
			//quest_self = g_QUEST_SELF_SAFETY;
		//}
	}
        else
        {
		needsToDo.REPAIR_KORPUS = false;                
        }

        // check conditions of all items here and set REPAIR_EQUIPMENT flag accordingly
        needsToDo.REPAIR_EQUIPMENT = false;
        
        // checkhjump
        failback_starsystem = getClosestStarSystem(false);
        if (failback_starsystem != NULL)
        {
   		needsToDo.GET_FUEL = false;
   	}
   	else
   	{
   	   	needsToDo.GET_FUEL = true;
   	}
        
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
        ship->getWeaponComplex()->weapon_selector.setAll(false);
        ship->getWeaponComplex()->selectWeapons();
        ship->getWeaponComplex()->resetDeselectedWeaponTargets();

        ship->getWeaponComplex()->weapon_selector.setAll(true);
        ship->getWeaponComplex()->selectWeapons();
        ship->getWeaponComplex()->setWeaponsTarget(observation->visible_ASTEROID_vec[0].asteroid);
                
        //printf("TARGET => ship_id, asteroid id = %i/%i\n", ship->getId(), sorted_visible_ASTEROID_pList[0]->getId());
}




void Npc:: jumpEvent()
{
	ship->jumpEvent();
}


void Npc:: dockEvent()
{
	ship->dockEvent();
}








Planet* Npc :: getPlanetForDocking()
{
     	Planet* _target_planet = starsystem->getClosestPlanet(ship->getPoints()->getCenter());  // improove
     	return _target_planet;
}


StarSystem* Npc :: getClosestStarSystem(bool _captured)
{
       	observation->findEchievableStarSystems_inStatic();
        	
       	StarSystem* _target_starsystem = observation->getClosestStarSystem(_captured);   
	return _target_starsystem;
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

	if (ship->ableTo.GRAB == true)
	{
		std::string grab_str = ship->grapple_slot.getGrappleEquipment()->getTargetStr();
		if (grab_str.size() > 0)
		{
			info.addNameStr("grab_id:");   		info.addValueStr( grab_str ); 
		}
	}
    	if (state_machine->getCurrentMacroTask()->getScenario() != NULL)
    	{ 	
    	info.addNameStr("macro_task_main:");   	info.addValueStr( state_machine->getCurrentMacroTask()->getScenario()->getDescription(this) ); 
    	}
    	
    	if (state_machine->getCurrentMicroTask()->getScenario() != NULL)
    	{ 	
    	info.addNameStr("micro_task:");   	info.addValueStr( state_machine->getCurrentMicroTask()->getScenario()->getDescription(this)  ); 
    	}
}



void Npc :: renderInfo(float _pos_x, float _pos_y, float _offset_x, float _offset_y)
{  
        updateInfo();
     	drawInfoIn2Column(&info.title_list, &info.value_list, _pos_x + 190, _pos_y);
}
     



Npc* getNewNpc(int _race_id, int _subtype_id)
{
	IdData data_id;
    	data_id.id         = g_NPC_ID_GENERATOR.getNextId(); 
    	data_id.type_id    = NPC_ID;
    	data_id.subtype_id = _subtype_id;
    	
    	LifeData data_life;
    	
       	TextureOb* texOb_face  = g_TEXTURE_MANAGER.getRandomFaceTexObWithFolloingAttributes(_race_id);
	Npc* npc = new Npc(_race_id, data_id, data_life, texOb_face);
	
	return npc;
}


