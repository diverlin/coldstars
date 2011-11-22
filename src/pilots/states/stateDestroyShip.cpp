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


StateDestroyShip :: StateDestroyShip()
{}


StateDestroyShip :: ~StateDestroyShip()
{}
		
void StateDestroyShip :: Enter(Npc* _npc)
{	
	printf("npc_id = %i, STARTS hunting on npc id = %i\n", _npc->getId(), _npc->getTaskOb()->getNpc()->getId());
}

void StateDestroyShip :: update_inStatic(Npc* _npc)
{
	// HJ
	_npc->getShip()->weapon_selector.setAll(true);
	_npc->getShip()->selectWeapons();
	_npc->getShip()->setWeaponsTarget(_npc->getTaskOb()->getNpc()->getShip());
                      
                             
	_npc->getShip()->getNavigator()->setTarget(_npc->getTaskOb()->getNpc()->getShip(), FOLLOWING_MIDDLE_NAVIGATOR_ACTION_ID );
}

void StateDestroyShip :: update_inDynamic(Npc* _npc)
{}

void StateDestroyShip :: Exit(Npc* _npc)
{
	printf("npc_id = %i, STOPS hunting on npc id = %i\n", _npc->getId(), _npc->getTaskOb()->getNpc()->getId());
}
