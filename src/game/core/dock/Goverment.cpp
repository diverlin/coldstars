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

#include <common/Global.hpp>
#include <managers/EntityManager.hpp>

Goverment::Goverment(int id)
:
textureOb_face(nullptr)
{
    setId(id);
    setTypeId(type::entity::GOVERMENT_ID);
}

Goverment::~Goverment()
{}


void Goverment::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    //save_ptree.put(root+"unresolved.angar_id",     angar->id());

}

void Goverment::LoadData(const boost::property_tree::ptree& load_ptree)
{
    //data_unresolved_Kosmoport.angar_id = load_ptree.get<int>("unresolved.angar_id");
}

void Goverment::ResolveData()
{
    ((Kosmoport*)global::get().entityManager().getEntity(data_unresolved_Room.owner_kosmoport_id))->BindGoverment(this); 
}

void Goverment::Save(boost::property_tree::ptree& save_ptree) const
{
    std::string root = "goverment." + std::to_string(id())+".";
    
    Base::SaveData(save_ptree, root);
    Room::SaveData(save_ptree, root);
    Goverment::SaveData(save_ptree, root);
}

void Goverment::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
    Room::LoadData(load_ptree);
    Goverment::LoadData(load_ptree);
}

void Goverment::Resolve()
{
    Base::ResolveData();
    Room::ResolveData();
    Goverment::ResolveData();
}

