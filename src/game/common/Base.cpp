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

#include "Base.hpp"
#include "Logger.hpp" 
#include "myStr.hpp"

Base::Base()
{}

/*virtual*/
Base::~Base()
{
    #if CREATEDESTROY_LOG_ENABLED == 1
    Logger::Instance().Log("___::~Base("+int2str(GetId())+")");
    #endif
}

std::string Base::GetDataTypeString() const
{
    std::string str;
    str += "id=" + int2str(GetId());
    str += "/t=" + getEntityTypeStr(GetTypeId());
    str += "/st=" + getEntityTypeStr(GetSubTypeId());    
    str += "/sst=" + getEntityTypeStr(GetSubSubTypeId());    
    return str;
}

void Base::SaveDataUniqueBase(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" Base("+int2str(GetId())+")::SaveDataUniqueBase", SAVELOAD_LOG_DIP);
    #endif
    
    save_ptree.put(root+"data_id.id",            m_Data_id.id);
    save_ptree.put(root+"data_id.type_id",       (int)m_Data_id.type_id);
    save_ptree.put(root+"data_id.subtype_id",    (int)m_Data_id.subtype_id);
    save_ptree.put(root+"data_id.subsubtype_id", (int)m_Data_id.subsubtype_id);
}

void Base::LoadDataUniqueBase(const boost::property_tree::ptree& load_ptree)
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" Base("+int2str(GetId())+")::LoadDataUniqueBase", SAVELOAD_LOG_DIP);
    #endif
    
    m_Data_id.id              = load_ptree.get<unsigned long int>("data_id.id");
    m_Data_id.type_id         = (TYPE::ENTITY)load_ptree.get<int>("data_id.type_id");
    m_Data_id.subtype_id      = (TYPE::ENTITY)load_ptree.get<int>("data_id.subtype_id");
    m_Data_id.subsubtype_id   = (TYPE::ENTITY)load_ptree.get<int>("data_id.subsubtype_id");
}

void Base::ResolveDataUniqueBase()
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" Base("+int2str(GetId())+")::ResolveDataUniqueBase", SAVELOAD_LOG_DIP);
    #endif
}
