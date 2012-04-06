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



SpaceItemBase :: SpaceItemBase()
{}

SpaceItemBase :: ~SpaceItemBase()
{}

void SpaceItemBase :: postCreateInit()
{
   	this->calcCollisionrRadius();
	points.CreateCenter();
}


void SpaceItemBase :: calcCollisionrRadius()
{
        collision_radius = (textureOb->getFrameWidth() + textureOb->getFrameHeight())/4; 
        
        points.setWidthHeight(textureOb->getFrameWidth(), textureOb->getFrameHeight());  // needs for finding visible corners
}

void SpaceItemBase :: moveToSpace(StarSystem* starsystem, vec2f start_pos)
{
	this->starsystem = starsystem;	
    	points.setCenter(start_pos);    	
    	target_pos = start_pos + getRandVec(60, 100);
        
        place_type_id = ENTITY::SPACE_ID;
        keep_moving = true;
}


           	

void SpaceItemBase :: update_inSpace(int time, bool show_effect)
{
	CheckDeath(show_effect);
	UpdateRotation();
		
	if (time > 0)
	{
     		if (keep_moving == true)
     		{
        		keep_moving = get_dX_dY_ToPoint(points.getCenter().x, points.getCenter().y, target_pos.x, target_pos.y, velocity, &d_pos.x, &d_pos.y);
        		points.setCenter(points.getCenter().x + d_pos.x, points.getCenter().y + d_pos.y);
     		}  
     	}
}


void SpaceItemBase :: silentKill()
{
	data_life.is_alive      = false;  
	data_life.garbage_ready = true;  // ??? death(false);
}
   
/* virtual */    
void SpaceItemBase :: PostDeathUniqueEvent(bool show_effect)
{
	if (show_effect == true)
     	{
        	createExplosion(starsystem, points.getCenter(), textureOb->size_id);        		
        }
}
       		
void SpaceItemBase :: render2D()
{ 
    	drawDynamic(textureOb, points.getCenter(), angle.z, points.getPosZ());
}


