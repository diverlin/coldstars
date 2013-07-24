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
#include "../world/EntityManager.hpp"
#include "../common/Logger.hpp"
#include "../resources/TextureManager.hpp"
#include "../world/starsystem.hpp"
#include "../builder/spaceobjects/RocketBulletBuilder.hpp"
#include "../resources/textureOb.hpp"
#include "../effects/particlesystem/DriveEffect.hpp"
#include "../render/Render.hpp"
#include "../text/VerticalFlowText.hpp" 
#include "../effects/particlesystem/ExplosionEffect.hpp"

RocketBullet::RocketBullet(int id)
:
target(nullptr)
{
	SetId(id);
	SetTypeId(ENTITY::TYPE::BULLET_ID);
	SetSubTypeId(ENTITY::TYPE::ROCKETBULLET_ID);
}

/* virtual */
RocketBullet::~RocketBullet()
{
	#if CREATEDESTROY_LOG_ENABLED == 1
	Logger::Instance().Log("___::~RocketBullet("+int2str(GetId())+")");
	#endif

	delete drive_effect;
}

void RocketBullet::CreateDriveComplexTextureDependedStuff()
{
    GetPoints().addMidLeftPoint();
    GetPoints().addMidFarLeftPoint();
    	
	drive_effect = GetNewDriveEffect(GetTextureOb()->size_id, GetPoints().GetpMidLeft(), GetPoints().GetpMidFarLeft());
}    

void RocketBullet::UpdateInSpace(int time, bool show_effect)
{
	CheckDeath(show_effect);
        
	if (time > 0)
	{
        UpdateOrientation();
            
        if (speed < data_bullet.speed_max)
        {
            speed += data_bullet.d_speed; 
        } 
                
		if (target != nullptr)
        { 
            get_dPos_ToPoint(GetCenter(), target->GetCenter(), speed/100.0, force, angle_inD);
        
            if (CheckTarget() == false)
            {
                target = nullptr;
            }
        }      
        SetAngleZ(angle_inD);
        SetCenter(GetCenter() + force);    

        data_bullet.live_time -= 1;
    }
}

bool RocketBullet::CheckTarget() const
{
    if (target->GetAlive() == true)
    {
        if (target->GetPlaceTypeId() == PLACE::TYPE::SPACE_ID)
        {
            if (target->GetStarSystem()->GetId() == starsystem->GetId())
            {
                return true;
            }
        }
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
    info.addNameStr("id/ss_id:");          	info.addValueStr( int2str(GetId()) + " / " + int2str(starsystem->GetId()) );
    info.addNameStr("armor:");     		info.addValueStr( int2str(data_life.armor) );
    if (target != nullptr) 
    { 
    	info.addNameStr("target_id:");   	info.addValueStr(int2str(target->GetId())); 
	}
}

/* virtual */
void RocketBullet::Hit(int damage, bool show_effect)
{
	data_life.armor -= damage;

    if (data_life.armor < 0)
    {
        data_life.is_alive = false;
    }

	if (show_effect == true)
	{
        // improove
        VerticalFlowText* text = new VerticalFlowText(int2str(damage), 12, GetCenter(), COLOR::COLOR4I_RED_LIGHT, GetCollisionRadius());
        starsystem->Add(text); 
    }
}

/* virtual */
void RocketBullet::PostDeathUniqueEvent(bool show_effect)  
{
	if (show_effect == true)
    {
        ExplosionEffect* explosion = getNewExplosionEffect(GetCollisionRadius());
        starsystem->Add(explosion, GetCenter());        		
    }
}

void RocketBullet::UpdateRenderStuff()
{}

void RocketBullet::RenderInSpace(float scale) const
{
	drawQuad(GetTextureOb(), GetCenter(), GetSize(), GetAngle().z);
			  
	drive_effect->Update();
	drive_effect->Render(scale, 0.0f);
}


void RocketBullet::SaveDataUniqueRocketBullet(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
	save_ptree.put(root+"speed", speed);
	save_ptree.put(root+"owner_id", owner_id);
	if (target != nullptr) 	{ save_ptree.put(root+"target_id", target->GetId()); }
	else                	{ save_ptree.put(root+"target_id", NONE_ID); }
	
	data_bullet.SaveData(save_ptree, root);
}

void RocketBullet::LoadDataUniqueRocketBullet(const boost::property_tree::ptree& load_ptree)
{
	speed = load_ptree.get<float>("speed");  
	owner_id = load_ptree.get<int>("owner_id");  
	unresolved_RocketBullet_target_id = load_ptree.get<int>("target_id");  
	
	data_bullet.LoadData(load_ptree.get_child("data_bullet"));
}

void RocketBullet::ResolveDataUniqueRocketBullet()
{           
	RocketBulletBuilder::Instance().CreateKorpusGeometry(this);
	CreateDriveComplexTextureDependedStuff();
				
	if (unresolved_RocketBullet_target_id != NONE_ID)
	{
		target = (BaseSpaceEntity*)EntityManager::Instance().GetEntityById(unresolved_RocketBullet_target_id);
	}
	
	((StarSystem*)EntityManager::Instance().GetEntityById(data_unresolved_BaseSpaceEntity.starsystem_id))->AddBullet(this, data_unresolved_Orientation.center, data_unresolved_Orientation.angle); 
}


/*virtual*/
void RocketBullet::SaveData(boost::property_tree::ptree& save_ptree) const
{
	const std::string root = "rocketbullet."+int2str(GetId())+".";
	SaveDataUniqueBase(save_ptree, root);
	SaveDataUniqueOrientation(save_ptree, root);
	SaveDataUniqueBaseDrawable(save_ptree, root);
	SaveDataUniqueBaseSpaceEntity(save_ptree, root);
	SaveDataUniqueRocketBullet(save_ptree, root);
}

/*virtual*/
void RocketBullet::LoadData(const boost::property_tree::ptree& load_ptree)
{
	LoadDataUniqueBase(load_ptree);
	LoadDataUniqueOrientation(load_ptree);
	LoadDataUniqueBaseDrawable(load_ptree);
	LoadDataUniqueBaseSpaceEntity(load_ptree);
	LoadDataUniqueRocketBullet(load_ptree);
}

/*virtual*/
void RocketBullet::ResolveData()
{
	ResolveDataUniqueBase();
	ResolveDataUniqueOrientation();
	ResolveDataUniqueBaseDrawable();
	ResolveDataUniqueBaseSpaceEntity();
	ResolveDataUniqueRocketBullet();
}
