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




ShockWaveEffect::ShockWaveEffect(float x, float y, float z, float time, 
 				     float d_x, float d_y, float d_z, float d_time)
{
	is_alive = true;
        is_alreadyInRemoveQueue = false;
	
        parameter.Set(x, y, z);
        this->time = time; 

        d_parameter.Set(d_x, d_y, d_z);
        this->d_time = d_time; 
}

ShockWaveEffect::~ShockWaveEffect()
{}
      		
void ShockWaveEffect::Update()
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
             
        
ShockWaveEffect* GetNewShockWave(int obSize, bool dynamic)
{       
	float x = 10;
	float y = 1.8;
	float z = 0.13;
	float time = 0.0; 
	float dx = 0;
	float dy = 0.02;
	float dz = 0.0005;
	float dtime = -(0.001 + obSize * 0.0003);     // 10, 1.8, 0.13, 0.0,  0,  0.02, 0.0005, -0.004 
	//float dtime = -(0.0001*obSize + obSize * 0.0003);     // 10, 1.8, 0.13, 0.0,  0,  0.02, 0.0005, -0.004 
		
        if (dynamic == false)
	{
		x = 100;
		y = 1.8;
		z = 0.02;
		time = 0.1; 
		dx = 0.0;
		dy = 0.0;
		dz = 0.0;
		dtime = 0.0;     
	}
	
	        
	ShockWaveEffect* shockwave = new ShockWaveEffect(x, y, z, time, dx, dy, dz, dtime);  
	return shockwave;
}
