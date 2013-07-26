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
#include "../world/Sector.hpp"
#include "../common/myStr.hpp"
#include "../common/rand.hpp"
#include "../world/EntityManager.hpp"
#include "../common/Logger.hpp"
#include "../common/common.hpp"
#include "../ai/aiModel/AiModelCollector.hpp"
#include "../render/Render.hpp"
#include "../docking/Kosmoport.hpp"

#include "../ai/aiModel/BaseAiModel.hpp"
#include "../pilots/Skills.hpp"

#include "../spaceobjects/Vehicle.hpp"
#include "../spaceobjects/Asteroid.hpp"
#include "../parts/WeaponComplex.hpp"

#include "../items/others/GoodsPack.hpp"

#include "../docking/Shop.hpp"
#include "../text/VerticalFlowText.hpp" 

#include "../common/GameDate.hpp" 
#include <types/RaceTypes.hpp> 

Npc::Npc(int id, TYPE::ENTITY subtype_id, TYPE::ENTITY subsubtype_id)
:
race_id(TYPE::RACE::NONE_ID),
credits(1000),
player(nullptr),
vehicle(nullptr),
vehicle_to_scan(nullptr),
ai_model(nullptr)
{ 
	is_alive = true;
    
	SetId(id);
	SetTypeId(TYPE::ENTITY::NPC_ID);
	SetSubTypeId(subtype_id);
    SetSubSubTypeId(subsubtype_id);
        
    observation.SetNpcOwner(this);
    state_machine.SetNpcOwner(this);   
}
    
/* virtual */
Npc::~Npc() 
{}  

StarSystem* Npc::GetStarSystem() const { return vehicle->GetStarSystem(); }

void Npc::CloneMacroTaskFrom(Npc* npc)
{
	state_machine.SetCurrentMacroTask(npc->GetStateMachine().GetMacroTaskManager().GetTask());
}
     		
bool Npc::WithdrawCredits(INTLONGEST amount)
{
	if (credits > amount)
	{
		credits -= amount;
		return true;
	}
	
	return false;
}

void Npc::UpdateInKosmoportInStatic()
{
	vehicle->ResolveNeedsInKosmoportInStatic();
	
	// if all things are DONE
	//((Planet*)vehicle->GetComplexDrive()->GetTarget())->GetLand()->AddToLaunchingQueue(this); // improove by adding spacestation
	if (player == nullptr)
	{
        	//if (ai_model)
        	//{
		//	ai_model->UpdateInStatic(this);
		//}

       		state_machine.UpdateInStaticInDock();      

       		vehicle->ManageItemsInCargo();       		
       		vehicle->SellItemsInCargo();
       		vehicle->LaunchingEvent();
       	}
       	

}

void Npc::UpdateInSpaceInStatic()
{
	#if AI_LOG_ENABLED == 1 
	Logger::Instance().Log("Npc("+int2str(GetId())+")::UpdateInSpaceInStatic START", AI_LOG_DIP); 
	#endif 

        vehicle->UpdateAllFunctionalItemsInStatic();
	vehicle->GetComplexWeapon().PrepareWeapons();
	        
	if (player == nullptr)
	{
        	vehicle->CheckNeedsInStatic();
                
                if (skills.GetAvailablePoints() > 0)
                {
                        skills.ManageAccordingToStrategy();
                }
                
        	observation.ObserveAllInSpace();  
                        
        	if (ai_model)
        	{
			ai_model->UpdateInStatic(this);
		}
      
                ScenarioFireVehicleAgressor();
      
		if (observation.see.ASTEROID == true)
		{
                	ScenarioFireAsteroid();
		}             

       		state_machine.UpdateInStaticInSpace();
        }

        vehicle->GetComplexDrive().UpdatePath();
        
        #if AI_LOG_ENABLED == 1 
	Logger::Instance().Log("Npc("+int2str(GetId())+")::UpdateInSpaceInStatic END", AI_LOG_DIP); 
	#endif 
}

void Npc::AddExpirience(int expirience, bool show_effect)
{
       	skills.AddExpirience(expirience);
	
	if (show_effect == true)
	{
       		VerticalFlowText* text = new VerticalFlowText(int2str(expirience), 12, vehicle->GetCenter(), COLOR::COLOR4I_BLUE_LIGHT, 10);
       		vehicle->GetStarSystem()->Add(text); 
	}
}
     	
void Npc::TakeIntoAccountAgressor(Vehicle* agressor)
{
	for (std::set<AgressorData>::iterator it=data_agressor_set.begin(); it!=data_agressor_set.end(); ++it)
	{
		if (it->npc_id == agressor->GetOwnerNpc()->GetId())
		{
            if (it->last_date != GameDate::Instance().GetDate())
            {
                int counter = it->counter;
                data_agressor_set.erase(it);
                
                AgressorData agressor_data(agressor->GetOwnerNpc()->GetId(), GameDate::Instance().GetDate(), ++counter);
                data_agressor_set.insert(agressor_data);
            }
    
            return;
		}
	}

	AgressorData agressor_data(agressor->GetOwnerNpc()->GetId(), GameDate::Instance().GetDate(), 1);	
	data_agressor_set.insert(agressor_data);
}

void Npc::UpdateInSpace(int time, bool show_effect)
{
        if (time > 0)
        {
       		state_machine.UpdateInDynamicInSpace();
       	}
}     	

void Npc::ScenarioFireVehicleAgressor()
{
        for (unsigned int i=0; i<observation.visible_VEHICLE_pair_vec.size(); i++)
        {
                for (std::set<AgressorData>::iterator it = data_agressor_set.begin(); it != data_agressor_set.end(); ++it)
                {
                        if (observation.visible_VEHICLE_pair_vec[i].object->GetOwnerNpc()->GetId() == it->npc_id)
                        {
                                vehicle->GetComplexWeapon().DeactivateAllWeapons();

                                vehicle->GetComplexWeapon().ActivateAllWeapons();
                                vehicle->GetComplexWeapon().SetTarget(observation.visible_VEHICLE_pair_vec[i].object);
                        
                                return;
                        }
                }
        }           
}

void Npc::ScenarioFireAsteroid()
{
        vehicle->GetComplexWeapon().DeactivateAllWeapons();

        vehicle->GetComplexWeapon().ActivateAllWeapons();
        vehicle->GetComplexWeapon().SetTarget(observation.visible_ASTEROID_pair_vec[0].object);
}

Planet* Npc::GetPlanetForDocking()
{
     	return GetStarSystem()->GetClosestInhabitedPlanet(vehicle->GetCenter());  // improove
}

StarSystem* Npc::GetClosestStarSystem(int requested_condition_id)
{
       	observation.FindEchievableStarSystems(GetStarSystem()->GetSector()->GetGalaxy());
        	
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
 
     	if (this->vehicle->GetProperties().scan > vehicle->GetProperties().protection) 
     	{
		return true;
        }

     	return false;
}


void Npc::ResetScanTarget() { vehicle_to_scan = nullptr; }
//// *********** SCANNING ***********


void Npc::UpdateInfo()
{
	info.clear();

    info.addTitleStr("NPC");
    info.addNameStr("id:");           info.addValueStr( int2str(GetId())  );
    info.addNameStr("race:");   	  info.addValueStr( getRaceStr(race_id) ); 
    info.addNameStr("subype_id:");    info.addValueStr( getEntityTypeStr(GetSubTypeId()) );  
    info.addNameStr("subsubype_id:"); info.addValueStr( getEntityTypeStr(GetSubSubTypeId()) );  
    info.addNameStr("model_ai:");     info.addValueStr( getAiModelStr(ai_model->GetTypeId()) );  
    info.addNameStr("credits:");   	  info.addValueStr( int2str(credits) );	
    info.addNameStr("expirience:");   info.addValueStr( int2str(skills.GetExpirience()) + " / " + int2str(skills.GetExpirienceNextLevel()) );	
    info.addNameStr("free skills:");  info.addValueStr( int2str(skills.GetAvailablePoints()) );	

    info.addNameStr("npc_agress:"); info.addValueStr( GetAgressorSetString() );
    
    if (state_machine.GetMacroTaskManager().GetScenario() != nullptr)
    { 	
        info.addNameStr("macro_task:");   info.addValueStr( state_machine.GetMacroTaskManager().GetScenario()->GetDescription(this) ); 
    }
    
    if (state_machine.GetMicroTaskManager().GetScenario() != nullptr)
    { 	
        info.addNameStr("micro_task:");   info.addValueStr( state_machine.GetMicroTaskManager().GetScenario()->GetDescription(this) ); 
    }
}

void Npc::RenderInfo(const Vec2<float>& center)
{
	UpdateInfo();
     	drawInfoIn2Column(info.title_list, info.value_list, center);
}
                   
  
bool Npc::BuyGoods()
{
	Shop* shop = ((Kosmoport*)vehicle->GetLand())->GetShop();
	TYPE::ENTITY subtype_id = (TYPE::ENTITY)getRandInt((int)TYPE::ENTITY::MINERALS_ID, (int)TYPE::ENTITY::EXCLUSIVE_ID);

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
  
void Npc::SaveData(boost::property_tree::ptree& save_ptree) const
{
	std::string root = "npc."+int2str(GetId())+".";
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
	save_ptree.put(root+"race_id", (int)race_id);
    save_ptree.put(root+"unresolved.vehicle_id", vehicle->GetId());
    save_ptree.put(root+"unresolved.aiModel_id", ai_model->GetTypeId());
	skills.SaveData(save_ptree, root);
	if (state_machine.GetMacroTaskManager().GetScenario() != nullptr)
	{
		const std::string child_root = root + "macrotask.";
		state_machine.GetMacroTaskManager().GetTask().SaveData(save_ptree, child_root);
	}
	
	if (state_machine.GetMicroTaskManager().GetScenario() != nullptr)	
	{
		const std::string child_root = root + "microtask.";
		state_machine.GetMicroTaskManager().GetTask().SaveData(save_ptree, child_root);
	}
}

void Npc::LoadDataUniqueNpc(const boost::property_tree::ptree& load_ptree)
{
	is_alive = load_ptree.get<bool>("is_alive");
	race_id  = (TYPE::RACE)load_ptree.get<int>("race_id");
	data_unresolved_npc.vehicle_id = load_ptree.get<int>("unresolved.vehicle_id");
	data_unresolved_npc.aiModel_id = load_ptree.get<int>("unresolved.aiModel_id");
	
	skills.LoadData(load_ptree.get_child("skill"));

	if (load_ptree.get_child_optional("macrotask"))
	{
		data_unresolved_npc.macrotask.LoadData(load_ptree.get_child("macrotask"));
	}
	
	if (load_ptree.get_child_optional("microtask"))
	{
		data_unresolved_npc.microtask.LoadData(load_ptree.get_child("microtask"));
	}
}

void Npc::ResolveDataUniqueNpc()
{
    ApplySkillsStrategy();
    
    ((Vehicle*)EntityManager::Instance().GetEntityById(data_unresolved_npc.vehicle_id))->BindOwnerNpc(this);
    SetAiModel(AiModelCollector::Instance().GetAiModel(data_unresolved_npc.aiModel_id));

	skills.ResolveData();
	
	if (data_unresolved_npc.macrotask.GetScenarioTypeId() != TYPE::AISCENARIO::NONE_ID)
	{
		state_machine.SetCurrentMacroTask(data_unresolved_npc.macrotask);
	}
	
	if (data_unresolved_npc.microtask.GetScenarioTypeId() != TYPE::AISCENARIO::NONE_ID)
	{
		state_machine.SetCurrentMicroTask(data_unresolved_npc.microtask);
	}
}

void Npc::ApplySkillsStrategy()
{           /*
    TYPE::ENTITY class_type_id = data_id.subtype_id;
    if (data_id.subtype_id == TYPE::ENTITY::RANGER_ID)
    {
            class_type_id = data_id.subsubtype_id;
    }
                   
    int skills_strategy[SKILLS_NUM];
    const int* strategy_class_type = getArrayDependingOnClassTypeId(class_type_id);
    const int* strategy_race       = getArrayDependingOnRaceId(race_id);

    for (unsigned int i=0; i<SKILLS_NUM; i++)
    {
            skills_strategy[i] = strategy_class_type[i] * strategy_race[i];
    }
    
    skills.BindStrategy(skills_strategy);     */
}

std::string Npc::GetAgressorSetString() const
{
    std::string str;
    for (std::set<AgressorData>::iterator it = data_agressor_set.begin(); it != data_agressor_set.end(); ++it)
    {
            str += int2str(it->npc_id) + ":" + int2str(it->counter) + " ";
    }
    
    return str;
}
