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
//#include <ceti/StringUtils.hpp>
#include <ceti/Logger.hpp>

ProtectorArtefact::ProtectorArtefact(int id)
:
protection(0)
{
    setId(id);
    setTypeId(TYPE::ENTITY::ARTEFACT_ID);
    setSubTypeId(TYPE::ENTITY::PROTECTOR_ARTEFACT_ID);
}

/* virtual */
ProtectorArtefact::~ProtectorArtefact ()
{}

/* virtual */
void ProtectorArtefact::AddUniqueInfo()
{
//    info.addTitleStr("protector artefact");
//    info.addNameStr("protection:");      info.addValueStr( std::to_string(protection) );
}

/* virtual */
void ProtectorArtefact::AddCommonInfo()
{
//    info.addNameStr("mass:");      info.addValueStr( std::to_string(data_item.mass) );
}

/* virtual */
void ProtectorArtefact::Save(boost::property_tree::ptree& save_ptree) const
{
    std::string root = "protector_artefact." + std::to_string(id()) + ".";
   
    Base::SaveData(save_ptree, root);
    BaseItem::SaveData(save_ptree, root);
    ProtectorArtefact::SaveData(save_ptree, root);
}

/* virtual */
void ProtectorArtefact::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
    BaseItem::LoadData(load_ptree);
    ProtectorArtefact::LoadData(load_ptree);
}

/* virtual */
void ProtectorArtefact::Resolve()
{
    Base::ResolveData();
    BaseItem::ResolveData();
    ProtectorArtefact::ResolveData();
}        
        
void ProtectorArtefact::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    Logger::Instance().Log(" ProtectorArtefact::SaveData()  id=" + std::to_string(id()) + " START", SAVELOAD_LOG_DIP);
    
    save_ptree.put(root+"protection", protection); 
}

void ProtectorArtefact::LoadData(const boost::property_tree::ptree& load_ptree)
{
    Logger::Instance().Log(" ProtectorArtefact::LoadData()  id=" + std::to_string(id()) + " START", SAVELOAD_LOG_DIP);
    
    protection = load_ptree.get<int>("protection");
}

void ProtectorArtefact::ResolveData()
{
    Logger::Instance().Log(" ProtectorArtefact::ResolveData()  id=" + std::to_string(id()) + " START", SAVELOAD_LOG_DIP);
}
