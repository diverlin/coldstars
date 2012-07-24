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


Observation::Observation(Npc* _npc)
{ 
    	npc_owner = _npc;
}
    
Observation::~Observation()
{}  
    
    
void Observation::FindEchievableStarSystems(Galaxy* galaxy)
{
        visible_STARSYSTEM_pair_vec.clear();

        for (unsigned int i = 0; i < galaxy->STARSYSTEM_vec.size(); i++)
        {    
        	float dist = distBetweenPoints(npc_owner->GetVehicle()->GetStarSystem()->GetPoints().GetCenter(),  galaxy->STARSYSTEM_vec[i]->GetPoints().GetCenter());
                //if (dist < npc_owner->getShip()->propetries.hyper)
                {
                	visible_STARSYSTEM_pair_vec.push_back( Pair<StarSystem*>(galaxy->STARSYSTEM_vec[i], dist) );
                } 
        }
        
        //Sort(&visible_STARSYSTEM_vec);
}
          
          
StarSystem* Observation::GetClosestStarSystem(bool _captured) const
{
	StarSystem* _target_starsystem = NULL;
	
 	for (unsigned int i = 0; i<visible_STARSYSTEM_pair_vec.size(); i++)
 	{
 		if (visible_STARSYSTEM_pair_vec[i].object->GetCaptured() == _captured)
 		{
 			_target_starsystem = visible_STARSYSTEM_pair_vec[i].object;
 			break;
 		}
 	}   
 	
 	return _target_starsystem;   	
}    	


Vehicle* Observation::GetClosestVehicle(std::vector<int>* _pVec_race_id) const
{
	for (unsigned int i=0; i<visible_VEHICLE_pair_vec.size(); i++)
        {
        	for (unsigned int j=0; j<_pVec_race_id->size(); j++)
        	{
        		if (visible_VEHICLE_pair_vec[i].object->GetOwnerNpc() != NULL)
        		{
        			if ( visible_VEHICLE_pair_vec[i].object->GetOwnerNpc()->GetRaceId() == (*_pVec_race_id)[j] )
        			{
        				return visible_VEHICLE_pair_vec[i].object;
        			}
        		}
        	}
        }
        
	return NULL;	
}

void Observation::ObserveAllInSpace()
{
     	FindVisibleAsteroidsInSpaceInStatic();
     	FindVisibleContainersInSpaceInStatic();
     	FindVisibleVehiclesInSpaceInStatic();
}

template <typename OBSERVED_DATA_TYPE>
void Observation::Sort(std::vector<OBSERVED_DATA_TYPE>* pDataVec)
{
	for (unsigned int i=0; i<pDataVec->size(); i++)
	{
		int i_min = i;
		float min = (*pDataVec)[i].dist;
		
		for (unsigned int j=i; j<pDataVec->size(); j++)
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


void Observation::FindVisibleAsteroidsInSpaceInStatic()
{
	const std::vector<Asteroid*>& asteroid_vec = npc_owner->GetStarSystem()->ASTEROID_vec;
	
	see.ASTEROID  = false;
	
        visible_ASTEROID_pair_vec.clear();

        for (unsigned int i=0; i<asteroid_vec.size(); i++)
        {    
        	float dist = distBetweenPoints(npc_owner->GetVehicle()->GetPoints().GetCenter(), asteroid_vec[i]->GetPoints().GetCenter());
                if (dist < npc_owner->GetVehicle()->propetries.radius)
                {
                	visible_ASTEROID_pair_vec.push_back( Pair<Asteroid*>(asteroid_vec[i], dist) );
                      	see.ASTEROID = true;
                } 
        }
        
        Sort(&visible_ASTEROID_pair_vec);
}

void Observation::FindVisibleContainersInSpaceInStatic()
{
	const std::vector<Container*>& container_vec = npc_owner->GetStarSystem()->CONTAINER_vec;
	
	see.CONTAINER   = false;
	
        visible_CONTAINER_pair_vec.clear();

        for (unsigned int i=0; i<container_vec.size(); i++)
        {    
        	float dist = distBetweenPoints(npc_owner->GetVehicle()->GetPoints().GetCenter(), container_vec[i]->GetPoints().GetCenter());
                if (dist < npc_owner->GetVehicle()->propetries.radius)
                {
                	visible_CONTAINER_pair_vec.push_back( Pair<Container*>(container_vec[i], dist) );
                	see.CONTAINER = true;
                } 
    	}
}

void Observation::FindVisibleVehiclesInSpaceInStatic()
{
	const std::vector<Vehicle*>& vehicle_vec = npc_owner->GetStarSystem()->VEHICLE_vec;

       	see.RANGER  = false;
       	see.WARRIOR = false;
       	see.TRADER = false;
       	see.PIRAT = false;
       	see.DIPLOMAT = false;
       		
	visible_VEHICLE_pair_vec.clear();

        for (unsigned int i=0; i<vehicle_vec.size(); i++)
        {    
        	float dist = distBetweenPoints(npc_owner->GetVehicle()->GetPoints().GetCenter(), vehicle_vec[i]->GetPoints().GetCenter());
                if (dist < npc_owner->GetVehicle()->propetries.radius)
                {
                	visible_VEHICLE_pair_vec.push_back( Pair<Vehicle*>(vehicle_vec[i], dist) );
               	} 
       	}	
        Sort(&visible_VEHICLE_pair_vec);
}



