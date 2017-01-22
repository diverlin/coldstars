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
    setTypeId(type::AISCENARIO::MACRO_GOODSTRADING_ID);
}

MacroScenarioGoodsTrading::~MacroScenarioGoodsTrading() 
{}

bool MacroScenarioGoodsTrading::IsAbleToBuyGoods(Npc* npc) const
{
    assert(false);
    //    if (npc->vehicle()->freeSpace() > 10)
//    {
//        if (npc->credits() > 100)
//        {
//            return true;
//        }
//    }
    
    return false;
}

/* virtual */
void MacroScenarioGoodsTrading::enter(Npc* npc) const
{
    assert(false);
    //LOG( "npc_id="+std::to_string(npc->id())+" ENTER MacroScenarioGoodsTrading");
}

/* virtual */
bool MacroScenarioGoodsTrading::Validation(Npc* npc) const
{
    assert(false);
//    if (npc->vehicle()->goodsPack() == nullptr)
//    {
//        return IsAbleToBuyGoods(npc);
//    }
//    else
//    {
//        return true;
//    }
        
    return false;
}

/* virtual */        
void MacroScenarioGoodsTrading::UpdateInStaticInSpace(Npc* npc) const
{
    assert(false);
//    bool see_pickable_container = npc->observation().GetVisionStatus().pickable_CONTAINER;
//    bool able_buy      = IsAbleToBuyGoods(npc);
//    bool has_goods     = false;
//    assert(false);
////    if (npc->vehicle()->goodsPack() != nullptr)
////    {
////        has_goods = true;
////    }
//    type::AISCENARIO microScenarioTypeId = npc->stateMachine().microTaskManager().task().GetScenarioTypeId();
    
//    // LOGIC
//    // grab container
//    if (see_pickable_container == true)
//    {
//        if (microScenarioTypeId != type::AISCENARIO::MICRO_GRAB_ID)
//        {
//            Container* container = npc->observation().GetClosestPickableContainer(); // find proper!
//            assert(false);
////            if (npc->vehicle()->freeSpace() > container->mass())
////            {
////                Task microtask(type::AISCENARIO::MICRO_GRAB_ID, container->id());
////                npc->stateMachine().setCurrentMicroTask(microtask);
            
////                return;
////            }
//        }
//    }
    
//    // buy goods
//    if ( (has_goods == false) and (able_buy == true) )
//    {
//        if (microScenarioTypeId != type::AISCENARIO::MICRO_DOCKING_ID)
//        {
//            Planet* planet = npc->planetForDocking(); // find proper planet!
////            Task microtask(type::AISCENARIO::MICRO_DOCKING_ID, planet->id());
////            npc->stateMachine().setCurrentMicroTask(microtask);
                
//            return;
//        }
//    }
    
//    // sell goods
//    if ( (has_goods == true) )
//    {
//        if (microScenarioTypeId != type::AISCENARIO::MICRO_DOCKING_ID)
//        {
////            Planet* planet = npc->planetForDocking(); // find proper planet
////            Task microtask(type::AISCENARIO::MICRO_DOCKING_ID, planet->id());
////            npc->stateMachine().setCurrentMicroTask(microtask);
            
//            return;
//        }
//    }

//    // explore space
//    if ( (has_goods == false) and (able_buy == false) )
//    {
//        if (microScenarioTypeId != type::AISCENARIO::MICRO_EXPLORATION_ID)
//        {
//            Task microtask(type::AISCENARIO::MICRO_EXPLORATION_ID);
//            npc->stateMachine().setCurrentMicroTask(microtask);
                
//            return;
//        }
//    }
}

/* virtual */
void MacroScenarioGoodsTrading::UpdateInStaticInDock(Npc* npc) const
{
    assert(false);
//    GoodsPack* goods_pack = npc->vehicle()->goodsPack();
//    while(goods_pack != nullptr)
//    {
//        npc->vehicle()->sellItem(goods_pack);
//        goods_pack = npc->vehicle()->goodsPack();
//    }

    assert(false);
//    if (IsAbleToBuyGoods(npc)) {
//        npc->buyGoods();
//    }

//    Task microtask(type::AISCENARIO::MICRO_LAUNCHING_ID);
//    npc->stateMachine().setCurrentMicroTask(microtask);
}

void MacroScenarioGoodsTrading::exit(Npc* npc) const
{
    assert(false);
    //LOG( "npc_id="+std::to_string(npc->id())+" EXIT MacroScenarioGoodsTrading");
}

/* virtual */
std::string MacroScenarioGoodsTrading::GetDescription(Npc* npc) const
{
    return "MacroScenarioGoodsTrading";
}
