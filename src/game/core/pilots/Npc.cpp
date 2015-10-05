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
#include <world/starsystem.hpp>
#include <world/Sector.hpp>
#include <managers/EntitiesManager.hpp>
//#include <ceti/StringUtils.hpp>
//#include <math/rand.hpp>
#include <meti/RandUtils.hpp>
#include "../common/Global.hpp"
#include <ceti/Logger.hpp>
#include <common/common.hpp>
#include "../ai/aiModel/AiModelCollector.hpp"
#include "../dock/Kosmoport.hpp"

#include "../ai/aiModel/BaseAiModel.hpp"
#include "../pilots/Skills.hpp"

#include "../spaceobjects/Vehicle.hpp"
#include "../spaceobjects/Asteroid.hpp"
#include "../parts/WeaponComplex.hpp"

#include "../items/others/GoodsPack.hpp"

#include "../dock/Shop.hpp"

#include "../common/GameDate.hpp" 
#include <types/RaceTypes.hpp> 

Npc::Npc(int id, TYPE::ENTITY subtype_id, TYPE::ENTITY subsubtype_id)
    :
      race_id(TYPE::RACE::NONE_ID),
      credits(1000),
      player(nullptr),
      vehicle(nullptr),
      ai_model(nullptr),
      vehicle_to_scan(nullptr)
{ 
    is_alive = true;
    
    setId(id);
    setTypeId(TYPE::ENTITY::NPC_ID);
    setSubTypeId(subtype_id);
    setSubSubTypeId(subsubtype_id);

    observation.SetNpcOwner(this);
    state_machine.SetNpcOwner(this);
}

/* virtual */
Npc::~Npc() 
{}  

StarSystem* Npc::starsystem() const { return vehicle->starsystem(); }

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
        //    ai_model->UpdateInStatic(this);
        //}

        state_machine.UpdateInStaticInDock();

        vehicle->ManageItemsInCargo();
        vehicle->SellItemsInCargo();
        vehicle->LaunchingEvent();
    }


}

void Npc::UpdateInSpaceInStatic()
{
    //Logger::Instance().Log("Npc("+std::to_string(id())+")::UpdateInSpaceInStatic START", AI_LOG_DIP);

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

    //Logger::Instance().Log("Npc("+std::to_string(id())+")::UpdateInSpaceInStatic END", AI_LOG_DIP);
}

void Npc::AddExpirience(int expirience, bool show_effect)
{
    skills.AddExpirience(expirience);
    
    if (show_effect == true) {
//        VerticalFlowText* text = new VerticalFlowText(std::to_string(expirience), 12, meti::vec2(vehicle->center()), COLOR::COLOR4I_BLUE_LIGHT, 10);
//        vehicle->starsystem()->Add(text);
    }
}

void Npc::remeberAgressor(Vehicle* agressor)
{
    for (std::set<AgressorData>::iterator it=data_agressor_set.begin(); it!=data_agressor_set.end(); ++it)
    {
        if (it->npc_id == agressor->GetOwnerNpc()->id())
        {
            if (it->last_date != global::get().gameDate())
            {
                int counter = it->counter;
                data_agressor_set.erase(it);
                
                AgressorData agressor_data(agressor->GetOwnerNpc()->id(), global::get().gameDate(), ++counter);
                data_agressor_set.insert(agressor_data);
            }

            return;
        }
    }

    AgressorData agressor_data(agressor->GetOwnerNpc()->id(), global::get().gameDate(), 1);
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
            if (observation.visible_VEHICLE_pair_vec[i].object->GetOwnerNpc()->id() == it->npc_id)
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
    return starsystem()->GetClosestInhabitedPlanet(meti::vec2(vehicle->center()));  // improove
}

StarSystem* Npc::GetClosestStarSystem(int requested_condition_id)
{
    observation.FindEchievableStarSystems(starsystem()->sector()->galaxy());
    
    StarSystem* _target_starsystem = observation.GetClosestStarSystem(requested_condition_id);
    return _target_starsystem;
}


//// *********** SCANNING ***********
bool Npc::CheckPossibilityToScan(Vehicle* vehicle)
{
    if (this->vehicle->id() == vehicle->id())    // selfscan is possible all time
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
//    info.clear();

//    info.addTitleStr("NPC");
//    info.addNameStr("id:");           info.addValueStr( std::to_string(id())  );
//    info.addNameStr("race:");         info.addValueStr( getRaceStr(race_id) );
//    info.addNameStr("subype_id:");    info.addValueStr( getStr(subTypeId()) );
//    info.addNameStr("subsubype_id:"); info.addValueStr( getStr(subSubTypeId()) );
//    //info.addNameStr("model_ai:");     info.addValueStr( ceti::getAiModelStr(ai_model->typeId()) );
//    info.addNameStr("credits:");      info.addValueStr( std::to_string(credits) );
//    info.addNameStr("expirience:");   info.addValueStr( std::to_string(skills.GetExpirience()) + " / " + std::to_string(skills.GetExpirienceNextLevel()) );
//    info.addNameStr("free skills:");  info.addValueStr( std::to_string(skills.GetAvailablePoints()) );

//    info.addNameStr("npc_agress:"); info.addValueStr( GetAgressorSetString() );
    
//    if (state_machine.GetMacroTaskManager().GetScenario() != nullptr) {
//        info.addNameStr("macro_task:");   info.addValueStr( state_machine.GetMacroTaskManager().GetScenario()->GetDescription(this) );
//    }
//    if (state_machine.GetMicroTaskManager().GetScenario() != nullptr) {
//        info.addNameStr("micro_task:");   info.addValueStr( state_machine.GetMicroTaskManager().GetScenario()->GetDescription(this) );
//    }
}

void Npc::RenderInfo(const glm::vec2& center)
{
    UpdateInfo();
    //drawInfoIn2Column(info.title_list, info.value_list, center);
}


bool Npc::BuyGoods()
{
    Shop* shop = ((Kosmoport*)vehicle->GetLand())->GetShop();
    TYPE::ENTITY subtype_id = (TYPE::ENTITY)meti::getRandInt((int)TYPE::ENTITY::MINERALS_ID, (int)TYPE::ENTITY::EXCLUSIVE_ID);

    // hard coded logic
    int amount_to_hold      = 0.8*vehicle->GetFreeSpace();
    int amount_to_buy     = GetCredits()/shop->GetPrice(subtype_id);
    int amount_available     = shop->GetAmount(subtype_id);
    
    int amount = getMin<int>(amount_to_hold, amount_to_buy, amount_available);
    if (amount != 0)
    {
        shop->SellGoods(this, subtype_id, amount);
    }
    
    return true;
}

void Npc::Save(boost::property_tree::ptree& save_ptree) const
{
    std::string root = "npc."+std::to_string(id())+".";
    Base::SaveData(save_ptree, root);
    Npc::SaveData(save_ptree, root);
}        

void Npc::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
    Npc::LoadData(load_ptree);
}        

void Npc::Resolve()
{
    Base::ResolveData();
    Npc::ResolveData();
}

void Npc::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const    
{
    save_ptree.put(root+"is_alive", is_alive);
    save_ptree.put(root+"race_id", (int)race_id);
    save_ptree.put(root+"unresolved.vehicle_id", vehicle->id());
    save_ptree.put(root+"unresolved.aiModel_id", ai_model->typeId());
    skills.Save(save_ptree, root);
    if (state_machine.GetMacroTaskManager().GetScenario() != nullptr)
    {
        const std::string child_root = root + "macrotask.";
        state_machine.GetMacroTaskManager().GetTask().Save(save_ptree, child_root);
    }
    
    if (state_machine.GetMicroTaskManager().GetScenario() != nullptr)
    {
        const std::string child_root = root + "microtask.";
        state_machine.GetMicroTaskManager().GetTask().Save(save_ptree, child_root);
    }
}

void Npc::LoadData(const boost::property_tree::ptree& load_ptree)
{
    is_alive = load_ptree.get<bool>("is_alive");
    race_id  = (TYPE::RACE)load_ptree.get<int>("race_id");
    data_unresolved_npc.vehicle_id = load_ptree.get<int>("unresolved.vehicle_id");
    data_unresolved_npc.aiModel_id = load_ptree.get<int>("unresolved.aiModel_id");
    
    skills.Load(load_ptree.get_child("skill"));

    if (load_ptree.get_child_optional("macrotask"))
    {
        data_unresolved_npc.macrotask.Load(load_ptree.get_child("macrotask"));
    }
    
    if (load_ptree.get_child_optional("microtask"))
    {
        data_unresolved_npc.microtask.Load(load_ptree.get_child("microtask"));
    }
}

void Npc::ResolveData()
{
    ApplySkillsStrategy();
    
    ((Vehicle*)global::get().entitiesManager().GetEntityById(data_unresolved_npc.vehicle_id))->BindOwnerNpc(this);
    SetAiModel(AiModelCollector::Instance().GetAiModel(data_unresolved_npc.aiModel_id));

    skills.Resolve();
    
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
        str += std::to_string(it->npc_id) + ":" + std::to_string(it->counter) + " ";
    }
    
    return str;
}
