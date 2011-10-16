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
                int getId() const;
                int getTypeId() const;

    		bool is_CAPTURED;
    		bool calculation_per_turn_allowed; 
   
    		//Color color;
    		Rect rect_onMap;

    	    	// ENTITY LISTS
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

    
    		StarSystem();
    		~StarSystem();
    
    		void setPositionOnWorldMap(Rect rect);
		void setDetailedSimulation(bool);
		
		bool getDetailedSimulation() const;

		void update_TRUE(int timer);
		void update_FALSE(int timer);

	        void render();        
   		    		
    		void asteroidManager(int num);

    		void manageEntities();
    		void removeDeadEntities();

    		void mouseControl();



    		//// TRANSITION
                void addStar(Star*);
                void addPlanet(Planet*);
    		void addAsteroid(Asteroid*);
    		void addShipToSpace(Ship*);
    		void addShipToPlanet(Ship*, Planet*);
    		void addNpcToSpace(Npc*);
    		void addNpcToPlanet(Npc*, Planet*);
    		void addMineral(Mineral*);
    		void addContainer(Container*);
    		void addRocket(RocketBullet*);
    		
    		void addExplosionEffect(ExplosionEffect*);
    		void addShockWaveEffect(ShockWaveEffect*);
    		void addLazerTraceEffect(LazerTraceEffect*);
    		void addDamageEffect(DamageEffect*);
   		
    		void addDistantNebula(DistantNebulaBgEffect*);
    		void addDistantStar(DistantStarBgEffect*);
                
    		bool removeShipById(int _id);    
    		bool removeNpc(int _id, int _race_id, int _subtype_id);  
         	bool removeNpcFromTheListById(std::vector<Npc*>* pTo_npc_pList, int _id);
   		//// TRANSITION

		int getShockWaveNum() const;
    		Planet* getClosestPlanet(vec2f);
    		Npc* getRandomNpc();
    		
    		void questManager();

    	private:
                int id, type_id;
    		bool detalied_simulation;
    	
    	    	// ENTITY LISTS
    	    	std::vector<DistantNebulaBgEffect*> distantNebulaBgEffect_pList;
    		std::vector<DistantStarBgEffect*> distantStarBgEffect_pList;
    		
    		std::vector<LazerTraceEffect*> effect_LAZERTRACE_vec;
    		std::vector<ExplosionEffect*>  effect_EXPLOSION_vec;
    		std::vector<DamageEffect*>     effect_DAMAGE_vec;
    		std::vector<ShockWaveEffect*>  effect_SHOCKWAVE_vec;
    		
    		
    		// REMOVE QUEUE LIST
    		std::vector<Ship*>  SHIP_remove_queue_pList;
    		std::vector<Npc*>   NPC_remove_queue_pList;

    		std::vector<Asteroid*>  ASTEROID_remove_queue_pList;
    		std::vector<Mineral*>   MINERAL_remove_queue_pList;
    		std::vector<Container*> CONTAINER_remove_queue_pList;
    		std::vector<RocketBullet*> ROCKET_remove_queue_pList;
    		
    		// VISIBLE ENTITY LIST
    		std::vector<Star*>      visible_STAR_vec;
    		std::vector<Planet*>    visible_PLANET_vec;
    		std::vector<Asteroid*>  visible_ASTEROID_vec;
    		std::vector<Mineral*>   visible_MINERAL_vec;
    		std::vector<Container*> visible_CONTAINER_vec;
    		std::vector<RocketBullet*> visible_ROCKET_vec;

    		std::vector<Ship*>      visible_SHIP_vec;
    		
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
    		
    		void debug__();
    	
};

bool collisionBetweenCenters(Points* points1, Points* points2, float collision_radius);
bool collisionBetweenCenters(Points* points1, float center2_x, float center2_y, float collision_radius);

bool isObjectVisible(Points* points, float startViewCoord_x, float startViewCoord_y);
bool isObjectVisible(float ob_centerx, float ob_centery, int ob_w, int ob_h, float startViewCoord_x, float startViewCoord_y); 

#endif 


                

