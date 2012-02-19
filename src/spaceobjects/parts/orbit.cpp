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


Orbit :: Orbit()
{}

Orbit :: ~Orbit()
{}

vec2f Orbit :: getPosition() const { return orbit_vec[orbit_it]; }
   
vec2f Orbit :: getNextTurnPosition() const 
{ 
        if (orbit_it + TURN_TIME < orbit_len)
        {
                return orbit_vec[orbit_it+TURN_TIME]; 
        }
        else
        {
                int d_orbit = orbit_len-orbit_it;
                return orbit_vec[TURN_TIME - d_orbit]; 
        }
}


void Orbit :: calcPath(float radius_A, float radius_B, float speed, float orbit_phi_inD)
{   
	orbit_vec.clear();
	
     	float d_angleInRad  = speed / RADIAN_TO_DEGREE_RATE;
     	float orbitPhiInRad = orbit_phi_inD / RADIAN_TO_DEGREE_RATE;
     	
     	vec2f new_coord;
     	for(float angleInRad = 0; angleInRad < 2*PI; angleInRad += d_angleInRad) 
     	{ 
         	new_coord.x = radius_A * cos(angleInRad) * cos(orbitPhiInRad) - radius_B * sin(angleInRad) * sin(orbitPhiInRad);
         	new_coord.y = radius_A * cos(angleInRad) * sin(orbitPhiInRad) + radius_B * sin(angleInRad) * cos(orbitPhiInRad);
         	orbit_vec.push_back(new_coord);
     	}
        orbit_len = orbit_vec.size();
        orbit_it = getRandInt(1, orbit_len);
}    

void Orbit :: calcPath(float radius, float speed)
{   	
	orbit_vec.clear();
	
     	float d_angleInRad  = speed / RADIAN_TO_DEGREE_RATE;
     	
     	vec2f new_coord;
     	for(float angleInRad = 0; angleInRad < 2*PI; angleInRad += d_angleInRad) 
     	{ 
         	new_coord.x = radius * cos(angleInRad)  - radius * sin(angleInRad);
         	new_coord.y = radius * cos(angleInRad)  + radius * sin(angleInRad);
         	orbit_vec.push_back(new_coord);
     	}
        orbit_len = orbit_vec.size();
        orbit_it = getRandInt(1, orbit_len);
}    



void Orbit :: updatePosition()
{   
     	if (orbit_it < orbit_len)
     	{ 
        	orbit_it++;
     	}
     	else
     	{
        	orbit_it = 0; // hack
        }
}    

void Orbit :: updateVisual()
{
	orbit_visual.fillData(g_UNIQUE_TEXTURE_COLLECTOR.texOb_dot_blue->texture, &orbit_vec, 50, 10);
}

void Orbit :: draw()
{   
	this->updateVisual();   // SLOWWWW
        orbit_visual.draw();
}


