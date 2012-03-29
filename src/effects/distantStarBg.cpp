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



DistantStarBgEffect :: DistantStarBgEffect(TextureOb* _texOb, vec2f _center, float _particleSize)
{
    	texOb = _texOb; 
    
    	center = _center; 
    
    	particleSize = _particleSize;
    	distance_rate = _particleSize / 1000;
}


void DistantStarBgEffect :: Render(float vx, float vy)
{   
    	glPointSize(particleSize);
    	//glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    	glBindTexture(GL_TEXTURE_2D, texOb->texture);
    	
    	glBegin(GL_POINTS);
    		glVertex3f(center.x - vx*distance_rate, center.y - vy*distance_rate , -2.0);
    	glEnd();
}

   
   
DistantStarBgEffect* getNewDistantStarBgEffect(int color_id)
{
	TextureOb* texOb = NULL;
	if (color_id == -1) texOb = g_TEXTURE_MANAGER.getRandomTexOb(TEXTURE::DISTANTSTAR_ID);
	else    	    texOb = g_TEXTURE_MANAGER.getTexObByColorId(TEXTURE::DISTANTSTAR_ID, color_id);
        
        vec2f _center(getRandInt(0, 1000), getRandInt(0, 1000));
        float size = (float)getRandInt(ENTITY::GALAXY::DISTANTSTAR_SIZE_MIN, ENTITY::GALAXY::DISTANTSTAR_SIZE_MAX);
        
        DistantStarBgEffect* ds = new DistantStarBgEffect(texOb, _center, size);
        return ds;
}
