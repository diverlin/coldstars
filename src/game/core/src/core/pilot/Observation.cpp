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

#include <core/pilot/Npc.hpp>

#include <core/world/galaxy.hpp>
#include <core/world/Sector.hpp>
#include <core/world/starsystem.hpp>

#include <core/spaceobject/Asteroid.hpp>
#include <core/spaceobject/Vehicle.hpp>
#include <core/spaceobject/Container.hpp>

#include <meti/RandUtils.hpp>


Observation::Observation(control::Npc* owner)
    :
      m_owner(owner)
{}


void Observation::__findEchievableStarSystems(control::Galaxy* galaxy)
{
    m_starsystem_pairs.clear();

    for (control::Sector* sector: galaxy->sectors()) {
        for (control::StarSystem* starsystem: sector->starSystems()) {
            const glm::vec3& starsystem_pos = m_owner->vehicle()->starsystem()->position();
            float dist = meti::distance(starsystem_pos, starsystem->position());
            if (dist < m_owner->vehicle()->properties().hyper) {
                m_starsystem_pairs.push_back( Pair<control::StarSystem*>(starsystem, dist) );
            }
        }
    }

    __sort(m_starsystem_pairs);
}


control::Asteroid*
Observation::nearestAsteroid() const
{
    if (!m_asteroid_pairs.empty()) {
        return m_asteroid_pairs.front().object;
    }
    return nullptr;
}

control::Container*
Observation::nearestPickableContainer() const
{
    if (!m_pickable_container_pairs.empty()) {
        return m_pickable_container_pairs.front().object;
    }
    return nullptr;
}

control::Container*
Observation::randPickableContainer() const
{
    if (!m_pickable_container_pairs.empty()) {
        unsigned long int rand_index = meti::rand::gen_int(m_pickable_container_pairs.size()-1);
        return m_pickable_container_pairs[rand_index].object;
    }

    return nullptr;
}

control::StarSystem*
Observation::nearestStarSystem(int requested_consdition_id) const
{
    for (const auto& pair: m_starsystem_pairs) {
        control::StarSystem* starsystem = pair.object;
        if (starsystem->conditionId() == requested_consdition_id) {
            return starsystem;
        }
    }

    return nullptr;
}        


control::Vehicle*
Observation::nearestVehicle(const std::vector<race::Type>& races) const
{
    for (const race::Type& race: races) {
        for (const auto& pair: m_vehicle_pairs) {
            control::Vehicle* vehicle = pair.object;
            if (race == vehicle->npc()->race()) {
                return vehicle;
            }
        }
    }

    return nullptr;
}

control::Vehicle*
Observation::randVehicle(const std::vector<race::Type>& races) const
{
    std::vector<control::Vehicle*> vehicles;
    for (const race::Type& race: races) {
        for (auto pair: m_vehicle_pairs) {
            control::Vehicle* vehicle = pair.object;
            if (race == vehicle->npc()->race()) {
                vehicles.push_back(vehicle);
            }
        }
    }    

    return meti::rand::get_pointer(vehicles);
}

void Observation::update()
{
    __findVisibleAsteroids();
    __findVisibleContainers();
    __findVisibleVehicles();
}

template <typename OBSERVED_DATA_TYPE>
void Observation::__sort(std::vector<OBSERVED_DATA_TYPE>& data)
{
    for (unsigned int i=0; i<data.size(); i++) {
        unsigned int i_min = i;
        float min = data[i].dist;
        
        for (unsigned int j=i; j<data.size(); j++) {
            if ( data[j].dist < min ) {
                i_min = j;
                min = data[j].dist;
            }
        }
        OBSERVED_DATA_TYPE tmp = data[i];
        data[i] = data[i_min];
        data[i_min] = tmp;
        //std::swap(data[i_min], data[i]);
    }
}


void Observation::__findVisibleAsteroids()
{
    m_see.asteroid  = false;
    
    m_asteroid_pairs.clear();

    for (control::Asteroid* asteroid: m_owner->starsystem()->asteroids()) {
        float dist = meti::distance(m_owner->vehicle()->position(), asteroid->position());
        if (dist < m_owner->vehicle()->properties().radar) {
            m_asteroid_pairs.push_back( Pair<control::Asteroid*>(asteroid, dist) );
            m_see.asteroid = true;
        }
    }

    __sort(m_asteroid_pairs);
}

void Observation::__findVisibleContainers()
{
    m_see.container           = false;
    m_see.pickable_container  = false;

    m_container_pairs.clear();
    m_pickable_container_pairs.clear();

    for (control::Container* container: m_owner->starsystem()->containers()) {
        float dist = meti::distance(m_owner->vehicle()->position(), container->position());
        if (dist < m_owner->vehicle()->properties().radar) {
            m_container_pairs.push_back( Pair<control::Container*>(container, dist) );
            int container_mass = container->mass();
            if(container_mass < m_owner->vehicle()->properties().grab_strength) {
                m_pickable_container_pairs.push_back( Pair<control::Container*>(container, dist) );
                m_see.pickable_container = true;
            }
            m_see.container = true;
        }
    }
}

void Observation::__findVisibleVehicles()
{
    m_see.ranger  = false;
    m_see.warrior = false;
    m_see.trader = false;
    m_see.pirat = false;
    m_see.diplomat = false;

    m_vehicle_pairs.clear();

    for (control::Vehicle* vehicle: m_owner->starsystem()->vehicles()) {
        float dist = meti::distance(m_owner->vehicle()->position(), vehicle->position());
        //std::cout<<"dist, radius = "<<dist<<", "<<npc_owner->vehicle()->propetries.radius<<std::endl;
        if (dist < m_owner->vehicle()->properties().radar) {
            m_vehicle_pairs.push_back( Pair<control::Vehicle*>(vehicle, dist) );
        }
    }
    __sort(m_vehicle_pairs);
}



