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
	get_dX_dY_ToPoint(points.getCenter().x, points.getCenter().y, _target.x, _target.y, force, &d_pos.x, &d_pos.y);
	//points.setCenter(points.getCenter().x + d_pos.x, points.getCenter().y + d_pos.y);
	points.setCenter(points.getCenter() + d_pos);
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
		VerticalFlowText* text = new VerticalFlowText(int2str(damage), points.getCenter(), COLOR::DEFAULT4i, collision_radius);
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

void BaseGameEntity::SaveDataUniqueBaseGameEntity(const std::string& root) const
{
	SaveManager::Instance().Put(root+"data_id.id",         data_id.id);
	SaveManager::Instance().Put(root+"data_id.type_id",    data_id.type_id);
	SaveManager::Instance().Put(root+"data_id.subtype_id", data_id.subtype_id);

	SaveManager::Instance().Put(root+"data_life.is_alive",   data_life.is_alive);
	SaveManager::Instance().Put(root+"data_life.armor",      data_life.armor);
	SaveManager::Instance().Put(root+"data_life.dying_time", data_life.dying_time);

	SaveManager::Instance().Put(root+"angle.x", angle.x);
	SaveManager::Instance().Put(root+"angle.y", angle.y);
	SaveManager::Instance().Put(root+"angle.z", angle.z);

	SaveManager::Instance().Put(root+"d_angle.x", d_angle.x);
	SaveManager::Instance().Put(root+"d_angle.y", d_angle.y);
	SaveManager::Instance().Put(root+"d_angle.z", d_angle.z);

	SaveManager::Instance().Put(root+"collision_radius", collision_radius);

	SaveManager::Instance().Put(root+"mass", mass);

	if (mesh) 	SaveManager::Instance().Put(root+"mesh_path", mesh->path);
	else            SaveManager::Instance().Put(root+"mesh_path", "none");
	
	if (textureOb) 	SaveManager::Instance().Put(root+"textureOb_path", textureOb->path);
	else            SaveManager::Instance().Put(root+"textureOb_path", "none");	

	if (parent) SaveManager::Instance().Put(root+"parent_id", parent->GetId());
	else        SaveManager::Instance().Put(root+"parent_id", -1);

	SaveManager::Instance().Put(root+"starsystem_id", starsystem->GetId());
	SaveManager::Instance().Put(root+"place_type_id", place_type_id);
			
	SaveManager::Instance().Put(root+"center.x", points.getCenter().x);
	SaveManager::Instance().Put(root+"center.y", points.getCenter().y);
	SaveManager::Instance().Put(root+"angle_2D", points.getAngleDegree());	
								
	SaveManager::Instance().SaveFile("save.info");	
}



void BaseGameEntity::LoadDataUniqueBaseGameEntity(const boost::property_tree::ptree& ptree)
{
	data_id.id           = ptree.get<int>("data_id.id");
	data_id.type_id      = ptree.get<int>("data_id.type_id");
	data_id.subtype_id   = ptree.get<int>("data_id.subtype_id");

	data_life.is_alive   = ptree.get<bool>("data_life.is_alive");
	data_life.armor      = ptree.get<int>("data_life.armor");
	data_life.dying_time = ptree.get<int>("data_life.dying_time");
	
	angle.x = ptree.get<float>("angle.x");
	angle.y = ptree.get<float>("angle.y");
	angle.z = ptree.get<float>("angle.z");

	d_angle.x = ptree.get<float>("d_angle.x");
	d_angle.y = ptree.get<float>("d_angle.y");
	d_angle.z = ptree.get<float>("d_angle.z");

	collision_radius = ptree.get<float>("collision_radius");

	mass = ptree.get<int>("mass");

	place_type_id = ptree.get<int>("place_type_id");	




	data_unresolved_bge.mesh_path      = ptree.get<std::string>("mesh_path");
	data_unresolved_bge.textureOb_path = ptree.get<std::string>("textureOb_path");
	
	data_unresolved_bge.parent_id = ptree.get<int>("parent_id");			
	data_unresolved_bge.starsystem_id = ptree.get<int>("starsystem_id");
			
	data_unresolved_bge.center.x = ptree.get<float>("center.x");
	data_unresolved_bge.center.y = ptree.get<float>("center.y");
	data_unresolved_bge.angle    = ptree.get<float>("angle_2D");
}

void BaseGameEntity::ResolveDataUniqueBaseGameEntity()
{
	points.setCenter(data_unresolved_bge.center);
	points.setAngle(data_unresolved_bge.angle);
	
	mesh = g_DEFORMED_SPHERE_MESH; //data_unresolved_bge.mesh_path; 
	textureOb = g_TEXTURE_MANAGER.GetTextureObByPath(data_unresolved_bge.textureOb_path);
	
	parent = EntityManager::Instance().GetEntityById(data_unresolved_bge.parent_id);
	starsystem = (StarSystem*)EntityManager::Instance().GetEntityById(data_unresolved_bge.starsystem_id);
}
