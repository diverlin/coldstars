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

namespace model {
class StarSystem;
} // namespace model

namespace control {
class Npc; 
} // namespace model

class Galaxy;
class Asteroid;
class Container;
class Vehicle;

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
    Visible()
        :
          asteroid(false),
          container(false),
          pickable_container(false),
          ranger(false),
          warrior(false),
          trader(false),
          pirat(false),
          diplomat(false) {}
    
    bool asteroid;
    bool container;
    bool pickable_container;

    bool ranger;
    bool warrior;
    bool trader;
    bool pirat;
    bool diplomat;
};


class Observation 
{
public:
    Observation();
    ~Observation();

    const Visible& visible() const { return see; }

    void SetNpcOwner(control::Npc* npc_owner) { this->npc_owner = npc_owner; }
    void ObserveAllInSpace();

    void FindEchievableStarSystems(Galaxy*);
    Container* GetClosestPickableContainer() const;
    Container* GetRandomPickableContainer() const;
    model::StarSystem* GetClosestStarSystem(int) const;
    Vehicle* GetClosestVisibleVehicle(const std::vector<race::Type>&) const;
    Vehicle* GetRandVisibleVehicle(const std::vector<race::Type>&) const;

    void FindVisibleAsteroidsInSpaceInStatic();
    void FindVisibleContainersInSpaceInStatic();
    void FindVisibleVehiclesInSpaceInStatic();

    template <typename OBSERVED_DATA_TYPE>
    void Sort(std::vector<OBSERVED_DATA_TYPE>&);

private:
    control::Npc* npc_owner;

    std::vector< Pair<model::StarSystem*> > visible_STARSYSTEM_pair_vec;
    std::vector< Pair<Container*> > visible_CONTAINER_pair_vec;
    std::vector< Pair<Container*> > visible_pickable_CONTAINER_pair_vec;
    std::vector< Pair<Asteroid*> > visible_ASTEROID_pair_vec;

    std::vector< Pair<Vehicle*> > visible_VEHICLE_pair_vec;

    Visible see;

    friend class Npc;
};


