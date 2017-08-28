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


#pragma once

#include <core/type/RaceType.hpp>

#include <vector>

namespace control {
class Npc; 
class Galaxy;
class StarSystem;
class Asteroid;
class Container;
class Vehicle;
} // namespace model

template <class TYPE>
class Pair
{
public:
    TYPE object;
    float dist;

    Pair(TYPE object, float dist):object(object), dist(dist) {}
    ~Pair() {}
};

struct Visible
{
    bool asteroid = false;
    bool container = false;
    bool pickable_container = false;

    bool ranger = false;
    bool warrior = false;
    bool trader = false;
    bool pirat = false;
    bool diplomat = false;
};


class Observation 
{
public:
    Observation(control::Npc*);
    ~Observation() = default;

    const Visible& visible() const { return m_see; }

    control::Container* nearestPickableContainer() const;
    control::Container* randPickableContainer() const;
    control::StarSystem* nearestStarSystem(int) const;
    control::Vehicle* nearestVehicle(const std::vector<race::Type>&) const;
    control::Vehicle* randVehicle(const std::vector<race::Type>&) const;

    void update();

private:
    control::Npc* m_owner = nullptr;

    std::vector<Pair<control::StarSystem*>> m_starsystem_pairs;
    std::vector<Pair<control::Container*>> m_container_pairs;
    std::vector<Pair<control::Container*>> m_pickable_container_pairs;
    std::vector<Pair<control::Asteroid*>> m_asteroid_pairs;

    std::vector<Pair<control::Vehicle*>> m_vehicle_pairs;

    Visible m_see;

    template <typename OBSERVED_DATA_TYPE>
    void __sort(std::vector<OBSERVED_DATA_TYPE>&);

    void __findEchievableStarSystems(control::Galaxy*);
    void __findVisibleAsteroids();
    void __findVisibleContainers();
    void __findVisibleVehicles();
};


