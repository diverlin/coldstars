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

#include <cmath>

#include "BaseParticleSystem.hpp"
#include "../../common/rand.hpp"
#include "../../common/constants.hpp"

BaseParticleSystem::BaseParticleSystem()
{
    	is_alive = true;
    	is_dying = false;
        
        parent = NULL; 
}
 
/* virtual */
BaseParticleSystem::~BaseParticleSystem()
{
	for (unsigned int i=0; i<particles_vec.size(); i++) 
     	{
  		delete particles_vec[i];
     	}
}
                
vec2f BaseParticleSystem::GetRandomVelocity()
{
     	if (getRandBool() == true)
     	{
        	return GetRandomDirtyVelocity();
        }
     	else
     	{
        	return GetRandomAccurateVelocity();
        }
}

vec2f BaseParticleSystem::GetRandomDirtyVelocity()
{
    	float dx_n = getRandFloat(0.1, 1.0)*getRandSign();
    	float dy_n = getRandFloat(0.1, 1.0)*getRandSign();

        vec2f d_pos;
    	d_pos.x = dx_n * data_particle.velocity_start;
    	d_pos.y = dy_n * data_particle.velocity_start;
        
        return d_pos;
}


vec2f BaseParticleSystem::GetRandomAccurateVelocity()
{
    	float _len   = getRandInt(50, 100);
    	float _angle = getRandInt(0, 360)/RADIAN_TO_DEGREE_RATE;

    	float target_x = sin(_angle) * _len;
    	float target_y = cos(_angle) * _len;

    	float dx_n = target_x/_len;
    	float dy_n = target_y/_len;

        vec2f d_pos;
    	d_pos.x = dx_n * data_particle.velocity_start;
    	d_pos.y = dy_n * data_particle.velocity_start;
        
        return d_pos;
}  


//void BaseParticleSystem::calcAccurateRandomVelocity2(vec2f center)
//{
    	//float _len   = getRandInt(50, 100);
    	//float _angle = getRandInt(0, 360)/RADIAN_TO_DEGREE_RATE;

	//vec2f target;
	//target = center;
	
    	//pos.x = center.x + sin(_angle) * _len;
    	//pos.y = center.y + cos(_angle) * _len;

    	//float xl = (target.x - pos.x);
    	//float yl = (target.y - pos.y);

    	//float dx_n = xl/_len;
    	//float dy_n = yl/_len;

    	//d_pos.x = dx_n * data_particle.velocity_start;
    	//d_pos.y = dy_n * data_particle.velocity_start;
//}  

