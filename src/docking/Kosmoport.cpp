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


Kosmoport :: Kosmoport(int id) 
{
	data_id.id = id;
	data_id.type_id = ENTITY::KOSMOPORT_ID;
	race_id = RACE::R0_ID;
	
	angar     = NULL;
        store     = NULL;
        shop      = NULL;
        goverment = NULL;
}

/* virtual */
Kosmoport :: ~Kosmoport()
{}
           
/* virtual */
bool Kosmoport::GetPermissionToLand() const
{
      	if (angar->GetFreeVehicleSlotTotalNum() > 0) 
        { 
        	return true; 
        }
        
        return false;
}
                
/* virtual */
bool Kosmoport::Add(Vehicle* vehicle)
{
        vehicle->SetPlaceTypeId(data_id.type_id);
                
        VEHICLE_vec.push_back(vehicle);
        angar->AddVehicle(vehicle);
        
        return true;
}

/* virtual */
bool Kosmoport::Add(Npc* npc)
{
        npc->SetPlaceTypeId(data_id.type_id);
        NPC_vec.push_back(npc);
        
        npc->SetLand(this);
 
        return true;
}

/* virtual */
bool Kosmoport::Remove(Vehicle* vehicle)
{
        bool is_removed_from_list = false;
        for (unsigned int i = 0; i < VEHICLE_vec.size(); i++)
        { 
                if (VEHICLE_vec[i] == vehicle)
                {
                        VEHICLE_vec.erase(VEHICLE_vec.begin() + i);
                        is_removed_from_list = true;
                }
        }
        
        bool is_removed_from_landing_area = angar->RemoveVehicle(vehicle); 
    
        if (is_removed_from_list && is_removed_from_landing_area)
                return true;
        else
                return false;
}

/* virtual */
bool Kosmoport::Remove(Npc* npc)
{
        bool is_removed = false;
        for (unsigned int i = 0; i < NPC_vec.size(); i++)
        { 
                if (NPC_vec[i] == npc)
                {
                        NPC_vec.erase(NPC_vec.begin() + i);
                        is_removed = true;
                }
        }
    
        return is_removed;
}

/* virtual */
void Kosmoport::Ai()
{
        for (unsigned int i = 0; i < NPC_vec.size(); i++)
        {
                NPC_vec[i]->ThinkCommon_inKosmoport_inStatic();
	}
}




void Kosmoport::SaveDataUniqueKosmoport(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
	save_ptree.put(root+"unresolved.angar_id",     angar->GetId());
	save_ptree.put(root+"unresolved.store_id",     store->GetId());
        save_ptree.put(root+"unresolved.shop_id",      shop->GetId());
	save_ptree.put(root+"unresolved.goverment_id", goverment->GetId());
}

void Kosmoport::LoadDataUniqueKosmoport(const boost::property_tree::ptree& load_ptree)
{
	data_unresolved_Kosmoport.angar_id = load_ptree.get<int>("unresolved.angar_id");
	data_unresolved_Kosmoport.store_id = load_ptree.get<int>("unresolved.store_id");
	data_unresolved_Kosmoport.shop_id = load_ptree.get<int>("unresolved.shop_id");
	data_unresolved_Kosmoport.goverment_id = load_ptree.get<int>("unresolved.goverment_id");
}

void Kosmoport::ResolveDataUniqueKosmoport()
{
	SetAngar( (Angar*)EntityManager::Instance().GetEntityById(data_unresolved_Kosmoport.angar_id) ); 
	SetStore( (Store*)EntityManager::Instance().GetEntityById(data_unresolved_Kosmoport.store_id) ); 
	SetShop( (Shop*)EntityManager::Instance().GetEntityById(data_unresolved_Kosmoport.shop_id) ); 
	SetGoverment( (Goverment*)EntityManager::Instance().GetEntityById(data_unresolved_Kosmoport.goverment_id) ); 
}


void Kosmoport::SaveData(boost::property_tree::ptree& save_ptree) const
{
	std::string root = "kosmoport." + int2str(GetId())+".";
	SaveDataUniqueBase(save_ptree, root);
	SaveDataUniqueBaseLand(save_ptree, root);
	SaveDataUniqueKosmoport(save_ptree, root);
}

void Kosmoport::LoadData(const boost::property_tree::ptree& load_ptree)
{
	LoadDataUniqueBase(load_ptree);
	LoadDataUniqueBaseLand(load_ptree);
	LoadDataUniqueKosmoport(load_ptree);
}

void Kosmoport::ResolveData()
{
	ResolveDataUniqueBase();
	ResolveDataUniqueBaseLand();
	ResolveDataUniqueKosmoport();
}
