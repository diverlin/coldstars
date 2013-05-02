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
#include "../docking/BaseLand.hpp"
#include "../effects/Atmosphere.hpp"
#include "../common/constants.hpp"
#include "../world/EntityManager.hpp"
#include "../common/myStr.hpp"
#include "../resources/TextureManager.hpp"
#include "../world/starsystem.hpp"
#include "../render/Render.hpp"
#include "../resources/ShaderCollector.hpp"
#include "../docking/Kosmoport.hpp"
#include "../spaceobjects/Vehicle.hpp"

#include "../garbage/EntityGarbage.hpp"
#include "../common/Logger.hpp"

Planet::Planet(int id):atmosphere(NULL)
{    
	data_id.id = id;
	data_id.type_id = ENTITY::PLANET_ID;
	
	population  = 0;
		      	
	land = NULL;
}

/* virtual */
Planet::~Planet()
{
	#if CREATEDESTROY_LOG_ENABLED == 1
	Logger::Instance().Log("___::~Planet("+int2str(GetId())+")");
	#endif	
	
	delete atmosphere;
}

/* virtual */
void Planet::PutChildsToGarbage() const
{
	EntityGarbage::Instance().Add(land);
}

void Planet::BindAtmosphere(Atmosphere* atmosphere) 
{
	this->atmosphere = atmosphere; 
	atmosphere->SetParent(this);
}
		
void Planet::BindLand(BaseLand* land)
{
	this->land = land;
	this->land->SetOwner(this);
        SetSubTypeId(land->GetTypeId());
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
	if (time > 0)
	{
		UpdatePosition();
	}
}

void Planet::UpdateInSpaceInStatic()
{
	land->UpdateInStatic();
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

void Planet::Render_NEW(const Vec2<float>& scroll_coords)
{
	UpdateRenderAnimation();
	RenderMesh(scroll_coords);
	if (atmosphere != NULL)
	{
		atmosphere->Render(scroll_coords);
	}
}
	
void Planet::Render_OLD() const
{
	RenderMesh_OLD();	
}
	
void Planet::SaveDataUniquePlanet(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" Planet("+int2str(GetId())+")::SaveDataUniquePlanet", SAVELOAD_LOG_DIP);
	#endif
	
	//SaveManager::Instance().Put(root+"race_id", race_id);
	save_ptree.put(root+"population", population);
}

void Planet::LoadDataUniquePlanet(const boost::property_tree::ptree& load_ptree)
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" Planet("+int2str(GetId())+")::LoadDataUniquePlanet", SAVELOAD_LOG_DIP);
	#endif
	
	//race_id = SaveManager::Instance().Get<int>(root+"race_id");
	population = load_ptree.get<int>("population");	
}

void Planet::ResolveDataUniquePlanet()
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" Planet("+int2str(GetId())+")::ResolveDataUniquePlanet", SAVELOAD_LOG_DIP);
	#endif
	
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
