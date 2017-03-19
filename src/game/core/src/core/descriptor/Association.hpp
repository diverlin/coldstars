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

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include <string>

namespace descriptor {

class Association {
public:
    Association()
    {}

public:
    void setRace(const std::string& race) { m_race = race; }
//    void setType(const std::string& type) { m_type = type; }
//    void setSubtype(const std::string& subtype) { m_subtype = subtype; }
    void setName(const std::string& name) { m_name = name; }
    void setColor(const std::string& color) { m_color = color; }

//    const std::string& type() const { return m_type; }

private:
    std::string m_race = "";
//    std::string m_type = "";
//    std::string m_subtype = "";
    std::string m_name = "";
    std::string m_color = "";

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & m_race;
//        ar & m_type;
//        ar & m_subtype;
        ar & m_name;
        ar & m_color;
    }
};

} // namespace descriptor
