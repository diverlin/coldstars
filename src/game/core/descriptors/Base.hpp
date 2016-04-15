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

#include <boost/serialization/map.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include <map>
#include <string>

namespace descriptor {

class Base
{
public:
    enum class Type: int {
        HIT,
        CONTAINER,
        BOMB,
        STARSYSTEM,
        BAK,
        DRIVE,
        DROID,
        GRAPPLE,
        SCANER,
        RADAR,
        PROTECTOR
    };

    static std::string KEY_ID;
    static std::string KEY_TYPE;
    static std::string KEY_RACE;
    static std::string KEY_OWNER;
    static std::string KEY_CHILD;
    static std::string KEY_TARGET;
    static std::string KEY_DAMAGE;
    static std::string KEY_RADIUS;

    static std::string KEY_TECH;
    static std::string KEY_MODULES_NUM;
    static std::string KEY_MASS;
    static std::string KEY_CONDITION;
    static std::string KEY_DETEORATION;
    static std::string KEY_FUEL;
    static std::string KEY_SPEED;
    static std::string KEY_HYPER;
    static std::string KEY_REPAIR;
    static std::string KEY_STRENGTH;
    static std::string KEY_SCAN;
    static std::string KEY_PROTECTION;

    Base();
    Base(const std::map<std::string, std::string>&);
    Base(const std::string& data);
    ~Base();

    std::string data() const;

    bool operator==(const Base& rhs) const;

    id_type id() const;
    int type() const;
    int race() const;
    id_type owner() const;
    id_type child() const;
    id_type target() const;
    int damage() const;
    int radius() const;
    int tech() const;
    int modules() const;
    int mass() const;
    int condition() const;
    int deteoration() const;
    int fuel() const;
    int speed() const;
    int hyper() const;
    int repair() const;
    int strength() const;
    int scan() const;
    int protection() const;

public: // todo make it protected
    void add(const std::string& key, const std::string& value);

private:
    const std::string& get_raw(const std::string& key) const;
    template<class var_type>
    var_type get(const std::string& key) const
    {
        std::istringstream ss(get_raw(key));
        var_type value;
        ss >> value;
        //std::cout << "get key=" << key <<" value=" << value << std::endl;
        return value;
    }

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & m_map;
    }

    std::map<std::string, std::string> m_map;
}; 

} // namespace descriptor
