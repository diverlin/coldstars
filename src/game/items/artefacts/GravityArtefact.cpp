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
#include <ceti/myStr.hpp>
#include "../../common/Logger.hpp"

GravityArtefact::GravityArtefact(int id)
:
gravity(0)
{
    SetId(id);
    SetTypeId(TYPE::ENTITY::ARTEFACT_ID);
    SetSubTypeId(TYPE::ENTITY::GRAVITY_ARTEFACT_ID);
}

/* virtual */
GravityArtefact::~GravityArtefact ()
{}

/* virtual */
void GravityArtefact::AddUniqueInfo()
{
    info.addTitleStr("gravity artefact");
    info.addNameStr("gravity:");      info.addValueStr( ceti::int2str(gravity) );
}

/* virtual */
void GravityArtefact::AddCommonInfo()
{
    info.addNameStr("mass:");      info.addValueStr( ceti::int2str(data_item.mass) );
}

/* virtual */
void GravityArtefact::Save(boost::property_tree::ptree& save_ptree) const
{
    std::string root = "gravity_artefact." + ceti::int2str(GetId()) + ".";
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
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" GravityArtefact::SaveData()  id=" + ceti::int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
    #endif
    
    save_ptree.put(root+"gravity", gravity); 
}

void GravityArtefact::LoadData(const boost::property_tree::ptree& load_ptree)
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" GravityArtefact::LoadData()  id=" + ceti::int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
    #endif
    
    gravity = load_ptree.get<int>("gravity");
}

void GravityArtefact::ResolveData()
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" GravityArtefact::ResolveData()  id=" + ceti::int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
    #endif
}
