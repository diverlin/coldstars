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


#include "shield.h"


ShieldEffect :: ShieldEffect(Ship* _pTo_ship, TextureOb* _pTo_texOb)
{
     pTo_ship = _pTo_ship;

     pTo_texOb = _pTo_texOb;
     texture = pTo_texOb->texture;

     angle_inD   = randIntInRange(0, 360);
     d_angle_inD = randIntInRange(0, 30) * 0.003;

     alpha_start = 0.4;
     d_alpha = 0.01;

     alpha = alpha_start;

     pos_z= -2.0;
}

ShieldEffect :: ~ShieldEffect()
{}


void ShieldEffect :: render()
{
    if (alpha > alpha_start)
       alpha -= d_alpha;
    else
       alpha = alpha_start;

    glColor4f(1.0, 1.0, 1.0, alpha);

    glBindTexture(GL_TEXTURE_2D, texture);
    drawFlatQuadPerVertexIn2D(pTo_ship->getPoints()->getBottomLeftShield(), 
     			      pTo_ship->getPoints()->getBottomRightShield(), 
     			      pTo_ship->getPoints()->getTopRightShield(), 
     			      pTo_ship->getPoints()->getTopLeftShield(), 
     			      pos_z);
}






    //def _renderDynamicFramesLoopRot(self):
    //    if self.alpha > self.alpha_init:
    //       self.alpha -= self.d_alpha
    //    else:
    //       self.alpha = self.alpha_init

    //    glColor4f(1.0, 1.0, 1.0, self.alpha)


    //    self.updateAnimationFrameLoop()
    //    glBindTexture(GL_TEXTURE_2D, self.texture_ID[self._tex_frame]) 
    //    drawQuadPer2DVertex(self.ob.points.bottomFarLeft, self.ob.points.bottomFarRight, self.ob.points.topFarRight, self.ob.points.topFarLeft, -2)
