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

#include "Planet.hpp"
#include "../common/constants.hpp"
#include "../common/EntityManager.hpp"
#include "../common/myStr.hpp"
#include "../resources/TextureManager.hpp"
#include "../world/starsystem.hpp"
#include "../render/Render.hpp"
#include "../resources/ShaderCollector.hpp"
#include "../docking/Kosmoport.hpp"
#include "../spaceobjects/Vehicle.hpp"

Planet::Planet(int id)
{    
	data_id.id = id;
	data_id.type_id = ENTITY::PLANET_ID;
	
	population  = 0;
		
	textureOb_atmosphere = TextureManager::Instance().GetRandomTextureOb(TEXTURE::ATMOSPHERE_ID);
	
	angle_atmosphere.Set(0.0, 0.0, 0.0);
	d_angle_atmosphere.Set(-0.1, 0.0, 0.0);
		      	
	land = NULL;
}


Planet::~Planet()
{
	EntityManager::Instance().RemoveEntity(this);
	
	delete land;
}

void Planet::BindLand(BaseLand* land)       		
{
	this->land = land;
	this->land->SetOwner(this);
}
	
void Planet::AddVehicle(Vehicle* vehicle) const
{
	if (vehicle->GetStarSystem() == NULL)
	{
		vehicle->SetStarSystem(starsystem);
	}
	
	land->AddVehicle(vehicle);
	
}
	
void Planet::UpdateInSpace(int time, bool show_effect)
{      
	UpdateRotation();
	angle_atmosphere += d_angle_atmosphere;
	if (time > 0)
	{
		UpdatePosition();
	}
}

void Planet::UpdateInSpaceInStatic()
{
	land->UpdateInSpaceInStatic();
}

void Planet::UpdateInfo()
{
	info.clear();

	info.addTitleStr("PLANET");
	info.addNameStr("id/ss_id:");    info.addValueStr(int2str(data_id.id) + " / " + int2str(starsystem->GetId()));
	info.addNameStr("armor:");  	 info.addValueStr(int2str(data_life.armor));
	info.addNameStr("population:");  info.addValueStr(int2str(population));
	info.addNameStr("dock_veh:");    info.addValueStr(land->GetDockVehicleStr());
}

void Planet::PostDeathUniqueEvent(bool)
{}

void Planet::Render_NEW(const vec2f& scroll_coords) const
{
	RenderMesh_NEW(scroll_coords);
	//glDepthMask(GL_FALSE);
	//RenderAtmosphere_NEW(scroll_coords);
	//glDepthMask(GL_TRUE);
}
	
void Planet::Render_OLD() const
{
	RenderMesh_OLD();	
}
				 		
void Planet::RenderAtmosphere_NEW(const vec2f& scroll_coords) const
{     	
     	glUseProgram(ShaderCollector::Instance().light);

     	glUniform4f(glGetUniformLocation(ShaderCollector::Instance().light, "lightPos"), -scroll_coords.x, -scroll_coords.y, -200.0, 0.0);
     	glUniform4f(glGetUniformLocation(ShaderCollector::Instance().light, "eyePos"), -scroll_coords.x, -scroll_coords.y, -200.0, 0.0);

     	glEnable(GL_BLEND);
     		glActiveTexture(GL_TEXTURE0);                                
     		glBindTexture(GL_TEXTURE_2D, textureOb_atmosphere->texture);
     		glUniform1i(glGetUniformLocation(ShaderCollector::Instance().light, "Texture_0"), 0);

		renderMesh(mesh->glList, points.GetCenter3f(), angle_atmosphere, scale*1.1f);
	glDisable(GL_BLEND);
	
     	glUseProgram(0);
     	glActiveTexture(GL_TEXTURE0);
}


void Planet::SaveDataUniquePlanet(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
	//SaveManager::Instance().Put(root+"race_id", race_id);
	save_ptree.put(root+"population", population);
	save_ptree.put(root+"unresolved.land_id", land->GetId());
}

void Planet::LoadDataUniquePlanet(const boost::property_tree::ptree& ptree)
{
	//race_id = SaveManager::Instance().Get<int>(root+"race_id");
	population = ptree.get<int>("population");	
	data_unresolved_Planet.land_id = ptree.get<int>("unresolved.land_id");
}

void Planet::ResolveDataUniquePlanet()
{
	BindLand((Kosmoport*)EntityManager::Instance().GetEntityById(data_unresolved_Planet.land_id));	
	((StarSystem*)EntityManager::Instance().GetEntityById(data_unresolved_BaseSpaceEntity.starsystem_id))->Add(this, parent, data_unresolved_BasePlanet.orbit_it); 
}
	
void Planet::SaveData(boost::property_tree::ptree& save_ptree) const		
{
	std::string root = "planet." + int2str(GetId())+".";
	SaveDataUniqueBase(save_ptree, root);
	SaveDataUniqueBaseSpaceEntity(save_ptree, root);
	SaveDataUniqueBasePlanet(save_ptree, root);
	SaveDataUniquePlanet(save_ptree, root);
}

void Planet::LoadData(const boost::property_tree::ptree& load_ptree)
{
	LoadDataUniqueBase(load_ptree);
	LoadDataUniqueBaseSpaceEntity(load_ptree);
	LoadDataUniqueBasePlanet(load_ptree);
	LoadDataUniquePlanet(load_ptree);
}

void Planet::ResolveData()
{
	ResolveDataUniqueBase();
	ResolveDataUniqueBaseSpaceEntity();
	ResolveDataUniqueBasePlanet();
	ResolveDataUniquePlanet();
}	
