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

#include "points.hpp"
#include "constants.hpp"

Points::Points():is_updated(false), angle_inD(0.0), pos_z(-500.0)
{
        center.Set(0, 0);     
        parent_center.Set(0, 0);       
}

Points::~Points()
{}              
                
void Points::Add(vec2f* point, vec2f* point_orig)
{ 
        vector_orig.push_back(point_orig);
        vector.push_back(point);
}
          
void Points::addMainQuadPoints()
{ 
	//float w = 1.0;
	//float h = 1.0;
	
        //////// Origin entity rect (for rotation only transformation)
        //bottomLeft_origin.Set(-w/2.0, -h/2.0);
        //bottomRight_origin.Set(+w/2.0, -h/2.0);
        //topRight_origin.Set(+w/2.0, +h/2.0);
        //topLeft_origin.Set(-w/2.0, +h/2.0);
      
        /////////////////////////////////////////////
        //////// Actual entity rect
        //bottomLeft.Set(-w/2.0, -h/2.0);
        //bottomRight.Set(+w/2.0, -h/2.0);
        //topRight.Set(+w/2.0, +h/2.0);
        //topLeft.Set(-w/2.0, +h/2.0);
        
      	///////////////////////////////////////////////////////////////
      	//////// Origin entity rect (for rotation only transformation)
      	//vector_orig.push_back(&bottomLeft_origin);
      	//vector_orig.push_back(&bottomRight_origin);
      	//vector_orig.push_back(&topRight_origin);
      	//vector_orig.push_back(&topLeft_origin);
      
      	/////////////////////////////////////////////
      	//////// Actual entity rect
      	//vector.push_back(&bottomLeft);     
      	//vector.push_back(&bottomRight);      
      	//vector.push_back(&topRight);                 
      	//vector.push_back(&topLeft);
}

void Points :: addMidLeftPoint()
{
     	midLeft_origin.Set(-0.5, 0.0);
     	midLeft.Set(-0.5, 0.0);
     	
     	vector_orig.push_back(&midLeft_origin);
     	vector.push_back(&midLeft);
}

void Points::addMidFarLeftPoint()
{
     	midFarLeft_origin.Set(-1.0, 0.0);
     	midFarLeft.Set(-1.0, 0.0);
     	
     	vector_orig.push_back(&midFarLeft_origin);
     	vector.push_back(&midFarLeft);
}


void Points::Update()
{
    	if (is_updated == false)
    	{   
        	vec2f pos = center;

       		float angle_radian = angle_inD/RADIAN_TO_DEGREE_RATE;
         
        	float cosa = cos(angle_radian);
        	float sina = sin(angle_radian);
 
        	for (unsigned int i=0; i<vector.size(); i++)
        	{   
           		////// rotation around center
            		vector[i]->x = cosa*scale.x*vector_orig[i]->x - sina*scale.y*vector_orig[i]->y;
            		vector[i]->y = sina*scale.x*vector_orig[i]->x + cosa*scale.y*vector_orig[i]->y;  
            		////// moving to position
            		vector[i]->x += pos.x;
            		vector[i]->y += pos.y;
        	}   
        	is_updated = true;
    	}
}        
         




       




