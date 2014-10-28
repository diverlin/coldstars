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


#ifndef STARSYSTEM_HPP
#define STARSYSTEM_HPP

#include <vector>
#include <spaceobjects/BaseSpaceEntity.hpp>
#include <garbage/garbageEffects.hpp>

#include <world/HyperSpace.hpp>
#include <world/AsteroidManager.hpp>
#include <types/RaceTypes.hpp>
#include <render/Render.hpp>

class RocketBullet;
class BasePlanet;
class Star;
class Planet;
class Asteroid;
class BlackHole;
class Vehicle;
class SpaceStation;
class Satellite; 
class Ship; 
class Container;

class Player;
class Npc;

class Sector;

class DistantNebulaEffect;
class DistantStarEffect;

class ShockWaveEffect;

namespace jeti {
class ExplosionEffect;
class BaseParticleSystem;
}

class LazerTraceEffect;


namespace ENTITY 
{
namespace STARSYSTEM
{
const int JUMPRADIUS = 1200;

const int PLANET_NUM_MIN = 3;
const int PLANET_NUM_MAX = 5;

const int SHIP_INIT_MIN = 4;
const int SHIP_INIT_MAX = 7;
const int SHIPENEMY_INIT_MIN = 50;
const int SHIPENEMY_INIT_MAX = 100;

const int SPACESTATION_NUM_MIN = 1;
const int SPACESTATION_NUM_MAX = 3;

const int DISTANT_NEBULA_MIN = 6;
const int DISTANT_NEBULA_MAX = 8;

enum CONDITION
{
    WAR_ID=1, CAPTURED_ID, SAFE_ID
};
}
}

struct UnresolvedData
{
        int sector_id;
};


class StarSystem : public BaseSpaceEntity
{
    public:
        StarSystem(int);
        ~StarSystem();
        
        virtual void PutChildsToGarbage() const;

        void SetContainerNumMax(int container_num_max) { this->container_num_max = container_num_max; }
        void SetSector(Sector* sector)  { this->sector = sector; }
        void SetColor(const glm::vec4& color)  { this->color = color; }
        AsteroidManager& GetAsteroidManager()  { return asteroid_manager; }

        const glm::vec4& GetColor() const { return color; }
        //bool GetDetailedSimulationFlag() const { return detalied_simulation; }
        int GetConditionId()     const { return condition_id; }
        TYPE::RACE GetRaceId()          const { return race_id; }
        TYPE::RACE GetConquerorRaceId() const { return conqueror_race_id; }
        Star* GetStar()          const { return STAR_vec[0]; }
        Sector* GetSector()      const { return sector; }
        unsigned int GetShockWaveEffectNum()    const { return effect_SHOCKWAVE_vec.size(); }
        unsigned int GetAsteroidNum()     const { return ASTEROID_vec.size(); }
        unsigned int GetExplosionEffectNum()     const { return effect_PARTICLESYSTEM_vec.size(); }
        unsigned int GetTextDamageNum()     const { return text_DAMAGE_vec.size(); }
        bool IsAnyActiveParticlesEffectPresent(int) const;

        HyperSpace& GetHyperSpace() { return hyperspace; };
        
        Npc* GetFreeLeaderByRaceId(TYPE::RACE) const;
        void CreateGroupAndShareTask(Npc*, StarSystem*, int) const;
        
        //// TRANSITION
        void AddVehicle(Vehicle*, const glm::vec3&, const glm::vec3&, const BaseSpaceEntity* const parent = nullptr);
        void AddBullet(RocketBullet*, const glm::vec3&, const glm::vec3&);

        void Add(BasePlanet*, const BaseSpaceEntity* parent = nullptr, int it = 0);
        void AddContainer(Container*, const glm::vec3&);
        void Add(BlackHole*, const glm::vec3&);

        // effects
        void Add(jeti::BaseParticleSystem*);
        void Add(ShockWaveEffect*, const glm::vec2&);
        void Add(jeti::ExplosionEffect*, const glm::vec3&, float, float);
        void Add(jeti::ExplosionEffect*, const glm::vec3&);
        void Add(LazerTraceEffect*);

        void Add(DistantNebulaEffect*);
        void Add(DistantStarEffect*);
        
        void Add(VerticalFlowText*);
        //
        
        void BombExplosionEvent(Container*, bool);
        void StarSparkEvent(float) const;
        
        void FindRenderVisibleEntities_c(Player*);
        void FindRadarVisibleEntities_c(Player*);
        
        void Update(int);
        void LoadEntitiesResource();

        float CalcResultGravityForce(const glm::vec3&, const glm::vec3&, float) const;

        void DrawBackground(const jeti::Renderer&, const glm::vec2&);
        void DrawOrbits(const jeti::Renderer&);
        void DrawPath();

        void Save(boost::property_tree::ptree&) const;
        void Load(const boost::property_tree::ptree&);
        void Resolve();

        // poor
        Planet* GetClosestInhabitedPlanet(const glm::vec2&) const;
        Planet* GetRandomInhabitedPlanet() const;
        Planet* GetRandomPlanet() const;
        Vehicle* GetRandomVehicle() const;
        Vehicle* GetRandomVehicleExcludingNpcRaceId(TYPE::RACE) const;
        Vehicle* GetRandomVehicleByNpcRaceId(TYPE::RACE) const;
        Vehicle* GetRandomVehicle(const std::vector<TYPE::RACE>&) const;
        //
    private:
        static int counter;
        
        TYPE::RACE race_id;
        TYPE::RACE conqueror_race_id;
        
        bool unique_update_inDymanic_done;
        bool unique_update_inStatic_done;
        
        int condition_id;
        unsigned int container_num_max;
        
        Sector* sector;
        glm::vec4 color;
        
        AsteroidManager asteroid_manager;
        
        // ENTITY VECTORS
        //std::vector<Player*>        PLAYER_vec;

        std::vector<Star*>         STAR_vec;
        std::vector<Planet*>       PLANET_vec;
        std::vector<Asteroid*>     ASTEROID_vec;
        std::vector<Container*>    CONTAINER_vec;
        std::vector<RocketBullet*> ROCKET_vec;
        std::vector<BlackHole*>    BLACKHOLE_vec;
        
        std::vector<Vehicle*> VEHICLE_vec;
        HyperSpace hyperspace;

        // effects
        std::vector<DistantNebulaEffect*> distantNebulaEffect_vec;
        std::vector<DistantStarEffect*>   distantStarEffect_vec;

        std::vector<LazerTraceEffect*>    effect_LAZERTRACE_vec;
        std::vector<jeti::BaseParticleSystem*>  effect_PARTICLESYSTEM_vec;
        std::vector<ShockWaveEffect*>     effect_SHOCKWAVE_vec;
        std::vector<VerticalFlowText*>    text_DAMAGE_vec;

        GarbageEffects  garbage_effects;

        UnresolvedData data_unresolved_StarSystem;

        void LaunchingEvent() const;

        void UpdateInSpaceInStatic_s();
        void UpdateEntities_s(int, bool);

        void UpdateStates();

        void DamageEventInsideCircle(const glm::vec3&, float, int, bool);

        void PostDeathUniqueEvent(bool);

        void ShipManager_s(unsigned int);
        
        void ManageUnavaliableObjects_s();
        void ManageDeadObjects_s();

        void rocketCollision_s(bool);
        void asteroidCollision_s(bool);
        void ExternalForcesAffection_s(bool);
        
        void SaveData(boost::property_tree::ptree&, const std::string&) const;
        void LoadData(const boost::property_tree::ptree&);
        void ResolveData();
        
        friend class GuiGalaxyMap;
        friend class Observation;
        friend class Player;
        friend class God;
};

#endif 




