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
#include "../../../common/Logger.hpp"
#include "../../../common/myStr.hpp"
#include "../../../ai/StateMachine.hpp"

#include "../../../items/others/GoodsPack.hpp"

MacroScenarioGoodsTrading::MacroScenarioGoodsTrading() 
{
	type_id = MACROSCENARIO::GOODSTRADING_ID;
}

MacroScenarioGoodsTrading::~MacroScenarioGoodsTrading() 
{}

bool MacroScenarioGoodsTrading::IsAbleToBuyGoods(Npc* npc) const
{
	if (npc->GetVehicle()->GetFreeSpace() > 10)
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
	#if AISCENARIO_LOG_ENABLED == 1 
	Logger::Instance().Log( "npc_id="+int2str(npc->GetId())+" ENTER MacroScenarioGoodsTrading"); 
	#endif
}

/* virtual */
bool MacroScenarioGoodsTrading::Validation(Npc* npc) const
{
	if (npc->GetVehicle()->GetGoodsPack() == NULL)
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
	bool see_container = npc->GetObservation().GetVisionStatus().CONTAINER;
	bool able_buy      = IsAbleToBuyGoods(npc);
	bool has_goods     = false;
	if (npc->GetVehicle()->GetGoodsPack() != NULL)
	{
		has_goods = true;
	}
	int microScenarioTypeId = npc->GetStateMachine().GetMicroTaskManager().GetTask().GetScenarioTypeId();
	
	// LOGIC
	if ( (see_container == true) and (has_goods == false) )
	{	
		if (microScenarioTypeId != MICROSCENARIO::GRAB_ID) 
		{
			Container* container = npc->GetObservation().GetClosestContainer(); // find proper!
			Task microtask(MICROSCENARIO::GRAB_ID, container->GetId());
			npc->GetStateMachine().SetCurrentMicroTask(microtask); 
			
			return;
		}
	}

	if ( (has_goods == false) and (able_buy == false) )
	{
		if (microScenarioTypeId != MICROSCENARIO::EXPLORATION_ID) 
		{
			Task microtask(MICROSCENARIO::EXPLORATION_ID);
			npc->GetStateMachine().SetCurrentMicroTask(microtask); 
				
			return;
		}
	}
	
	if ( (has_goods == false) and (able_buy == true) )
	{
		if (microScenarioTypeId != MICROSCENARIO::DOCKING_ID)
		{
			Planet* planet = npc->GetPlanetForDocking(); // find proper planet!
			Task microtask(MICROSCENARIO::DOCKING_ID, planet->GetId());
			npc->GetStateMachine().SetCurrentMicroTask(microtask); 
				
			return;
		}
	}
			
	if (has_goods == true)
	{
		if (microScenarioTypeId != MICROSCENARIO::DOCKING_ID)
		{
			Planet* planet = npc->GetPlanetForDocking(); // find proper planet
			Task microtask(MICROSCENARIO::DOCKING_ID, planet->GetId());
			npc->GetStateMachine().SetCurrentMicroTask(microtask);
			
			return;
		}
	}
}

/* virtual */
void MacroScenarioGoodsTrading::UpdateInStaticInDock(Npc* npc) const
{
	GoodsPack* goods_pack = npc->GetVehicle()->GetGoodsPack(); 
	while(goods_pack != NULL)
	{
		npc->GetVehicle()->SellItem(goods_pack);
		goods_pack = npc->GetVehicle()->GetGoodsPack(); 
	}
	
	if (IsAbleToBuyGoods(npc) == true)
	{
		npc->BuyGoods();
	}

	Task microtask(MICROSCENARIO::LAUNCHING_ID);
	npc->GetStateMachine().SetCurrentMicroTask(microtask);		
}

void MacroScenarioGoodsTrading::Exit(Npc* npc) const
{
	#if AISCENARIO_LOG_ENABLED == 1 
	Logger::Instance().Log( "npc_id="+int2str(npc->GetId())+" EXIT MacroScenarioGoodsTrading"); 
	#endif
}

/* virtual */
std::string MacroScenarioGoodsTrading::GetDescription(Npc* npc) const
{
	return "MacroScenarioGoodsTrading";
}
