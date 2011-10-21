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


bool taskGenerator(Npc* npc)
{
	if ( (npc->getShip()->needsToDo.REPAIR == true) and (npc->getTaskOb()->getActionId() != LANDING_TASK_ID) )
	{
        	Planet* _target_planet = npc->getPlanetForDocking();  // depending on purpouse
		npc->getTaskOb()->setTask(_target_planet, LANDING_TASK_ID);
		
		printf("trololo\n");
		return true;
	}
	
	return false;
}


bool questGenerator(Npc* npc)
{
	Npc* target_npc = NULL;
	
	int counter = 0;
	do
	{
		target_npc = npc->getStarSystem()->getRandomNpc();
		counter++;
	} 
	while ( (npc->getId() == target_npc->getId() ) and (counter < 20) );
	
	if (target_npc != NULL)
	{
		if (npc->getId() != target_npc->getId())
		{
			npc->getQuestOb()->setTask(target_npc, DESTROY_TASK_ID);
			return true;
		}
	}

	return false;
	
}
