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


SpaceStation::SpaceStation(int id)
{      
	data_id.id = id;
	data_id.type_id = ENTITY::VEHICLE_ID;
	data_id.subtype_id = ENTITY::SPACESTATION_ID;  
	
    	mass = getRandInt(ENTITY::SPACESTATION::MASS_MIN, ENTITY::SPACESTATION::MASS_MAX);
	land = NULL;
}

SpaceStation::~SpaceStation() 
{
	delete land;
}    
 
void SpaceStation::BindLand(BaseLand* land)       		
{
	this->land = land;
	this->land->SetOwner(this);
}
       	
void SpaceStation::UpdateInSpace(int time, bool show_effect)
{
	CheckDeath(show_effect);
	if (time > 0)
	{}
}

//overriding
void SpaceStation::UpdateInfo()
{
	info.clear();

    	info.addTitleStr("StarBase" + int2str(data_id.subtype_id));

    	info.addNameStr("id/ss_id:");    info.addValueStr(int2str(data_id.id) + " / " + int2str(starsystem->GetId()));
    	info.addNameStr("id:");          info.addValueStr(int2str(data_id.id));
    	info.addNameStr("mass:");        info.addValueStr(int2str(mass));
} 

void SpaceStation::UpdateRenderStuff()
{
    	//points.update(); 
    	protection_complex->GetShieldEffect()->Update();
    	
    	//if (ableTo.DRIVE == true)
    	//{
       		//drive_trail->update();
    	//}
}

void SpaceStation::RenderInSpace() const
{   
        //if (ableTo.GRAB == true)
        //{
                //renderGrappleTrail();
        //}
        
    	RenderKorpus();
    	
    	if (data_korpus.draw_turrels == true)
    	{
        	weapon_complex->RenderTurrels();
        }

    	//if (ableTo.DRIVE == true)
    	//{
		//renderDriveTrail();
    	//}
    	
    	if (ableTo.PROTECT == true)
    	{
        	RenderShield(); 
        }
}

void SpaceStation::RenderAtPlanet() const
{
	//renderKorpus();
	
	//if (data_korpus.render_TURRELS == true)
    	//{
        	//weapon_complex->renderTurrels();
        //}
}		



/*virtual*/
void SpaceStation::SaveData(boost::property_tree::ptree& save_ptree) const
{
	const std::string root = "spacestation."+int2str(data_id.id)+".";
        SaveDataUniqueBase(save_ptree, root);
	SaveDataUniqueBaseGameEntity(save_ptree, root);
	SaveDataUniqueVehicle(save_ptree, root);
	SaveDataUniqueSpaceStation(save_ptree, root);
}

/*virtual*/
void SpaceStation::LoadData(const boost::property_tree::ptree& load_ptree)
{
        LoadDataUniqueBase(load_ptree);
	LoadDataUniqueBaseGameEntity(load_ptree);
	LoadDataUniqueVehicle(load_ptree);
	LoadDataUniqueSpaceStation(load_ptree);
}

/*virtual*/
void SpaceStation::ResolveData()
{
        ResolveDataUniqueBase();
	ResolveDataUniqueBaseGameEntity();
	ResolveDataUniqueVehicle();
	ResolveDataUniqueSpaceStation();
}

void SpaceStation::SaveDataUniqueSpaceStation(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
	save_ptree.put(root+"unresolved.land_id", land->GetId());
}

void SpaceStation::LoadDataUniqueSpaceStation(const boost::property_tree::ptree& load_ptree)
{
	data_unresolved_SpaceStation.land_id = load_ptree.get<int>("unresolved.land_id");
}

void SpaceStation::ResolveDataUniqueSpaceStation()
{
        SpaceStationBuilder::Instance().CreateKorpusGeometry(this);
        SpaceStationBuilder::Instance().CreateKorpusGui(this);
        
        SpaceStationBuilder::Instance().CreateProtectionComplex(this);
        SpaceStationBuilder::Instance().CreateDriveComplex(this);
        SpaceStationBuilder::Instance().CreateWeaponsComplex(this);        

	BindLand((Kosmoport*)EntityManager::Instance().GetEntityById(data_unresolved_SpaceStation.land_id));	                       
	((StarSystem*)EntityManager::Instance().GetEntityById(data_unresolved_BaseGameEntity.starsystem_id))->AddVehicle(this, data_unresolved_BaseGameEntity.center, data_unresolved_BaseGameEntity.angle, parent); 
}
