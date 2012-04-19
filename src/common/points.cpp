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

Points :: Points()
{
        is_updated = false;  
        angle_inD = 0;
        pos_z = -500.0; 
        
        CreateCenter();          
}

Points :: ~Points()
{}              
                

void Points :: initCenterPoint()
{ 
        center_origin.set(0, 0);
        center.set(0, 0);
}  

void Points :: addCenterPoint()
{ 
        vector_orig.push_back(&center_origin);
        vector.push_back(&center);
}
     




void Points :: initWeapon1CenterPoint(float _pos_x, float _pos_y)
{ 
        weapon_1_origin_center.set(_pos_x, _pos_y);
        weapon_1_center.set(_pos_x, _pos_y);
}

void Points :: addWeapon1CenterPoint()
{ 
        vector_orig.push_back(&weapon_1_origin_center);
        vector.push_back(&weapon_1_center);
}




void Points :: initWeapon2CenterPoint(float _pos_x, float _pos_y)
{
        weapon_2_origin_center.set(_pos_x, _pos_y);
        weapon_2_center.set(_pos_x, _pos_y);
}

void Points :: addWeapon2CenterPoint()
{
        vector_orig.push_back(&weapon_2_origin_center);
        vector.push_back(&weapon_2_center);
}






void Points :: initWeapon3CenterPoint(float _pos_x, float _pos_y)
{
     	weapon_3_origin_center.set(_pos_x, _pos_y);
     	weapon_3_center.set(_pos_x, _pos_y);
}
  
void Points :: addWeapon3CenterPoint()
{
     	vector_orig.push_back(&weapon_3_origin_center);
     	vector.push_back(&weapon_3_center);
}




void Points :: initWeapon4CenterPoint(float _pos_x, float _pos_y)
{
     	weapon_4_origin_center.set(_pos_x, _pos_y);
     	weapon_4_center.set(_pos_x, _pos_y);
}

void Points :: addWeapon4CenterPoint()
{
     	vector_orig.push_back(&weapon_4_origin_center);
     	vector.push_back(&weapon_4_center);
}




    
void Points :: initWeapon5CenterPoint(float _pos_x, float _pos_y)
{
     	weapon_5_origin_center.set(_pos_x, _pos_y);
     	weapon_5_center.set(_pos_x, _pos_y);
}
   
void Points :: addWeapon5CenterPoint()
{
     	vector_orig.push_back(&weapon_5_origin_center);
     	vector.push_back(&weapon_5_center);
}
   



void Points :: initMainQuadPoints(int _w, int _h)
{ 
        setWidthHeight(_w, _h);  

        ////// Origin entity rect (for rotation only transformation)
        bottomLeft_origin.set(-w/2, -h/2);
        bottomRight_origin.set(+w/2, -h/2);
        topRight_origin.set(+w/2, +h/2);
        topLeft_origin.set(-w/2, +h/2);
      
        ///////////////////////////////////////////
        ////// Actual entity rect
        bottomLeft.set(-w/2, -h/2);
        bottomRight.set(+w/2, -h/2);
        topRight.set(+w/2, +h/2);
        topLeft.set(-w/2, +h/2);
}

          
void Points :: addMainQuadPoints()
{ 
      	/////////////////////////////////////////////////////////////
      	////// Origin entity rect (for rotation only transformation)
      	vector_orig.push_back(&bottomLeft_origin);
      	vector_orig.push_back(&bottomRight_origin);
      	vector_orig.push_back(&topRight_origin);
      	vector_orig.push_back(&topLeft_origin);
      
      	///////////////////////////////////////////
      	////// Actual entity rect
      	vector.push_back(&bottomLeft);     
      	vector.push_back(&bottomRight);      
      	vector.push_back(&topRight);                 
      	vector.push_back(&topLeft);
}

void Points :: initMidLeftPoint()
{
     	midLeft_origin.set(-w/2, 0);
     	midLeft.set(-w/2, 0);
}

void Points :: addMidLeftPoint()
{
     	vector_orig.push_back(&midLeft_origin);
     	vector.push_back(&midLeft);
}




void Points :: initMidFarLeftPoint()
{
     	midFarLeft_origin.set(-w, 0);
     	midFarLeft.set(-w, 0);
}

void Points :: addMidFarLeftPoint()
{
     	vector_orig.push_back(&midFarLeft_origin);
     	vector.push_back(&midFarLeft);
}



void Points :: setWidthHeight(int _w, int _h)
{
        w = _w;
        h = _h;
}  



void Points :: setCenter(float _centerx, float _centery) 
{
    	center.set(_centerx, _centery);
      
    	is_updated = false;       
}
       
void  Points :: setCenter(vec2f _center)
{
    	center = _center;
      
    	is_updated = false;   
}
                       
    
void Points :: setAngle(float _angle_inD)
{ 
    	angle_inD = _angle_inD;
    
    	is_updated = false; 
}  


void Points :: update()
{
    	if (is_updated == false)
    	{   
        	vec2f pos = center;

       		float angle_radian = angle_inD/RADIAN_TO_DEGREE_RATE;
         
        	float cosa = cos(angle_radian);
        	float sina = sin(angle_radian);
 
        	for (unsigned int i = 0; i < vector.size(); i++)
        	{   
           		////// rotation around center
            		vector[i]->x = vector_orig[i]->x * cosa - vector_orig[i]->y * sina;
            		vector[i]->y = vector_orig[i]->x * sina + vector_orig[i]->y * cosa;  
            		////// moving to position
            		vector[i]->x += pos.x;
            		vector[i]->y += pos.y;
        	}   
        	is_updated = true;
    	}
}        
         
void Points::CreateCenter()
{
	initCenterPoint();
	addCenterPoint();
}




       




