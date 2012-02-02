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
	printf("npc_id = %i, enter MicroScenarioDestroy\n", _npc->getId());
}

void MicroScenarioDestroy :: update_inStatic(Npc* _npc) const
{
	if (_npc->getStateMachine()->getCurrentMicroTask()->getTarget()->getValid() == true)
	{
		if ( (*_npc->getStateMachine()->getCurrentMicroTask()->getTarget()->getpAlive() == false) or ( _npc->getStarSystem()->getId() != _npc->getStateMachine()->getCurrentMicroTask()->getTarget()->getStarSystem()->getId()) )
		{
			_npc->getStateMachine()->getCurrentMicroTask()->getTarget()->reset();
		}

		else
		{
			_npc->getVehicle()->getWeaponComplex()->weapon_selector.setAll(true);
			_npc->getVehicle()->getWeaponComplex()->selectWeapons();
			_npc->getVehicle()->getWeaponComplex()->setWeaponsTarget(_npc->getStateMachine()->getCurrentMicroTask()->getTarget()->getNpc()->getVehicle());
                      
                             
			_npc->getVehicle()->getNavigator()->setTarget(_npc->getStateMachine()->getCurrentMicroTask()->getTarget()->getNpc()->getVehicle(), FOLLOWING_MIDDLE_NAVIGATOR_ACTION_ID ); 
		}
	}
}

void MicroScenarioDestroy :: update_inDynamic(Npc* _npc) const
{}

void MicroScenarioDestroy :: exit(Npc* _npc) const
{
	printf("npc_id = %i, exit MicroScenarioDestroy\n", _npc->getId());
}


std::string MicroScenarioDestroy :: getDescription(Npc* _npc) const
{
	return "DESTROY to ob_id" + int2str( _npc->getStateMachine()->getCurrentMicroTask()->getTarget()->getObId()) ;
}
