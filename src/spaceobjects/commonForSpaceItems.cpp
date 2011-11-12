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

void CommonForSpaceItems :: CommonForSpaceItems_init(IdData _data_id, LifeData _data_life, TextureOb* _texOb, vec2f _start_pos)
{   
    	data_id = _data_id;
    	data_life = _data_life;
    	
    	texOb = _texOb;
    	starsystem = NULL;
    
   	calcRenderConstants();
     
    	collision_radius = (texOb->w + texOb->h)/2;
    	

    	//////
    	points.initCenterPoint();
    	points.addCenterPoint();

    	points.setCenter(_start_pos.x, _start_pos.y);
    	//////

    	data_angle_inD.d_z      = getRandInt(10, 100)*0.01;    	    	    	
    	keep_moving = true;
    	
    	target_pos = getRandomVec(_start_pos, 60, 100);
        
        place_type_id = SPACE_ID;
}

bool CommonForSpaceItems :: getAlive() const { return data_life.is_alive; }     
int CommonForSpaceItems :: getId() const { return data_id.id; }
int CommonForSpaceItems :: getTypeId() const { return data_id.type_id; }
int CommonForSpaceItems :: getSubTypeId() const { return data_id.subtype_id; }
bool* CommonForSpaceItems :: getpAlive() { return &data_life.is_alive; }  
int* CommonForSpaceItems :: getpPlaceTypeId() { return &place_type_id; }
void CommonForSpaceItems :: setPlaceTypeId(int _place_type_id) { place_type_id = _place_type_id; }
        	
Points* CommonForSpaceItems :: getPoints() { return &points; } 
void CommonForSpaceItems :: setStarSystem(StarSystem* _starsystem) { starsystem = _starsystem; }
StarSystem* CommonForSpaceItems :: getStarSystem() { return starsystem; }
int CommonForSpaceItems :: getCollisionRadius() const {return collision_radius; }	
int CommonForSpaceItems :: getMass() const { return mass; }

void CommonForSpaceItems :: moveExternalyToPosition(vec2f _target)
{
        get_dX_dY_ToPoint(points.getCenter().x, points.getCenter().y, _target.x, _target.y, velocity, &d_pos.x, &d_pos.y);
        points.setCenter(points.getCenter().x + d_pos.x, points.getCenter().y + d_pos.y);
}
            	

void CommonForSpaceItems :: update_inSpace_inDynamic_TRUE()
{
     	if (keep_moving == true)
     	{
        	keep_moving = get_dX_dY_ToPoint(points.getCenter().x, points.getCenter().y, target_pos.x, target_pos.y, velocity, &d_pos.x, &d_pos.y);
        	points.setCenter(points.getCenter().x + d_pos.x, points.getCenter().y + d_pos.y);
     	}
      
     	if (data_life.is_dying == true)
     	{
        	data_life.dying_time--;
        	if (data_life.dying_time < 0)
        	{
           		death_TRUE();
           	}
     	}    
}

void CommonForSpaceItems :: update_inSpace_inDynamic_FALSE()
{
	points.setCenter(target_pos.x, target_pos.y);
       	keep_moving = false;
}


void CommonForSpaceItems :: hit_TRUE(int _damage)
{
    	data_life.armor -= _damage;
    	if (data_life.armor <= 0)
    	{
       		data_life.is_dying = true;
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
       		death_FALSE();
       	}
}

void CommonForSpaceItems :: silentKill()
{
	data_life.is_alive = false;  
}

void CommonForSpaceItems :: death_TRUE()
{
     	data_life.is_alive = false;   

     	if (data_life.is_explosed == false)
     	{   
        	createExplosion(starsystem, points.getCenter(), texOb->size_id);
        	data_life.is_explosed = true;
     	}
}
   
void CommonForSpaceItems :: death_FALSE()
{
     	data_life.is_alive = false;   
}


void CommonForSpaceItems :: calcRenderConstants()
{
    	minus_half_w = -texOb->w/2;
    	minus_half_h = -texOb->h/2;
    	plus_half_w  =  texOb->w/2;
    	plus_half_h  =  texOb->h/2;
}     

          
void CommonForSpaceItems :: render2D()
{ 
    	glBindTexture(GL_TEXTURE_2D, texOb->texture);
    	drawDynamic(points.getCenter().x, points.getCenter().y, data_angle_inD.z, minus_half_w, minus_half_h, plus_half_w, plus_half_h, points.getPosZ());
    	data_angle_inD.z += data_angle_inD.d_z;
}


