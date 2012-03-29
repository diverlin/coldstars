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



ShieldEffect :: ShieldEffect(Vehicle* owner_vehicle, TextureOb* _texOb)
{
     this->owner_vehicle = owner_vehicle;
     texOb = _texOb;

     alpha_start = 0.4;
     d_alpha = 0.01;

     color.r = 1.0;
     color.g = 1.0;
     color.b = 1.0;
     color.a = alpha_start;
}

ShieldEffect :: ~ShieldEffect()
{}


void ShieldEffect :: setAlpha(float _alpha)	{ color.a = _alpha; }

void ShieldEffect :: update()
{
    	if (color.a > alpha_start)
       		color.a -= d_alpha;
    	else
       		color.a = alpha_start;
}

void ShieldEffect :: Render() const
{
    	setColor(color);

    	drawFlatQuadPerVertexIn2D(texOb,
    				  owner_vehicle->GetPoints().getBottomLeftShield(), 
     			     	  owner_vehicle->GetPoints().getBottomRightShield(), 
     			      	  owner_vehicle->GetPoints().getTopRightShield(), 
     			      	  owner_vehicle->GetPoints().getTopLeftShield(), 
     			      	  owner_vehicle->GetPoints().getPosZ());
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
