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
#include <managers/EntityManager.hpp>
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

#include <item/others/GoodsPack.hpp>

#include "../dock/Shop.hpp"

#include "../common/GameDate.hpp" 
#include <types/RaceTypes.hpp> 

Npc::Npc(int id, type::entity subtype_id, type::entity subsubtype_id)
    :
      m_raceId(type::race::NONE_ID),
      m_credits(1000),
      m_player(nullptr),
      m_vehicle(nullptr),
      m_aiModel(nullptr),
      m_scanTarget(nullptr)
{ 
    m_isAlive = true;
    
    setId(id);
    setTypeId(type::entity::NPC_ID);
    setSubTypeId(subtype_id);
    setSubSubTypeId(subsubtype_id);

    m_observation.SetNpcOwner(this);
    m_stateMachine.setNpc(this);
}

/* virtual */
Npc::~Npc() 
{}  

Starsystem* Npc::starsystem() const { return m_vehicle->starsystem(); }

void Npc::cloneMacroTaskFrom(Npc* npc)
{
    m_stateMachine.setCurrentMacroTask(npc->stateMachine().macroTaskManager().task());
}

bool Npc::withdrawCredits(unsigned long int amount)
{
    if (m_credits > amount) {
        m_credits -= amount;
        return true;
    }    
    return false;
}

void Npc::updateInKosmoportInStatic()
{
    m_vehicle->ResolveNeedsInKosmoportInStatic();
    
    // if all things are DONE
    //((Planet*)vehicle->GetComplexDrive()->GetTarget())->GetLand()->AddToLaunchingQueue(this); // improove by adding spacestation
    if (m_player == nullptr)
    {
        //if (ai_model)
        //{
        //    ai_model->UpdateInStatic(this);
        //}

        m_stateMachine.updateInStaticInDock();

        m_vehicle->manageItemsInCargo();
        m_vehicle->sellItemsInCargo();
        m_vehicle->LaunchingEvent();
    }


}

void Npc::updateInSpaceInStatic()
{
    //LOG("Npc("+std::to_string(id())+")::UpdateInSpaceInStatic START");

    m_vehicle->UpdateAllFunctionalItemsInStatic();
    m_vehicle->weaponComplex().prepareWeapons();

    if (!m_player) {
        m_vehicle->CheckNeedsInStatic();
        if (m_skills.availablePoints()) {
            m_skills.manageAccordingToStrategy();
        }

        m_observation.ObserveAllInSpace();

//        if (ai_model) {
//            ai_model->UpdateInStatic(this);
//        }

        __scenarioFireVehicleAgressor();

        if (m_observation.see.ASTEROID) {
            __scenarioFireAsteroid();
        }

        m_stateMachine.updateInStaticInSpace();
    }

    m_vehicle->driveComplex().UpdatePath();

    //LOG("Npc("+std::to_string(id())+")::UpdateInSpaceInStatic END");
}

void Npc::addExpirience(int expirience, bool show_effect)
{
    m_skills.addExpirience(expirience);
    
    if (show_effect == true) {
//        VerticalFlowText* text = new VerticalFlowText(std::to_string(expirience), 12, meti::vec2(vehicle->center()), COLOR::COLOR4I_BLUE_LIGHT, 10);
//        vehicle->starsystem()->Add(text);
    }
}

void Npc::remeberAgressor(Vehicle* agressor)
{
    for (std::set<AgressorData>::iterator it=m_agressorsData.begin(); it!=m_agressorsData.end(); ++it)
    {
        if (it->npc_id == agressor->npc()->id())
        {
            if (it->last_date != global::get().gameDate())
            {
                int counter = it->counter;
                m_agressorsData.erase(it);
                
                AgressorData agressor_data(agressor->npc()->id(), global::get().gameDate(), ++counter);
                m_agressorsData.insert(agressor_data);
            }

            return;
        }
    }

    AgressorData agressor_data(agressor->npc()->id(), global::get().gameDate(), 1);
    m_agressorsData.insert(agressor_data);
}

void Npc::updateInSpace(int time, bool show_effect)
{
    if (time > 0) {
        m_stateMachine.updateInDynamicInSpace();
    }
}         

void Npc::__scenarioFireVehicleAgressor()
{
    for (unsigned int i=0; i<m_observation.visible_VEHICLE_pair_vec.size(); i++)
    {
        for (std::set<AgressorData>::iterator it = m_agressorsData.begin(); it != m_agressorsData.end(); ++it)
        {
            if (m_observation.visible_VEHICLE_pair_vec[i].object->npc()->id() == it->npc_id)
            {
                m_vehicle->weaponComplex().deactivateWeapons();

                m_vehicle->weaponComplex().activateWeapons();
                m_vehicle->weaponComplex().setTarget(m_observation.visible_VEHICLE_pair_vec[i].object);

                return;
            }
        }
    }
}

void Npc::__scenarioFireAsteroid()
{
    m_vehicle->weaponComplex().deactivateWeapons();

    m_vehicle->weaponComplex().activateWeapons();
    m_vehicle->weaponComplex().setTarget(m_observation.visible_ASTEROID_pair_vec[0].object);
}

Planet* Npc::planetForDocking()
{
    assert(false);
    //return starsystem()->closestInhabitedPlanet(meti::vec2(m_vehicle->position()));  // improove
}

Starsystem* Npc::closestStarSystem(int requested_condition_id)
{
    m_observation.FindEchievableStarSystems(starsystem()->sector()->galaxy());
    
    Starsystem* _target_starsystem = m_observation.GetClosestStarSystem(requested_condition_id);
    return _target_starsystem;
}


//// *********** SCANNING ***********
bool Npc::isAbleToScan(Vehicle* vehicle)
{
    if (this->m_vehicle->id() == vehicle->id())    // selfscan is possible all time
    {
        return true;
    }

    if (this->m_vehicle->properties().scan > vehicle->properties().protection)
    {
        return true;
    }

    return false;
}


void Npc::resetScanTarget() { m_scanTarget = nullptr; }
//// *********** SCANNING ***********


void Npc::__updateInfo()
{
//    info.clear();

//    info.addTitleStr("NPC");
//    info.addNameStr("id:");           info.addValueStr( std::to_string(id())  );
//    info.addNameStr("race:");         info.addValueStr( getRaceStr(race_id) );
//    info.addNameStr("subype_id:");    info.addValueStr( str(subTypeId()) );
//    info.addNameStr("subsubype_id:"); info.addValueStr( str(subSubTypeId()) );
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

void Npc::renderInfo(const glm::vec2& center)
{
    __updateInfo();
    //drawInfoIn2Column(info.title_list, info.value_list, center);
}


bool Npc::buyGoods()
{
    Shop* shop = ((Kosmoport*)m_vehicle->land())->GetShop();
    type::entity subtype_id = (type::entity)meti::getRandInt((int)type::entity::MINERALS_ID, (int)type::entity::EXCLUSIVE_ID);

    // hard coded logic
    int amount_to_hold      = 0.8*m_vehicle->freeSpace();
    int amount_to_buy     = credits()/shop->GetPrice(subtype_id);
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
    save_ptree.put(root+"is_alive", m_isAlive);
    save_ptree.put(root+"race_id", (int)m_raceId);
    save_ptree.put(root+"unresolved.vehicle_id", m_vehicle->id());
    save_ptree.put(root+"unresolved.aiModel_id", m_aiModel->typeId());
    m_skills.Save(save_ptree, root);
    if (m_stateMachine.macroTaskManager().scenario()) {
        const std::string child_root = root + "macrotask.";
        m_stateMachine.macroTaskManager().task().save(save_ptree, child_root);
    }
    
    if (m_stateMachine.microTaskManager().scenario()) {
        const std::string child_root = root + "microtask.";
        m_stateMachine.microTaskManager().task().save(save_ptree, child_root);
    }
}

void Npc::LoadData(const boost::property_tree::ptree& load_ptree)
{
    m_isAlive = load_ptree.get<bool>("is_alive");
    m_raceId  = (type::race)load_ptree.get<int>("race_id");
    data_unresolved_npc.vehicle_id = load_ptree.get<int>("unresolved.vehicle_id");
    data_unresolved_npc.aiModel_id = load_ptree.get<int>("unresolved.aiModel_id");
    
    m_skills.Load(load_ptree.get_child("skill"));

    if (load_ptree.get_child_optional("macrotask"))
    {
        data_unresolved_npc.macrotask.load(load_ptree.get_child("macrotask"));
    }
    
    if (load_ptree.get_child_optional("microtask"))
    {
        data_unresolved_npc.microtask.load(load_ptree.get_child("microtask"));
    }
}

void Npc::ResolveData()
{
    applySkillsStrategy();
    
    ((Vehicle*)global::get().entityManager().get(data_unresolved_npc.vehicle_id))->bindNpc(this);
    setAiModel(AiModelCollector::Instance().GetAiModel(data_unresolved_npc.aiModel_id));

    m_skills.Resolve();
    
    if (data_unresolved_npc.macrotask.GetScenarioTypeId() != type::AISCENARIO::NONE_ID)
    {
        m_stateMachine.setCurrentMacroTask(data_unresolved_npc.macrotask);
    }
    
    if (data_unresolved_npc.microtask.GetScenarioTypeId() != type::AISCENARIO::NONE_ID)
    {
        m_stateMachine.setCurrentMicroTask(data_unresolved_npc.microtask);
    }
}

void Npc::applySkillsStrategy()
{           /*
    type::entity class_type_id = data_id.subtype_id;
    if (data_id.subtype_id == type::entity::RANGER_ID)
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

std::string Npc::agressorSetString() const
{
    std::string str;
    for (std::set<AgressorData>::iterator it = m_agressorsData.begin(); it != m_agressorsData.end(); ++it)
    {
        str += std::to_string(it->npc_id) + ":" + std::to_string(it->counter) + " ";
    }
    
    return str;
}
