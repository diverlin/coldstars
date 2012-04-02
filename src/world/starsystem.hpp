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


#ifndef STARSYSTEM_H
#define STARSYSTEM_H
//#include <vector>
//#include "../spaceobjects/BaseGameEntity.hpp"
//#include "../spaceobjects/planet.hpp"
//#include "../pilots/player.hpp"
//#include "../pilots/npc.hpp"
//#include "../spaceobjects/star.hpp"
//#include "../spaceobjects/asteroid.hpp"
//#include "../spaceobjects/mineral.hpp"
//#include "../spaceobjects/container.hpp"
//#include "../spaceobjects/rocketBullet.hpp"
//#include "../common/myVector.hpp"
//#include "../spaceobjects/planet.hpp"
//#include "../spaceobjects/blackHole.hpp"
//#include "../spaceobjects/spaceStation.hpp"
//#include "../spaceobjects/satellite.hpp"
//#include "../spaceobjects/ship.hpp"
//#include "../world/galaxy.hpp"
//#include "../gui/guiVehicle.hpp"


class StarSystem : public BaseGameEntity
{
	public:
		StarSystem(int);
		~StarSystem();

		void SetGalaxy(Galaxy* galaxy)  { this->galaxy = galaxy; };
						
		bool GetDetailedSimulationFlag() const { return detalied_simulation; };
		bool GetCaptured()       const { return is_CAPTURED; };  
		int GetRaceId()          const { return race_id; };
		int GetConquerorRaceId() const { return conqueror_race_id; };  
		Star* GetStar()          const { return STAR_vec[0]; };		
		Galaxy* GetGalaxy()      const { return galaxy; };
		int GetShockWaveNum()    const { return effect_SHOCKWAVE_vec.size(); };
		
		//// TRANSITION
		void AddToHyperJumpQueue(Vehicle*);

		void AddToSpace(Vehicle*, vec2f, float, BaseGameEntity*);
						
		void AddToSpace(Star*);
		void AddToSpace(Planet*, BaseGameEntity*);
		void AddToSpace(Asteroid*);
		void AddToSpace(Mineral*, vec2f);
		void AddToSpace(Container*, vec2f);
		void AddToSpace(RocketBullet*);
		void AddToSpace(BlackHole*, vec2f);

		// effects
		void AddToSpace(BaseParticleSystem*);
		void AddToSpace(ShockWaveEffect*);
		void AddToSpace(LazerTraceEffect*);

		void AddToSpace(DistantNebulaBgEffect*);
		void AddToSpace(DistantStarBgEffect*);
		
		void AddToSpace(VerticalFlowText*);
		//

		void AddToRemoveFromOuterSpaceQueue(Mineral*);
		void AddToRemoveFromOuterSpaceQueue(Container*);
		void AddToRemoveFromOuterSpaceQueue(Vehicle*);
				
		bool RemoveShip(int);    
		bool RemoveNpc(int, int); 
		
		void BombExplosionEvent(Container*, bool);
		
		void FindVisibleEntities_c(Player*);  

		void Update(int, bool);

    		void RestoreDefaultColor();
    		void RestoreSceneColor();
    		void DrawBackground(vec2f);
                void DrawOrbits();
                void DrawPath();
                
                void SaveEvent() const;
                void LoadEvent(const std::string&) const;
                                           		    		    		
		// poor
		Planet* GetClosestPlanet(vec2f);
		Npc* GetRandomNpc();
		Npc* GetRandomNpcExcludingRaceId(int);
		Npc* GetRandNpcByRaceId(int) const;
		Npc* GetRandNpc(std::vector<int>*) const;
		// 
    	private:
                int race_id, conqueror_race_id;
                
    		bool detalied_simulation;
    		bool calculation_per_turn_allowed; 
    		bool calculation_per_turn_allowed_inDynamic; 
    		    		
    		bool is_CAPTURED;
    		
    		Galaxy* galaxy;
    	
    		// ENTITY VECTORS
		std::vector<Player*> 	   PLAYER_vec;

		std::vector<Star*>         STAR_vec;
		std::vector<Planet*>       PLANET_vec;
		std::vector<Asteroid*>     ASTEROID_vec;
		std::vector<Mineral*>      MINERAL_vec;
		std::vector<Container*>    CONTAINER_vec;
		std::vector<RocketBullet*> ROCKET_vec;
		std::vector<BlackHole*>    BLACKHOLE_vec;
		std::vector<SpaceStation*> SPACESTATION_vec;
		std::vector<Satellite*>    SATELLITE_vec;

		std::vector<Ship*> SHIP_inSPACE_vec;
		std::vector<Npc*>  NPC_inSPACE_vec;
		// these 5 list below is needed for AI
		std::vector<Npc*>  NPC_RANGER_inSPACE_vec;  
		std::vector<Npc*>  NPC_WARRIOR_inSPACE_vec;
		std::vector<Npc*>  NPC_TRADER_inSPACE_vec;
		std::vector<Npc*>  NPC_PIRAT_inSPACE_vec;
		std::vector<Npc*>  NPC_DIPLOMAT_inSPACE_vec;
		//  
		
		
    	    	// ENTITY VECTORS
                std::vector<Vehicle*> appear_VEHICLE_queue;
                
    	    	std::vector<DistantNebulaBgEffect*> distantNebulaBgEffect_vec;
    		std::vector<DistantStarBgEffect*>   distantStarBgEffect_vec;
    		   
    		// effects
    		std::vector<LazerTraceEffect*>    effect_LAZERTRACE_vec;
    		std::vector<BaseParticleSystem*>  effect_PARTICLESYSTEM_vec;
    		std::vector<ShockWaveEffect*>     effect_SHOCKWAVE_vec;    		
    		std::vector<VerticalFlowText*> text_DAMAGE_vec;
    		
    		// remove queue 	
    		std::vector<Container*>    remove_CONTAINER_queue;
    		std::vector<Mineral*>      remove_MINERAL_queue;
    		std::vector<Ship*>         remove_SHIP_queue;
    		std::vector<SpaceStation*> remove_SPACESTATION_queue;
    		std::vector<Satellite*>    remove_SATELLITE_queue;    		
    		//    			    		    	  
    		  	
    		GarbageEntities garbage_entities;
    		GarbageEffects  garbage_effects;
    		            
    		void AddToSpace(Npc*);
    		            		    
                void PostHyperJumpEvent();
                void LaunchingEvent() const;
    		
    		void updateEntities_inStatic_s();
    		void updateEntities_s(int, bool);   		
                      
                bool RemoveFromTheListById(std::vector<Npc*>*, int);
    		
    		void updateStates();
    		
    		void damageEventInsideCircle(vec2f epicentr, float radius, int damage, bool show_effect);
    		
    		void PostDeathUniqueEvent(bool);


		void asteroidManager_s(unsigned int num);

		void manageUnavaliableObjects_s();
		void manageDeadObjects_s();

		void rocketCollision_s(bool);
		void asteroidCollision_s(bool);
		
		void SaveUniqueStarSystem(const std::string&) const;
		
		friend class GuiMap;
		friend class Observation;
		friend class Player;
};

StarSystem* GetNewStarSystem(int);

template <typename AGRESSOR, typename VICTIM>
bool checkCollision(AGRESSOR*,  VICTIM*, bool);

bool collisionBetweenCenters(Points* points1, Points* points2, float collision_radius);
bool collisionBetweenCenters(Points* points1, vec2f point2, float collision_radius);
bool collisionBetweenCenters(Points* points1, float center2_x, float center2_y, float collision_radius);

#endif 




