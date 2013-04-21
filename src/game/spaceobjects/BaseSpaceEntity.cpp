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

BaseSpaceEntity::BaseSpaceEntity():
starsystem(NULL), 
mesh(NULL), 
textureOb(NULL), 
parent(NULL),
place_type_id(NONE_ID), 
collision_radius(0), 
mass(0), 
given_expirience(0),
scale(0),
ZYX(false)
{}

/* virtual */
BaseSpaceEntity::~BaseSpaceEntity()
{
	#if CREATEDESTROY_LOG_ENABLED == 1
	Logger::Instance().Log("___::~BaseSpaceEntity("+int2str(GetId())+")");
	#endif
}

void BaseSpaceEntity::RecalculateCollisionRadius()
{
	if (mesh)
	{
		collision_radius = scale/2; // for 3d object
	}
	else
	{
		collision_radius = (textureOb->GetFrameWidth() + textureOb->GetFrameHeight())/3; // for 2D object
	}
}

void BaseSpaceEntity::UpdateRotation()
{
	angle.x += d_angle.x;  
	angle.y += d_angle.y;  
	angle.z += d_angle.z; 
}

void BaseSpaceEntity::MovingByExternalForce(const vec2f& _target_pos, float force)
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

void BaseSpaceEntity::RenderInfoInSpace(const vec2f& scroll_coords)
{ 
	UpdateInfo();
	vec2f pos(points.GetCenter().x - scroll_coords.x, points.GetCenter().y - scroll_coords.y);
     	drawInfoIn2Column(info.title_list, info.value_list, pos);
}

void BaseSpaceEntity::RenderInfo(const vec2f& center)
{ 
	UpdateInfo();
     	drawInfoIn2Column(info.title_list, info.value_list, center);
}

void BaseSpaceEntity::RenderMesh(const vec2f& scroll_coords) const
{
     	glUseProgram(ShaderCollector::Instance().light);

     	glUniform4f(glGetUniformLocation(ShaderCollector::Instance().light, "lightPos"), -scroll_coords.x, -scroll_coords.y, -200.0, 0.0);
     	glUniform4f(glGetUniformLocation(ShaderCollector::Instance().light, "eyePos"), -scroll_coords.x, -scroll_coords.y, -200.0, 0.0);

     	glActiveTexture(GL_TEXTURE0);
     	glBindTexture(GL_TEXTURE_2D, textureOb->texture);
     	glUniform1i(glGetUniformLocation(ShaderCollector::Instance().light, "Texture_0"), 0);
     	
	renderMesh(mesh, points.GetCenter3f(), angle, scale, ZYX);
		
     	glUseProgram(0);
     	glActiveTexture(GL_TEXTURE0);
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

	save_ptree.put(root+"angle.x", angle.x);
	save_ptree.put(root+"angle.y", angle.y);
	save_ptree.put(root+"angle.z", angle.z);

	save_ptree.put(root+"d_angle.x", d_angle.x);
	save_ptree.put(root+"d_angle.y", d_angle.y);
	save_ptree.put(root+"d_angle.z", d_angle.z);

	save_ptree.put(root+"collision_radius", collision_radius);

	save_ptree.put(root+"mass", mass);
	save_ptree.put(root+"scale", scale);	

	//save_ptree.put(root+"d_pos.x", d_pos.x);
	//save_ptree.put(root+"d_pos.y", d_pos.y);	
		
	if (mesh) save_ptree.put(root+"data_unresolved_BaseSpaceEntity.mesh_type_id", mesh->GetTypeId());
	else      save_ptree.put(root+"data_unresolved_BaseSpaceEntity.mesh_type_id", NONE_ID);
	
	if (textureOb) 	save_ptree.put(root+"data_unresolved_BaseSpaceEntity.textureOb_path", textureOb->path);
	else            save_ptree.put(root+"data_unresolved_BaseSpaceEntity.textureOb_path", "none");

	if (parent) save_ptree.put(root+"data_unresolved_BaseSpaceEntity.parent_id", parent->GetId());
	else        save_ptree.put(root+"data_unresolved_BaseSpaceEntity.parent_id", NONE_ID);

	if (starsystem)	save_ptree.put(root+"data_unresolved_BaseSpaceEntity.starsystem_id", starsystem->GetId());
	else	        save_ptree.put(root+"data_unresolved_BaseSpaceEntity.starsystem_id", NONE_ID);
		
	save_ptree.put(root+"place_type_id", place_type_id);
			
	save_ptree.put(root+"data_unresolved_BaseSpaceEntity.center.x", points.GetCenter().x);
	save_ptree.put(root+"data_unresolved_BaseSpaceEntity.center.y", points.GetCenter().y);
	save_ptree.put(root+"data_unresolved_BaseSpaceEntity.angle_2D", points.GetAngleDegree());
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
	
	angle.x = load_ptree.get<float>("angle.x");
	angle.y = load_ptree.get<float>("angle.y");
	angle.z = load_ptree.get<float>("angle.z");

	d_angle.x = load_ptree.get<float>("d_angle.x");
	d_angle.y = load_ptree.get<float>("d_angle.y");
	d_angle.z = load_ptree.get<float>("d_angle.z");

	collision_radius = load_ptree.get<float>("collision_radius");

	mass = load_ptree.get<int>("mass");
	scale = load_ptree.get<float>("scale");

	place_type_id = load_ptree.get<int>("place_type_id");	

	//d_pos.x = load_ptree.get<float>("d_pos.x");
	//d_pos.y = load_ptree.get<float>("d_pos.y");

	data_unresolved_BaseSpaceEntity.mesh_type_id = load_ptree.get<int>("data_unresolved_BaseSpaceEntity.mesh_type_id");
	data_unresolved_BaseSpaceEntity.textureOb_path = load_ptree.get<std::string>("data_unresolved_BaseSpaceEntity.textureOb_path");
	
	data_unresolved_BaseSpaceEntity.parent_id     = load_ptree.get<int>("data_unresolved_BaseSpaceEntity.parent_id");			
	data_unresolved_BaseSpaceEntity.starsystem_id = load_ptree.get<int>("data_unresolved_BaseSpaceEntity.starsystem_id");
		
	data_unresolved_BaseSpaceEntity.center.x = load_ptree.get<float>("data_unresolved_BaseSpaceEntity.center.x");
	data_unresolved_BaseSpaceEntity.center.y = load_ptree.get<float>("data_unresolved_BaseSpaceEntity.center.y");
	data_unresolved_BaseSpaceEntity.angle    = load_ptree.get<float>("data_unresolved_BaseSpaceEntity.angle_2D");
}

void BaseSpaceEntity::ResolveDataUniqueBaseSpaceEntity()
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" BaseSpaceEntity("+int2str(GetId())+")::ResolveDataUniqueBaseSpaceEntity", SAVELOAD_LOG_DIP);
	#endif
	
	if (data_unresolved_BaseSpaceEntity.mesh_type_id != NONE_ID)
	{
		mesh = MeshCollector::Instance().GetMeshByTypeId(data_unresolved_BaseSpaceEntity.mesh_type_id); 
	}
	
	textureOb = TextureManager::Instance().GetTextureObByPath(data_unresolved_BaseSpaceEntity.textureOb_path);
	
	if (data_unresolved_BaseSpaceEntity.parent_id != NONE_ID)
	{
		parent = (BaseSpaceEntity*)EntityManager::Instance().GetEntityById(data_unresolved_BaseSpaceEntity.parent_id);
	}

	if (data_unresolved_BaseSpaceEntity.starsystem_id != NONE_ID)
	{
		starsystem = (StarSystem*)EntityManager::Instance().GetEntityById(data_unresolved_BaseSpaceEntity.starsystem_id);
	}
}
