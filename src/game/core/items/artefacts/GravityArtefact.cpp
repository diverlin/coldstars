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

#include "GravityArtefact.hpp"
#include "../../common/constants.hpp"
//#include <ceti/StringUtils.hpp>
#include <ceti/Logger.hpp>

GravityArtefact::GravityArtefact(int id)
:
gravity(0)
{
    setId(id);
    setTypeId(TYPE::ENTITY::ARTEFACT_ID);
    setSubTypeId(TYPE::ENTITY::GRAVITY_ARTEFACT_ID);
}

/* virtual */
GravityArtefact::~GravityArtefact ()
{}

/* virtual */
void GravityArtefact::AddUniqueInfo()
{
//    info.addTitleStr("gravity artefact");
//    info.addNameStr("gravity:");      info.addValueStr( std::to_string(gravity) );
}

/* virtual */
void GravityArtefact::AddCommonInfo()
{
//    info.addNameStr("mass:");      info.addValueStr( std::to_string(data_item.mass) );
}

/* virtual */
void GravityArtefact::Save(boost::property_tree::ptree& save_ptree) const
{
    std::string root = "gravity_artefact." + std::to_string(id()) + ".";
    Base::SaveData(save_ptree, root);
    BaseItem::SaveData(save_ptree, root);
    GravityArtefact::SaveData(save_ptree, root);
}

/* virtual */
void GravityArtefact::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
    BaseItem::LoadData(load_ptree);
    GravityArtefact::LoadData(load_ptree);
}

/* virtual */
void GravityArtefact::Resolve()
{
    Base::ResolveData();
    BaseItem::ResolveData();
    GravityArtefact::ResolveData();
}        
        
void GravityArtefact::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    LOG(" GravityArtefact::SaveData()  id=" + std::to_string(id()) + " START");
    
    save_ptree.put(root+"gravity", gravity); 
}

void GravityArtefact::LoadData(const boost::property_tree::ptree& load_ptree)
{
    LOG(" GravityArtefact::LoadData()  id=" + std::to_string(id()) + " START");
    
    gravity = load_ptree.get<int>("gravity");
}

void GravityArtefact::ResolveData()
{
    LOG(" GravityArtefact::ResolveData()  id=" + std::to_string(id()) + " START");
}
