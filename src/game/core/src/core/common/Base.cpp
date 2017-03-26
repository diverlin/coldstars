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
#include <ceti/StringUtils.hpp>

#include <ceti/serialization/macro.hpp>

namespace model {

Base::Base(const std::string& data)
{
    MACRO_READ_SERIALIZED_DATA
}

std::string
Base::data() const
{
    MACRO_SAVE_SERIALIZED_DATA
}

//std::string Base::typeInfo() const
//{
//    std::string text;
//    text += "id = (" + std::to_string(id());
//    text += " | " + to_string(type());
//    text += " | " + to_string(subtype());
//    text += " | " + to_string(subsubtype()) + " )";
//    return text;
//}


} // namespace model

namespace control {

Base::Base(model::Base* model)
    :
      m_model_base(model)
{}

Base::~Base()
{}

//void Base::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
//{
//    LOG(" Base("+std::to_string(id())+")::SaveDataUniqueBase");
    
////    save_ptree.put(root+"data_id.id",            m_data_id.id);
////    save_ptree.put(root+"data_id.type_id",       static_cast<int>(m_data_id.type_id));
////    save_ptree.put(root+"data_id.subtype_id",    static_cast<int>(m_data_id.subtype_id));
////    save_ptree.put(root+"data_id.subsubtype_id", static_cast<int>(m_data_id.subsubtype_id));
//}

//void Base::LoadData(const boost::property_tree::ptree& load_ptree)
//{
//    LOG(" Base("+std::to_string(id())+")::LoadDataUniqueBase");
    
////    m_data_id.id              = load_ptree.get<unsigned long int>("data_id.id");
////    m_data_id.type_id         = (entity::Type)load_ptree.get<int>("data_id.type_id");
////    m_data_id.subtype_id      = (entity::Type)load_ptree.get<int>("data_id.subtype_id");
////    m_data_id.subsubtype_id   = (entity::Type)load_ptree.get<int>("data_id.subsubtype_id");
//}

//void Base::ResolveData()
//{
//    LOG(" Base("+std::to_string(id())+")::ResolveDataUniqueBase");
//}

} // namespace control


//namespace core {

//Base::Base()
//{}

///*virtual*/
//Base::~Base()
//{
//    LOG("___::~Base("+std::to_string(id())+")");
//}

//std::string Base::dataTypeStr() const
//{
//    std::string text;
//    text += "id = (" + std::to_string(id());
//    text += " | " + str(type());
//    text += " | " + str(subtype());
//    text += " | " + str(subsubtype()) + " )";
//    return text;
//}

//void Base::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
//{
//    LOG(" Base("+std::to_string(id())+")::SaveDataUniqueBase");

////    save_ptree.put(root+"data_id.id",            m_data_id.id);
////    save_ptree.put(root+"data_id.type_id",       static_cast<int>(m_data_id.type_id));
////    save_ptree.put(root+"data_id.subtype_id",    static_cast<int>(m_data_id.subtype_id));
////    save_ptree.put(root+"data_id.subsubtype_id", static_cast<int>(m_data_id.subsubtype_id));
//}

//void Base::LoadData(const boost::property_tree::ptree& load_ptree)
//{
//    LOG(" Base("+std::to_string(id())+")::LoadDataUniqueBase");

////    m_data_id.id              = load_ptree.get<unsigned long int>("data_id.id");
////    m_data_id.type_id         = (entity::Type)load_ptree.get<int>("data_id.type_id");
////    m_data_id.subtype_id      = (entity::Type)load_ptree.get<int>("data_id.subtype_id");
////    m_data_id.subsubtype_id   = (entity::Type)load_ptree.get<int>("data_id.subsubtype_id");
//}

//void Base::ResolveData()
//{
//    LOG(" Base("+std::to_string(id())+")::ResolveDataUniqueBase");
//}

//} // namespace core
