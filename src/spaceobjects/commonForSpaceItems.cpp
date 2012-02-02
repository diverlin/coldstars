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



CommonForSpaceItems :: CommonForSpaceItems()
{}

CommonForSpaceItems :: ~CommonForSpaceItems()
{}

void CommonForSpaceItems :: postCreateInit()
{
   	this->calcCollisionrRadius();
	this->createCenter();
}


void CommonForSpaceItems :: calcCollisionrRadius()
{
        collision_radius = (texOb->w + texOb->h)/4; 
        
        points.setWidthHeight(texOb->w, texOb->h);  // needs for finding visible corners
}

void CommonForSpaceItems :: moveToSpace(StarSystem* starsystem, vec2f start_pos)
{
	this->starsystem = starsystem;	
    	points.setCenter(start_pos);    	
    	target_pos = start_pos + getRandVec(60, 100);
        
        place_type_id = SPACE_ID;
        keep_moving = true;
}





void CommonForSpaceItems :: moveExternalyToPosition(vec2f _target)
{
        get_dX_dY_ToPoint(points.getCenter().x, points.getCenter().y, _target.x, _target.y, 10*velocity, &d_pos.x, &d_pos.y);
        points.setCenter(points.getCenter().x + d_pos.x, points.getCenter().y + d_pos.y);
        //points.setCenter(points.getCenter() + d_pos);
}
            	

void CommonForSpaceItems :: update_inSpace_inDynamic_TRUE()
{
     	if (keep_moving == true)
     	{
        	keep_moving = get_dX_dY_ToPoint(points.getCenter().x, points.getCenter().y, target_pos.x, target_pos.y, velocity, &d_pos.x, &d_pos.y);
        	points.setCenter(points.getCenter().x + d_pos.x, points.getCenter().y + d_pos.y);
     	}  
}

void CommonForSpaceItems :: update_inSpace_inDynamic_FALSE()
{
	points.setCenter(target_pos.x, target_pos.y);
       	keep_moving = false;
}

void CommonForSpaceItems :: updateDyingEffect_TRUE()
{
	if (data_life.is_alive == false)
     	{
        	data_life.dying_time--;
        	if (data_life.dying_time < 0)
        	{
           		death_TRUE();
           	}
     	}  
}

void CommonForSpaceItems :: updateDyingEffect_FALSE()
{
	if (data_life.is_alive == false)
     	{
       		death_FALSE();
     	}  
}

void CommonForSpaceItems :: hit_TRUE(int _damage)
{
    	data_life.armor -= _damage;
    	if (data_life.armor <= 0)
    	{
       		data_life.is_alive = false;
       	}
       	
       	// improove
       	Color4i color;     		
       	VerticalFlowText* _text = new VerticalFlowText(int2str(_damage), points.getCenter(), color, collision_radius);
       	starsystem->add(_text); 
}

void CommonForSpaceItems :: hit_FALSE(int damage)
{
    	data_life.armor -= damage;
    	if (data_life.armor <= 0)
    	{
    		data_life.is_alive = false;
       		death_FALSE();
       	}
}

void CommonForSpaceItems :: silentKill()
{
	data_life.is_alive      = false;  
	data_life.garbage_ready = true; 
}

void CommonForSpaceItems :: death_TRUE()
{
     	if (data_life.garbage_ready == false)
     	{   
        	createExplosion(starsystem, points.getCenter(), texOb->size_id);
        	data_life.garbage_ready = true;
     	}
}
   
void CommonForSpaceItems :: death_FALSE()
{
	data_life.garbage_ready = true;
}

       
void CommonForSpaceItems :: render2D()
{ 
    	drawDynamic(texOb, points.getCenter(), angle.z, points.getPosZ());
    	angle.z += d_angle.z;
}


