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


MicroScenarioDestroy::MicroScenarioDestroy()
{}

MicroScenarioDestroy::~MicroScenarioDestroy()
{}
		
void MicroScenarioDestroy::Enter(Npc* npc) const
{	
	printf("npc_id = %i, enter MicroScenarioDestroy\n", npc->GetId());
}

void MicroScenarioDestroy::UpdateInStatic(Npc* npc) const
{
	if (npc->GetStateMachine()->GetMicroTaskHolder()->GetScenario() != NULL)
	{
		if ( (npc->GetStateMachine()->GetMicroTaskHolder()->GetTarget()->GetAlive() == true) or ( npc->GetStarSystem() == npc->GetStateMachine()->GetMicroTaskHolder()->GetTarget()->GetStarSystem()) )
		{
			npc->GetVehicle()->GetWeaponComplex()->ActivateAllWeapons();
			//npc->GetVehicle()->GetWeaponComplex()->SetTarget(npc->GetStateMachine()->GetMicroTaskHolder()->GetTarget()->GetNpc()->GetVehicle());
                        //npc->GetVehicle()->GetDriveComplex()->SetTarget(npc->GetStateMachine()->GetMicroTaskHolder()->GetTarget()->GetNpc()->GetVehicle(), FOLLOWING_MIDDLE_NAVIGATOR_ACTION_ID ); 
		}
	}
}

void MicroScenarioDestroy::UpdateInDynamic(Npc* npc) const
{
	if (npc->GetStateMachine()->GetMicroTaskHolder()->GetTarget()->GetAlive() == false)
	{
		npc->GetStateMachine()->GetMicroTaskHolder()->SetResult(SUCCESS_ID);
	}
	
	if (npc->GetStarSystem() != npc->GetStateMachine()->GetMicroTaskHolder()->GetTarget()->GetStarSystem())
	{
		npc->GetStateMachine()->GetMicroTaskHolder()->SetResult(FAIL_ID);
	}
	
}

void MicroScenarioDestroy::Exit(Npc* npc) const
{
	printf("npc_id = %i, exit MicroScenarioDestroy\n", npc->GetId());
}


std::string MicroScenarioDestroy::GetDescription(Npc* npc) const
{
	return "DESTROY to ob_id" + int2str( npc->GetStateMachine()->GetMicroTaskHolder()->GetTarget()->GetId()) ;
}
