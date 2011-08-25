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


#include "commonForSpaceItems.h"

CommonForSpaceItems :: CommonForSpaceItems()
{}

void CommonForSpaceItems :: CommonForSpaceItems_init(StarSystem* _pTo_starsystem, TextureOb* _pTo_texOb, float _pos_x, float _pos_y, float _target_pos_x, float _target_pos_y)
{
    is_alive = true;
    is_dying = false; 
    is_explosed = false;
    
    dying_time = 30;

    pTo_texOb = _pTo_texOb;
    pTo_starsystem = _pTo_starsystem;
    
    in_SPACE             = true;
    is_COLLECTED         = false;
    draw_grabbing_ICON   = false;
    
    dx = 0;
    dy = 0;
    //self.owner = None

    //if self.animated == True:
    //   self.renderInSpace = self._renderDynamicFramesLoopRot
    //   self.renderInSlot = self._renderStaticFramesLoopOnRect
    //else:
    //self.renderInSpace = self._renderDynamicFrameRot
    //   self.renderInSlot = self._renderStaticFrameOnRect

    texture = (*pTo_texOb).texture;
    w = (*pTo_texOb).w;
    h = (*pTo_texOb).h;
    updateWHRenderConstants();
     
    size = returnObjectSize(w, h);
    collision_threshold = (w + h)/2;

    //self.hunters_list = []
    //self.info         = []

    //////
    points = Points();

    points.initCenterPoint();
    points.addCenterPoint();

    points.setCenter(_pos_x, _pos_y);
    //////


    //########  init values  #######
    angle_x_inD        = 0.0;
    angle_y_inD        = 0.0;
    angle_z_inD        = 0.0;
    d_angle_z_inD      = randIntInRange(10, 100)*0.01;
    pos_z          = -500.0f;

    target_pos_x = _target_pos_x;
    target_pos_y = _target_pos_y;

    keep_moving = true;
}

void CommonForSpaceItems :: update_inSpace_inDynamic_TRUE()
{
     if (keep_moving == true)
     {
        keep_moving = get_dX_dY_ToPoint(points.center_x, points.center_y, target_pos_x, target_pos_y, step, &dx, &dy);
        points.setCenter(points.center_x + dx, points.center_y + dy);
     }
      
     if (is_dying == true)
     {
        dying_time--;
        if (dying_time < 0)
           death_TRUE();
     }    
}

void CommonForSpaceItems :: update_inSpace_inDynamic_FALSE()
{
     if (keep_moving == true)
     {
        points.setCenter(target_pos_x, target_pos_y);
        keep_moving = false;
     }
}


void CommonForSpaceItems :: hit_TRUE(int damage)
{
    armor -= damage;
    if (armor <= 0)
       is_dying = true;
}

void CommonForSpaceItems :: hit_FALSE(int damage)
{
    armor -= damage;
    if (armor <= 0)
       death_FALSE();
}


void CommonForSpaceItems :: death_TRUE()
{
     is_alive = false;   

     if (is_explosed == false)
     {   
        pTo_starsystem->addExplosion(points.center_x, points.center_y, size);
        is_explosed = true;
     }
}
   
void CommonForSpaceItems :: death_FALSE()
{
     is_alive = false;   
}


void CommonForSpaceItems :: stepCalculation()
{
    step = (float)speed / 100;
}

void CommonForSpaceItems :: updateWHRenderConstants()
{
    minus_half_w = -w/2;
    minus_half_h = -h/2;
    plus_half_w  =  w/2;
    plus_half_h  =  h/2;
}     


      //def _renderDynamicFramesLoopRot(self):
          //drawDynamic(self.texture_ID[self._tex_frame], (self.points.center[0], self.points.center[1]), self.angle, (self.minus_half_w, self.minus_half_h, self.plus_half_w, self.plus_half_h ))
          //self.updateAnimationFrameLoop()

          //self.angle += self.deltaAngle

      //def _renderStaticFramesLoopOnRect(self, rect):
          //drawTexturedRect(self.texture_ID[self._tex_frame], rect, -1.0)
          //self.updateAnimationFrameLoop()
		        
      //def _renderDynamicFrameRot(self):
          //drawDynamic(self.texture_ID, (self.points.center[0], self.points.center[1]), self.angle, (self.minus_half_w, self.minus_half_h,  self.plus_half_w, self.plus_half_h))
          //self.angle += self.deltaAngle

      //def _renderStaticFrameOnRect(self, rect):
          //drawTexturedRect(self.texture_ID, rect, -1.0)
          
void CommonForSpaceItems :: render2D()
{ 
    glBindTexture(GL_TEXTURE_2D, texture);
    //drawDynamic(100, 100, angle_z, -50, -50, 50, 50, pos_z);
    drawDynamic(points.center_x, points.center_y, angle_z_inD, minus_half_w, minus_half_h, plus_half_w, plus_half_h, pos_z);
    //printf("ddfs = %i,%i,%i,%i \n ", minus_half_w, minus_half_h, plus_half_w, plus_half_h);
    angle_z_inD += d_angle_z_inD;
}


