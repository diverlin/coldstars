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
#include "orbit.hpp"
#include "../common/constants.hpp"


Orbit::Orbit():it(0)
{}

Orbit::~Orbit()
{}
 
const Vec2<float>& Orbit::GetNextTurnPosition() const 
{ 
        if (it + TURN_TIME < len)
        {
                return coords_vec[it+TURN_TIME]; 
        }
        else
        {
                int d_orbit = len-it;
                return coords_vec[TURN_TIME - d_orbit]; 
        }
}


void Orbit::CalcPath(float radius_A, float radius_B, float speed, float orbit_phi_inD, bool clockwise)
{   
	coords_vec.clear();
	
     	float d_angleInRad = speed / RADIAN_TO_DEGREE_RATE;;
     	if (clockwise == true) 
     	{
     		d_angleInRad *= -1;
     	}     	
		 
     	float orbitPhiInRad = orbit_phi_inD / RADIAN_TO_DEGREE_RATE;
     	
     	Vec2<float> new_coord;
     	
     	for(float angleInRad=0; fabs(angleInRad)<2*PI; angleInRad+=d_angleInRad) 
     	{ 
         	new_coord.x = radius_A * cos(angleInRad) * cos(orbitPhiInRad) - radius_B * sin(angleInRad) * sin(orbitPhiInRad);
         	new_coord.y = radius_A * cos(angleInRad) * sin(orbitPhiInRad) + radius_B * sin(angleInRad) * cos(orbitPhiInRad);
         	coords_vec.push_back(new_coord);
     	}
        len = coords_vec.size();
}    

void Orbit::CalcPath(float radius, float speed, bool clockwise)
{   	
	coords_vec.clear();
	
     	float d_angleInRad  = speed / RADIAN_TO_DEGREE_RATE;
     	if (clockwise == true) 
     	{
     		d_angleInRad *= -1;
     	}    
     	
     	Vec2<float> new_coord;
     	for(float angleInRad=0; fabs(angleInRad)<2*PI; angleInRad+=d_angleInRad) 
     	{ 
         	new_coord.x = radius * cos(angleInRad)  - radius * sin(angleInRad);
         	new_coord.y = radius * cos(angleInRad)  + radius * sin(angleInRad);
         	coords_vec.push_back(new_coord);
     	}
        len = coords_vec.size();
}    

void Orbit::UpdatePosition()
{   
     	if (it < len-1) { it++; }
     	else 		{ it = 0; }
}    

void Orbit::UpdatePathVisualisation()
{
	visual_orbit_path.FillData(coords_vec, 30, 10);
        visual_orbit_turn.FillData(coords_vec, TURN_TIME, 13);
}

void Orbit::DrawPath()
{   
	this->UpdatePathVisualisation();   // TOO SLOW
        visual_orbit_path.Draw();
        visual_orbit_turn.Draw();
}


