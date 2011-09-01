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
		int id; 

    		bool is_CAPTURED; 
   
    		Color color;
    		Rect rect_onMap;

    		// ENTITY LISTS
    		VEC_pDistantNebulaBgEffect_type distantNebulaBgEffect_pList;
    		VEC_pDistantStarBgEffect_type distantStarBgEffect_pList;

    		std::vector<Star*>         STAR_pList;
    		std::vector<Planet*>       PLANET_pList;
    		std::vector<Asteroid*>     ASTEROID_pList;
    		std::vector<Mineral*>      MINERAL_pList;
    		std::vector<Container*>    CONTAINER_pList;
    		std::vector<RocketBullet*> ROCKET_pList;

		std::vector<Ship*> SHIP_pList;
    		std::vector<Npc*>  NPC_pList;
		// these 5 list below is needed for AI
    		std::vector<Npc*>  NPC_RANGER_pList;  
    		std::vector<Npc*>  NPC_WARRIOR_pList;
    		std::vector<Npc*>  NPC_TRADER_pList;
    		std::vector<Npc*>  NPC_PIRAT_pList;
    		std::vector<Npc*>  NPC_DIPLOMAT_pList;

    		std::vector<LazerTraceEffect*>       effect_LAZERTRACE_pList;
    		std::vector<ExplosionEffect*>  effect_EXPLOSION_pList;
    		std::vector<DamageEffect*> 	   effect_DAMAGE_pList;
    		VEC_pShockWaveEffect_type  effect_SHOCKWAVE_pList;
       
    		// REMOVE QUEUE LIST
    		std::vector<Ship*>  SHIP_remove_queue_pList;
    		std::vector<Npc*>   NPC_remove_queue_pList;

    		std::vector<Asteroid*>  ASTEROID_remove_queue_pList;
    		std::vector<Mineral*>   MINERAL_remove_queue_pList;
    		std::vector<Container*> CONTAINER_remove_queue_pList;
    		std::vector<RocketBullet*> ROCKET_remove_queue_pList;

    		// VISIBLE ENTITY LIST
    		std::vector<Star*>      visible_STAR_pList;
    		std::vector<Planet*>    visible_PLANET_pList;
    		std::vector<Asteroid*>  visible_ASTEROID_pList;
    		std::vector<Mineral*>   visible_MINERAL_pList;
    		std::vector<Container*> visible_CONTAINER_pList;
    		std::vector<RocketBullet*> visible_ROCKET_pList;

    		std::vector<Ship*>      visible_SHIP_pList;

     

    		StarSystem();
    		~StarSystem();
    
    		void setPositionOnWorldMap(Rect rect);


    		void rocketCollision_TRUE();
    		void rocketCollision_FALSE();

    		void asteroidCollision_TRUE();
    		void asteroidCollision_FALSE();

    		void updateEntities_inDynamic_TRUE();
    		void updateEntities_inDynamic_FALSE();
    		void updateEntities_inStatic();

    		void findVisibleEntities();
        
                FBO* pTo_fbo0;
                FBO* pTo_fbo1;
                FBO* pTo_fbo2;
                FBO* pTo_fbo3;
                BloomEffect* pTo_bloom; 
                                          
                void defineSceneColor(TextureOb*);
                                                
                void createPostProcessStuff();
    		void renderEntities_NEW();
    		void renderEntities_OLD();
    			void setSceneColor();
    			void renderBackground();
        
   		    		
    		void asteroidManager(int num);

    		void manageEntities();
    		void removeDeadEntities();


    		void mouseControl();

    		void fireEvents_TRUE(int timer);
    		void fireEvents_FALSE(int timer);

    		//// TRANSITION
    		void createExplosion(vec2f _center_pos, int obSize);
    		void createShockWave(vec2f _center_pos, int obSize);
    		
                bool addStar(Star*);
                bool addPlanet(Planet*);
    		bool addAsteroid(Asteroid*);
    		bool addShip(Ship*);
    		bool addNpc(Npc*);
    		bool addMineral(Mineral*);
    		bool addContainer(Container*);
    		bool addExplosion(ExplosionEffect*);
    		bool addShockWave(ShockWaveEffect*);
    		
                
    		bool removeShipById(int _id);    
    		bool removeNpc(int _id, int _race_id, int _subtype_id);  
         	bool removeNpcFromTheListById(std::vector<Npc*>* pTo_npc_pList, int _id);
   		//// TRANSITION

    		Planet* returnClosestPlanet(vec2f);

    		void debug__();
};

#endif 


                

