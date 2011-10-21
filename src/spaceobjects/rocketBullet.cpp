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
			     float _start_pos_x, 
			     float _start_pos_y, 
			     float _angle_inD, 
			     float* _pTo_target_pos_x, 
			     float* _pTo_target_pos_y, 
			     bool* _pTo_target_is_alive, 
			     int _owner_id)
{
	data_id     = _data_id;
	data_life   = _data_life;
	data_bullet = _data_bullet;
	

        starsystem = NULL;

        owner_ship_id = _owner_id;
        //target_type_id = 0;

        target_is_alive = true;
        pTo_target_is_alive = _pTo_target_is_alive;
        pTo_target_pos_x = _pTo_target_pos_x;
        pTo_target_pos_y = _pTo_target_pos_y;

        texOb = _data_bullet.texOb;
        size_id = returnObjectSize(texOb->w, texOb->h);


        speed = _data_bullet.speed_init;
        step = 0;

        // points
        points = Points();

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

        points.setCenter(_start_pos_x, _start_pos_y);
        angle_inD = _angle_inD;
        points.setAngle(angle_inD);
        
   	drive_trail = createTrailEffect(size_id, points.getpMidLeft(), points.getpMidFarLeft());
}


RocketBullet :: ~RocketBullet()
{
	delete drive_trail;
}


void RocketBullet :: setStarSystem(StarSystem* _starsystem) { starsystem = _starsystem; }

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
       		stepCalculation();
    	} 

    	if ((*pTo_target_is_alive) == false)
    	{
        	target_is_alive = false;    // this step is needed after deleting target object in order to rocket keep moving
        }

    	if (target_is_alive == true)
    	{ 
        	//dx, dy, angle_new = rocketWayCalc((self.points.center[0], self.points.center[1]), (self.target.points.center[0], self.target.points.center[1]), self.points.angle, self.angular_speed, self.step)
        	get_dX_dY_angleInD_ToPoint(points.getCenter().x, points.getCenter().y, (*pTo_target_pos_x), (*pTo_target_pos_y), step, &dx, &dy, &angle_inD);
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


void RocketBullet :: stepCalculation()
{
     	step = speed / 100.0;
}



void RocketBullet :: collision_TRUE()
{
	death_TRUE();
}

void RocketBullet :: collision_FALSE()
{
	death_FALSE();
}



void RocketBullet :: hit_TRUE(int _damage)
{
    	data_life.armor -= _damage;
    	if (data_life.armor <= 0)
    	{
        	death_TRUE();
        }
}

void RocketBullet :: hit_FALSE(int _damage)
{
    	data_life.armor -= _damage;
    	if (data_life.armor <= 0)
    	{
        	death_FALSE();
        }
}

void RocketBullet :: death_TRUE()
{
     	data_life.is_alive = false; 

     	if (data_life.is_explosed == false)
     	{   
        	createExplosion(starsystem, points.getCenter(), size_id);
        	data_life.is_explosed = true;
     	}
}

void RocketBullet :: death_FALSE()
{
     	data_life.is_alive = false; 
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
    	glBindTexture(GL_TEXTURE_2D, texOb->texture); 
    	
    	drawFlatQuadPerVertexIn2D(points.getBottomLeft(), 
                              	  points.getBottomRight(), 
                              	  points.getTopRight(), 
                              	  points.getTopLeft(), 
                              	  -500);
}

void RocketBullet :: renderInSpace() const
{
	renderKorpus();
	renderDriveTrail();
}






RocketBullet* rocketGenerator(BulletData data_bullet, ItemSlot* slot)
{
	IdData data_id;
	LifeData data_life;
	
	data_id.id = -1;
	data_id.type_id = ROCKET_BULLET_ID;
	data_id.subtype_id = -1;
	
	data_life.is_alive    = true;
        data_life.is_explosed = false;
        data_life.armor = data_bullet.armor;        

    	RocketBullet* rocket; 
    	if (slot->getShip()->data_korpus.render_TURRELS == true)
    	{
        	rocket = new RocketBullet(data_id,
        			          data_life,		
        				  data_bullet,
        				  slot->getTurrel()->getCenterX(), 
                                  	  slot->getTurrel()->getCenterY(), 
                                  	  slot->getTurrel()->getAngle(), 
                                  	  slot->getTurrel()->getTarget_pCenterX(), 
                                  	  slot->getTurrel()->getTarget_pCenterY(), 
                                  	  slot->getTurrel()->getTarget_pAliveStatus(), 
                                  	  slot->getShip()->getId());
        }
    	else
    	{
        	rocket = new RocketBullet(data_id,
        			          data_life,		
        				  data_bullet,
        				  slot->getShip()->getPoints()->getCenter().x, 
                                  	  slot->getShip()->getPoints()->getCenter().y, 
                                  	  slot->getTurrel()->getAngle(), 
                                  	  slot->getTurrel()->getTarget_pCenterX(), 
                                  	  slot->getTurrel()->getTarget_pCenterY(), 
                                  	  slot->getTurrel()->getTarget_pAliveStatus(), 
                                  	  slot->getShip()->getId());
         }
         
         return rocket;
}
