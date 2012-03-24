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


class RocketBullet : public Vehicle
{
        public:
                RocketBullet(BulletData,  
                	     BaseGameEntity*, 
                	     int _owner_id);
                	     
                ~RocketBullet();
                
                
		void place(vec2f, float, float);

        
        	int getDamage() const;
        	int getOwnerShipId() const;
        
                void update_inSpace(int, bool);

		void collisionEvent(bool);

             	void updateRenderStuff();
                void render_inSpace() const;
                
        private:
                BulletData data_bullet;

                int owner_ship_id;

                float speed;
               
                float dx, dy;
                float angle_inD;                
                
                BaseGameEntity* target;
               
                void deathEventUnique(bool);
                
                virtual void updateInfo(); 
                
                bool isTargetOk() const;
                bool isStarSystemOk() const;     
};

RocketBullet* getNewRocketBullet(BulletData, ItemSlot*, float, bool force_center_start = false);

#endif 
