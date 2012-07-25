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

BaseGameEntity::BaseGameEntity():starsystem(NULL), mesh(NULL), textureOb(NULL), parent(NULL),
				 place_type_id(NONE_ID), collision_radius(0), mass(0)
{
	angle.x        = getRandInt(10, 40);
	angle.y        = getRandInt(10, 40);
	angle.z        = 0.0;

	d_angle.x      = 0.0;
	d_angle.y      = 0.0;
	d_angle.z      = getRandInt(10, 100)*0.01;  
	
	scale = 1;
}

BaseGameEntity::~BaseGameEntity()
{}


void BaseGameEntity::UpdateRotation()
{
	angle.x += d_angle.x;  
	angle.y += d_angle.y;  
	angle.z += d_angle.z; 
}

void BaseGameEntity::MovingByExternalForce(vec2f _target, float force)
{
	vec2f d_pos;
	get_dX_dY_ToPoint(points.GetCenter().x, points.GetCenter().y, _target.x, _target.y, force, &d_pos.x, &d_pos.y);
	//points.SetCenter(points.GetCenter().x + d_pos.x, points.GetCenter().y + d_pos.y);
	points.SetCenter(points.GetCenter() + d_pos);
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
		VerticalFlowText* text = new VerticalFlowText(int2str(damage), points.GetCenter(), COLOR::DEFAULT4i, collision_radius);
		starsystem->Add(text); 
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

void BaseGameEntity::RenderInfoInSpace(const vec2f& scroll_coords)
{ 
	UpdateInfo();
     	drawInfoIn2Column(&info.title_list, &info.value_list, points.GetCenter().x - scroll_coords.x, points.GetCenter().y - scroll_coords.y);
}

void BaseGameEntity::RenderInfo(const vec2f& center)
{ 
	UpdateInfo();
     	drawInfoIn2Column(&info.title_list, &info.value_list, center.x, center.y);
}

void BaseGameEntity::SaveDataUniqueBaseGameEntity(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
	save_ptree.put(root+"data_life.is_alive",   data_life.is_alive);
	save_ptree.put(root+"data_life.armor",      data_life.armor);
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
	
	if (mesh) 	save_ptree.put(root+"data_unresolved_BaseGameEntity.mesh_path", mesh->path);
	else           save_ptree.put(root+"data_unresolved_BaseGameEntity.mesh_path", "none");
	
	if (textureOb) 	save_ptree.put(root+"data_unresolved_BaseGameEntity.textureOb_path", textureOb->path);
	else            save_ptree.put(root+"data_unresolved_BaseGameEntity.textureOb_path", "none");

	if (parent) save_ptree.put(root+"data_unresolved_BaseGameEntity.parent_id", parent->GetId());
	else        save_ptree.put(root+"data_unresolved_BaseGameEntity.parent_id", NONE_ID);

	save_ptree.put(root+"data_unresolved_BaseGameEntity.starsystem_id", starsystem->GetId());
	save_ptree.put(root+"place_type_id", place_type_id);
			
	save_ptree.put(root+"data_unresolved_BaseGameEntity.center.x", points.GetCenter().x);
	save_ptree.put(root+"data_unresolved_BaseGameEntity.center.y", points.GetCenter().y);
	save_ptree.put(root+"data_unresolved_BaseGameEntity.angle_2D", points.GetAngleDegree());
}



void BaseGameEntity::LoadDataUniqueBaseGameEntity(const boost::property_tree::ptree& load_ptree)
{
	data_life.is_alive   = load_ptree.get<bool>("data_life.is_alive");
	data_life.armor      = load_ptree.get<int>("data_life.armor");
	data_life.dying_time = load_ptree.get<int>("data_life.dying_time");
	
	angle.x = load_ptree.get<float>("angle.x");
	angle.y = load_ptree.get<float>("angle.y");
	angle.z = load_ptree.get<float>("angle.z");

	d_angle.x = load_ptree.get<float>("d_angle.x");
	d_angle.y = load_ptree.get<float>("d_angle.y");
	d_angle.z = load_ptree.get<float>("d_angle.z");

	collision_radius = load_ptree.get<float>("collision_radius");

	mass = load_ptree.get<int>("mass");
	scale = load_ptree.get<int>("scale");
	
	place_type_id = load_ptree.get<int>("place_type_id");	


	data_unresolved_BaseGameEntity.mesh_path      = load_ptree.get<std::string>("data_unresolved_BaseGameEntity.mesh_path");
	data_unresolved_BaseGameEntity.textureOb_path = load_ptree.get<std::string>("data_unresolved_BaseGameEntity.textureOb_path");
	
	data_unresolved_BaseGameEntity.parent_id = load_ptree.get<int>("data_unresolved_BaseGameEntity.parent_id");			
	data_unresolved_BaseGameEntity.starsystem_id = load_ptree.get<int>("data_unresolved_BaseGameEntity.starsystem_id");
			
	data_unresolved_BaseGameEntity.center.x = load_ptree.get<float>("data_unresolved_BaseGameEntity.center.x");
	data_unresolved_BaseGameEntity.center.y = load_ptree.get<float>("data_unresolved_BaseGameEntity.center.y");
	data_unresolved_BaseGameEntity.angle    = load_ptree.get<float>("data_unresolved_BaseGameEntity.angle_2D");
}

void BaseGameEntity::ResolveDataUniqueBaseGameEntity()
{
	mesh = g_DEFORMED_SPHERE_MESH; //data_unresolved_bge.mesh_path; 
	textureOb = TextureManager::Instance().GetTextureObByPath(data_unresolved_BaseGameEntity.textureOb_path);
	
	if (data_unresolved_BaseGameEntity.parent_id != NONE_ID)
	{
		parent = (BaseGameEntity*)EntityManager::Instance().GetEntityById(data_unresolved_BaseGameEntity.parent_id);
	}

	starsystem = (StarSystem*)EntityManager::Instance().GetEntityById(data_unresolved_BaseGameEntity.starsystem_id);
}
