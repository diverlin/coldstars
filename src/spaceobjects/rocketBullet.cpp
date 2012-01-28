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

#include "rocketBullet.hpp"


RocketBullet :: RocketBullet(IdData _data_id, 
			     LifeData _data_life, 
			     BulletData _data_bullet, 
			     vec2f _start_pos, 
			     float _angle_inD, 
                             TargetObject* _targetOb,
			     int _owner_id,
			     float offset)
{
	data_id     = _data_id;
	data_life   = _data_life;
	data_bullet = _data_bullet;
	

        starsystem = NULL;

        owner_ship_id = _owner_id;

	targetOb = new TargetObject();
        targetOb->copy(_targetOb);

        texOb = _data_bullet.texOb;

        speed = _data_bullet.speed_init;

        // points
        points.initCenterPoint();
        points.addCenterPoint();

        points.initMainQuadPoints(texOb->w, texOb->h);
        points.addMainQuadPoints();
        
        points.initMidLeftPoint();
    	points.addMidLeftPoint();

    	points.initMidFarLeftPoint();
    	points.addMidFarLeftPoint();
    	//

        dx = 0;
        dy = 0;

        points.setCenter(_start_pos.x + offset, _start_pos.y + offset);
        angle_inD = _angle_inD;
        points.setAngle(angle_inD);
        
   	drive_trail = createTrailEffect(texOb->size_id, points.getpMidLeft(), points.getpMidFarLeft());
}


RocketBullet :: ~RocketBullet()
{
	delete drive_trail;
	delete targetOb;
}


void RocketBullet :: setStarSystem(StarSystem* _starsystem) { starsystem = _starsystem; }

bool RocketBullet :: getGarbageReady() const { return data_life.garbage_ready; }
bool RocketBullet :: getAlive() const { return data_life.is_alive; }
int RocketBullet :: getArmor() const  { return data_life.armor; }
int RocketBullet :: getDamage() const { return data_bullet.damage; }
int RocketBullet :: getOwnerShipId() const { return owner_ship_id; }
        	
Points* RocketBullet :: getPoints() { return &points; }


void RocketBullet :: update_inSpace_inDynamic()
{
    	if (speed < data_bullet.speed_max)
    	{
       		speed += data_bullet.d_speed; 
    	} 

	targetOb->validation(starsystem);
    	if (targetOb->getValid() == true)
    	{ 
        	//dx, dy, angle_new = rocketWayCalc((self.points.center[0], self.points.center[1]), (self.target.points.center[0], self.target.points.center[1]), self.points.angle, self.angular_speed, self.step)
        	get_dX_dY_angleInD_ToPoint(points.getCenter().x, points.getCenter().y, targetOb->getpCenter()->x, targetOb->getpCenter()->y, speed/100.0, &dx, &dy, &angle_inD);
    	}      
    	points.setAngle(angle_inD);
    	points.setCenter(points.getCenter().x + dx, points.getCenter().y + dy);
    

    	data_bullet.live_time -= 1;
    	if (data_bullet.live_time < 0)
    	{
       		death_TRUE();
    	}
}

void RocketBullet :: updateDebugWay(int _timer)   // DEBUG
{
   // # DEBUG WAY
   // def updateDebugWay(self, timer, mx, my):
    //    if 1 > 0:
      //     if self.speed < ROCKET_SPEED_MAX:
        //      self.speed += ROCKET_DELTA_SPEED/2.0
          //    self.stepCalculation()
           
        //   (self.dx, self.dy), self.angle_new = rocketWayCalc((self.points.center[0], self.points.center[1]), (mx, my), self.points.angle, self.angular_speed, self.step)
           
        //   # NEW !!!
        //   self.points.setAngle(self.angle_new)
        //   self.points.setCenter(self.points.center[0] + self.dx, self.points.center[1] + self.dy)
         //  self.points.update()

}


void RocketBullet :: collisionEvent_TRUE()
{
	data_life.is_alive = false; 
	death_TRUE();
}

void RocketBullet :: collisionEvent_FALSE()
{
	data_life.is_alive = false; 
	death_FALSE();
}



void RocketBullet :: hit_TRUE(int _damage)
{
    	data_life.armor -= _damage;
    	if (data_life.armor <= 0)
    	{
    	     	data_life.is_alive = false; 
        	death_TRUE();
        }
}

void RocketBullet :: hit_FALSE(int _damage)
{
    	data_life.armor -= _damage;
    	if (data_life.armor <= 0)
    	{
    	     	data_life.is_alive = false; 
        	death_FALSE();
        }
}

void RocketBullet :: death_TRUE()
{
     	if (data_life.garbage_ready == false)
     	{   
        	createExplosion(starsystem, points.getCenter(), texOb->size_id);
        	data_life.garbage_ready = true;
     	}
}

void RocketBullet :: death_FALSE()
{
     	data_life.garbage_ready = true; 
}



void RocketBullet :: updateRenderStuff()
{
	points.update();
	drive_trail->update();
}

void RocketBullet :: renderDriveTrail() const
{
	drive_trail->render();
}

void RocketBullet :: renderKorpus() const
{
    	drawFlatQuadPerVertexIn2D(texOb,
    				  points.getBottomLeft(), 
                              	  points.getBottomRight(), 
                              	  points.getTopRight(), 
                              	  points.getTopLeft(), 
                              	  points.getPosZ());
}

void RocketBullet :: render_inSpace() const
{
	renderKorpus();
	renderDriveTrail();
}






RocketBullet* rocketBulletGenerator(BulletData data_bullet, ItemSlot* slot, float offset, bool force_center_start)
{
	IdData data_id;
	LifeData data_life;
	
	data_id.id = -1;
	data_id.type_id = ROCKET_BULLET_ID;
	data_id.subtype_id = -1;
	
	data_life.is_alive      = true;
        data_life.garbage_ready = false;
        data_life.armor = data_bullet.armor;        

    	RocketBullet* rocket; 
    	if ( (slot->getOwnerShip()->data_korpus.render_TURRELS == true) and (force_center_start == false))
    	{
        	rocket = new RocketBullet(data_id,
        			          data_life,		
        				  data_bullet,
        				  slot->getTurrel()->getCenter(), 
                                  	  slot->getTurrel()->getAngle(), 
                                  	  slot->getTurrel()->getTargetOb(), 
                                  	  slot->getOwnerShip()->getId(),
                                  	  offset);
        }
    	else
    	{
        	rocket = new RocketBullet(data_id,
        			          data_life,		
        				  data_bullet,
                                  	  slot->getOwnerShip()->getPoints()->getCenter(), 
                                  	  slot->getTurrel()->getAngle(), 
                                  	  slot->getTurrel()->getTargetOb(), 
                                  	  slot->getOwnerShip()->getId(),
                                  	  offset);
         }
         
         return rocket;
}
