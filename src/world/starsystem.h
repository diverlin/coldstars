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

    		VEC_pStar_type         STAR_pList;
    		VEC_pPlanet_type       PLANET_pList;
    		VEC_pAsteroid_type     ASTEROID_pList;
    		VEC_pMineral_type      MINERAL_pList;
    		VEC_pContainer_type    CONTAINER_pList;
    		VEC_pRocketBullet_type ROCKET_pList;

		VEC_pShip_type     SHIP_pList;
    		VEC_pNpc_type      NPC_pList;
    		VEC_pNpc_type      NPC_RANGER_pList;  // these 5 list below is needed for AI
    		VEC_pNpc_type      NPC_WARRIOR_pList;
    		VEC_pNpc_type      NPC_TRADER_pList;
    		VEC_pNpc_type      NPC_PIRAT_pList;
    		VEC_pNpc_type      NPC_DIPLOMAT_pList;

    		VEC_pLazerTrace_type       effect_LAZERTRACE_pList;
    		VEC_pExplosionEffect_type  effect_EXPLOSION_pList;
    		VEC_pDamageEffect_type 	   effect_DAMAGE_pList;
    		VEC_pShockWaveEffect_type  effect_SHOCKWAVE_pList;
       
    		// REMOVE QUEUE LIST
    		VEC_pShip_type      SHIP_remove_queue_pList;
    		VEC_pNpc_type       NPC_remove_queue_pList;

    		VEC_pAsteroid_type  ASTEROID_remove_queue_pList;
    		VEC_pMineral_type   MINERAL_remove_queue_pList;
    		VEC_pContainer_type CONTAINER_remove_queue_pList;
    		VEC_pRocketBullet_type      ROCKET_remove_queue_pList;

    		// VISIBLE ENTITY LIST
    		VEC_pStar_type      visible_STAR_pList;
    		VEC_pPlanet_type    visible_PLANET_pList;
    		VEC_pAsteroid_type  visible_ASTEROID_pList;
    		VEC_pMineral_type   visible_MINERAL_pList;
    		VEC_pContainer_type visible_CONTAINER_pList;
    		VEC_pRocketBullet_type      visible_ROCKET_pList;

    		VEC_pShip_type      visible_SHIP_pList;

     

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
                                          
                void defineSceneColor(TextureOb* _pTo_texOb);
                                                
                void createPostProcessStuff();
    		void renderEntities_NEW();
    		void renderEntities_OLD();
    			void setSceneColor();
    			void renderBackground();
        
    		void addExplosion(float _center_x, float _center_y, int obSize);
    		void addShockWave(float _center_x, float _center_y, int obSize);
    		    		
    		void asteroidManager(int num);
    		void addNumMinerals(float _center_x, float _center_y, int num);

    		void manageEntities();
    		void removeDeadEntities();


    		void mouseControl();

    		void fireEvents_TRUE(int timer);
    		void fireEvents_FALSE(int timer);

    		//// TRANSITION
                bool addStar(Star* _star);
                bool addPlanet(Planet* _planet);
    		bool addAsteroid(Asteroid* _asteroid);
    		bool addShip(Ship* _ship);
    		bool addNpc(Npc* _npc);
    		bool addMineral(Mineral* _mineral);
    		bool addContainer(Container* _container);
                
    		bool removeShipById(int _id);    
    		bool removeNpc(int _id, int _race_id, int _subtype_id);  
         	bool removeNpcFromTheListById(VEC_pNpc_type* pTo_npc_pList, int _id);
   		//// TRANSITION

    		Planet* returnClosestPlanet(int _pos_x, int _pos_y);

    		void debug__();
};

#endif 


                

