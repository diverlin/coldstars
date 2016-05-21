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

#include "MacroScenarioGoodsTrading.hpp"
#include "../../../pilots/Npc.hpp"
#include "../../../spaceobjects/Vehicle.hpp"
#include "../../../spaceobjects/Planet.hpp"
#include "../../../spaceobjects/Container.hpp"
#include "../../../common/constants.hpp"
#include <ceti/Logger.hpp>
//#include <ceti/StringUtils.hpp>
#include "../../../ai/StateMachine.hpp"

#include "../../../item/others/GoodsPack.hpp"

MacroScenarioGoodsTrading::MacroScenarioGoodsTrading() 
{
    type_id = TYPE::AISCENARIO::MACRO_GOODSTRADING_ID;
}

MacroScenarioGoodsTrading::~MacroScenarioGoodsTrading() 
{}

bool MacroScenarioGoodsTrading::IsAbleToBuyGoods(Npc* npc) const
{
    if (npc->GetVehicle()->free_space() > 10)
    {
        if (npc->GetCredits() > 100)
        {
            return true;
        }
    }
    
    return false;
}

/* virtual */
void MacroScenarioGoodsTrading::Enter(Npc* npc) const
{
    LOG( "npc_id="+std::to_string(npc->id())+" ENTER MacroScenarioGoodsTrading");
}

/* virtual */
bool MacroScenarioGoodsTrading::Validation(Npc* npc) const
{
    if (npc->GetVehicle()->GetGoodsPack() == nullptr)
    {
        return IsAbleToBuyGoods(npc);
    }
    else
    {
        return true;
    }
        
    return false;
}

/* virtual */        
void MacroScenarioGoodsTrading::UpdateInStaticInSpace(Npc* npc) const
{
    bool see_pickable_container = npc->GetObservation().GetVisionStatus().pickable_CONTAINER;
    bool able_buy      = IsAbleToBuyGoods(npc);
    bool has_goods     = false;
    if (npc->GetVehicle()->GetGoodsPack() != nullptr)
    {
        has_goods = true;
    }
    TYPE::AISCENARIO microScenarioTypeId = npc->GetStateMachine().GetMicroTaskManager().GetTask().GetScenarioTypeId();
    
    // LOGIC
    // grab container
    if (see_pickable_container == true)
    {    
        if (microScenarioTypeId != TYPE::AISCENARIO::MICRO_GRAB_ID) 
        {
            Container* container = npc->GetObservation().GetClosestPickableContainer(); // find proper!
            if (npc->GetVehicle()->free_space() > container->mass())
            {
                Task microtask(TYPE::AISCENARIO::MICRO_GRAB_ID, container->id());
                npc->GetStateMachine().SetCurrentMicroTask(microtask); 
            
                return;
            }
        }
    }
    
    // buy goods
    if ( (has_goods == false) and (able_buy == true) )
    {
        if (microScenarioTypeId != TYPE::AISCENARIO::MICRO_DOCKING_ID)
        {
            Planet* planet = npc->GetPlanetForDocking(); // find proper planet!
            Task microtask(TYPE::AISCENARIO::MICRO_DOCKING_ID, planet->id());
            npc->GetStateMachine().SetCurrentMicroTask(microtask); 
                
            return;
        }
    }
    
    // sell goods        
    if ( (has_goods == true) )
    {
        if (microScenarioTypeId != TYPE::AISCENARIO::MICRO_DOCKING_ID)
        {
            Planet* planet = npc->GetPlanetForDocking(); // find proper planet
            Task microtask(TYPE::AISCENARIO::MICRO_DOCKING_ID, planet->id());
            npc->GetStateMachine().SetCurrentMicroTask(microtask);
            
            return;
        }
    }

    // explore space
    if ( (has_goods == false) and (able_buy == false) )
    {
        if (microScenarioTypeId != TYPE::AISCENARIO::MICRO_EXPLORATION_ID) 
        {
            Task microtask(TYPE::AISCENARIO::MICRO_EXPLORATION_ID);
            npc->GetStateMachine().SetCurrentMicroTask(microtask); 
                
            return;
        }
    }
}

/* virtual */
void MacroScenarioGoodsTrading::UpdateInStaticInDock(Npc* npc) const
{
    GoodsPack* goods_pack = npc->GetVehicle()->GetGoodsPack(); 
    while(goods_pack != nullptr)
    {
        npc->GetVehicle()->SellItem(goods_pack);
        goods_pack = npc->GetVehicle()->GetGoodsPack(); 
    }
    
    if (IsAbleToBuyGoods(npc) == true)
    {
        npc->BuyGoods();
    }

    Task microtask(TYPE::AISCENARIO::MICRO_LAUNCHING_ID);
    npc->GetStateMachine().SetCurrentMicroTask(microtask);        
}

void MacroScenarioGoodsTrading::Exit(Npc* npc) const
{
    LOG( "npc_id="+std::to_string(npc->id())+" EXIT MacroScenarioGoodsTrading");
}

/* virtual */
std::string MacroScenarioGoodsTrading::GetDescription(Npc* npc) const
{
    return "MacroScenarioGoodsTrading";
}
