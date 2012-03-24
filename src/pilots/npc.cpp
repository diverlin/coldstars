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

void Npc :: setLand(LandBase* land)   		        { this->land = land; }
void Npc :: setScanTarget(Vehicle* vehicle_to_scan)     { this->vehicle_to_scan = vehicle_to_scan; }
void Npc :: setUpperControl(bool upper_control)         { this->upper_control = upper_control; }


int Npc :: getRaceId() const	   { return race_id; }
StarSystem* Npc :: getFailBackStarSystem() const { return failback_starsystem; }
Vehicle* Npc :: getVehicle()       { return vehicle; }
Skill* Npc :: getSkill() 	   { return skill; }	
Vehicle* Npc :: getScanTarget()	   { return vehicle_to_scan; }	
Observation* Npc :: getObservation() const { return observation; }


unsigned long int Npc :: getCredits() const { return credits; }   
StateMachine* Npc :: getStateMachine() {return state_machine; }

LandBase* Npc :: getLand() const { return land; }
   		
void Npc :: bind(Vehicle* vehicle) 	           
{ 
	this->vehicle = vehicle; 
	vehicle->SetNpc(this); 
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


        vehicle    = NULL;
    	land       = NULL;
    	starsystem = NULL;
    	
    	vehicle_to_scan = NULL;
    	
    	failback_starsystem = NULL;
    	    		
	skill = new Skill();
        
   		
        observation = new Observation(this);

        state_machine = new StateMachine(this);        
        
        // depending on type        
        ai_model = NULL;
        if (( race_id == RACE_6_ID) or ( race_id == RACE_7_ID) )
        {
                ai_model = g_AIMODEL_CONQUEROR;
        }
        else
        {
       		ai_model = g_AIMODEL_RANGER;        
        }
}
    
Npc :: ~Npc() /* virtual */
{
        delete skill;
      
        delete observation;

        delete state_machine;        
}  
    


void Npc :: thinkCommon_inKosmoport_inStatic()
{   		
	if (needsToDo.REPAIR_KORPUS == true)
	{
                vehicle->ExternalRepairEvent();
		needsToDo.REPAIR_KORPUS = false;
	}
	
	// if all things are DONE
	((Planet*)vehicle->GetDriveComplex()->getTarget())->getLand()->addToLaunchingQueue(this); // improove by adding spacestation
}

void Npc :: thinkCommon_inLand_inStatic()
{}




void Npc :: update_inSpace_inStatic()
{
	vehicle->GetWeaponComplex()->prepareWeapons();
        vehicle->GetGrappleSlot()->getGrappleEquipment()->validateTargets();
        vehicle->SelfRepairEvent();
        // drive work, energy and so on
               	     		
	if (upper_control == false)
	{
        	checkNeeds();
                
		observation->observeAll_inSpace_inStatic();          
        
        	// place model here
        	if (ai_model)
        	{
			ai_model->update_inStatic(this);
		}
		//
        
       
		if (observation->see.ASTEROID == true)
		{
                	asteroidScenario();
		}
             

       		state_machine->update_inStatic();                 
        }

        vehicle->GetDriveComplex()->update_inSpace_inStatic();
}


void Npc :: update_inSpace(int time, bool show_effect)
{
        //	macroTask_stateMachine->update_inDynamic(); // is it needed ?
        if (time > 0)
        {
       		state_machine->update_inDynamic();
       	}
}     	





void Npc :: checkNeeds()
{
        if (vehicle->getArmor() < 0.5*vehicle->data_korpus.armor)   // move to ship
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
        vehicle->GetWeaponComplex()->weapon_selector.setAll(false);
        vehicle->GetWeaponComplex()->selectWeapons();
        vehicle->GetWeaponComplex()->resetDeselectedWeaponTargets();

        vehicle->GetWeaponComplex()->weapon_selector.setAll(true);
        vehicle->GetWeaponComplex()->selectWeapons();
        vehicle->GetWeaponComplex()->setTarget(observation->visible_ASTEROID_vec[0].asteroid);
                
        //printf("TARGET => ship_id, asteroid id = %i/%i\n", ship->getId(), sorted_visible_ASTEROID_pList[0]->getId());
}




void Npc:: jumpEvent()
{
	vehicle->HyperJumpEvent();
}


void Npc:: dockEvent()
{
	vehicle->DockingEvent();
}








Planet* Npc :: getPlanetForDocking()
{
     	Planet* _target_planet = starsystem->getClosestPlanet(vehicle->getPoints()->getCenter());  // improove
     	return _target_planet;
}


StarSystem* Npc :: getClosestStarSystem(bool _captured)
{
       	observation->findEchievableStarSystems_inStatic(starsystem->getGalaxy());
        	
       	StarSystem* _target_starsystem = observation->getClosestStarSystem(_captured);   
	return _target_starsystem;
}


//// *********** SCANNING ***********
bool Npc :: checkPossibilityToScan(Vehicle* vehicle)
{
     	if (this->vehicle->getId() == vehicle->getId())    // selfscan is possible all time
     	{
        	return true;
        }
 
     	if (this->vehicle->ableTo.SCAN == true) 
     	{
        	if (vehicle->GetProtectorSlot()->getEquipedStatus() == true)
        	{
           		if (this->vehicle->GetScanerSlot()->getScanerEquipment()->getScan() >= vehicle->GetProtectorSlot()->getProtectorEquipment()->getProtection()) 
              		{
              			return true;
              		}
              	}
              	else
              	{
              		return true;
              	}
        }

     	return false;
}


bool Npc :: scanProceeding()
{
     	return true;
}

void Npc :: resetScanTarget() { vehicle_to_scan = NULL; }
//// *********** SCANNING ***********




void Npc :: updateInfo()
{
	info.clear();

    	info.addTitleStr("NPC");
    	info.addNameStr("id/ss_id:");           info.addValueStr( int2str(data_id.id) + " / "  + int2str(starsystem->getId()) );
    	info.addNameStr("race:");   		info.addValueStr( returnRaceStringByRaceId(texOb->race_id) ); 

	if (vehicle->ableTo.GRAB == true)
	{
		std::string grab_str = vehicle->GetGrappleSlot()->getGrappleEquipment()->getTargetStr();
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
     	drawInfoIn2Column(&info.title_list, &info.value_list, _pos_x + 190, _pos_y, _offset_x, _offset_y);
}
     
void Npc :: postDeathUniqueEvent(bool) /* virtual */
{}



Npc* getNewNpc(int _race_id, int _subtype_id)
{
	IdData data_id;
    	data_id.id         = g_ID_GENERATOR.getNextId(); 
    	data_id.type_id    = NPC_ID;
    	data_id.subtype_id = _subtype_id;
    	
    	LifeData data_life;
    	
       	TextureOb* texOb_face  = g_TEXTURE_MANAGER.getRandomFaceTexObWithFolloingAttributes(_race_id);
	Npc* npc = new Npc(_race_id, data_id, data_life, texOb_face);
	
	GetEntityManager().RegisterEntity(npc);
	    	
	return npc;
}


