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


MicroScenarioDocking :: MicroScenarioDocking()
{}


MicroScenarioDocking :: ~MicroScenarioDocking()
{}
		
void MicroScenarioDocking :: enter(Npc* npc) const
{	
	npc->GetVehicle()->GetDriveComplex()->setTarget(npc->GetStateMachine()->getCurrentMicroTask()->getTarget(), NAVIGATOR_ACTION::KEEP_CLOSE_ID);

	npc->GetVehicle()->GetDriveComplex()->Update_inSpace_inStatic();
	printf("npc_id = %i, is going to MicroScenarioDocking to ob id = %i\n", npc->GetId(), npc->GetStateMachine()->getCurrentMicroTask()->getTarget()->GetId());
}

void MicroScenarioDocking :: update_inStatic(Npc* npc) const
{

}

void MicroScenarioDocking :: update_inDynamic(Npc* _npc) const
{
     	if (_npc->GetVehicle()->GetDriveComplex()->checkEchievement() == true)
     	{
     		if (_npc->GetVehicle()->GetDriveComplex()->getDockingPermission() == true)
     		{
     		     	_npc->GetVehicle()->DockingEvent();
     		     	printf("npc id = %i, dockEvent()\n", _npc->GetId());
     		}
     		else
     		{
     			// wait or reset
     		}
     	}
}

void MicroScenarioDocking :: exit(Npc* _npc) const 
{
	printf("npc_id = %i, finish to MicroScenarioDocking to ob id = %i\n", _npc->GetId(), _npc->GetStateMachine()->getCurrentMicroTask()->getTarget()->GetId());
}


std::string MicroScenarioDocking :: getDescription(Npc* _npc) const
{
	return "MicroScenarioDocking to ob_id = " + int2str( _npc->GetStateMachine()->getCurrentMicroTask()->getTarget()->GetId());
}
