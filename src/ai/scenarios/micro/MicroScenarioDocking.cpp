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


MicroScenarioDocking::MicroScenarioDocking()
{
	type_id = MICROSCENARIO::DOCKING_ID;
}


MicroScenarioDocking::~MicroScenarioDocking()
{}
		
void MicroScenarioDocking::Enter(Npc* npc) const
{	
	npc->GetVehicle()->GetDriveComplex()->SetTarget(npc->GetStateMachine()->GetMicroTaskManager()->GetMicroTask()->GetTarget(), NAVIGATOR_ACTION::KEEP_CLOSE_ID);

	printf("npc_id = %i, is going to MicroScenarioDocking to ob id = %i\n", npc->GetId(), npc->GetStateMachine()->GetMicroTaskManager()->GetMicroTask()->GetTarget()->GetId());
}

void MicroScenarioDocking::UpdateInStatic(Npc* npc) const
{

}

void MicroScenarioDocking::UpdateInDynamic(Npc* npc) const
{
     	if (npc->GetVehicle()->GetDriveComplex()->CheckTargetEchievement() == true)
     	{
     		if (npc->GetVehicle()->GetDriveComplex()->GetDockingPermission() == true)
     		{
	     		if (npc->GetVehicle()->DockingEffect() == true)
     	     		{
     	     			npc->GetVehicle()->DockingEvent();
     	     			printf("npc id = %i, DockingEvent()\n", npc->GetId());
     			}
     		}
     		else
     		{
     			// wait or reset
     		}
     	}
}

void MicroScenarioDocking::Exit(Npc* _npc) const 
{
	printf("npc_id = %i, finish to MicroScenarioDocking to ob id = %i\n", _npc->GetId(), _npc->GetStateMachine()->GetMicroTaskManager()->GetMicroTask()->GetTarget()->GetId());
}


std::string MicroScenarioDocking::GetDescription(Npc* _npc) const
{
	return "MicroScenarioDocking to ob_id = " + int2str( _npc->GetStateMachine()->GetMicroTaskManager()->GetMicroTask()->GetTarget()->GetId());
}
