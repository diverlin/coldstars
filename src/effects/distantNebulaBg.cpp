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



DistantNebulaBgEffect :: DistantNebulaBgEffect(TextureOb* _texOb, vec3f _center)
{
    	texOb = _texOb;
        center = _center; 

    	if(texOb->getFrameWidth() * texOb->getFrameHeight() > 300000)
     		distance_rate =  1/60.0; 
    	else
      		distance_rate =  1/40.0;

        angle_inD = getRandInt(0, 360);
        if(texOb->is_rotated)
    		d_angle_inD = getRandInt(8,12)*0.001 * getRandSign();
    	else
    	     	d_angle_inD = 0;
}
   
   
void DistantNebulaBgEffect :: updateRenderStuff()
{
     	angle_inD += d_angle_inD;  
}        


void DistantNebulaBgEffect :: Render(float vx, float vy)
{ 
   	drawDynamic(texOb, vec2f(center.x - vx*distance_rate, center.y - vy*distance_rate), angle_inD, center.z);
}
              

DistantNebulaBgEffect* createDistantNebula(int color_id)
{
	TextureOb* texOb = NULL;
	if (color_id == -1) texOb = g_TEXTURE_MANAGER.GetRandomTextureOb(TEXTURE::NEBULA_BACKGROUND_ID);
	else    	    texOb = g_TEXTURE_MANAGER.getTexObByColorId(TEXTURE::NEBULA_BACKGROUND_ID, color_id);	
	   	
   	vec3f center((float)getRandInt(0, 1000), (float)getRandInt(0, 1000), -999.0);
        
        DistantNebulaBgEffect* dn = new DistantNebulaBgEffect(texOb, center);
        return dn;

}
