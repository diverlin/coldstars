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
#include <ceti/Logger.hpp>
#include <ceti/myStr.hpp>

Base::Base()
    :
      m_mesh_id(0),
      m_texture_id(0)
{}

/*virtual*/
Base::~Base()
{
    #if CREATEDESTROY_LOG_ENABLED == 1
    Logger::Instance().Log("___::~Base("+std::to_string(id())+")");
    #endif
}

std::string Base::dataTypeString() const
{
    std::string str;
    str += "id=" + std::to_string(id());
    str += "/t=" + getStr(typeId());
    str += "/st=" + getStr(subTypeId());
    str += "/sst=" + getStr(subSubTypeId());
    return str;
}

void Base::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" Base("+std::to_string(id())+")::SaveDataUniqueBase", SAVELOAD_LOG_DIP);
    #endif
    
    save_ptree.put(root+"data_id.id",            m_data_id.id);
    save_ptree.put(root+"data_id.type_id",       static_cast<int>(m_data_id.type_id));
    save_ptree.put(root+"data_id.subtype_id",    static_cast<int>(m_data_id.subtype_id));
    save_ptree.put(root+"data_id.subsubtype_id", static_cast<int>(m_data_id.subsubtype_id));
}

void Base::LoadData(const boost::property_tree::ptree& load_ptree)
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" Base("+std::to_string(id())+")::LoadDataUniqueBase", SAVELOAD_LOG_DIP);
    #endif
    
    m_data_id.id              = load_ptree.get<unsigned long int>("data_id.id");
    m_data_id.type_id         = (TYPE::ENTITY)load_ptree.get<int>("data_id.type_id");
    m_data_id.subtype_id      = (TYPE::ENTITY)load_ptree.get<int>("data_id.subtype_id");
    m_data_id.subsubtype_id   = (TYPE::ENTITY)load_ptree.get<int>("data_id.subsubtype_id");
}

void Base::ResolveData()
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" Base("+std::to_string(id())+")::ResolveDataUniqueBase", SAVELOAD_LOG_DIP);
    #endif
}
