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


#include "distantStarBg.hpp"

DistantStarBgEffect :: DistantStarBgEffect(TextureOb* _texOb, vec2f _center, float _particleSize)
{
    	texOb = _texOb; 
    
    	center = _center; 
    
    	particleSize = _particleSize;
    	distance_rate = _particleSize / 1000;
}


void DistantStarBgEffect :: render(float vx, float vy)
{   
    	glPointSize(particleSize);
    	//glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    	glBindTexture(GL_TEXTURE_2D, texOb->texture);
    	
    	glBegin(GL_POINTS);
    		glVertex3f(center.x - vx*distance_rate, center.y - vy*distance_rate , -2.0);
    	glEnd();
}

   
   
DistantStarBgEffect* createDistantStar()
{
	TextureOb* texOb_distantStar = g_TEXTURE_MANAGER.returnParticleTexObByColorId(YELLOW_COLOR_ID);
        vec2f _center(randIntInRange(0, 1000), randIntInRange(0, 1000));
        float size = (float)randIntInRange(DISTANTSTAR_SIZE_MIN, DISTANTSTAR_SIZE_MAX);
        
        DistantStarBgEffect* ds = new DistantStarBgEffect(texOb_distantStar, _center, size);
        return ds;
}
