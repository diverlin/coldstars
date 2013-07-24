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

#include "Particle.hpp"
#include "../../common/rand.hpp"
#include "../../render/Render.hpp"

Particle::Particle(const ParticleData& data_particle)
{
	is_alive = true;
	
	this->data_particle = data_particle;
	
	color = data_particle.color_start;
			
	size  = data_particle.size_start;
} 
      
Particle::~Particle()
{}

void Particle::RandomizeLifeTime(float low, float high)
{
	float speed_rate              = getRandFloat(low, high);   // 0.5, 0.8
	data_particle.d_size         *= speed_rate;
	data_particle.velocity_start *= speed_rate;
}

void Particle::Randomize_d_alpha(float val1_f, float val2_f)
{
	float val1_i = val1_f*10000;
	float val2_i = val2_f*10000;
		
	data_particle.color_delta.a = getRandInt(val1_i, val2_i)/1000.0;
}            	
      		
                
void Particle::CalcRandomVelocity()
{
	if (getRandBool() == true)
	{
		CalcRandomDirtyVelocity();
	}
	else
	{
		CalcRandomAccurateVelocity();
	}
}

void Particle::CalcRandomDirtyVelocity()
{
	float dx_n = getRandFloat(0.1, 1.0)*getRandSign();
	float dy_n = getRandFloat(0.1, 1.0)*getRandSign();
	
	d_pos.x = dx_n * data_particle.velocity_start;
	d_pos.y = dy_n * data_particle.velocity_start;
}


void Particle::CalcRandomAccurateVelocity()
{
	float _len   = getRandInt(50, 100);
	float _angle = getRandInt(0, 360)/RADIAN_TO_DEGREE_RATE;
	
	float target_x = cos(_angle) * _len;
	float target_y = sin(_angle) * _len;
	
	float dx_n = target_x/_len;
	float dy_n = target_y/_len;
	
	d_pos.x = dx_n * data_particle.velocity_start;
	d_pos.y = dy_n * data_particle.velocity_start;
}  


//void Particle::calcAccurateRandomVelocity2(Vec2<float> center)
//{
    	//float _len   = getRandInt(50, 100);
    	//float _angle = getRandInt(0, 360)/RADIAN_TO_DEGREE_RATE;

	//Vec2<float> target;
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

void Particle::Reborn()
{       	
	pos.Set(0.0, 0.0); 
	is_alive = true;
       			
	color = data_particle.color_start;
	size  = data_particle.size_start;
}
      		

void Particle::Update()
{
	pos += d_pos;
	
	color.a -= data_particle.color_delta.a;
	size  -= data_particle.d_size;
	  
	if ((color.a < data_particle.color_end.a) or (size < data_particle.size_end))
	{
			is_alive = false;
	}
}

void Particle::Render() const
{
	if (is_alive == true)
	{
		drawParticle(pos, size, color);
	}
}

void Particle::Render(float scale) const
{
	if (is_alive == true)
	{
		drawParticle(pos, size*scale, color.r, color.g, color.b, color.a);
	}
}

void Particle::Render(float scale, float parent_d_alpha) const
{
	if (is_alive == true)
	{
		drawParticle(pos, size*scale, color.r, color.g, color.b, color.a - parent_d_alpha);
	}
}
