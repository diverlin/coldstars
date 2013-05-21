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

#include "BasePlanet.hpp"
#include "../resources/ShaderCollector.hpp"
#include "../render/Render.hpp"

#include "../common/Logger.hpp" 
#include "../common/myStr.hpp"

BasePlanet::BasePlanet()
{}

/* virtual */
BasePlanet::~BasePlanet()
{
	#if CREATEDESTROY_LOG_ENABLED == 1
	Logger::Instance().Log("___::~BasePlanet("+int2str(GetId())+")");
	#endif
}

void BasePlanet::CreateOrbit()
{
	orbit.CalcPath(data_planet.radius_A, data_planet.radius_B, data_planet.speed, data_planet.orbit_phi_inD, data_planet.clockwise);
}

void BasePlanet::PostDeathUniqueEvent(bool)  /* virtual */
{}		
	
void BasePlanet::UpdatePosition()
{
	orbit.UpdatePosition();  
	if (parent == NULL)
	{
		points.SetCenter(orbit.GetPosition());
	}
	else
	{
		points.SetCenter(parent->GetPoints().GetCenter() + orbit.GetPosition());
	}
}

void BasePlanet::RenderMesh_OLD() const
{   	
	glBindTexture(GL_TEXTURE_2D, textureOb->texture);
	renderMesh(mesh, points.GetCenter(), points.GetAngle(), points.GetScale(), ZYX);
}


void BasePlanet::SaveDataUniqueBasePlanet(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" BasePlanet("+int2str(GetId())+")::SaveDataUniqueBasePlanet", SAVELOAD_LOG_DIP);
	#endif
	
	save_ptree.put(root+"data.orbit_center.x", data_planet.orbit_center.x);	
	save_ptree.put(root+"data.orbit_center.y", data_planet.orbit_center.y);	
	save_ptree.put(root+"data.radius_A", data_planet.radius_A);	
	save_ptree.put(root+"data.radius_B", data_planet.radius_B);
	save_ptree.put(root+"data.orbit_phi_inD", data_planet.orbit_phi_inD);		
	save_ptree.put(root+"data.speed", data_planet.speed);
	save_ptree.put(root+"data.clockwise", data_planet.clockwise);
	
	save_ptree.put(root+"unresolved.orbit_it", orbit.GetIt());
}

void BasePlanet::LoadDataUniqueBasePlanet(const boost::property_tree::ptree& load_ptree)
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" BasePlanet("+int2str(GetId())+")::LoadDataUniqueBasePlanet", SAVELOAD_LOG_DIP);
	#endif
	
	data_planet.orbit_center.x = load_ptree.get<float>("data.orbit_center.x");	
	data_planet.orbit_center.y = load_ptree.get<float>("data.orbit_center.y");	
	data_planet.radius_A = load_ptree.get<float>("data.radius_A");	
	data_planet.radius_B = load_ptree.get<float>("data.radius_B");
	data_planet.orbit_phi_inD = load_ptree.get<float>("data.orbit_phi_inD");		
	data_planet.speed = load_ptree.get<float>("data.speed");
	data_planet.clockwise = load_ptree.get<bool>("data.clockwise");
	
	data_unresolved_BasePlanet.orbit_it = load_ptree.get<int>("unresolved.orbit_it");
}

void BasePlanet::ResolveDataUniqueBasePlanet()
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" BasePlanet("+int2str(GetId())+")::ResolveDataUniqueBasePlanet", SAVELOAD_LOG_DIP);
	#endif
}


