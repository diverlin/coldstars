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

MineralObservationData :: MineralObservationData(Mineral* _mineral, float _dist)
{
	mineral = _mineral;
	dist = _dist;
}		


Observation :: Observation(Npc* _npc)
{ 
    	npc = _npc;
}
    
Observation :: ~Observation()
{}  
    

void Observation :: observeAll_inSpace_inStatic()
{
     	findVisibleAsteroids_inSpace_inStatic();
     	sortVisibleAsteroids_inSpace_inStatic();

     	findVisibleMinerals_inSpace_inStatic();
        sortVisibleMinerals_inSpace_inStatic();
        
     	findVisibleContainers_inSpace_inStatic();

     	findVisibleNpcs_inSpace_inStatic();
}

void Observation :: findVisibleAsteroids_inSpace_inStatic()
{
	see.ASTEROID  = false;
        visible_ASTEROID_vec.clear();
        asteroid_distance_vec.clear();

        for (unsigned int ai = 0; ai < npc->getStarSystem()->ASTEROID_vec.size(); ai++)
        {    
        	float dist = distBetweenPoints(npc->getShip()->getPoints()->getCenter(), npc->getStarSystem()->ASTEROID_vec[ai]->getPoints()->getCenter());
                if (dist < npc->getShip()->propetries.radius)
                {
                	visible_ASTEROID_vec.push_back(npc->getStarSystem()->ASTEROID_vec[ai]);
                      	asteroid_distance_vec.push_back(dist);
                      	see.ASTEROID = true;
                } 
        }
}


void Observation :: sortVisibleAsteroids_inSpace_inStatic()
{
	sorted_visible_ASTEROID_vec.clear();
	
	for (unsigned int i = 0; i<visible_ASTEROID_vec.size(); i++)
	{
		int i_min = 0;
		float min = asteroid_distance_vec[i];
		
		for (unsigned int j = i; j<visible_ASTEROID_vec.size(); j++)
		{	
        		if ( asteroid_distance_vec[j] < min )
        		{
        			i_min = j;
        			min = asteroid_distance_vec[j];
        		}
        	}
        	sorted_visible_ASTEROID_vec.push_back(visible_ASTEROID_vec[i_min]);        	
        }
}



void Observation :: findVisibleMinerals_inSpace_inStatic()
{
	see.MINERAL   = false;
        visible_MINERAL_vec.clear();

        for (unsigned int mi = 0; mi < npc->getStarSystem()->MINERAL_vec.size(); mi++)
        {    
         	float dist = distBetweenPoints(npc->getShip()->getPoints()->getCenter(), npc->getStarSystem()->MINERAL_vec[mi]->getPoints()->getCenter());
               	if (dist < npc->getShip()->propetries.radius)
              	{
              		
               		visible_MINERAL_vec.push_back(MineralObservationData(npc->getStarSystem()->MINERAL_vec[mi], dist));
              		see.MINERAL = true;
               	} 
        }
}


void Observation :: sortVisibleMinerals_inSpace_inStatic()
{
	for (unsigned int i = 0; i < visible_MINERAL_vec.size(); i++)
	{
		int i_min = i;
		float min = visible_MINERAL_vec[i].dist;
		
		for (unsigned int j = i; j < visible_MINERAL_vec.size(); j++)
		{	
        		if ( visible_MINERAL_vec[j].dist < min )
        		{
        			i_min = j;
        			min = visible_MINERAL_vec[j].dist;
        		}
        	}
        	MineralObservationData tmp = visible_MINERAL_vec[i];
        	visible_MINERAL_vec[i]     = visible_MINERAL_vec[i_min];
        	visible_MINERAL_vec[i_min] = tmp;
        }
}



	//for (unsigned int i = 0; i<visible_MINERAL_vec.size(); i++)
	//{
		//int i_min = 0;
		//float min = mineral_distance_vec[i];
		
		//for (unsigned int j = 0; j<visible_MINERAL_vec.size(); j++)
		//{	
        		//if ( mineral_distance_vec[j] < min )
        		//{
        			//i_min = j;
        			//min = mineral_distance_vec[j];
        		//}
        	//}
        	//sorted_visible_MINERAL_vec.push_back(visible_MINERAL_vec[i_min]);        	
        //}


void Observation :: findVisibleContainers_inSpace_inStatic()
{
	see.CONTAINER   = false;
        visible_CONTAINER_vec.clear();
        container_distance_vec.clear();

        for (unsigned int ci = 0; ci < npc->getStarSystem()->CONTAINER_vec.size(); ci++)
        {    
        	float dist = distBetweenPoints(npc->getShip()->getPoints()->getCenter(), npc->getStarSystem()->CONTAINER_vec[ci]->getPoints()->getCenter());
                if (dist < npc->getShip()->propetries.radius)
                {
                	visible_CONTAINER_vec.push_back(npc->getStarSystem()->CONTAINER_vec[ci]);
                	container_distance_vec.push_back(dist);
                	see.CONTAINER = true;
                } 
    	}

}


void Observation ::findVisibleNpcs_inSpace_inStatic()
{
	findVisibleRangerNpcs_inSpace_inStatic();
        findVisibleWarriorNpcs_inSpace_inStatic();
        findVisibleTraderNpcs_inSpace_inStatic();
        findVisiblePiratNpcs_inSpace_inStatic();
        findVisibleDiplomatNpcs_inSpace_inStatic();
}


void Observation :: findVisibleRangerNpcs_inSpace_inStatic()
{
	see.RANGER = false;
        visible_NPC_RANGER_vec.clear();
        npc_ranger_distance_vec.clear();

        for (unsigned int nri = 0; nri < npc->getStarSystem()->NPC_RANGER_inSPACE_vec.size(); nri++)
        {    
        	float dist = distBetweenPoints(npc->getShip()->getPoints()->getCenter(), npc->getStarSystem()->NPC_RANGER_inSPACE_vec[nri]->getShip()->getPoints()->getCenter());
                if (dist < npc->getShip()->propetries.radius)
                {
                	visible_NPC_RANGER_vec.push_back(npc->getStarSystem()->NPC_RANGER_inSPACE_vec[nri]);
                        npc_ranger_distance_vec.push_back(dist);
                        see.RANGER = true;
               	} 
       }
}


void Observation :: findVisibleWarriorNpcs_inSpace_inStatic()
{
	see.WARRIOR = false;
        visible_NPC_WARRIOR_vec.clear();
        npc_warrior_distance_vec.clear();

        for (unsigned int nwi = 0; nwi < npc->getStarSystem()->NPC_WARRIOR_inSPACE_vec.size(); nwi++)
        {    
        	float dist = distBetweenPoints(npc->getShip()->getPoints()->getCenter(), npc->getStarSystem()->NPC_WARRIOR_inSPACE_vec[nwi]->getShip()->getPoints()->getCenter());
               	if (dist < npc->getShip()->propetries.radius)
              	{
               		visible_NPC_WARRIOR_vec.push_back(npc->getStarSystem()->NPC_WARRIOR_inSPACE_vec[nwi]);
              		npc_warrior_distance_vec.push_back(dist);
               		see.WARRIOR = true;
              	} 
        }
} 


void Observation :: findVisibleTraderNpcs_inSpace_inStatic()
{
       see.TRADER = false;
       visible_NPC_TRADER_vec.clear();
       npc_trader_distance_vec.clear();

       for (unsigned int nti = 0; nti < npc->getStarSystem()->NPC_TRADER_inSPACE_vec.size(); nti++)
       {    
       		float dist = distBetweenPoints(npc->getShip()->getPoints()->getCenter(), npc->getStarSystem()->NPC_TRADER_inSPACE_vec[nti]->getShip()->getPoints()->getCenter());
               	if (dist < npc->getShip()->propetries.radius)
               	{
               		visible_NPC_TRADER_vec.push_back(npc->getStarSystem()->NPC_TRADER_inSPACE_vec[nti]);
               		npc_trader_distance_vec.push_back(dist);
               		see.TRADER = true;
              	} 
       }
}


void Observation :: findVisiblePiratNpcs_inSpace_inStatic()
{
     	see.PIRAT = false;
        visible_NPC_PIRAT_vec.clear();
        npc_pirat_distance_vec.clear();

        for (unsigned int npi = 0; npi < npc->getStarSystem()->NPC_PIRAT_inSPACE_vec.size(); npi++)
        {    
       		float dist = distBetweenPoints(npc->getShip()->getPoints()->getCenter(), npc->getStarSystem()->NPC_PIRAT_inSPACE_vec[npi]->getShip()->getPoints()->getCenter());
               	if (dist < npc->getShip()->propetries.radius)
               	{
               		visible_NPC_PIRAT_vec.push_back(npc->getStarSystem()->NPC_PIRAT_inSPACE_vec[npi]);
               		npc_pirat_distance_vec.push_back(dist);
               		see.PIRAT = true;
               	} 
       }
}


void Observation :: findVisibleDiplomatNpcs_inSpace_inStatic()
{
 	see.DIPLOMAT = false;
        visible_NPC_DIPLOMAT_vec.clear();
        npc_diplomat_distance_vec.clear();

        for (unsigned int ndi = 0; ndi < npc->getStarSystem()->NPC_DIPLOMAT_inSPACE_vec.size(); ndi++)
        {    
         	float dist = distBetweenPoints(npc->getShip()->getPoints()->getCenter(), npc->getStarSystem()->NPC_DIPLOMAT_inSPACE_vec[ndi]->getShip()->getPoints()->getCenter());
               	if (dist < npc->getShip()->propetries.radius)
               	{
               		visible_NPC_DIPLOMAT_vec.push_back(npc->getStarSystem()->NPC_DIPLOMAT_inSPACE_vec[ndi]);
               		npc_diplomat_distance_vec.push_back(dist);
               		see.DIPLOMAT = true;
              	} 
        }
}


void Observation :: printVisibleMineralInformation() const
{
	printf("visible_MINERAL_vec for npc_id = %i\n", npc->getId());
	for (unsigned int i = 0; i < visible_MINERAL_vec.size(); i++)
        {                   
        	printf("%i ", visible_MINERAL_vec[i].mineral->getId());                                              
	}
	printf("\n");
	
	for (unsigned int i = 0; i < visible_MINERAL_vec.size(); i++)
        {                   
        	printf("%f ", visible_MINERAL_vec[i].dist);                                              
	}
	printf("\n");
}
               	


