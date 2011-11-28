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
	printf("npc_id = %i, enter MicroScenarioDestroy (hunting on npc id = %i)\n", _npc->getId(), _npc->getMicroTask()->getTarget()->getNpc()->getId());
}

void MicroScenarioDestroy :: update_inStatic(Npc* _npc) const
{
	if (_npc->getMicroTask()->getTarget()->getValid() == true)
	{
		if ( (*_npc->getMicroTask()->getTarget()->getpAlive() == false) or ( _npc->getStarSystem()->getId() != _npc->getMicroTask()->getTarget()->getStarSystem()->getId()) )
		{
			_npc->getMicroTask()->getTarget()->reset();
		}

		else
		{
			_npc->getShip()->weapon_selector.setAll(true);
			_npc->getShip()->selectWeapons();
			_npc->getShip()->setWeaponsTarget(_npc->getMicroTask()->getTarget()->getNpc()->getShip());
                      
                             
			_npc->getShip()->getNavigator()->setTarget(_npc->getMicroTask()->getTarget()->getNpc()->getShip(), FOLLOWING_MIDDLE_NAVIGATOR_ACTION_ID );
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
	return "DESTROY to ob_id" + int2str( _npc->getMicroTask()->getTarget()->getObId()) ;
}
