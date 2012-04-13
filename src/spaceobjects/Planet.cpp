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


Planet::Planet(int id)
{    
	data_id.id = id;
	data_id.type_id = ENTITY::PLANET_ID;
	
	//textureOb_atmosphere = _textureOb_atmoshere;
	population  = 0;      	
	land = NULL;
}


Planet::~Planet()
{
	delete land;
}

int Planet::GetDockingRadius() const { return data_planet.scale; }


void Planet::Update_inSpace(int time, bool show_effect)
{      
	UpdateRotation();
	if (time > 0)
	{
		orbit->UpdatePosition();  
		if (parent == NULL)
		{
			points.setCenter(orbit->GetPosition());
		}
		else
		{
			points.setCenter(parent->GetPoints().getCenter() + orbit->GetPosition());
		}
	}
}

void Planet::Update_inSpace_inStatic()
{}

void Planet::UpdateInfo()
{
	info.clear();

	info.addTitleStr("PLANET");
	info.addNameStr("id/ss_id:");    info.addValueStr(int2str(data_id.id) + " / " + int2str(starsystem->GetId()));
	info.addNameStr("population:");  info.addValueStr(int2str(population));
}

void Planet::renderInfo_inSpace(vec2f scroll_coords)
{  
	UpdateInfo();
	drawInfoIn2Column(&info.title_list, &info.value_list, points.getCenter().x, points.getCenter().y, scroll_coords.x, scroll_coords.y);
}

void Planet::PostDeathUniqueEvent(bool)
{}

void Planet::SaveDataUniquePlanet(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
	//SaveManager::Instance().Put(root+"race_id", race_id);
	save_ptree.put(root+"population", population);
	//if (land) SaveManager::Instance().Put(root+"land_id", land->GetId());
	//else      SaveManager::Instance().Put(root+"land_id", -1);
}

void Planet::LoadDataUniquePlanet(const boost::property_tree::ptree& ptree)
{
	//race_id = SaveManager::Instance().Get<int>(root+"race_id");
	population = ptree.get<int>("population");
}

void Planet::ResolveDataUniquePlanet()
{}
	
void Planet::SaveData(boost::property_tree::ptree& save_ptree) const		
{
	std::string root = "planet." + int2str(GetId())+".";
	SaveDataUniqueBase(save_ptree, root);
	SaveDataUniqueBaseGameEntity(save_ptree, root);
	SaveDataUniqueBasePlanet(save_ptree, root);
	SaveDataUniquePlanet(save_ptree, root);
}

void Planet::LoadData(boost::property_tree::ptree& load_ptree)
{
	LoadDataUniqueBase(load_ptree);
	LoadDataUniqueBaseGameEntity(load_ptree);
	LoadDataUniqueBasePlanet(load_ptree);
	LoadDataUniquePlanet(load_ptree);
}

void Planet::ResolveData()
{
	ResolveDataUniqueBase();
	ResolveDataUniqueBaseGameEntity();
	ResolveDataUniqueBasePlanet();
	ResolveDataUniquePlanet();
}	
