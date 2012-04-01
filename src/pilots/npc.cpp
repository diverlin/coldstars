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
   		
void Npc::Bind(Vehicle* vehicle) 	           
{ 
	this->vehicle = vehicle; 
	vehicle->SetNpc(this); 
} 	

void Npc::IncreaseCredits(int credits) { this->credits += credits; }
void Npc::DecreaseCredits(int credits) { this->credits -= credits; }

		
Npc::Npc(int _race_id, IdData _data_id, LifeData _data_life, TextureOb* _texOb)
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
        if (( race_id == RACE::R6_ID) or ( race_id == RACE::R7_ID) )
        {
                ai_model = AIMODEL_CONQUEROR;
        }
        else
        {
       		ai_model = AIMODEL_RANGER;        
        }
}
    
Npc :: ~Npc() /* virtual */
{
        delete skill;
      
        delete observation;

        delete state_machine;        
}  
    
void Npc::ThinkCommon_inKosmoport_inStatic()
{   		
	if (needsToDo.REPAIR_KORPUS == true)
	{
                vehicle->ExternalRepairEvent();
		needsToDo.REPAIR_KORPUS = false;
	}
	
	// if all things are DONE
	((Planet*)vehicle->GetDriveComplex()->getTarget())->GetLand()->addToLaunchingQueue(this); // improove by adding spacestation
}

void Npc::ThinkCommon_inLand_inStatic()
{}

void Npc::Update_inSpace_inStatic()
{
	vehicle->GetWeaponComplex()->PrepareWeapons();
        vehicle->GetGrappleSlot()->GetGrappleEquipment()->validateTargets();
        vehicle->SelfRepairEvent();
        // drive work, energy and so on
               	     		
	if (upper_control == false)
	{
        	CheckNeeds();
                
		observation->observeAll_inSpace_inStatic();          
        
        	// place model here
        	if (ai_model)
        	{
			ai_model->update_inStatic(this);
		}
		//
        
       
		if (observation->see.ASTEROID == true)
		{
                	AsteroidScenario();
		}
             

       		state_machine->update_inStatic();                 
        }

        vehicle->GetDriveComplex()->Update_inSpace_inStatic();
}

void Npc::Update_inSpace(int time, bool show_effect)
{
        //	macroTask_stateMachine->update_inDynamic(); // is it needed ?
        if (time > 0)
        {
       		state_machine->update_inDynamic();
       	}
}     	

void Npc::CheckNeeds()
{
        if (vehicle->GetArmor() < 0.5*vehicle->data_korpus.armor)   // move to ship
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
        failback_starsystem = GetClosestStarSystem(false);
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

void Npc::AsteroidScenario()
{
        vehicle->GetWeaponComplex()->weapon_selector.setAll(false);
        vehicle->GetWeaponComplex()->SelectWeapons();
        vehicle->GetWeaponComplex()->ResetDeselectedWeaponTargets();

        vehicle->GetWeaponComplex()->weapon_selector.setAll(true);
        vehicle->GetWeaponComplex()->SelectWeapons();
        vehicle->GetWeaponComplex()->SetTarget(observation->visible_ASTEROID_vec[0].asteroid);
                
        //printf("TARGET => ship_id, asteroid id = %i/%i\n", ship->GetId(), sorted_visible_ASTEROID_pList[0]->GetId());
}


Planet* Npc::GetPlanetForDocking()
{
     	Planet* _target_planet = starsystem->GetClosestPlanet(vehicle->GetPoints().getCenter());  // improove
     	return _target_planet;
}

StarSystem* Npc::GetClosestStarSystem(bool _captured)
{
       	observation->findEchievableStarSystems_inStatic(starsystem->GetGalaxy());
        	
       	StarSystem* _target_starsystem = observation->getClosestStarSystem(_captured);   
	return _target_starsystem;
}


//// *********** SCANNING ***********
bool Npc::CheckPossibilityToScan(Vehicle* vehicle)
{
     	if (this->vehicle->GetId() == vehicle->GetId())    // selfscan is possible all time
     	{
        	return true;
        }
 
     	if (this->vehicle->ableTo.SCAN == true) 
     	{
        	if (vehicle->GetProtectionComplex()->GetProtectorSlot().GetEquipedStatus() == true)
        	{
           		if (this->vehicle->GetScanerSlot()->GetScanerEquipment()->getScan() >= vehicle->GetProtectionComplex()->GetProtectorSlot().GetProtectorEquipment()->getProtection()) 
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


void Npc::ResetScanTarget() { vehicle_to_scan = NULL; }
//// *********** SCANNING ***********


void Npc::UpdateInfo()
{
	info.clear();

    	info.addTitleStr("NPC");
    	info.addNameStr("id/ss_id:");           info.addValueStr( int2str(data_id.id) + " / "  + int2str(starsystem->GetId()) );
    	info.addNameStr("race:");   		info.addValueStr( returnRaceStringByRaceId(texOb->race_id) ); 

	if (vehicle->ableTo.GRAB == true)
	{
		std::string grab_str = vehicle->GetGrappleSlot()->GetGrappleEquipment()->getTargetStr();
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



void Npc::RenderInfo(float _pos_x, float _pos_y, float _offset_x, float _offset_y)
{  
        UpdateInfo();
     	drawInfoIn2Column(&info.title_list, &info.value_list, _pos_x + 190, _pos_y, _offset_x, _offset_y);
}
     
void Npc :: PostDeathUniqueEvent(bool) /* virtual */
{}


Npc* getNewNpc(int _race_id, int _subtype_id)
{
	IdData data_id;
    	data_id.id         = g_ID_GENERATOR.getNextId(); 
    	data_id.type_id    = ENTITY::NPC_ID;
    	data_id.subtype_id = _subtype_id;
    	
    	LifeData data_life;
    	
       	TextureOb* texOb_face  = g_TEXTURE_MANAGER.getRandomFaceTexObWithFolloingAttributes(_race_id);
	Npc* npc = new Npc(_race_id, data_id, data_life, texOb_face);
	
	GetEntityManager().RegisterEntity(npc);
	    	
	return npc;
}


