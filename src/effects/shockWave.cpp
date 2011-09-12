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


#include "shockWave.hpp"



ShockWaveEffect :: ShockWaveEffect(vec2f _center_pos, 
 				   float _x, float _y, float _z, float _time, 
 				   float _d_x, float _d_y, float _d_z, float _d_time)
{
	is_alive = true;
        is_alreadyInRemoveQueue = false;

        //starsystem = NULL;
        center.set(_center_pos.x/float(g_VIEW_WIDTH), _center_pos.y/float(g_VIEW_HEIGHT));

        parameter.set(_x, _y, _z);
        time = _time; 

        d_parameter.set(_d_x, _d_y, _d_z);
        d_time = _d_time; 
}

ShockWaveEffect :: ~ShockWaveEffect()
{}



      		
void ShockWaveEffect :: update()
{
	parameter.x -= d_parameter.x;

	if (parameter.y > 0)
		parameter.y -= d_parameter.y;
	else
            	is_alive = false;

     	parameter.z -= d_parameter.z;
      	time -= d_time;

    	if (is_alive == false)
      	{
          	if (is_alreadyInRemoveQueue == false)
            	{
                	//pTo_starsystem.effect_SHOCKWAVE_remove_queue.append();
                	is_alreadyInRemoveQueue = true;
             	}   
	}	         
}
             




void createShockWave(StarSystem* _starsystem, vec2f _center_pos, int obSize)
{
	if ( (obSize > 3) && (_starsystem->getShockWaveNum() < 10) )
	{
		int w = g_VIEW_WIDTH;
		int h = g_VIEW_HEIGHT;      
        
		float x = 10;
		float y = 1.8;
		float z = 0.13;
		float time = 0.0; 
		float dx = 0;
		float dy = 0.02;
		float dz = 0.0005;
		float dtime = -(0.002 + 0.3 * obSize * 0.001);     // 10, 1.8, 0.13, 0.0,  0,  0.02, 0.0005, -0.004 
        
		ShockWaveEffect* pTo_shockWave = new ShockWaveEffect(_center_pos, x, y, z, time, dx, dy, dz, dtime);  
       		_starsystem->addShockWaveEffect(pTo_shockWave);
	}
}
