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

#include "ProtectorArtefact.hpp"
#include "../../common/constants.hpp"
#include "../../common/myStr.hpp"
#include "../../common/Logger.hpp"

ProtectorArtefact::ProtectorArtefact(int id)
:
protection(0)
{
    SetId(id);
    SetTypeId(TYPE::ENTITY::ARTEFACT_ID);
    SetSubTypeId(TYPE::ENTITY::PROTECTOR_ARTEFACT_ID);
}

/* virtual */
ProtectorArtefact::~ProtectorArtefact ()
{}

/* virtual */
void ProtectorArtefact::AddUniqueInfo()
{
    info.addTitleStr("protector artefact");
    info.addNameStr("protection:");      info.addValueStr( int2str(protection) );
}

/* virtual */
void ProtectorArtefact::AddCommonInfo()
{
        info.addNameStr("mass:");      info.addValueStr( int2str(data_item.mass) );
}

/* virtual */
void ProtectorArtefact::Save(boost::property_tree::ptree& save_ptree) const
{
    std::string root = "protector_artefact." + int2str(GetId()) + ".";    
    Base::SaveData(save_ptree, root);
        BaseItem::SaveData(save_ptree, root);
    SaveDataUniqueProtectorArtefact(save_ptree, root);
}

/* virtual */
void ProtectorArtefact::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
        BaseItem::LoadData(load_ptree);
    LoadDataUniqueProtectorArtefact(load_ptree);
}

/* virtual */
void ProtectorArtefact::Load()
{
    Base::ResolveData();
        BaseItem::ResolveData();
    ResolveDataUniqueProtectorArtefact();
}        
        
void ProtectorArtefact::SaveDataUniqueProtectorArtefact(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" SaveDataUniqueProtectorArtefact()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
    #endif
    
        save_ptree.put(root+"protection", protection); 
}

void ProtectorArtefact::LoadDataUniqueProtectorArtefact(const boost::property_tree::ptree& load_ptree)
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" LoadDataUniqueProtectorArtefact()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
    #endif
    
    protection = load_ptree.get<int>("protection");
}

void ProtectorArtefact::ResolveDataUniqueProtectorArtefact()
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" ResolveDataUniqueProtectorArtefact()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
    #endif
}
