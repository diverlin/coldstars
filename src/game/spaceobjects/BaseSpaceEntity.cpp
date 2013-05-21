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

#include "BaseSpaceEntity.hpp"
#include "../resources/MeshCollector.hpp"
#include "../resources/TextureManager.hpp"
#include "../resources/GuiTextureObCollector.hpp"
#include "../common/constants.hpp"
#include "../common/rand.hpp"
#include "../common/common.hpp"
#include "../common/myStr.hpp"
#include "../world/EntityManager.hpp"
#include "../world/starsystem.hpp"
#include "../render/Render.hpp"
#include "../text/VerticalFlowText.hpp" 
#include "../common/Logger.hpp"
#include "../resources/ShaderCollector.hpp"
#include "../animations/AnimationBase.hpp"


BaseSpaceEntity::BaseSpaceEntity():
starsystem(NULL), 
parent(NULL),
place_type_id(NONE_ID), 
mass(0), 
given_expirience(0)
{}

/* virtual */
BaseSpaceEntity::~BaseSpaceEntity()
{
	#if CREATEDESTROY_LOG_ENABLED == 1
	Logger::Instance().Log("___::~BaseSpaceEntity("+int2str(GetId())+")");
	#endif
}

void BaseSpaceEntity::MovingByExternalForce(const Vec3<float>& _target_pos, float force)
{
	get_dPos_ToPoint(points.GetCenter(), _target_pos, force, d_pos);
}

/* virtual */
void BaseSpaceEntity::Hit(int damage, bool show_effect)
{
	data_life.armor -= damage;
	if (data_life.armor <= 0)
	{
		data_life.is_alive = false; 
		data_life.dying_time -= 3;
	}

	if (show_effect == true)
	{	
		VerticalFlowText* text = new VerticalFlowText(int2str(damage), 12, points.GetCenter(), COLOR::COLOR4I_RED_LIGHT, collision_radius);
		starsystem->Add(text); 
	}

}

void BaseSpaceEntity::SilentKill()
{
	data_life.is_alive      = false;  
	data_life.garbage_ready = true;
}

void BaseSpaceEntity::CheckDeath(bool show_effect)
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
		
void BaseSpaceEntity::RenderInfoInSpace(const Vec2<float>& scroll_coords)
{ 
	UpdateInfo();
	Vec2<float> pos(points.GetCenter().x - scroll_coords.x, points.GetCenter().y - scroll_coords.y);
     	drawInfoIn2Column(info.title_list, info.value_list, pos);
}

void BaseSpaceEntity::RenderInfo(const Vec2<float>& center)
{ 
	UpdateInfo();
     	drawInfoIn2Column(info.title_list, info.value_list, center);
}
	
void BaseSpaceEntity::SaveDataUniqueBaseSpaceEntity(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" BaseSpaceEntity("+int2str(GetId())+")::SaveDataUniqueBaseSpaceEntity", SAVELOAD_LOG_DIP);
	#endif
	
	save_ptree.put(root+"data_life.is_alive",   data_life.is_alive);
	save_ptree.put(root+"data_life.armor",      data_life.armor);
	save_ptree.put(root+"data_life.life_time",  data_life.life_time);
	save_ptree.put(root+"data_life.dying_time", data_life.dying_time);

	save_ptree.put(root+"mass", mass);


	if (parent) save_ptree.put(root+"data_unresolved_BaseSpaceEntity.parent_id", parent->GetId());
	else        save_ptree.put(root+"data_unresolved_BaseSpaceEntity.parent_id", NONE_ID);

	if (starsystem)	save_ptree.put(root+"data_unresolved_BaseSpaceEntity.starsystem_id", starsystem->GetId());
	else	        save_ptree.put(root+"data_unresolved_BaseSpaceEntity.starsystem_id", NONE_ID);
		
	save_ptree.put(root+"place_type_id", place_type_id);
}



void BaseSpaceEntity::LoadDataUniqueBaseSpaceEntity(const boost::property_tree::ptree& load_ptree)
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" BaseSpaceEntity("+int2str(GetId())+")::LoadDataUniqueBaseSpaceEntity", SAVELOAD_LOG_DIP);
	#endif
	
	data_life.is_alive   = load_ptree.get<bool>("data_life.is_alive");
	data_life.armor      = load_ptree.get<int>("data_life.armor");
	data_life.life_time  = load_ptree.get<int>("data_life.life_time");
	data_life.dying_time = load_ptree.get<int>("data_life.dying_time");

	mass = load_ptree.get<int>("mass");

	place_type_id = load_ptree.get<int>("place_type_id");	
	
	data_unresolved_BaseSpaceEntity.parent_id     = load_ptree.get<int>("data_unresolved_BaseSpaceEntity.parent_id");			
	data_unresolved_BaseSpaceEntity.starsystem_id = load_ptree.get<int>("data_unresolved_BaseSpaceEntity.starsystem_id");
}

void BaseSpaceEntity::ResolveDataUniqueBaseSpaceEntity()
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" BaseSpaceEntity("+int2str(GetId())+")::ResolveDataUniqueBaseSpaceEntity", SAVELOAD_LOG_DIP);
	#endif	
	
	if (data_unresolved_BaseSpaceEntity.parent_id != NONE_ID)
	{
		parent = (BaseSpaceEntity*)EntityManager::Instance().GetEntityById(data_unresolved_BaseSpaceEntity.parent_id);
	}

	if (data_unresolved_BaseSpaceEntity.starsystem_id != NONE_ID)
	{
		starsystem = (StarSystem*)EntityManager::Instance().GetEntityById(data_unresolved_BaseSpaceEntity.starsystem_id);
	}
}
