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
	npc->getVehicle()->getDriveComplex()->setTarget(npc->getStateMachine()->getCurrentMicroTask()->getTarget(), FOLLOWING_CLOSE_NAVIGATOR_ACTION_ID);

	npc->getVehicle()->getDriveComplex()->update_inSpace_inStatic();
	printf("npc_id = %i, is going to MicroScenarioDocking to ob id = %i\n", npc->getId(), npc->getStateMachine()->getCurrentMicroTask()->getTarget()->getId());
}

void MicroScenarioDocking :: update_inStatic(Npc* npc) const
{

}

void MicroScenarioDocking :: update_inDynamic(Npc* _npc) const
{
     	if (_npc->getVehicle()->getDriveComplex()->checkEchievement() == true)
     	{
     		if (_npc->getVehicle()->getDriveComplex()->getDockingPermission() == true)
     		{
     		     	_npc->dockEvent();
     		     	printf("npc id = %i, dockEvent()\n", _npc->getId());
     		}
     		else
     		{
     			// wait or reset
     		}
     	}
}

void MicroScenarioDocking :: exit(Npc* _npc) const 
{
	printf("npc_id = %i, finish to MicroScenarioDocking to ob id = %i\n", _npc->getId(), _npc->getStateMachine()->getCurrentMicroTask()->getTarget()->getId());
}


std::string MicroScenarioDocking :: getDescription(Npc* _npc) const
{
	return "MicroScenarioDocking to ob_id = " + int2str( _npc->getStateMachine()->getCurrentMicroTask()->getTarget()->getId());
}
