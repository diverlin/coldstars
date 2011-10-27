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

#include "lazerTrace.hpp"


LazerTraceEffect :: LazerTraceEffect(TextureOb* _texOb, TextureOb* _texOb_particle, float _particle_size, float* _pTo_start_pos_x, float* _pTo_start_pos_y, float* _pTo_end_pos_x, float* _pTo_end_pos_y)
{
        is_alive = true;
        is_alreadyInRemoveQueue = false; 

	texOb = _texOb;
        texOb_particle = _texOb_particle;
        
    	if (texOb->is_animated == false)
       		pToFunc_render = &LazerTraceEffect::_renderFrame;
    	else
       		pToFunc_render = &LazerTraceEffect::_renderFrames;

        particle_size = _particle_size;

        existance_time = getRandInt(40, 45);

        if (getRandInt(1,2) == 1)
        	d_angle_inR = 0.0005 * 3;  //self.target.size
        else
        	d_angle_inR = -0.0005 * 3; // self.target.size


       	additional_angle_inR = 0;

       	pTo_start_pos_x = _pTo_start_pos_x;
       	pTo_start_pos_y = _pTo_start_pos_y;

       	pTo_end_pos_x = _pTo_end_pos_x;
       	pTo_end_pos_y = _pTo_end_pos_y;

       	damage_effect = NULL;
       
       	updateAngleAndLen();
}

LazerTraceEffect :: ~LazerTraceEffect()
{}


void LazerTraceEffect :: setDamageEffect(DamageEffect* _damage_effect) { damage_effect = _damage_effect; }
bool LazerTraceEffect :: getAlive() const { return is_alive; }
		
		

void LazerTraceEffect :: update()
{
	updateAngleAndLen();

    	if (existance_time < 0)
    	{
       		is_alive = false;
       		if (is_alreadyInRemoveQueue == false)
       		{ 
          		damage_effect->setDying();
          		is_alreadyInRemoveQueue = true;
       		}
    	} 
    
    	existance_time -= 1;
}

void LazerTraceEffect :: updateAngleAndLen()
{
    	// performs within game loop
    	float xl = (*pTo_end_pos_x) - (*pTo_start_pos_x);
    	float yl = (*pTo_end_pos_y) - (*pTo_start_pos_y);

    	len = sqrt((xl*xl) + (yl*yl));

    	angle_inR = atan2(yl, xl);
    	angle_inR += additional_angle_inR;

    	angle_inD = angle_inR * RADIAN_TO_DEGREE_RATE;

    	//additional_angle_inR += d_angle_inR;

    	//self.ex = sin(HALF_PI - self.angle_radian) * self.Len + self.owner.points.center[0]
    	//self.ey = sin(self.angle_radian) * self.Len + self.owner.points.center[1]

    	//# NEW !!!!
    	//if self.damage_effect == None:
	//###                                                    texture,             starsystem,      center,  num_particles, pSize,              velocity_max, alpha_init, alpha_end, d_alpha):
             //#self.damage_effect = tinyExplosionEffect(self.particle_texOb  self.starsystem, self.p2, 10,             15,                1.5,          1.0,        0.2,       0.05)
             //self.damage_effect = tinyExplosionEffect(self.particle_texOb,  self.starsystem, self.p2, 5,             self.pSize, 0.5,          0.7,        0.2,       0.1)              
             //self.starsystem.effect_DAMAGE_list.append(self.damage_effect)

    	//self.damage_effect.setNewCenter([self.ex, self.ey])
}


void LazerTraceEffect :: render()
{
	if (is_alive == true)
	{
     		(this->*pToFunc_render)();
	}
}



void LazerTraceEffect :: _renderFrame()
{
    	drawLine(texOb->texture, (*pTo_start_pos_x), (*pTo_start_pos_y), -2, len, angle_inD, texOb->h/4);
}

void LazerTraceEffect :: _renderFrames()
{
    	int i = texOb->updateAnimationFrame(); 
    	drawLine(texOb->texture, 
    	*pTo_start_pos_x, 
    	*pTo_start_pos_y, 
    	-2, 
    	len, 
    	angle_inD, 
    	texOb->h/3, 
    	texOb->texCoord_bottomLeft_x_list[i], 
    	texOb->texCoord_bottomLeft_y_list[i], 
    	texOb->texCoord_bottomRight_x_list[i], 
    	texOb->texCoord_bottomRight_y_list[i], 
    	texOb->texCoord_topLeft_x_list[i], 
    	texOb->texCoord_topLeft_y_list[i], 
    	texOb->texCoord_topRight_x_list[i], 
    	texOb->texCoord_topRight_y_list[i]);
}

