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



RocketBullet :: RocketBullet(BulletData _data_bullet, 			     
                             BaseGameEntity* target,
			     int _owner_id)
{
	data_bullet = _data_bullet;
	
        owner_ship_id = _owner_id;

        this->target = target;

        speed = _data_bullet.speed_init;

}

RocketBullet :: ~RocketBullet()
{}

void RocketBullet :: place(vec2f _start_pos, float _angle_inD, float offset)
{
	dx = 0;
        dy = 0;

        points.setCenter(_start_pos.x + offset, _start_pos.y + offset);
        angle_inD = _angle_inD;
        points.setAngle(angle_inD);
}


int RocketBullet :: getDamage() const { return data_bullet.damage; }
int RocketBullet :: getOwnerShipId() const { return owner_ship_id; }

void RocketBullet :: update_inSpace(int time, bool show_effect)
{
	CheckDeath(show_effect);
        
	if (time > 0)
	{
                points.update();
                
    		if (speed < data_bullet.speed_max)
    		{
       			speed += data_bullet.d_speed; 
    		} 
                
		if (target != NULL)
    		{ 
        		get_dX_dY_angleInD_ToPoint(points.getCenter().x, points.getCenter().y, target->GetPoints().getCenter().x, target->GetPoints().getCenter().y, speed/100.0, &dx, &dy, &angle_inD);
    		
                        if (isTargetOk() == false)
                        {
                                target = NULL;
                        }
                }      
    		points.setAngle(angle_inD);
    		points.setCenter(points.getCenter().x + dx, points.getCenter().y + dy);
    

    		data_bullet.live_time -= 1;
    	}
}

bool RocketBullet :: isTargetOk() const
{
        if (target->GetAlive() == true)
        {
                if (isStarSystemOk() == true)
                {
                        return true;
                }
        }
        
        return false;
}

bool RocketBullet :: isStarSystemOk() const
{
        if (target->GetStarSystem() == starsystem)
        {
                return true;
        }
        
        return false;
}  

void RocketBullet :: collisionEvent(bool show_effect)
{
	data_life.is_alive = false; 
	data_life.dying_time = -1;
}




void RocketBullet :: deathEventUnique(bool show_effect)
{
	if (show_effect == true)
	{
       		createExplosion(starsystem, points.getCenter(), texOb->size_id);
       	}
}


void RocketBullet :: updateInfo()
{}



void RocketBullet :: updateRenderStuff()
{
	//points.update();
}


void RocketBullet :: render_inSpace() const
{
	RenderKorpus();
	RenderDriveTrail();
}





