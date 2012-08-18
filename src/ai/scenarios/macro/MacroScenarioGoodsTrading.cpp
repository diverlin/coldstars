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
#include "../../../common/constants.hpp"
#include "../../../spaceobjects/Planet.hpp"

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
		
void MacroScenarioGoodsTrading::UpdateInStaticInSpace(Npc* npc) const
{
	if (npc->GetVehicle()->GetGoodsPack() == NULL)
	{
		if (IsAbleToBuyGoods(npc) == true)
		{
			if (npc->GetStateMachine()->GetMicroTaskManager()->GetMicroTask()->GetScenarioTypeId() != MICROSCENARIO::DOCKING_ID)
			{
				Planet* planet = npc->GetPlanetForDocking(); // find proper planet!
				MicroTask* microtask = new MicroTask(MICROSCENARIO::DOCKING_ID, planet);
				npc->GetStateMachine()->SetCurrentMicroTask(microtask);
				
				return;
			}
		}

		if (IsAbleToBuyGoods(npc) == false)
		{
	
			//if (npc->GetStateMachine()->GetMicroTaskManager()->GetMicroTask()->GetScenarioTypeId() != MICROSCENARIO::MINERAL_HARVEST) 
			{
				// mineral hunting micro scenario
				
				return;
			}
		}
	}
	else
	{
		if (npc->GetStateMachine()->GetMicroTaskManager()->GetMicroTask()->GetScenarioTypeId() != MICROSCENARIO::DOCKING_ID)
		{
			Planet* planet = npc->GetPlanetForDocking(); // find proper planet
			MicroTask* microtask = new MicroTask(MICROSCENARIO::DOCKING_ID, planet);
			npc->GetStateMachine()->SetCurrentMicroTask(microtask);
			
			return;
		}
	}

}


void MacroScenarioGoodsTrading::UpdateInStaticInDock(Npc* npc) const
{
	GoodsPack* goods_pack = npc->GetVehicle()->GetGoodsPack(); 
	while(goods_pack != NULL)
	{
		npc->SellGoods(goods_pack);
		goods_pack = npc->GetVehicle()->GetGoodsPack(); 
	}
	
	if (IsAbleToBuyGoods(npc) == true)
	{
		npc->BuyGoods();
	}

	MicroTask* microtask = new MicroTask(MICROSCENARIO::LAUNCHING_ID);
	npc->GetStateMachine()->SetCurrentMicroTask(microtask);		
}

std::string MacroScenarioGoodsTrading::GetDescription(Npc* npc) const
{
	return "MacroScenarioGoodsTrading";
}
