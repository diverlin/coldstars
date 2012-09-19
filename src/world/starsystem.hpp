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
//#include "../spaceobjects/BaseGameEntity.hpp"
//#include "../spaceobjects/planet.hpp"
class Player; //#include "../pilots/Player.hpp"
//#include "../pilots/npc.hpp"

//#include "../spaceobjects/asteroid.hpp"
//#include "../spaceobjects/container.hpp"
class RocketBullet; //#include "../spaceobjects/RocketBullet.hpp"

class BasePlanet;
class Star;
class Planet;
class Asteroid;
class BlackHole;
class Vehicle;
class SpaceStation;
class Satellite; 
class Ship; 
class Galaxy;
class Container;

#include "../effects/DistantNebulaEffect.hpp"
#include "../effects/DistantStarEffect.hpp"

#include "../world/GarbageEntities.hpp"
#include "../world/garbageEffects.hpp"

struct UnresolvedDataUniqueStarSystem
{
	int galaxy_id;
};


class StarSystem : public BaseGameEntity
{
	public:
		StarSystem(int);
		~StarSystem();

		void SetGalaxy(Galaxy* galaxy)  { this->galaxy = galaxy; };
						
		//bool GetDetailedSimulationFlag() const { return detalied_simulation; };
		int GetConditionId()     const { return condition_id; };
		int GetRaceId()          const { return race_id; };
		int GetConquerorRaceId() const { return conqueror_race_id; };  
		Star* GetStar()          const { return STAR_vec[0]; };		
		Galaxy* GetGalaxy()      const { return galaxy; };
		int GetShockWaveNum()    const { return effect_SHOCKWAVE_vec.size(); };
		
		//// TRANSITION
		void AddToHyperJumpQueue(Vehicle*);

		void AddVehicle(Vehicle*, const vec2f&, float, BaseGameEntity* parent = NULL);
		void AddBullet(RocketBullet*, const vec2f&, float);
								
		void Add(BasePlanet*, BaseGameEntity* parent = NULL, int it = 0);
		void Add(Container*, const vec2f&);
		void Add(BlackHole*, const vec2f&);

		// effects
		void Add(BaseParticleSystem*);
		void Add(ShockWaveEffect*, const vec2f&);
		void Add(LazerTraceEffect*);

		void Add(DistantNebulaEffect*);
		void Add(DistantStarEffect*);
		
		void Add(VerticalFlowText*);
		//

		void AddToRemoveFromOuterSpaceQueue(Container*);
		void AddToRemoveFromOuterSpaceQueue(Vehicle*);
				
		bool RemoveVehicle(Vehicle*);    
		
		void BombExplosionEvent(Container*, bool);
		
		void FindRenderVisibleEntities_c(Player*);  
		void FindRadarVisibleEntities_c(Player*);  
		
		void Update(int, bool);

    		void RestoreDefaultColor();
    		void RestoreSceneColor();
    		void DrawBackground(vec2f);
                void DrawOrbits();
                void DrawPath();
                
		void SaveData(boost::property_tree::ptree&) const;
		void LoadData(const boost::property_tree::ptree&);
		void ResolveData();
				                                           		    		    		
		// poor
		Planet* GetClosestPlanet(const vec2f&);
		Vehicle* GetRandomVehicle();
		Vehicle* GetRandomVehicleExcludingNpcRaceId(int);
		Vehicle* GetRandomVehicleByNpcRaceId(int) const;
		Vehicle* GetRandomVehicle(const std::vector<int>&) const;
		// 
    	private:
                int race_id, conqueror_race_id;
                
    		//bool detalied_simulation;
    		bool calculation_per_turn_allowed; 
    		bool calculation_per_turn_allowed_inDynamic; 
    		    		
    		int condition_id;
    		
    		Galaxy* galaxy;
    	
    		// ENTITY VECTORS
		//std::vector<Player*> 	   PLAYER_vec;

		std::vector<Star*>         STAR_vec;
		std::vector<Planet*>       PLANET_vec;
		std::vector<Asteroid*>     ASTEROID_vec;
		std::vector<Container*>    CONTAINER_vec;
		std::vector<RocketBullet*> ROCKET_vec;
		std::vector<BlackHole*>    BLACKHOLE_vec;
		
		std::vector<Vehicle*> VEHICLE_vec;
    		   
    		// effects
    	    	std::vector<DistantNebulaEffect*> distantNebulaEffect_vec;
    		std::vector<DistantStarEffect*>   distantStarEffect_vec;
    		
    		std::vector<LazerTraceEffect*>    effect_LAZERTRACE_vec;
    		std::vector<BaseParticleSystem*>  effect_PARTICLESYSTEM_vec;
    		std::vector<ShockWaveEffect*>     effect_SHOCKWAVE_vec;    		
    		std::vector<VerticalFlowText*> 	  text_DAMAGE_vec;
    		
    		// remove queue 	
    		std::vector<Container*>    remove_CONTAINER_queue;
    		std::vector<Ship*>         remove_SHIP_queue;
    		std::vector<SpaceStation*> remove_SPACESTATION_queue;
    		std::vector<Satellite*>    remove_SATELLITE_queue;    		
    		//    			    		    	  

    	    	// ENTITY VECTORS
                std::vector<Vehicle*> appear_VEHICLE_queue;
                    		  	
    		GarbageEntities garbage_entities;
    		GarbageEffects  garbage_effects;
 		    		            
    		UnresolvedDataUniqueStarSystem data_unresolved_ss;
    		            		    
                void PostHyperJumpEvent();
                void LaunchingEvent() const;
    		
    		void MindEntitiesInStatic_s();
    		void UpdateEntities_s(int, bool);   		
    		
    		void updateStates();
    		
    		void damageEventInsideCircle(vec2f epicentr, float radius, int damage, bool show_effect);
    		
    		void PostDeathUniqueEvent(bool);


		void asteroidManager_s(unsigned int num);

		void manageUnavaliableObjects_s();
		void manageDeadObjects_s();

		void rocketCollision_s(bool);
		void asteroidCollision_s(bool);
		
		void SaveDataUniqueStarSystem(boost::property_tree::ptree&, const std::string&) const;
		void LoadDataUniqueStarSystem(const boost::property_tree::ptree&);
		void ResolveDataUniqueStarSystem();
		
		friend class GuiMap;
		friend class Observation;
		friend class Player;
};

#endif 




