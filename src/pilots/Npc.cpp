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

#include "Npc.hpp"
#include "../spaceobjects/Vehicle.hpp"
#include "../world/starsystem.hpp"
#include "../common/myStr.hpp"
#include "../common/rand.hpp"
#include "../common/EntityManager.hpp"
#include "../common/common.hpp"
#include "../ai/aiModel/AiModelCollector.hpp"
#include "../render/Render.hpp"
#include "../docking/Kosmoport.hpp"

#include "../ai/aiModel/BaseAiModel.hpp"
#include "../pilots/Skill.hpp"
#include "../ai/StateMachine.hpp"
#include "../spaceobjects/Vehicle.hpp"

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
 		
        observation.SetNpcOwner(this);
        state_machine 	= new StateMachine(this);   
        
        ai_model = NULL;     
}
    
/* virtual */
Npc :: ~Npc() 
{ 
        delete state_machine;        
}  

StarSystem* Npc::GetStarSystem() const { return vehicle->GetStarSystem(); }
		
void Npc::MindInKosmoport()
{   		
	if (needsToDo.REPAIR_KORPUS == true)
	{
                vehicle->ExternalRepairEvent();
		needsToDo.REPAIR_KORPUS = false;
	}
	
	// if all things are DONE
	//((Planet*)vehicle->GetDriveComplex()->GetTarget())->GetLand()->AddToLaunchingQueue(this); // improove by adding spacestation
	if (upper_control == false)
	{
        	//if (ai_model)
        	//{
		//	ai_model->UpdateInStatic(this);
		//}

       		state_machine->UpdateInStaticInDock();      
       	}
	
}

void Npc::MindInSpace()
{
	vehicle->GetWeaponComplex()->PrepareWeapons();
	// this check is performed in Dynamic, no need to repeat in Static
	//if (vehicle->ableTo.GRAB == true) 
	//{
        	//vehicle->GetGrappleSlot()->GetGrappleEquipment()->ValidateTargets(); 
        //}
        vehicle->UpdateAllFunctionalItemsInStatic();
        
	if (upper_control == false)
	{
        	CheckNeeds();
        	observation.ObserveAllInSpace();  
                        
        	if (ai_model)
        	{
			ai_model->UpdateInStatic(this);
		}
      
		if (observation.see.ASTEROID == true)
		{
                	AsteroidScenario();
		}             

       		state_machine->UpdateInStaticInSpace();                 
        }

        vehicle->GetDriveComplex()->UpdatePath();
}

void Npc::UpdateInSpace(int time, bool show_effect)
{
        if (time > 0)
        {
       		state_machine->UpdateInDynamicInSpace();
       	}
}     	

void Npc::CheckNeeds()
{
        if (vehicle->GetArmor() < 0.5*vehicle->GetKorpusData().armor)   // move to ship
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
        vehicle->GetWeaponComplex()->SetTarget(observation.visible_ASTEROID_pair_vec[0].object);
                
        //printf("TARGET => ship_id, asteroid id = %i/%i\n", ship->GetId(), sorted_visible_ASTEROID_pList[0]->GetId());
}


Planet* Npc::GetPlanetForDocking()
{
     	Planet* _target_planet = GetStarSystem()->GetClosestPlanet(vehicle->GetPoints().GetCenter());  // improove
     	return _target_planet;
}

StarSystem* Npc::GetClosestStarSystem(int requested_condition_id)
{
       	observation.FindEchievableStarSystems(GetStarSystem()->GetGalaxy());
        	
       	StarSystem* _target_starsystem = observation.GetClosestStarSystem(requested_condition_id);   
	return _target_starsystem;
}


//// *********** SCANNING ***********
bool Npc::CheckPossibilityToScan(Vehicle* vehicle)
{
     	if (this->vehicle->GetId() == vehicle->GetId())    // selfscan is possible all time
     	{
        	return true;
        }
 
     	if (this->vehicle->GetPropetries().scan > vehicle->GetPropetries().protection) 
     	{
		return true;
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
    	info.addNameStr("race:");   	  info.addValueStr( getRaceStr(race_id) ); 
    	info.addNameStr("class:");   	  info.addValueStr( getClassStr(data_id.subtype_id) );  
    	info.addNameStr("model_ai:");     info.addValueStr( getAiModelStr(ai_model->GetTypeId()) );  
    	info.addNameStr("credits:");   	  info.addValueStr( int2str(credits) );	
    	info.addNameStr("expirience:");   info.addValueStr( int2str(skill.GetExpirience()) + " / " + int2str(skill.GetExpirienceNextLevel()) );	
    	info.addNameStr("availiable points:");   info.addValueStr( int2str(skill.GetAvailiablePoints()) );	
	
    	if (state_machine->GetMacroTaskManager()->GetScenario() != NULL)
    	{ 	
    	info.addNameStr("macro_task_main:");   	info.addValueStr( state_machine->GetMacroTaskManager()->GetScenario()->GetDescription(this) ); 
    	}
    	
    	if (state_machine->GetMicroTaskManager()->GetScenario() != NULL)
    	{ 	
    	info.addNameStr("micro_task:");   	info.addValueStr( state_machine->GetMicroTaskManager()->GetScenario()->GetDescription(this) ); 
    	}
}

void Npc::RenderInfo(const vec2f& center)
{ 
	UpdateInfo();
     	drawInfoIn2Column(&info.title_list, &info.value_list, center.x, center.y);
}
                   
  
bool Npc::BuyGoods()
{
	Shop* shop = ((Kosmoport*)vehicle->GetLand())->GetShop();
	int subtype_id = getRandInt(ENTITY::MINERALS_ID, ENTITY::EXCLUSIVE_ID);

	// hard coded logic
	int amount_to_hold  	= 0.8*vehicle->GetFreeSpace();
	int amount_to_buy 	= GetCredits()/shop->GetPrice(subtype_id);
	int amount_available 	= shop->GetAmount(subtype_id); 
	
	int amount = getMin<int>(amount_to_hold, amount_to_buy, amount_available);
	if (amount != 0)		
	{
		shop->SellGoods(this, subtype_id, amount); 
	}
}

bool Npc::SellGoods(GoodsPack* goods_pack)
{
	((Kosmoport*)vehicle->GetLand())->GetShop()->BuyGoods(this, goods_pack); 
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
        save_ptree.put(root+"unresolved.aiModel_id", ai_model->GetTypeId());
	skill.SaveData(save_ptree, root);
}

void Npc::LoadDataUniqueNpc(const boost::property_tree::ptree& load_ptree)
{
	is_alive = load_ptree.get<bool>("is_alive");
	race_id  = load_ptree.get<int>("race_id");
	data_unresolved_npc.vehicle_id = load_ptree.get<int>("unresolved.vehicle_id");
	data_unresolved_npc.aiModel_id = load_ptree.get<int>("unresolved.aiModel_id");
	
	skill.LoadData(load_ptree.get_child("skill"));
}

void Npc::ResolveDataUniqueNpc()
{
        ((Vehicle*)EntityManager::Instance().GetEntityById(data_unresolved_npc.vehicle_id))->BindOwnerNpc(this);
        SetAiModel(AiModelCollector::Instance().GetAiModel(data_unresolved_npc.aiModel_id));

	skill.ResolveData();
}		
