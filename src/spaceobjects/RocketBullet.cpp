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



RocketBullet::RocketBullet(int id)
{
	data_id.id = id;
	data_id.type_id = ENTITY::ROCKET_ID;

	target = NULL;
	
	dx = 0;
        dy = 0;
}

RocketBullet::~RocketBullet()
{}

void RocketBullet::UpdateInSpace(int time, bool show_effect)
{
	CheckDeath(show_effect);
        
	if (time > 0)
	{
                points.Update();
                
    		if (speed < data_bullet.speed_max)
    		{
       			speed += data_bullet.d_speed; 
    		} 
                
		if (target != NULL)
    		{ 
        		get_dX_dY_angleInD_ToPoint(points.GetCenter().x, points.GetCenter().y, target->GetPoints().GetCenter().x, target->GetPoints().GetCenter().y, speed/100.0, &dx, &dy, &angle_inD);
    		
                        if (CheckTarget() == false)
                        {
                                target = NULL;
                        }
                }      
    		points.SetAngle(angle_inD);
    		points.SetCenter(points.GetCenter().x + dx, points.GetCenter().y + dy);
    

    		data_bullet.live_time -= 1;
    	}
}

bool RocketBullet::CheckTarget() const
{
        if (target->GetAlive() == true)
        {
                if (CheckStarSystem() == true)
                {
                        return true;
                }
        }
        
        return false;
}

bool RocketBullet::CheckStarSystem() const
{
        if (target->GetStarSystem() == starsystem)
        {
                return true;
        }
        
        return false;
}  

void RocketBullet::CollisionEvent(bool show_effect)
{
	data_life.is_alive = false; 
	data_life.dying_time = -1;
}




void RocketBullet::deathEventUnique(bool show_effect)
{
	if (show_effect == true)
	{
       		createExplosion(starsystem, points.GetCenter(), textureOb->size_id);
       	}
}


void RocketBullet::UpdateInfo()
{}



void RocketBullet::UpdateRenderStuff()
{
	//points.update();
}


void RocketBullet::RenderInSpace() const
{
	RenderKorpus();
	RenderDriveTrail();
}



/*virtual*/
void RocketBullet::SaveData(boost::property_tree::ptree& save_ptree) const
{
	//const std::string root = "rocket."+int2str(data_id.id)+".";
}

/*virtual*/
void RocketBullet::LoadData(const boost::property_tree::ptree& load_ptree)
{

}

/*virtual*/
void RocketBullet::ResolveData()
{

}

