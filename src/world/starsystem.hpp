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


class StarSystem
{
	public:
    	    	// ENTITY VECTORS
    	    	std::vector<Player*> 	   PLAYER_vec;
    	    	
    		std::vector<Star*>         STAR_vec;
    		std::vector<Planet*>       PLANET_vec;
    		std::vector<Asteroid*>     ASTEROID_vec;
    		std::vector<Mineral*>      MINERAL_vec;
    		std::vector<Container*>    CONTAINER_vec;
    		std::vector<RocketBullet*> ROCKET_vec;


		std::vector<Ship*> SHIP_inSPACE_vec;
    		std::vector<Npc*>  NPC_inSPACE_vec;
		// these 5 list below is needed for AI
    		std::vector<Npc*>  NPC_RANGER_inSPACE_vec;  
    		std::vector<Npc*>  NPC_WARRIOR_inSPACE_vec;
    		std::vector<Npc*>  NPC_TRADER_inSPACE_vec;
    		std::vector<Npc*>  NPC_PIRAT_inSPACE_vec;
    		std::vector<Npc*>  NPC_DIPLOMAT_inSPACE_vec;
    	    	//  
    
    		StarSystem();
    		~StarSystem();
    
    		void setPosition(vec2f);
		//void setDetailedSimulationFlag(bool);
		void setCapturedFlag(bool);
		
		int getId() const;
                int getTypeId() const;
                StarSystem* getStarSystem();
		bool getDetailedSimulationFlag() const;
		bool getCapturedFlag() const;
		vec2f getPosition() const;
		int getShockWaveNum() const;
		
		// poor
    		Planet* getClosestPlanet(vec2f);
    		Npc* getRandomNpc();
                Npc* getRandomNpcExcludingRaceId(int);
                Npc* getEvilNpc(vec2f);
    		// 

		void update_TRUE(int timer);
		void update_FALSE(int timer);

	        void render();      
   		    		
    		void mouseControl();

    		//// TRANSITION
                void addToHyperJumpQueue(Npc*);
                                
    		void moveToSpace(Ship*);
    		void moveToSpace(Npc*);

    		
                void add(Star*);
                void add(Planet*);
    		void add(Asteroid*);
    		void add(Mineral*);
    		void add(Container*);
    		void add(RocketBullet*);
    		
    		
    		void killMineralById(int _id);
    		void removeContainer(int _id);
    		    		
    		// effects
    		void add(ExplosionEffect*);
    		void add(ShockWaveEffect*);
    		void add(LazerTraceEffect*);
    		void add(DamageEffect*);
    		
    		void add(VerticalFlowText*);
   		
    		void add(DistantNebulaBgEffect*);
    		void add(DistantStarBgEffect*);
                
    		bool removeShip(int _id);    
    		bool removeNpc(int _id, int _subtype_id);  
   		//// 
    		
    	private:
                int id, type_id;
                
    		bool detalied_simulation;
    		bool calculation_per_turn_allowed; 
    		bool calculation_per_turn_allowed_inDynamic; 
    		    		
    		bool is_CAPTURED;
    		
    		vec2f center;
    	
    	    	// ENTITY VECTORS
                std::vector<Npc*> NPC_appear_vec;
                
    	    	std::vector<DistantNebulaBgEffect*> distantNebulaBgEffect_vec;
    		std::vector<DistantStarBgEffect*> distantStarBgEffect_vec;
    		
    		// effects
    		std::vector<LazerTraceEffect*> effect_LAZERTRACE_vec;
    		std::vector<ExplosionEffect*>  effect_EXPLOSION_vec;
    		std::vector<DamageEffect*>     effect_DAMAGE_vec;
    		std::vector<ShockWaveEffect*>  effect_SHOCKWAVE_vec;
    		
    		std::vector<VerticalFlowText*> text_DAMAGE_vec;
    		// 
    		
   		// VISIBLE ENTITY LIST
    		std::vector<Star*>         visible_STAR_vec;
    		std::vector<Planet*>       visible_PLANET_vec;
    		std::vector<Asteroid*>     visible_ASTEROID_vec;
    		std::vector<Mineral*>      visible_MINERAL_vec;
    		std::vector<Container*>    visible_CONTAINER_vec;
    		std::vector<RocketBullet*> visible_ROCKET_vec;

    		std::vector<Ship*>      visible_SHIP_vec;
    		//  
    		    	    	
    		Garbage garbage;
                
                void postHyperJumpEvent();

    		void asteroidManager(unsigned int num);
    		    		
    		void manageDeadObjects();
   		
                void rocketCollision_TRUE();
    		void rocketCollision_FALSE();

    		void asteroidCollision_TRUE();
    		void asteroidCollision_FALSE();

    		void updateEntities_inDynamic_TRUE();
    		void updateEntities_inDynamic_FALSE();
    		void updateEntities_inStatic();
    		void updateEffects();
    		
    		void fireEvents_TRUE(int timer);
    		void fireEvents_FALSE(int timer);
    		
    		
		void findVisibleEntities();    
    		void renderEntities_NEW();
    		void renderEntities_OLD();
    		        void restoreDefaultColor();
    			void restoreSceneColor();
    			void renderBackground();
                        
                bool removeFromTheListById(std::vector<Npc*>* _pTo_npc_vec, int _id);
    		
    		void debug__();    	
};

template <typename AGRESSOR, typename VICTIM>
bool collideEvent_TRUE(AGRESSOR*,  VICTIM*);

bool collisionBetweenCenters(Points* points1, Points* points2, float collision_radius);
bool collisionBetweenCenters(Points* points1, vec2f point2, float collision_radius);
bool collisionBetweenCenters(Points* points1, float center2_x, float center2_y, float collision_radius);

bool isObjectVisible(Points* points, float startViewCoord_x, float startViewCoord_y);
bool isObjectVisible(float ob_centerx, float ob_centery, int ob_w, int ob_h, float startViewCoord_x, float startViewCoord_y); 

#endif 


                

