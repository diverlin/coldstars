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

ContainerObservationData :: ContainerObservationData(Container* _container, float _dist)
{
	container = _container;
	dist = _dist;
}	

AsteroidObservationData :: AsteroidObservationData(Asteroid* _asteroid, float _dist)
{
	asteroid = _asteroid;
	dist = _dist;
}	

NpcObservationData :: NpcObservationData(Npc* _npc, float _dist)
{
	npc = _npc;
	dist = _dist;
}	

StarSystemObservationData :: StarSystemObservationData(StarSystem* _starsystem, float _dist)
{
	starsystem = _starsystem;
	dist = _dist;
}	



Observation :: Observation(Npc* _npc)
{ 
    	npc_owner = _npc;
}
    
Observation :: ~Observation()
{}  
    
    
void Observation :: findEchievableStarSystems_inStatic(Galaxy* galaxy)
{
        visible_STARSYSTEM_vec.clear();

        for (unsigned int i = 0; i < galaxy->STARSYSTEM_vec.size(); i++)
        {    
        	float dist = distBetweenPoints(npc_owner->getVehicle()->GetStarSystem()->getPosition(),  galaxy->STARSYSTEM_vec[i]->getPosition());
                //if (dist < npc_owner->getShip()->propetries.hyper)
                {
                	visible_STARSYSTEM_vec.push_back( StarSystemObservationData(galaxy->STARSYSTEM_vec[i], dist) );
                } 
        }
        
        sort(&visible_STARSYSTEM_vec);
}
          
          
StarSystem* Observation :: getClosestStarSystem(bool _captured) const
{
	StarSystem* _target_starsystem = NULL;
	
 	for (unsigned int i = 0; i<visible_STARSYSTEM_vec.size(); i++)
 	{
 		if (visible_STARSYSTEM_vec[i].starsystem->getCaptured() == _captured)
 		{
 			_target_starsystem = visible_STARSYSTEM_vec[i].starsystem;
 			break;
 		}
 	}   
 	
 	return _target_starsystem;   	
}    	


Npc* Observation :: getClosestNpc(std::vector<int>* _pVec_race_id) const
{
	for (unsigned int i = 0; i < visible_NPC_vec.size(); i++)
        {
        	for (unsigned int j = 0; j < _pVec_race_id->size(); j++)
        	{
        		if ( visible_NPC_vec[i].npc->getRaceId() == (*_pVec_race_id)[j] )
        		{
        			return visible_NPC_vec[i].npc;

        		}
        	}
        }
        
	return NULL;	
}

void Observation :: observeAll_inSpace_inStatic()
{
     	findVisibleAsteroids_inSpace_inStatic();
     	findVisibleMinerals_inSpace_inStatic();
        
     	findVisibleContainers_inSpace_inStatic();

     	findVisibleNpcs_inSpace_inStatic();
}

void Observation :: findVisibleAsteroids_inSpace_inStatic()
{
	see.ASTEROID  = false;
        visible_ASTEROID_vec.clear();

        for (unsigned int ai = 0; ai < npc_owner->GetStarSystem()->ASTEROID_vec.size(); ai++)
        {    
        	float dist = distBetweenPoints(npc_owner->getVehicle()->GetPoints().getCenter(), npc_owner->GetStarSystem()->ASTEROID_vec[ai]->GetPoints().getCenter());
                if (dist < npc_owner->getVehicle()->propetries.radius)
                {
                	visible_ASTEROID_vec.push_back( AsteroidObservationData(npc_owner->GetStarSystem()->ASTEROID_vec[ai], dist) );
                      	see.ASTEROID = true;
                } 
        }
        
        sort(&visible_ASTEROID_vec);
}



void Observation :: findVisibleMinerals_inSpace_inStatic()
{
	see.MINERAL   = false;
        visible_MINERAL_vec.clear();

        for (unsigned int mi = 0; mi < npc_owner->GetStarSystem()->MINERAL_vec.size(); mi++)
        {    
         	float dist = distBetweenPoints(npc_owner->getVehicle()->GetPoints().getCenter(), npc_owner->GetStarSystem()->MINERAL_vec[mi]->GetPoints().getCenter());
               	if (dist < npc_owner->getVehicle()->propetries.radius)
              	{              		
               		visible_MINERAL_vec.push_back(MineralObservationData(npc_owner->GetStarSystem()->MINERAL_vec[mi], dist));
              		see.MINERAL = true;
               	} 
        }
        
        sort(&visible_MINERAL_vec);
}

template <typename OBSERVED_DATA_TYPE>
void Observation :: sort(std::vector<OBSERVED_DATA_TYPE>* pDataVec)
{
	for (unsigned int i = 0; i < pDataVec->size(); i++)
	{
		int i_min = i;
		float min = (*pDataVec)[i].dist;
		
		for (unsigned int j = i; j < pDataVec->size(); j++)
		{	
        		if ( (*pDataVec)[j].dist < min )
        		{
        			i_min = j;
        			min = (*pDataVec)[j].dist;
        		}
        	}
        	OBSERVED_DATA_TYPE tmp = (*pDataVec)[i];
        	(*pDataVec)[i]         = (*pDataVec)[i_min];
        	(*pDataVec)[i_min]     = tmp;
        }
}




void Observation :: findVisibleContainers_inSpace_inStatic()
{
	see.CONTAINER   = false;
        visible_CONTAINER_vec.clear();

        for (unsigned int ci = 0; ci < npc_owner->GetStarSystem()->CONTAINER_vec.size(); ci++)
        {    
        	float dist = distBetweenPoints(npc_owner->getVehicle()->GetPoints().getCenter(), npc_owner->GetStarSystem()->CONTAINER_vec[ci]->GetPoints().getCenter());
                if (dist < npc_owner->getVehicle()->propetries.radius)
                {
                	visible_CONTAINER_vec.push_back( ContainerObservationData(npc_owner->GetStarSystem()->CONTAINER_vec[ci], dist) );
                	see.CONTAINER = true;
                } 
    	}

}


void Observation ::findVisibleNpcs_inSpace_inStatic()
{
	visible_NPC_vec.clear();

        for (unsigned int i = 0; i < npc_owner->GetStarSystem()->NPC_inSPACE_vec.size(); i++)
        {    
        	float dist = distBetweenPoints(npc_owner->getVehicle()->GetPoints().getCenter(), npc_owner->GetStarSystem()->NPC_inSPACE_vec[i]->getVehicle()->GetPoints().getCenter());
                if (dist < npc_owner->getVehicle()->propetries.radius)
                {
                	visible_NPC_vec.push_back( NpcObservationData(npc_owner->GetStarSystem()->NPC_inSPACE_vec[i], dist) );
               	} 
       	}	
        sort(&visible_NPC_vec);
       	
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

        for (unsigned int nri = 0; nri < npc_owner->GetStarSystem()->NPC_RANGER_inSPACE_vec.size(); nri++)
        {    
        	float dist = distBetweenPoints(npc_owner->getVehicle()->GetPoints().getCenter(), npc_owner->GetStarSystem()->NPC_RANGER_inSPACE_vec[nri]->getVehicle()->GetPoints().getCenter());
                if (dist < npc_owner->getVehicle()->propetries.radius)
                {
                	visible_NPC_RANGER_vec.push_back( NpcObservationData(npc_owner->GetStarSystem()->NPC_RANGER_inSPACE_vec[nri], dist) );
                        see.RANGER = true;
               	} 
       	}	
       
       	sort(&visible_NPC_RANGER_vec);
}


void Observation :: findVisibleWarriorNpcs_inSpace_inStatic()
{
	see.WARRIOR = false;
        visible_NPC_WARRIOR_vec.clear();

        for (unsigned int nwi = 0; nwi < npc_owner->GetStarSystem()->NPC_WARRIOR_inSPACE_vec.size(); nwi++)
        {    
        	float dist = distBetweenPoints(npc_owner->getVehicle()->GetPoints().getCenter(), npc_owner->GetStarSystem()->NPC_WARRIOR_inSPACE_vec[nwi]->getVehicle()->GetPoints().getCenter());
               	if (dist < npc_owner->getVehicle()->propetries.radius)
              	{
               		visible_NPC_WARRIOR_vec.push_back( NpcObservationData(npc_owner->GetStarSystem()->NPC_WARRIOR_inSPACE_vec[nwi], dist) );
               		see.WARRIOR = true;
              	} 
        }
        
       	sort(&visible_NPC_WARRIOR_vec);
} 


void Observation :: findVisibleTraderNpcs_inSpace_inStatic()
{
       	see.TRADER = false;
       	visible_NPC_TRADER_vec.clear();

       	for (unsigned int nti = 0; nti < npc_owner->GetStarSystem()->NPC_TRADER_inSPACE_vec.size(); nti++)
       	{    
       		float dist = distBetweenPoints(npc_owner->getVehicle()->GetPoints().getCenter(), npc_owner->GetStarSystem()->NPC_TRADER_inSPACE_vec[nti]->getVehicle()->GetPoints().getCenter());
               	if (dist < npc_owner->getVehicle()->propetries.radius)
               	{
               		visible_NPC_TRADER_vec.push_back( NpcObservationData(npc_owner->GetStarSystem()->NPC_TRADER_inSPACE_vec[nti], dist) );
               		see.TRADER = true;
              	} 
       	}
       	
       	sort(&visible_NPC_TRADER_vec);
}


void Observation :: findVisiblePiratNpcs_inSpace_inStatic()
{
     	see.PIRAT = false;
        visible_NPC_PIRAT_vec.clear();

        for (unsigned int npi = 0; npi < npc_owner->GetStarSystem()->NPC_PIRAT_inSPACE_vec.size(); npi++)
        {    
       		float dist = distBetweenPoints(npc_owner->getVehicle()->GetPoints().getCenter(), npc_owner->GetStarSystem()->NPC_PIRAT_inSPACE_vec[npi]->getVehicle()->GetPoints().getCenter());
               	if (dist < npc_owner->getVehicle()->propetries.radius)
               	{
               		visible_NPC_PIRAT_vec.push_back( NpcObservationData(npc_owner->GetStarSystem()->NPC_PIRAT_inSPACE_vec[npi], dist) );
               		see.PIRAT = true;
               	} 
       }
       
	sort(&visible_NPC_PIRAT_vec);
}


void Observation :: findVisibleDiplomatNpcs_inSpace_inStatic()
{
 	see.DIPLOMAT = false;
        visible_NPC_DIPLOMAT_vec.clear();

        for (unsigned int ndi = 0; ndi < npc_owner->GetStarSystem()->NPC_DIPLOMAT_inSPACE_vec.size(); ndi++)
        {    
         	float dist = distBetweenPoints(npc_owner->getVehicle()->GetPoints().getCenter(), npc_owner->GetStarSystem()->NPC_DIPLOMAT_inSPACE_vec[ndi]->getVehicle()->GetPoints().getCenter());
               	if (dist < npc_owner->getVehicle()->propetries.radius)
               	{
               		visible_NPC_DIPLOMAT_vec.push_back( NpcObservationData(npc_owner->GetStarSystem()->NPC_DIPLOMAT_inSPACE_vec[ndi], dist) );
               		see.DIPLOMAT = true;
              	} 
        }
        
	sort(&visible_NPC_DIPLOMAT_vec);
}


void Observation :: printVisibleMineralInformation() const
{
	printf("visible_MINERAL_vec for npc_id = %i\n", npc_owner->GetId());
	for (unsigned int i = 0; i < visible_MINERAL_vec.size(); i++)
        {                   
        	printf("%i ", visible_MINERAL_vec[i].mineral->GetId());                                              
	}
	printf("\n");
	
	for (unsigned int i = 0; i < visible_MINERAL_vec.size(); i++)
        {                   
        	printf("%f ", visible_MINERAL_vec[i].dist);                                              
	}
	printf("\n");
}
               	


