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


StateDocking :: StateDocking()
{}


StateDocking :: ~StateDocking()
{}
		
void StateDocking :: enter(Npc* _npc)
{	
	printf("npc_id = %i, is going to DOCKING to ob id = %i\n", _npc->getId(), _npc->getTaskOb()->getObId());
}

void StateDocking :: update_inStatic(Npc* _npc)
{

}

void StateDocking :: update_inDynamic(Npc* _npc)
{
     	if (_npc->getShip()->getNavigator()->checkEchievement() == true)
     	{
     		if (_npc->getShip()->getNavigator()->getDockingPermission() == true)
     		{
     		     	_npc->dockEvent();
     		}
     		else
     		{
     			// wait or reset
     		}
     	}
}

void StateDocking :: exit(Npc* _npc)
{
	printf("npc_id = %i, finish to DOCKING to ob id = %i\n", _npc->getId(), _npc->getTaskOb()->getObId());
}
