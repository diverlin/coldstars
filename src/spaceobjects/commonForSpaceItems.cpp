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



void CommonForSpaceItems :: CommonForSpaceItems_init(IdData _data_id, LifeData _data_life, TextureOb* _texOb)
{   
    	data_id   = _data_id;
    	data_life = _data_life;
    	
    	texOb = _texOb;
    	starsystem = NULL;
    
   	this->calcRenderConstants();
     
    	collision_radius = (texOb->w + texOb->h)/4;    	

    	//////
    	points.initCenterPoint();
    	points.addCenterPoint();
    	//////

    	data_angle_inD.d_z      = -getRandInt(10, 100)*0.01;    	    	    	
}


void CommonForSpaceItems :: moveToSpace(StarSystem* starsystem, vec2f start_pos)
{
	this->starsystem = starsystem;	
    	points.setCenter(start_pos.x, start_pos.y);    	
    	target_pos = start_pos + getRandVec(60, 100);
        
        place_type_id = SPACE_ID;
        keep_moving = true;
        //printf("target_pos = %f,%f\n", target_pos.x, target_pos.y);
}



//void CommonForSpaceItems :: setStarSystem(StarSystem* _starsystem) { starsystem = _starsystem; }
void CommonForSpaceItems :: setPlaceTypeId(int _place_type_id) { place_type_id = _place_type_id; }

int CommonForSpaceItems :: getId() const { return data_id.id; }
int CommonForSpaceItems :: getTypeId() const { return data_id.type_id; }
int CommonForSpaceItems :: getSubTypeId() const { return data_id.subtype_id; }
bool CommonForSpaceItems :: getGarbageReady() const { return data_life.garbage_ready; }  
bool CommonForSpaceItems :: getAlive() const { return data_life.is_alive; }  
bool* CommonForSpaceItems :: getpAlive() { return &data_life.is_alive; }  
int* CommonForSpaceItems :: getpPlaceTypeId() { return &place_type_id; }
int CommonForSpaceItems :: getPlaceTypeId() const { return place_type_id; }
        	
Points* CommonForSpaceItems :: getPoints() { return &points; } 
StarSystem* CommonForSpaceItems :: getStarSystem() { return starsystem; }
int CommonForSpaceItems :: getCollisionRadius() const {return collision_radius; }	
int CommonForSpaceItems :: getMass() const { return mass; }

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


void CommonForSpaceItems :: calcRenderConstants()
{
    	minus_half_w = -texOb->w/2;
    	minus_half_h = -texOb->h/2;
    	plus_half_w  =  texOb->w/2;
    	plus_half_h  =  texOb->h/2;
}     

          
void CommonForSpaceItems :: render2D()
{ 
    	drawDynamic(texOb, points.getCenter(), data_angle_inD.z, minus_half_w, minus_half_h, plus_half_w, plus_half_h, points.getPosZ());
    	data_angle_inD.z += data_angle_inD.d_z;
}


