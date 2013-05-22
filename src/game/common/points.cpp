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

Points::Points()
{}

Points::~Points()
{}              
                
void Points::Add(Vec3<float>* point, Vec3<float>* point_orig)
{ 
        vector_orig.push_back(point_orig);
        vector.push_back(point);
}
          
void Points::addMidLeftPoint()
{
     	midLeft_origin.Set(-0.5, 0.0, DEFAULT_ENTITY_ZPOS);
     	midLeft.Set(-0.5, 0.0, DEFAULT_ENTITY_ZPOS);
     	
     	vector_orig.push_back(&midLeft_origin);
     	vector.push_back(&midLeft);
}

void Points::addMidFarLeftPoint()
{
     	midFarLeft_origin.Set(-1.0, 0.0, DEFAULT_ENTITY_ZPOS);
     	midFarLeft.Set(-1.0, 0.0, DEFAULT_ENTITY_ZPOS);
     	
     	vector_orig.push_back(&midFarLeft_origin);
     	vector.push_back(&midFarLeft);
}


void Points::Update(const Vec3<float>& center, const Vec3<float>& angle, const Vec3<float>& scale, const Vec3<float>& uOrient)
{
       	Vec3<float> pos = center;

       	for (unsigned int i=0; i<vector.size(); i++)
       	{   
       		////// rotation around center
       		vector[i]->x = uOrient.x*scale.x*vector_orig[i]->x - uOrient.y*scale.y*vector_orig[i]->y;
		vector[i]->y = uOrient.y*scale.x*vector_orig[i]->x + uOrient.x*scale.y*vector_orig[i]->y;  
		////// moving to position
		vector[i]->x += pos.x;
		vector[i]->y += pos.y;
		
		vector[i]->z = vector_orig[i]->z;
    	}
}        
         




       




