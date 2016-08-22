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

#pragma once

#include <types/IdType.hpp>

#include <common/IdGenerator.hpp>

#include <boost/serialization/map.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include <string>

namespace ceti {
namespace descriptor {


struct Id {
    Id(int c, const std::string& n)
        :
          code(c)
        , name(n)
    {}
    Id(const Id& id)
        :
          code(id.code)
        , name(id.name)
    {}
    int code = 0;
    std::string name = "";
};

class Property : public Id {
public:
    enum {INT, STR};

    Property(const Id& id, const int_type& value)
        :
          Id(id)
        , valueType(INT)
        , intValue(value)
    {}
    Property(const Id& id, const std::string& value)
        :
          Id(id)
        , valueType(STR)
        , strValue(value)
    {}
    int valueType;
    int_type intValue = 0;
    std::string strValue = "";
};

class Base
{
public:
    Base(/*const id_type&, bool generate_id = true*/);
    Base(const std::string& data);
    ~Base();

    std::string data() const;

    bool operator==(const Base& rhs) const;

    const int_type& get(int) const;

    void add(const Property&);
    void add(const std::vector<Property>&);

    std::string info() const;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & m_type;
        ar & m_intValues;
        if (!m_strValues.empty()) {
            ar & m_strValues;
        }
    }

    id_type m_type = -1;
    std::map<int, int_type> m_intValues;
    std::map<int, std::string> m_strValues;
    static IdGenerator m_idGenerator; // ?

public:
    static std::map<int, Property> m_ids;
};

//class Base
//{
//public:
//    Base() {
//        m_id = m_idGenerator.nextId();
//    }
//    virtual ~Base() {}

//    const id_type& id() const { return m_id; }

//    virtual std::string info() const {
//        std::string result;
//        result += std::string("id=") + std::to_string(m_id);
//        return result;
//    }

//private:
//    friend class boost::serialization::access;
//    template<class Archive>
//    void serialize(Archive & ar, const unsigned int version) {
//        ar & m_id;
//    }

//private:
//    id_type m_id = -1;

//    static IdGenerator m_idGenerator;
//};

} // namespace descriptor
} // namespace ceti
