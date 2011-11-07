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
                	     vec2f _start_pos, 
                	     float _angle_inD, 
                	     TargetObject* _targetOb, 
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
                void render_inSpace() const;
                
        private:
      		IdData data_id;
                LifeData data_life;
                BulletData data_bullet;

                int owner_ship_id;
                                
                TextureOb* texOb;
                Points points;
                
                StarSystem* starsystem;

                float speed;
               
                float dx, dy;
                float angle_inD;                
                
                TargetObject* targetOb;
                TrailEffect* drive_trail;                
               
                void death_TRUE();
                void death_FALSE();
                
		void renderKorpus() const;
                void renderDriveTrail() const;        
};

RocketBullet* rocketGenerator(BulletData, ItemSlot*);

#endif 
