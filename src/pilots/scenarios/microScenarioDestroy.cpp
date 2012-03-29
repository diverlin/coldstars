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


MicroScenarioDestroy :: MicroScenarioDestroy()
{}

MicroScenarioDestroy :: ~MicroScenarioDestroy()
{}
		
void MicroScenarioDestroy :: enter(Npc* _npc) const
{	
	printf("npc_id = %i, enter MicroScenarioDestroy\n", _npc->GetId());
}

void MicroScenarioDestroy :: update_inStatic(Npc* _npc) const
{
	if (_npc->getStateMachine()->getCurrentMicroTask()->getValid() == true)
	{
		if ( (_npc->getStateMachine()->getCurrentMicroTask()->getTarget()->GetAlive() == true) or ( _npc->GetStarSystem() == _npc->getStateMachine()->getCurrentMicroTask()->getTarget()->GetStarSystem()) )
		{
			_npc->getVehicle()->GetWeaponComplex()->weapon_selector.setAll(true);
			_npc->getVehicle()->GetWeaponComplex()->SelectWeapons();
			//_npc->getVehicle()->getWeaponComplex()->setTarget(_npc->getStateMachine()->getCurrentMicroTask()->getTarget()->getNpc()->getVehicle());
                                                   
			//_npc->getVehicle()->getDriveComplex()->setTarget(_npc->getStateMachine()->getCurrentMicroTask()->getTarget()->getNpc()->getVehicle(), FOLLOWING_MIDDLE_NAVIGATOR_ACTION_ID ); 
		}
		else
		{
			_npc->getStateMachine()->getCurrentMicroTask()->reset();
		}
	}
}

void MicroScenarioDestroy :: update_inDynamic(Npc* _npc) const
{}

void MicroScenarioDestroy :: exit(Npc* _npc) const
{
	printf("npc_id = %i, exit MicroScenarioDestroy\n", _npc->GetId());
}


std::string MicroScenarioDestroy :: getDescription(Npc* _npc) const
{
	return "DESTROY to ob_id" + int2str( _npc->getStateMachine()->getCurrentMicroTask()->getTarget()->GetId()) ;
}
