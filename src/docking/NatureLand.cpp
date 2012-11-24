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

#include "NatureLand.hpp"
#include "../spaceobjects/Vehicle.hpp"
#include "../common/constants.hpp"
#include "../common/myStr.hpp"
#include "../resources/TextureManager.hpp"

NatureLand::NatureLand(int id)
{
	data_id.id = id;
	data_id.type_id = ENTITY::NATURELAND_ID;
}

/* virtual */
NatureLand::~NatureLand()
{}


//// ******* TRANSITION ******* 
/* virtual */
bool NatureLand::AddVehicle(Vehicle* vehicle)
{
       	vehicle->SetPlaceTypeId(data_id.type_id); 
       	vehicle->SetLand(this);
       	
        VEHICLE_vec.push_back(vehicle);
        
        if (vehicle->GetStarSystem() == NULL) // used if vehicle added directly after creation
        {
                vehicle->SetStarSystem(owner->GetStarSystem());
        }
        return true;
}

/*virtual */
bool NatureLand::RemoveVehicle(Vehicle* vehicle)
{       
        for (unsigned int i=0; i<VEHICLE_vec.size(); i++) 
        {
                if (VEHICLE_vec[i]->GetId() == vehicle->GetId())
                {
                        VEHICLE_vec.erase(VEHICLE_vec.begin() + i);
                        return true;
                }
        }
        
        return false;
}


/* virtual */
bool NatureLand::GetPermissionToLand() const
{
       	return true;
}

/* virtual */
void NatureLand::UpdateInSpaceInStatic()
{
        //for (unsigned int i = 0; i < NPC_vec.size(); i++)
        //{
           	//NPC_vec[i]->ThinkCommon_inLand_inStatic();      
	//}
}  

/*virtual*/
void NatureLand::SaveData(boost::property_tree::ptree& save_ptree) const
{
	const std::string root = "natureland."+int2str(data_id.id)+".";
        SaveDataUniqueBase(save_ptree, root);
	SaveDataUniqueBaseLand(save_ptree, root);
	SaveDataUniqueNatureLand(save_ptree, root);
}

/*virtual*/
void NatureLand::LoadData(const boost::property_tree::ptree& load_ptree)
{
        LoadDataUniqueBase(load_ptree);
	LoadDataUniqueBaseLand(load_ptree);
	LoadDataUniqueNatureLand(load_ptree);
}

/*virtual*/
void NatureLand::ResolveData()
{
        ResolveDataUniqueBase();
	ResolveDataUniqueBaseLand();
	ResolveDataUniqueNatureLand();
}


void NatureLand::SaveDataUniqueNatureLand(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
	save_ptree.put(root+"data_unresolved_NatureLand.textureOb_background_path", owner->GetId());
}

void NatureLand::LoadDataUniqueNatureLand(const boost::property_tree::ptree& load_ptree)
{
	data_unresolved_NatureLand.textureOb_background_path = load_ptree.get<int>("data_unresolved_NatureLand.textureOb_background_path");
}

void NatureLand::ResolveDataUniqueNatureLand()
{
	textureOb_background = TextureManager::Instance().GetTextureObByPath(data_unresolved_NatureLand.textureOb_background_path);
}
