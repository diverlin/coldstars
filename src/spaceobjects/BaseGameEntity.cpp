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

//#include "BaseGameEntity.hpp"

BaseGameEntity::BaseGameEntity()
{
	angle.x        = getRandInt(10, 40);
	angle.y        = getRandInt(10, 40);
	angle.z        = 0.0;

	d_angle.x      = 0.0;
	d_angle.y      = 0.0;
	d_angle.z      = getRandInt(10, 100)*0.01;  

	place_type_id = NONE_ID;

	starsystem = NULL;
	mesh       = NULL;
	texOb      = NULL;

	parent = NULL;
}

BaseGameEntity::~BaseGameEntity()
{}


void BaseGameEntity: CreateCenter()
{
	points.initCenterPoint();
	points.addCenterPoint();
}

void BaseGameEntity::UpdateRotation()
{
	angle.x += d_angle.x;  
	angle.y += d_angle.y;  
	angle.z += d_angle.z; 
	//printf("1. angle = %f\n", angle.z);
}

void BaseGameEntity::MovingByExternalForce(vec2f _target, float force)
{
	vec2f d_pos;
	get_dX_dY_ToPoint(points.getCenter().x, points.getCenter().y, _target.x, _target.y, force, &d_pos.x, &d_pos.y);
	points.setCenter(points.getCenter().x + d_pos.x, points.getCenter().y + d_pos.y);
	//points.setCenter(points.getCenter() + d_pos);
}

void BaseGameEntity::Hit(int damage, bool show_effect)
{
	data_life.armor -= damage;
	if (data_life.armor <= 0)
	{
		data_life.is_alive = false; 
		data_life.dying_time -= 3;
	}

	if (show_effect == true)
	{	
		// improove
		Color4i color;     		
		VerticalFlowText* _text = new VerticalFlowText(int2str(damage), points.getCenter(), color, collision_radius);
		starsystem->addToSpace(_text); 
	}

}

void BaseGameEntity::CheckDeath(bool show_effect)
{
	if (data_life.is_alive == false)
	{
		data_life.dying_time--;
		if (data_life.dying_time < 0)
		{
			if (data_life.garbage_ready == false)
			{   
				PostDeathUniqueEvent(show_effect);
				data_life.garbage_ready = true;
			}
		}
	}  
}


