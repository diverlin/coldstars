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

#include "RocketBullet.hpp"
#include "../common/common.hpp"
#include "../common/constants.hpp"
#include "../common/myStr.hpp"
#include "../common/EntityManager.hpp"
#include "../resources/TextureManager.hpp"
#include "../world/starsystem.hpp"

RocketBullet::RocketBullet(int id)
{
	data_id.id = id;
	data_id.type_id    = ENTITY::VEHICLE_ID;
	data_id.subtype_id = ENTITY::ROCKETBULLET_ID;

	target = NULL;
}

RocketBullet::~RocketBullet()
{

}

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
        		get_dPos_ToPoint(points.GetCenter(), target->GetPoints().GetCenter(), speed/100.0, d_pos, angle_inD);
    		
                        if (CheckTarget() == false)
                        {
                                target = NULL;
                        }
                }      
    		points.SetAngle(angle_inD);
    		points.SetCenter(points.GetCenter() + d_pos);
    

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

void RocketBullet::UpdateInfo()
{
	info.clear();

    	info.addTitleStr("ROCKET");
    	info.addNameStr("id/ss_id:");          	info.addValueStr( int2str(data_id.id) + " / " + int2str(starsystem->GetId()) );
    	info.addNameStr("armor/max:");     	info.addValueStr( int2str(data_life.armor) + "/" + int2str(data_korpus.armor) );
    	if (target != NULL) 
    	{ 
    	info.addNameStr("target_id:");   	info.addValueStr(int2str(target->GetId())); 
	}
}


void RocketBullet::UpdateRenderStuff()
{
	//points.update();
}


void RocketBullet::RenderInSpace() const
{
	RenderKorpus();
	RenderDriveEffect();
}



/*virtual*/
void RocketBullet::SaveData(boost::property_tree::ptree& save_ptree) const
{
	const std::string root = "rocketbullet."+int2str(data_id.id)+".";
        SaveDataUniqueBase(save_ptree, root);
	SaveDataUniqueBaseGameEntity(save_ptree, root);
	SaveDataUniqueVehicle(save_ptree, root);
	SaveDataUniqueRocketBullet(save_ptree, root);
}

/*virtual*/
void RocketBullet::LoadData(const boost::property_tree::ptree& load_ptree)
{
        LoadDataUniqueBase(load_ptree);
	LoadDataUniqueBaseGameEntity(load_ptree);
	LoadDataUniqueVehicle(load_ptree);
	LoadDataUniqueRocketBullet(load_ptree);
}

/*virtual*/
void RocketBullet::ResolveData()
{
        ResolveDataUniqueBase();
	ResolveDataUniqueBaseGameEntity();
	ResolveDataUniqueVehicle();
	ResolveDataUniqueRocketBullet();
}

void RocketBullet::SaveDataUniqueRocketBullet(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
        save_ptree.put(root+"speed", speed);
        save_ptree.put(root+"owner_id", owner_id);
        if (target != NULL) 	{ save_ptree.put(root+"target_id", target->GetId()); }
	else                	{ save_ptree.put(root+"target_id", NONE_ID); }
	
	data_bullet.SaveData(save_ptree, root);
}

void RocketBullet::LoadDataUniqueRocketBullet(const boost::property_tree::ptree& load_ptree)
{
        speed = load_ptree.get<float>("speed");  
        owner_id = load_ptree.get<int>("owner_id");  
        unresolved_target_id = load_ptree.get<int>("target_id");  
        
        data_bullet.LoadData(load_ptree.get_child("data_bullet"));
}

void RocketBullet::ResolveDataUniqueRocketBullet()
{                       
        if (unresolved_target_id != NONE_ID)
        {
        	target = (BaseGameEntity*)EntityManager::Instance().GetEntityById(unresolved_target_id);
        }
}

