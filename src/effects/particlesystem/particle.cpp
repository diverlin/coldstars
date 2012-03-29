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


Particle :: Particle(ParticleData _data_particle)
{
	is_alive = true;
  
	data_particle = _data_particle;

        color = _data_particle.color_start;
                
      	size  = _data_particle.size_start;
} 
      
Particle :: ~Particle()
{}

void Particle :: setPosition(vec2f pos) { this->pos = pos; } 
void Particle :: setVelocity(vec2f _velocity) { d_pos = _velocity; }

bool Particle :: GetAlive()       const { return is_alive; }   
float Particle :: getAlpha()      const { return color.a; }
float Particle :: getAlphaStart() const { return data_particle.color_start.a; }



void Particle :: randomizeLifeTime(float low, float high)
{
        float speed_rate              = getRandFloat(low, high);   // 0.5, 0.8
        data_particle.d_size         *= speed_rate;
        data_particle.velocity_start *= speed_rate;
}

void Particle :: randomize_d_alpha(float val1_f, float val2_f)
{
	float val1_i = val1_f*10000;
	float val2_i = val2_f*10000;
		
	data_particle.color_delta.a = getRandInt(val1_i, val2_i)/1000.0;
}            	
      		

//void Particle :: reborn(vec2f center)
//{       	 
	//is_alive = true;
       			
	//alpha = data_particle.alpha_start;
	//size  = data_particle.size_start;

       	////calcRandomVelocity(center);
//}


void Particle :: reborn()
{       	 
	is_alive = true;
       	//pos = _new_pos_start;  
       			
	color = data_particle.color_start;
	size  = data_particle.size_start;

       	//d_pos = _d_pos;
}
      		

void Particle :: update()
{
    	pos.x += d_pos.x;
    	pos.y += d_pos.y; 
    	
    	color.a -= data_particle.color_delta.a;
    	size  -= data_particle.d_size;
          
    	if ((color.a < data_particle.color_end.a) or (size < data_particle.size_end))
    	{
       	       	is_alive = false;
    	}
}

void Particle :: Render() const
{
	if (is_alive == true)
	{
     		glPointSize(size);
        	
        	glBegin(GL_POINTS);           		
     			glColor4f(color.r, color.g, color.b, color.a);
     			glVertex3f(pos.x, pos.y, -2);
       		glEnd();
     	}
}
