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

void MacroScenarioGoodsTrading::UpdateInStatic(Npc* npc) const
{
	if (npc->GetVehicle()->GetPlaceTypeId() == ENTITY::SPACE_ID)
	{
		if (npc->GetVehicle()->GetFreeSpace() > 10)
		{
			if (npc->GetCredits() > 100)
			{
				Planet* planet = npc->GetPlanetForDocking(); // find proper planet!
				MicroTask* microtask = new MicroTask(planet, MICROSCENARIO::DOCKING_ID);
				npc->GetStateMachine()->SetCurrentMicroTask(microtask);
				
				return;
			}
			else
			{
				// mineral hunting micro scenario
				
				return;
			}
		}
		else
		{
			if (npc->GetVehicle()->HasSomeGoodsInCargo() == true)
			{
				Planet* planet = npc->GetPlanetForDocking(); // find proper planet
				MicroTask* microtask = new MicroTask(planet, MICROSCENARIO::DOCKING_ID);
				npc->GetStateMachine()->SetCurrentMicroTask(microtask);
				
				return;
			}
		}
			
		
	}
}


std::string MacroScenarioGoodsTrading::GetDescription(Npc* npc) const
{
	return "MacroScenarioGoodsTrading";
}
