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

#include "rocketBullet.h"


RocketBullet :: RocketBullet(StarSystem* _pTo_starsystem, TextureOb* _pTo_texOb, float _start_pos_x, float _start_pos_y, float _angle_inD, float* _pTo_target_pos_x, float* _pTo_target_pos_y, bool* _pTo_target_is_alive, int _owner_id, int _damage, int _size, int _armor, float _speed_init, float _speed_max, float _d_speed, float _angular_speed, int _live_time)
{
        type_id = ROCKET_BULLET_ID;
       
        is_alive = true;
        is_explosed = false;

        pTo_starsystem = _pTo_starsystem;

        //CommonInstance.__init__(self, texOb.texture, (texOb.w, texOb.h))
        //if self.animated == True:
        //   self.render = self.renderInSpace
        //else:
        //   self.render = self.renderInSpace

        owner_id = _owner_id;
        //target_type_id = 0;

        target_is_alive = true;
        pTo_target_is_alive = _pTo_target_is_alive;
        pTo_target_pos_x = _pTo_target_pos_x;
        pTo_target_pos_y = _pTo_target_pos_y;

        damage = _damage;

        pTo_texOb = _pTo_texOb;
        texture = pTo_texOb->texture;
        w = pTo_texOb->w;
        h = pTo_texOb->h;

        size = _size;
        armor = _armor;

        speed_init = _speed_init;
        speed_max = _speed_max;
        d_speed = _d_speed;  
        angular_speed = _angular_speed;
        speed = speed_init;
        step = 0;

        live_time = _live_time;


        
        points = Points();

        points.initCenterPoint();
        points.addCenterPoint();

        points.initMainQuadPoints(w, h);
        points.addMainQuadPoints();

        dx = 0;
        dy = 0;

        points.setCenter(_start_pos_x, _start_pos_y);
        angle_inD = _angle_inD;
        points.setAngle(angle_inD);
        //self.drive_jet = driveTrailEffect(self, TEXTURE_MANAGER.returnParticleTexObBy_ColorID(YELLOW_COLOR_ID), 5, 15*self.size, 1.0, 1.0, 0.1, 0.15) 
}


RocketBullet :: ~RocketBullet()
{}

Points* RocketBullet :: getPoints() { return &points; }

//void RocketBullet :: setShipAsTarget(Ship* _pTo_ship)
//{
    //pTo_shipTarget      = _pTo_ship;
    //target_type_id = pTo_shipTarget->type_id;
    
    //pTo_target_pos_x = &(pTo_shipTarget->points.center_x);
    //pTo_target_pos_y = &(pTo_shipTarget->points.center_y);  
    
    //pTo_target_is_alive = &(pTo_shipTarget->is_alive);      
//}

//void RocketBullet :: setAsteroidAsTarget(Asteroid* _pTo_asteroid)
//{
    //pTo_asteroidTarget  = _pTo_asteroid;
    //target_type_id = pTo_asteroidTarget->type_id;
    
    //pTo_target_pos_x = &(pTo_asteroidTarget->points.center_x);
    //pTo_target_pos_y = &(pTo_asteroidTarget->points.center_y);
    
    //pTo_target_is_alive = &(pTo_asteroidTarget->is_alive);   
//}

//void RocketBullet :: setMineralAsTarget(Mineral* _pTo_mineral)
//{
    //pTo_mineralTarget   = _pTo_mineral;
    //target_type_id = pTo_mineralTarget->type_id;
    
    //pTo_target_pos_x = &(pTo_mineralTarget->points.center_x);
    //pTo_target_pos_y = &(pTo_mineralTarget->points.center_y);
    
    //pTo_target_is_alive = &(pTo_mineralTarget->is_alive);   
//}

//void RocketBullet :: setContainerAsTarget(Container* _pTo_container)
//{
    //pTo_containerTarget = _pTo_container; 
    //target_type_id = pTo_containerTarget->type_id;
    
    //pTo_target_pos_x = &(pTo_containerTarget->points.center_x);
    //pTo_target_pos_y = &(pTo_containerTarget->points.center_y);
    
    //pTo_target_is_alive = &(pTo_containerTarget->is_alive);  
//}

void RocketBullet :: update_inSpace_inDynamic()
{
    if (speed < speed_max)
    {
       speed += d_speed; 
       stepCalculation();
    } 

    if ((*pTo_target_is_alive) == false)
        target_is_alive = false;    // this step is needed after deleting target object in order to rocket keep moving

    if (target_is_alive == true)
    { 
        //dx, dy, angle_new = rocketWayCalc((self.points.center[0], self.points.center[1]), (self.target.points.center[0], self.target.points.center[1]), self.points.angle, self.angular_speed, self.step)
        get_dX_dY_angleInD_ToPoint(points.getCenter().x, points.getCenter().y, (*pTo_target_pos_x), (*pTo_target_pos_y), step, &dx, &dy, &angle_inD);
    }      
    points.setAngle(angle_inD);
    points.setCenter(points.getCenter().x + dx, points.getCenter().y + dy);
    

    live_time -= 1;
    if (live_time < 0)
       death();
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

void RocketBullet :: hit(int _damage)
{
    armor -= _damage;
    if (armor <= 0)
        death();
}

void RocketBullet :: death()
{
     is_alive = false; 

     if (is_explosed == false)
     {   
        pTo_starsystem->createExplosion(points.getCenter(), size);
        is_explosed = true;
     }
}


void RocketBullet :: renderDriveJet()
{
     //drive_jet.update();
     //drive_jet.render();
}


void RocketBullet :: renderInSpace()
{
    points.update();

    glBindTexture(GL_TEXTURE_2D, texture); 
    drawFlatQuadPerVertexIn2D(points.getBottomLeft(), 
                              points.getBottomRight(), 
                              points.getTopRight(), 
                              points.getTopLeft(), 
                              -500);
}




