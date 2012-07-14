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


Npc::Npc(int id)
{ 
	is_alive = true;
	data_id.id = id;
    	data_id.type_id    = ENTITY::NPC_ID;
    	race_id = NONE_ID;
    	
    	upper_control = false;

    	credits = 1000;   	


        vehicle    = NULL;
    	
    	vehicle_to_scan = NULL;
    	
    	failback_starsystem = NULL;
    	    		
	skill 		= new Skill();          		
        observation 	= new Observation(this);
        state_machine 	= new StateMachine(this);   
        
        ai_model = NULL;     
}
    
/* virtual */
Npc :: ~Npc() 
{
        delete skill;      
        delete observation;
        delete state_machine;        
}  
    
void Npc::MindInKosmoport()
{   		
	if (needsToDo.REPAIR_KORPUS == true)
	{
                vehicle->ExternalRepairEvent();
		needsToDo.REPAIR_KORPUS = false;
	}
	
	// if all things are DONE
	//((Planet*)vehicle->GetDriveComplex()->GetTarget())->GetLand()->AddToLaunchingQueue(this); // improove by adding spacestation
}

void Npc::MindInSpace()
{
	vehicle->GetWeaponComplex()->PrepareWeapons();
	if (vehicle->ableTo.GRAB == true)
	{
        	vehicle->GetGrappleSlot()->GetGrappleEquipment()->ValidateTargets();
        }
        vehicle->SelfRepairEvent();
        // drive work, energy and so on
        
	if (upper_control == false)
	{
        	CheckNeeds();
                
		observation->ObserveAllInSpaceInStatic();          
        
        	if (ai_model)
        	{
			ai_model->UpdateInStatic(this);
		}
      
		if (observation->see.ASTEROID == true)
		{
                	AsteroidScenario();
		}             

       		state_machine->UpdateInStatic();                 
        }

        vehicle->GetDriveComplex()->UpdatePath();
}

void Npc::UpdateInSpace(int time, bool show_effect)
{
        if (time > 0)
        {
       		state_machine->UpdateInDynamic();
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
        vehicle->GetWeaponComplex()->DeactivateAllWeapons();

        vehicle->GetWeaponComplex()->ActivateAllWeapons();
        vehicle->GetWeaponComplex()->SetTarget(observation->visible_ASTEROID_pair_vec[0].object);
                
        //printf("TARGET => ship_id, asteroid id = %i/%i\n", ship->GetId(), sorted_visible_ASTEROID_pList[0]->GetId());
}


Planet* Npc::GetPlanetForDocking()
{
     	Planet* _target_planet = GetStarSystem()->GetClosestPlanet(vehicle->GetPoints().GetCenter());  // improove
     	return _target_planet;
}

StarSystem* Npc::GetClosestStarSystem(bool _captured)
{
       	observation->FindEchievableStarSystemsInStatic(GetStarSystem()->GetGalaxy());
        	
       	StarSystem* _target_starsystem = observation->GetClosestStarSystem(_captured);   
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
        	if (vehicle->GetProtectionComplex()->GetProtectorSlot()->GetEquipedStatus() == true)
        	{
           		if (this->vehicle->GetScanerSlot()->GetScanerEquipment()->GetScan() >= vehicle->GetProtectionComplex()->GetProtectorSlot()->GetProtectorEquipment()->GetProtection()) 
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
    	info.addNameStr("id:");           info.addValueStr( int2str(data_id.id)  );
    	info.addNameStr("race:");   	  info.addValueStr( returnRaceStringByRaceId(race_id) ); 

	if (vehicle->ableTo.GRAB == true)
	{
		std::string grab_str = vehicle->GetGrappleSlot()->GetGrappleEquipment()->GetTargetStr();
		if (grab_str.size() > 0)
		{
			info.addNameStr("grab_id:");   		info.addValueStr( grab_str ); 
		}
	}
    	if (state_machine->GetMacroTaskManager()->GetScenario() != NULL)
    	{ 	
    	info.addNameStr("macro_task_main:");   	info.addValueStr( state_machine->GetMacroTaskManager()->GetScenario()->GetDescription(this) ); 
    	}
    	
    	if (state_machine->GetMicroTaskManager()->GetScenario() != NULL)
    	{ 	
    	info.addNameStr("micro_task:");   	info.addValueStr( state_machine->GetMicroTaskManager()->GetScenario()->GetDescription(this)  ); 
    	}
}

void Npc::RenderInfo(const vec2f& center)
{ 
	UpdateInfo();
     	drawInfoIn2Column(&info.title_list, &info.value_list, center.x, center.y);
}
                   
   
void Npc::SaveData(boost::property_tree::ptree& save_ptree) const
{
	std::string root = "npc."+int2str(data_id.id)+".";
	SaveDataUniqueBase(save_ptree, root);
	SaveDataUniqueNpc(save_ptree, root);	
}		

void Npc::LoadData(const boost::property_tree::ptree& load_ptree)
{
	LoadDataUniqueBase(load_ptree);
	LoadDataUniqueNpc(load_ptree);	   
}        

void Npc::ResolveData()
{
	ResolveDataUniqueBase();
	ResolveDataUniqueNpc();	
}
  
void Npc::SaveDataUniqueNpc(boost::property_tree::ptree& save_ptree, const std::string& root) const	
{
	save_ptree.put(root+"is_alive", is_alive);
	save_ptree.put(root+"race_id", race_id);
        save_ptree.put(root+"unresolved.vehicle_id", vehicle->GetId());
	skill->SaveData(save_ptree, root);
}

void Npc::LoadDataUniqueNpc(const boost::property_tree::ptree& load_ptree)
{
	is_alive = load_ptree.get<bool>("is_alive");
	race_id  = load_ptree.get<int>("race_id");
	data_unresolved_npc.vehicle_id = load_ptree.get<int>("unresolved.vehicle_id");

	skill->LoadData(load_ptree.get_child("skill"));
}

void Npc::ResolveDataUniqueNpc()
{
        ((Vehicle*)EntityManager::Instance().GetEntityById(data_unresolved_npc.vehicle_id))->BindOwnerNpc(this);

	skill->ResolveData();
}		
