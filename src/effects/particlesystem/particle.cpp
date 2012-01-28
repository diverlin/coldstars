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



Particle :: Particle(vec2f _pos_start, ParticleData _data_particle, bool _randomize_life_time)
{
	is_alive = true;
  
	data_particle = _data_particle;

     	pos   = _pos_start;      	
      	alpha = _data_particle.alpha_start;
      	size  = _data_particle.size_start;

	if (_randomize_life_time == true)
	{
        	float speed_rate = getRandInt(5,8) * 0.1; //???? 
    		data_particle.d_size         *= speed_rate;
    		data_particle.velocity_start *= speed_rate;
    	}
    		
        calcRandomVelocity();	
} 
      
Particle :: ~Particle()
{}

      			 
void Particle :: setVelocity(vec2f _velocity) { d_pos = _velocity; }

bool Particle :: getAlive() const  { return is_alive; }   
float Particle :: getAlpha() const { return alpha; }
float Particle :: getAlphaStart() const { return data_particle.alpha_start; }
      		

void Particle :: calcRandomVelocity()
{
     	if (getRandBool() == true)
     	{
        	calcFastRandomVelocity();
        }
     	else
     	{
        	calcAccurateRandomVelocity();
        }
}


void Particle :: randomize_d_alpha(float val1_f, float val2_f)
{
	float val1_i = val1_f*10000;
	float val2_i = val2_f*10000;
		
	data_particle.d_alpha = getRandInt(val1_i, val2_i)/1000.0;
}            	
      		
void Particle :: calcFastRandomVelocity()
{
    	float dx_n = getRandInt(0, 10)*getRandSign()*0.1;
    	float dy_n = getRandInt(0, 10)*getRandSign()*0.1;

    	d_pos.x = dx_n * data_particle.velocity_start;
    	d_pos.y = dy_n * data_particle.velocity_start;
}


void Particle :: calcAccurateRandomVelocity()
{
    	float _len   = getRandInt(50, 100);
    	float _angle = getRandInt(0, 360)/57.0;

    	float target_x = pos.x + sin(_angle) * _len;
    	float target_y = pos.y + cos(_angle) * _len;

    	float xl = (target_x - pos.x);
    	float yl = (target_y - pos.y);

    	float dx_n = xl/_len;
    	float dy_n = yl/_len;

    	d_pos.x = dx_n * data_particle.velocity_start;
    	d_pos.y = dy_n * data_particle.velocity_start;
}  


void Particle :: reborn(vec2f _new_pos_start)
{       	 
	is_alive = true;
       	pos = _new_pos_start;  
       			
	alpha = data_particle.alpha_start;
	size  = data_particle.size_start;

       	calcRandomVelocity();
}


void Particle :: reborn(vec2f _new_pos_start, vec2f _d_pos)
{       	 
	is_alive = true;
       	pos = _new_pos_start;  
       			
	alpha = data_particle.alpha_start;
	size  = data_particle.size_start;

       	d_pos = _d_pos;
}
      		

void Particle :: update()
{
    	pos.x += d_pos.x;
    	pos.y += d_pos.y; 
    	
    	alpha -= data_particle.d_alpha;
    	size  -= data_particle.d_size;
          
    	if ((alpha < data_particle.alpha_end) or (size < data_particle.size_end))
    	{
       	       	is_alive = false;
    	}
}

void Particle :: render() const
{
	if (is_alive == true)
	{
     		glPointSize(size);
        	
        	glBegin(GL_POINTS);           		
     			glColor4f(1.0, 1.0, 1.0, alpha);
     			glVertex3f(pos.x, pos.y, -2);
       		glEnd();
     	}
}
