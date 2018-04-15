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

namespace core {

class AssociationDescr {
public:
    AssociationDescr()
    {}

public:
    void setRaceStr(const std::string& race) { m_raceStr = race; }
    void setTypeStr(const std::string& type) { m_typeStr = type; }
    void setSubTypeStr(const std::string& subtype) { m_subtypeStr = subtype; }
    void setNameStr(const std::string& name) { m_nameStr = name; }
    void setColorStr(const std::string& color) { m_colorStr = color; }

    const std::string& typeStr() const { return m_typeStr; }

private:
    std::string m_raceStr = "";
    std::string m_typeStr = "";
    std::string m_subtypeStr = "";
    std::string m_nameStr = "";
    std::string m_colorStr = "";

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & m_raceStr;
        ar & m_typeStr;
        ar & m_subtypeStr;
        ar & m_nameStr;
        ar & m_colorStr;
    }
};

} // namespace core
