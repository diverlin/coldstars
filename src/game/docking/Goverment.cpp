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


#include "Goverment.hpp"
#include "Kosmoport.hpp"
#include "../common/constants.hpp"
#include "../common/myStr.hpp"
#include "../world/EntityManager.hpp"

Goverment::Goverment(int id)
:
textureOb_face(nullptr)
{
	SetId(id);
	SetTypeId(TYPE::ENTITY::GOVERMENT_ID);
}

Goverment::~Goverment()
{}


void Goverment::SaveDataUniqueGoverment(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
	//save_ptree.put(root+"unresolved.angar_id",     angar->GetId());

}

void Goverment::LoadDataUniqueGoverment(const boost::property_tree::ptree& load_ptree)
{
	//data_unresolved_Kosmoport.angar_id = load_ptree.get<int>("unresolved.angar_id");
}

void Goverment::ResolveDataUniqueGoverment()
{
	((Kosmoport*)EntityManager::Instance().GetEntityById(data_unresolved_Room.owner_kosmoport_id))->BindGoverment(this); 
}

void Goverment::SaveData(boost::property_tree::ptree& save_ptree) const
{
	std::string root = "goverment." + int2str(GetId())+".";
	SaveDataUniqueBase(save_ptree, root);
	SaveDataUniqueRoom(save_ptree, root);
	SaveDataUniqueGoverment(save_ptree, root);
}

void Goverment::LoadData(const boost::property_tree::ptree& load_ptree)
{
	LoadDataUniqueBase(load_ptree);
	LoadDataUniqueRoom(load_ptree);
	LoadDataUniqueGoverment(load_ptree);
}

void Goverment::ResolveData()
{
	ResolveDataUniqueBase();
	ResolveDataUniqueRoom();
	ResolveDataUniqueGoverment();
}

