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
        	float dist = distBetweenPoints(npc_owner->GetVehicle()->GetStarSystem()->GetPoints().GetCenter(),  galaxy->STARSYSTEM_vec[i]->GetPoints().GetCenter());
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
 		if (visible_STARSYSTEM_vec[i].starsystem->GetCaptured() == _captured)
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
        		if ( visible_NPC_vec[i].npc->GetRaceId() == (*_pVec_race_id)[j] )
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
        	float dist = distBetweenPoints(npc_owner->GetVehicle()->GetPoints().GetCenter(), npc_owner->GetStarSystem()->ASTEROID_vec[ai]->GetPoints().GetCenter());
                if (dist < npc_owner->GetVehicle()->propetries.radius)
                {
                	visible_ASTEROID_vec.push_back( AsteroidObservationData(npc_owner->GetStarSystem()->ASTEROID_vec[ai], dist) );
                      	see.ASTEROID = true;
                } 
        }
        
        sort(&visible_ASTEROID_vec);
}



void Observation :: findVisibleMinerals_inSpace_inStatic()
{
	//see.MINERAL   = false;
        //visible_MINERAL_vec.clear();

        //for (unsigned int mi = 0; mi < npc_owner->GetStarSystem()->MINERAL_vec.size(); mi++)
        //{    
         	//float dist = distBetweenPoints(npc_owner->GetVehicle()->GetPoints().GetCenter(), npc_owner->GetStarSystem()->MINERAL_vec[mi]->GetPoints().GetCenter());
               	//if (dist < npc_owner->GetVehicle()->propetries.radius)
              	//{              		
               		//visible_MINERAL_vec.push_back(MineralObservationData(npc_owner->GetStarSystem()->MINERAL_vec[mi], dist));
              		//see.MINERAL = true;
               	//} 
        //}
        
        //sort(&visible_MINERAL_vec);
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
        	float dist = distBetweenPoints(npc_owner->GetVehicle()->GetPoints().GetCenter(), npc_owner->GetStarSystem()->CONTAINER_vec[ci]->GetPoints().GetCenter());
                if (dist < npc_owner->GetVehicle()->propetries.radius)
                {
                	visible_CONTAINER_vec.push_back( ContainerObservationData(npc_owner->GetStarSystem()->CONTAINER_vec[ci], dist) );
                	see.CONTAINER = true;
                } 
    	}

}


void Observation ::findVisibleNpcs_inSpace_inStatic()
{
	visible_NPC_vec.clear();

        for (unsigned int i = 0; i < npc_owner->GetStarSystem()->NPC_vec.size(); i++)
        {    
        	float dist = distBetweenPoints(npc_owner->GetVehicle()->GetPoints().GetCenter(), npc_owner->GetStarSystem()->NPC_vec[i]->GetVehicle()->GetPoints().GetCenter());
                if (dist < npc_owner->GetVehicle()->propetries.radius)
                {
                	visible_NPC_vec.push_back( NpcObservationData(npc_owner->GetStarSystem()->NPC_vec[i], dist) );
               	} 
       	}	
        sort(&visible_NPC_vec);
       	
       	
       	see.RANGER  = false;
       	see.WARRIOR = false;
       	see.TRADER = false;
       	see.PIRAT = false;
       	see.DIPLOMAT = false;
       	       	       	
        visible_NPC_RANGER_vec.clear();
	visible_NPC_WARRIOR_vec.clear();
       	visible_NPC_TRADER_vec.clear();
       	visible_NPC_PIRAT_vec.clear();
       	visible_NPC_DIPLOMAT_vec.clear();
       	       	       	
        for (unsigned int i = 0; i < npc_owner->GetStarSystem()->NPC_vec.size(); i++)
        {    
        	float dist = distBetweenPoints(npc_owner->GetVehicle()->GetPoints().GetCenter(), npc_owner->GetStarSystem()->NPC_vec[i]->GetVehicle()->GetPoints().GetCenter());
                if (dist < npc_owner->GetVehicle()->propetries.radius)
                {
                	switch(npc_owner->GetStarSystem()->NPC_vec[i]->GetSubTypeId())
                	{
                		case CLASS::RANGER_ID:
                		{
                			visible_NPC_RANGER_vec.push_back( NpcObservationData(npc_owner->GetStarSystem()->NPC_vec[i], dist) );
                        		see.RANGER = true;
                        		break;
                		}
                	
                	        case CLASS::WARRIOR_ID:
                		{
                			visible_NPC_WARRIOR_vec.push_back( NpcObservationData(npc_owner->GetStarSystem()->NPC_vec[i], dist) );
                        		see.WARRIOR = true;
                        		break;
                		}

                	        case CLASS::TRADER_ID:
                		{
                			visible_NPC_TRADER_vec.push_back( NpcObservationData(npc_owner->GetStarSystem()->NPC_vec[i], dist) );
                        		see.TRADER = true;
                        		break;
                		}

                	        case CLASS::PIRAT_ID:
                		{
                			visible_NPC_PIRAT_vec.push_back( NpcObservationData(npc_owner->GetStarSystem()->NPC_vec[i], dist) );
                        		see.PIRAT = true;
                        		break;
                		}                		                			

                	        case CLASS::DIPLOMAT_ID:
                		{
                			visible_NPC_DIPLOMAT_vec.push_back( NpcObservationData(npc_owner->GetStarSystem()->NPC_vec[i], dist) );
                        		see.DIPLOMAT = true;
                        		break;
                		}   
                	}

               	}
               	else
               	{
               		break;
               	} 
       	}   

}




void Observation :: printVisibleMineralInformation() const
{
	//printf("visible_MINERAL_vec for npc_id = %i\n", npc_owner->GetId());
	//for (unsigned int i = 0; i < visible_MINERAL_vec.size(); i++)
        //{                   
        	//printf("%i ", visible_MINERAL_vec[i].mineral->GetId());                                              
	//}
	//printf("\n");
	
	//for (unsigned int i = 0; i < visible_MINERAL_vec.size(); i++)
        //{                   
        	//printf("%f ", visible_MINERAL_vec[i].dist);                                              
	//}
	//printf("\n");
}
               	


