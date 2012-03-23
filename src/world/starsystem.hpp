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


class StarSystem : public SpaceObjectBase
{
	public:
		Star* getStar() const;
		
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
    	    	
    	    	Points* getPoints() const;
   		bool* getpAlive();
   		int* getpPlaceTypeId();
   		float getCollisionRadius() const;
   		
   		int getShockWaveNum() const;
    
    		StarSystem(int);
    		~StarSystem();
    
    		void setPosition(vec2f);
		void setGalaxy(Galaxy*);
		
		int getId() const;
                int getTypeId() const;
                StarSystem* getStarSystem();
		bool getDetailedSimulationFlag() const;
		bool getCaptured() const;
		vec2f getPosition() const;
		int getRaceId() const;
		int getConquerorRaceId() const;
		
		Galaxy* getGalaxy() const;
		
		// poor
    		Planet* getClosestPlanet(vec2f);
    		Npc* getRandomNpc();
                Npc* getRandomNpcExcludingRaceId(int);
                Npc* getRandNpcByRaceId(int) const;
		Npc* getRandNpc(std::vector<int>*) const;
    		// 

		void update_s(int, bool);

    		//// TRANSITION
                void addToHyperJumpQueue(Npc*);
                                
    		void addToSpace(VehicleBase*, vec2f, float, SpaceObjectBase*);
    		void addToSpace(Npc*);

                void addToSpace(Star*);
                void addToSpace(Planet*, SpaceObjectBase*);
    		void addToSpace(Asteroid*);
    		void addToSpace(Mineral*, vec2f);
    		void addToSpace(Container*, vec2f);
    		void addToSpace(RocketBullet*);
    		void addToSpace(BlackHole*, vec2f);
    		    		
     		// effects
    		void addToSpace(BaseParticleSystem*);
    		void addToSpace(ShockWaveEffect*);
    		void addToSpace(LazerTraceEffect*);
    		
    		void addToSpace(VerticalFlowText*);
   		
    		void addToSpace(DistantNebulaBgEffect*);
    		void addToSpace(DistantStarBgEffect*);
                
    		bool removeShip(int _id);    
    		bool removeNpc(int _id, int _subtype_id);  
   		////
   		
   		void addToRemoveFromOuterSpaceQueue(Mineral*);
   		void addToRemoveFromOuterSpaceQueue(Container*);
   		void addToRemoveFromOuterSpaceQueue(VehicleBase*);
   		    		
   		void bombExplosionEvent(Container*, bool);
   		
   		void findVisibleEntities_c(Player*);  

    		void restoreDefaultColor();
    		void restoreSceneColor();
    		void renderBackground(vec2f);
                void drawOrbits();
                void drawPath();
                           		    		    		
    	private:
                int id, type_id;
                int race_id, conqueror_race_id;
                
    		bool detalied_simulation;
    		bool calculation_per_turn_allowed; 
    		bool calculation_per_turn_allowed_inDynamic; 
    		    		
    		bool is_CAPTURED;
    		
    		vec2f center;
    		
    		Galaxy* galaxy;
    	
    	    	// ENTITY VECTORS
                std::vector<Npc*> NPC_appear_vec;
                
    	    	std::vector<DistantNebulaBgEffect*> distantNebulaBgEffect_vec;
    		std::vector<DistantStarBgEffect*> distantStarBgEffect_vec;
    		   
    		// effects
    		std::vector<LazerTraceEffect*> effect_LAZERTRACE_vec;
    		std::vector<BaseParticleSystem*>  effect_PARTICLESYSTEM_vec;
    		std::vector<ShockWaveEffect*>  effect_SHOCKWAVE_vec;    		
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
    		                
                void postHyperJumpEvent_s();
                void launchingEvent_s() const;

    		void asteroidManager_s(unsigned int num);

   		void manageUnavaliableObjects_s();
    		void manageDeadObjects_s();
    		   		
                void rocketCollision_s(bool);
    		void asteroidCollision_s(bool);

    		
    		void updateEntities_inStatic_s();
    		void updateEntities_s(int, bool);     		
   		
                      
                bool removeFromTheListById(std::vector<Npc*>*, int _id);
    		
    		void update_s();
    		
    		void damageEventInsideCircle(vec2f epicentr, float radius, int damage, bool show_effect);
    		
    		void debug__();    	
    		
    		void postDeathUniqueEvent(bool);
};

template <typename AGRESSOR, typename VICTIM>
bool checkCollision(AGRESSOR*,  VICTIM*, bool);

bool collisionBetweenCenters(Points* points1, Points* points2, float collision_radius);
bool collisionBetweenCenters(Points* points1, vec2f point2, float collision_radius);
bool collisionBetweenCenters(Points* points1, float center2_x, float center2_y, float collision_radius);

#endif 


                

