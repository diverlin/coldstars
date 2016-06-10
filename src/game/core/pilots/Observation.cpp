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

#include "Observation.hpp"
#include "../world/galaxy.hpp"
//#include <math/rand.hpp>
#include <meti/RandUtils.hpp>
#include "../pilots/Npc.hpp"
#include "../world/starsystem.hpp"

#include "../spaceobjects/Asteroid.hpp"
#include "../spaceobjects/Vehicle.hpp"
#include "../spaceobjects/Container.hpp"

Observation::Observation():npc_owner(nullptr)
{}

Observation::~Observation()
{}  


void Observation::FindEchievableStarSystems(Galaxy* galaxy)
{
    //visible_STARSYSTEM_pair_vec.clear();

    //for (unsigned int i=0; i<galaxy->STARSYSTEM_vec.size(); i++)
    //{
    //const glm::vec3& starsystem_pos = npc_owner->GetVehicle()->starsystem()->center();
    //float dist = meti::distance(starsystem_pos, galaxy->STARSYSTEM_vec[i]->position());
    ////if (dist < npc_owner->getShip()->propetries.hyper)
    //{
    //visible_STARSYSTEM_pair_vec.push_back( Pair<StarSystem*>(galaxy->STARSYSTEM_vec[i], dist) );
    //}
    //}

    //Sort(&visible_STARSYSTEM_vec);
}

Container* Observation::GetClosestPickableContainer() const
{
    assert(visible_pickable_CONTAINER_pair_vec.empty());
    return visible_pickable_CONTAINER_pair_vec[0].object;
}

Container* Observation::GetRandomPickableContainer() const
{
    assert(visible_pickable_CONTAINER_pair_vec.empty());
    return visible_pickable_CONTAINER_pair_vec[meti::getRandInt(0, visible_pickable_CONTAINER_pair_vec.size()-1)].object;
}

Starsystem* Observation::GetClosestStarSystem(int requested_consdition_id) const
{
    Starsystem* _target_starsystem = nullptr;
    for (unsigned int i=0; i<visible_STARSYSTEM_pair_vec.size(); i++) {
        if (visible_STARSYSTEM_pair_vec[i].object->conditionId() == requested_consdition_id) {
            _target_starsystem = visible_STARSYSTEM_pair_vec[i].object;
            break;
        }
    }

    return _target_starsystem;
}        


Vehicle* Observation::GetClosestVisibleVehicle(const std::vector<type::race>& rVec_race_id) const
{
    for (unsigned int i=0; i<rVec_race_id.size(); i++)
    {
        for (unsigned int j=0; j<visible_VEHICLE_pair_vec.size(); j++)
        {
            if (rVec_race_id[i] == visible_VEHICLE_pair_vec[j].object->npc()->GetRaceId())
            {
                return visible_VEHICLE_pair_vec[j].object;
            }
        }
    }

    return nullptr;
}

Vehicle* Observation::GetRandVisibleVehicle(const std::vector<type::race>& rVec_race_id) const
{
    std::vector<Vehicle*> tmp_vehicle;
    for (unsigned int i=0; i<rVec_race_id.size(); i++) {
        for (unsigned int j=0; j<visible_VEHICLE_pair_vec.size(); j++) {
            if (rVec_race_id[i] == visible_VEHICLE_pair_vec[j].object->npc()->GetRaceId()) {
                tmp_vehicle.push_back(visible_VEHICLE_pair_vec[j].object);
            }
        }
    }
    
    if (tmp_vehicle.size() > 0) {
        return tmp_vehicle[meti::getRandInt(0, tmp_vehicle.size()-1)];
    }

    return nullptr;
}

void Observation::ObserveAllInSpace()
{
    FindVisibleAsteroidsInSpaceInStatic();
    FindVisibleContainersInSpaceInStatic();
    FindVisibleVehiclesInSpaceInStatic();
}

template <typename OBSERVED_DATA_TYPE>
void Observation::Sort(std::vector<OBSERVED_DATA_TYPE>& rDataVec)
{
    for (unsigned int i=0; i<rDataVec.size(); i++)
    {
        int i_min = i;
        float min = rDataVec[i].dist;
        
        for (unsigned int j=i; j<rDataVec.size(); j++)
        {
            if ( rDataVec[j].dist < min )
            {
                i_min = j;
                min = rDataVec[j].dist;
            }
        }
        OBSERVED_DATA_TYPE tmp = rDataVec[i];
        rDataVec[i]            = rDataVec[i_min];
        rDataVec[i_min]        = tmp;
    }
}


void Observation::FindVisibleAsteroidsInSpaceInStatic()
{
    const std::vector<Asteroid*>& asteroid_vec = npc_owner->starsystem()->m_asteroids;
    
    see.ASTEROID  = false;
    
    visible_ASTEROID_pair_vec.clear();

    for (unsigned int i=0; i<asteroid_vec.size(); i++) {
        float dist = meti::distance(npc_owner->GetVehicle()->position(), asteroid_vec[i]->position());
        if (dist < npc_owner->GetVehicle()->properties().radar) {
            visible_ASTEROID_pair_vec.push_back( Pair<Asteroid*>(asteroid_vec[i], dist) );
            see.ASTEROID = true;
        }
    }

    Sort(visible_ASTEROID_pair_vec);
}

void Observation::FindVisibleContainersInSpaceInStatic()
{
    const std::vector<Container*>& container_vec = npc_owner->starsystem()->m_containers;
    
    see.CONTAINER       = false;
    see.pickable_CONTAINER  = false;

    visible_CONTAINER_pair_vec.clear();
    visible_pickable_CONTAINER_pair_vec.clear();

    for (unsigned int i=0; i<container_vec.size(); i++)
    {
        float dist = meti::distance(npc_owner->GetVehicle()->position(), container_vec[i]->position());
        if (dist < npc_owner->GetVehicle()->properties().radar)
        {
            visible_CONTAINER_pair_vec.push_back( Pair<Container*>(container_vec[i], dist) );
            int container_mass = container_vec[i]->mass();
            if(container_mass < npc_owner->GetVehicle()->properties().grab_strength)
            {
                visible_pickable_CONTAINER_pair_vec.push_back( Pair<Container*>(container_vec[i], dist) );
                see.pickable_CONTAINER = true;
            }
            see.CONTAINER = true;
        }
    }
}

void Observation::FindVisibleVehiclesInSpaceInStatic()
{
    const std::vector<Vehicle*>& vehicle_vec = npc_owner->starsystem()->m_vehicles;

    see.RANGER  = false;
    see.WARRIOR = false;
    see.TRADER = false;
    see.PIRAT = false;
    see.DIPLOMAT = false;

    visible_VEHICLE_pair_vec.clear();

    for (unsigned int i=0; i<vehicle_vec.size(); i++)
    {
        float dist = meti::distance(npc_owner->GetVehicle()->position(), vehicle_vec[i]->position());
        //std::cout<<"dist, radius = "<<dist<<", "<<npc_owner->GetVehicle()->propetries.radius<<std::endl;
        if (dist < npc_owner->GetVehicle()->properties().radar)
        {
            visible_VEHICLE_pair_vec.push_back( Pair<Vehicle*>(vehicle_vec[i], dist) );
        }
    }
    Sort(visible_VEHICLE_pair_vec);
    //std::cout<<"visible_VEHICLE_pair_vec.size = "<<visible_VEHICLE_pair_vec.size()<<std::endl;
}



