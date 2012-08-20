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

#include "MicroScenarioDocking.hpp"
#include "../../../common/constants.hpp"
#include "../../../common/Logger.hpp"
#include "../../../common/myStr.hpp"
#include "../../../spaceobjects/Vehicle.hpp"

MicroScenarioDocking::MicroScenarioDocking()
{
	type_id = MICROSCENARIO::DOCKING_ID;
}


MicroScenarioDocking::~MicroScenarioDocking()
{}
		
void MicroScenarioDocking::Enter(Npc* npc) const
{	
	npc->GetVehicle()->GetDriveComplex()->SetTarget(npc->GetStateMachine()->GetMicroTaskManager()->GetMicroTask()->GetTarget(), NAVIGATOR_ACTION::DOCKING_ID);

	#if LOG_ENABLED == 1 
	Logger::Instance().Log( "npc_id="+int2str(npc->GetId())+" ENTER MicroScenarioDocking, docking to ob_id="+int2str(npc->GetStateMachine()->GetMicroTaskManager()->GetMicroTask()->GetTarget()->GetId()) ); 
	#endif
}

bool MicroScenarioDocking::Validate(Npc* npc) const
{
	if (npc->GetVehicle()->GetPlaceTypeId() == ENTITY::SPACE_ID)
	{
		return true;
	}

	return false;
}

void MicroScenarioDocking::UpdateInStaticInSpace(Npc* npc) const
{}

void MicroScenarioDocking::UpdateInDynamicInSpace(Npc* npc) const
{
     	if (npc->GetVehicle()->GetDriveComplex()->CheckTargetEchievement() == true)
     	{
     		if (npc->GetVehicle()->GetDriveComplex()->GetDockingPermission() == true)
     		{
     			npc->GetVehicle()->SetSpecialActionId(SPECIAL_ACTION::INITIATE_DOCKING_ID);
     		}
     		else
     		{
     			// wait or reset
     		}
     	}
}

void MicroScenarioDocking::Exit(Npc* npc) const 
{
	#if LOG_ENABLED == 1 
	Logger::Instance().Log("npc_id="+int2str( npc->GetId())+" _EXIT MicroScenarioDocking, docking to ob_id="+int2str( npc->GetStateMachine()->GetMicroTaskManager()->GetMicroTask()->GetTarget()->GetId() ) ); 
	#endif
}


std::string MicroScenarioDocking::GetDescription(Npc* npc) const
{
	return "MicroScenarioDocking to ob_id = " + int2str( npc->GetStateMachine()->GetMicroTaskManager()->GetMicroTask()->GetTarget()->GetId());
}
