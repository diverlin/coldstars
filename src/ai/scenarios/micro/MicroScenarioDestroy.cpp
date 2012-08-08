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

#include "MicroScenarioDestroy.hpp"
#include "../../../common/constants.hpp"
#include "../../../common/Logger.hpp"
#include "../../../common/myStr.hpp"
#include "../../../spaceobjects/Vehicle.hpp"

MicroScenarioDestroy::MicroScenarioDestroy()
{
	type_id = MICROSCENARIO::DESTROY_ID;
}

/* virtual */
MicroScenarioDestroy::~MicroScenarioDestroy()
{}
	
bool MicroScenarioDestroy::Validate(Npc* npc) const
{	
	if (npc->GetStateMachine()->GetMicroTaskManager()->GetMicroTask()->GetTarget()->GetAlive() == false)
	{
		return false;
	} 
	
	if (npc->GetStarSystem() != npc->GetStateMachine()->GetMicroTaskManager()->GetMicroTask()->GetTarget()->GetStarSystem())
	{
		 return false;
	}
	
	return true;		
}
				
void MicroScenarioDestroy::Enter(Npc* npc) const
{	
	Logger::Instance().Log("npc_id=" + int2str(npc->GetId()) + ", enter MicroScenarioDestroy");
}

void MicroScenarioDestroy::UpdateInStatic(Npc* npc) const
{
	npc->GetVehicle()->GetWeaponComplex()->ActivateAllWeapons();
	npc->GetVehicle()->GetWeaponComplex()->SetTarget(npc->GetStateMachine()->GetMicroTaskManager()->GetMicroTask()->GetTarget());
        npc->GetVehicle()->GetDriveComplex()->SetTarget(npc->GetStateMachine()->GetMicroTaskManager()->GetMicroTask()->GetTarget(), NAVIGATOR_ACTION::KEEP_MIDDLE_ID); 
}

void MicroScenarioDestroy::UpdateInDynamic(Npc* npc) const
{}

void MicroScenarioDestroy::Exit(Npc* npc) const
{
	Logger::Instance().Log("npc_id=" + int2str(npc->GetId()) + ", exit MicroScenarioDestroy");
}


std::string MicroScenarioDestroy::GetDescription(Npc* npc) const
{
	return "DESTROY ob_id=" + int2str( npc->GetStateMachine()->GetMicroTaskManager()->GetMicroTask()->GetTarget()->GetId()) ;
}
