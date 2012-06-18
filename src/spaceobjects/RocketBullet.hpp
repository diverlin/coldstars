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
                RocketBullet(int);
                	     
                ~RocketBullet();
                                
		void Place(vec2f, float, float);
		
		void SetBulletData(BulletData data_bullet) { this->data_bullet = data_bullet; speed = data_bullet.speed_init; };
		void SetOwner(BaseGameEntity* owner) { this->owner = owner; };
		void SetTarget(BaseGameEntity* target) { this->target = target; };
		
        	int GetDamage() const { return data_bullet.damage; };
		BaseGameEntity* GetOwner() const { return owner; };
        
                void UpdateInSpace(int, bool);

		void CollisionEvent(bool);

             	void UpdateRenderStuff();
                void RenderInSpace() const;
                
                void SaveData(boost::property_tree::ptree&) const;
    		void LoadData(const boost::property_tree::ptree&);
    		void ResolveData();
    		
        private:
                BulletData data_bullet;
               
                float speed;
               
                float dx, dy;
                float angle_inD;                
                
                BaseGameEntity* owner;
                BaseGameEntity* target;
               
                void deathEventUnique(bool);
                
                virtual void UpdateInfo(); 
                
                bool CheckTarget() const;
                bool CheckStarSystem() const;     
};

#endif 
