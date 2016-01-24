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

#include <map>
#include <string>
#include <boost/serialization/map.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class Descriptor
{
public:
    static std::string KEY_ID;
    static std::string KEY_OWNER;
    static std::string KEY_TARGET;
    static std::string KEY_DAMAGE;
    static std::string KEY_RADIUS;

    std::map<std::string, std::string> map;

    Descriptor(const std::map<std::string, std::string>&);
    Descriptor(const std::string& data);
    ~Descriptor() {}

    std::string data() const;

    bool operator==(const Descriptor& rhs) const;

    id_type id() const;
    id_type owner() const;
    id_type target() const;
    int damage() const;
    int radius() const;

private:
    const std::string& get_raw(const std::string& key) const;
    template<class var_type>
    var_type get(const std::string& key) const
    {
        std::istringstream ss(get_raw(key));
        var_type value;
        ss >> value;
        std::cout << "get key=" << key <<"value=" << value;
        return value;
    }


private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & map;
    }
}; 
