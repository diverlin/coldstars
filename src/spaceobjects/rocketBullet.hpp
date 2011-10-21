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


#ifndef ROCKETBULLET_H
#define ROCKETBULLET_H


class RocketBullet
{
        public:
                RocketBullet(IdData _data_id,
                	     LifeData _data_life,
                	     BulletData _data_bullet, 
                	     float _start_pos_x, 
                	     float _start_pos_y, 
                	     float _angle_inD, 
                	     float* _pTo_target_pos_x, 
                	     float* _pTo_target_pos_y, 
                	     bool* _pTo_target_is_alive, 
                	     int _owner_id);
                	     
                ~RocketBullet();
        
        	void setStarSystem(StarSystem*);
        	
        	bool getAlive() const;
        	int getArmor() const;
        	int getDamage() const;
        	int getOwnerShipId() const;
                Points* getPoints();
        
                void update_inSpace_inDynamic();
                					void updateDebugWay(int _timer);   // DEBUG
		void collision_TRUE();
		void collision_FALSE();

                void hit_TRUE(int _damage);
                void hit_FALSE(int _damage);

             	void updateRenderStuff();
                void renderInSpace() const;
                
        private:
      		IdData data_id;
                LifeData data_life;
                BulletData data_bullet;

                int owner_ship_id;
                                
                TextureOb* texOb;
                Points points;
                
                StarSystem* starsystem;
                
                               
                int size_id;

                float speed;
                float step;

                float* pTo_target_pos_x;
                float* pTo_target_pos_y;
                bool target_is_alive;    
                bool* pTo_target_is_alive;
                
                float dx, dy;
                float angle_inD;
                
                
                TrailEffect* drive_trail;
                
                void stepCalculation();
                
                void death_TRUE();
                void death_FALSE();
                
		void renderKorpus() const;
                void renderDriveTrail() const;
        
};

RocketBullet* rocketGenerator(BulletData, ItemSlot*);

#endif 
