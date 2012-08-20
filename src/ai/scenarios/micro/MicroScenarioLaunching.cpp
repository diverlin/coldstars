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

#include "MicroScenarioLaunching.hpp"
#include "../../../common/constants.hpp"
#include "../../../common/Logger.hpp"
#include "../../../common/myStr.hpp"
#include "../../../spaceobjects/Vehicle.hpp"

MicroScenarioLaunching::MicroScenarioLaunching()
{
	type_id = MICROSCENARIO::LAUNCHING_ID;
}


MicroScenarioLaunching::~MicroScenarioLaunching()
{}
		
void MicroScenarioLaunching::Enter(Npc* npc) const
{	
	printf("npc_id = %i, Enter MicroScenarioLaunching\n", npc->GetId());
}

/* virtual */
bool MicroScenarioLaunching::Validate(Npc* npc) const
{
	if (npc->GetVehicle()->GetPlaceTypeId() != ENTITY::SPACE_ID)
	{
		return true;
	}

	return false;
}
		
void MicroScenarioLaunching::UpdateInStaticInSpace(Npc* npc) const
{}

void MicroScenarioLaunching::UpdateInDynamicInSpace(Npc* npc) const
{}

/* virtual */
void MicroScenarioLaunching::UpdateInStaticInDock(Npc* npc) const
{
	npc->GetVehicle()->LaunchingEvent();
	npc->GetVehicle()->SetSpecialActionId(SPECIAL_ACTION::INITIATE_LAUNCHING_ID);
}

void MicroScenarioLaunching::Exit(Npc* _npc) const 
{
	printf("npc_id = %i, finish to MicroScenarioLaunching\n", _npc->GetId());
}


std::string MicroScenarioLaunching::GetDescription(Npc* _npc) const
{
	return "MicroScenarioLaunching";
}
