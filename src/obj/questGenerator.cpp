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

//bool mineralCollecting(Npc* npc)
//{
        //StarSystem* taret_starsystem = npc->getStarSystem();
        //npc->getQuestOb()->setTask(taret_starsystem, GRABBING_GOODS_QUEST_ID);

        //return true;        
//}


//bool liberationStarSystemQuestGenerator(Npc* npc)
//{
	////StarSystem* taret_starsystem = g_GALAXY->getRandomCapturedStarSystem();
	////npc->getQuestOb()->setTask(taret_starsystem, LIBERATION_STARSYSTEM_QUEST_ID);

        ////return true;
//}


//bool destroyShipQuestGenerator(Npc* npc)
//{
	//Npc* target_npc = NULL;
	
	//int counter = 0;
	//do
	//{ 
                //target_npc = g_GALAXY->getRandomStarSystem()->getRandomNpc();
		////target_npc = npc->getStarSystem()->getRandomNpc();
		//counter++;
	//} 
	//while ( (npc->getId() == target_npc->getId() ) and (counter < 20) );
	
	//if (target_npc != NULL)
	//{
		//if (npc->getId() != target_npc->getId())
		//{
			//npc->getQuestOb()->setObject(target_npc);
			//return true;
		//}
	//}

	//return false;
//}

//bool questEvilGenerator(Npc* npc)
//{
        //Npc* target_npc = NULL;
	
	//int counter = 0;
	//do
	//{
		//target_npc = npc->getStarSystem()->getRandomNpcExcludingRaceId(npc->getRaceId());
		//counter++;
	//} 
	//while ( (npc->getId() == target_npc->getId() ) and (counter < 20) );
	
	//if (target_npc != NULL)
	//{
		//if (npc->getId() != target_npc->getId())
		//{
			//npc->getQuestOb()->setObject(target_npc);
			//return true;
		//}
	//}

	//return false;
//}
