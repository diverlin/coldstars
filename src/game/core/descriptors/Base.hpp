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

enum class Key: int {
    // const
    TYPE,
    RACE,
    DAMAGE,
    RADIUS,
    TECH,
    MODULES_NUM,
    MASS,
    CONDITION_MAX,
    DETERIORATION,
    FUEL_MAX,
    SPEED,
    HYPER,
    REPAIR,
    STRENGTH,
    SCAN,
    PROTECTION,
    PRICE,
    // dynamic
    ID,
    OWNER,
    CHILD,
    TARGET
};

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

std::string keyStr(const Key&);
std::string typeStr(const Type&);

class Base
{
public:
    // const
    static std::string KEY_TYPE;
    static std::string KEY_TARGET;
    static std::string KEY_DAMAGE;
    static std::string KEY_RADIUS;
    static std::string KEY_TECH;
    static std::string KEY_MODULES_NUM;
    static std::string KEY_MASS;
    static std::string KEY_CONDITION_MAX;
    static std::string KEY_DETERIORATION;
    static std::string KEY_FUEL_MAX;
    static std::string KEY_SPEED;
    static std::string KEY_HYPER;
    static std::string KEY_REPAIR;
    static std::string KEY_STRENGTH;
    static std::string KEY_SCAN;
    static std::string KEY_PROTECTION;
    static std::string KEY_PRICE;
    // dynamic
    static std::string KEY_ID;
    static std::string KEY_RACE;
    static std::string KEY_OWNER;
    static std::string KEY_CHILD;

    Base();
    Base(const std::map<Key, int_type>&);
    Base(const std::string& data);
    ~Base();

    std::string data() const;

    bool operator==(const Base& rhs) const;

    const int_type& id() const;
    const int_type& type() const;
    const int_type& race() const;
    const int_type& owner() const;
    const int_type& child() const;
    const int_type& target() const;
    const int_type& damage() const;
    const int_type& radius() const;
    const int_type& tech() const;
    const int_type& modulesNum() const;
    const int_type& mass() const;
    const int_type& conditionMax() const;
    const int_type& deterioration() const;
    const int_type& fuelMax() const;
    const int_type& speed() const;
    const int_type& hyper() const;
    const int_type& repair() const;
    const int_type& strength() const;
    const int_type& scan() const;
    const int_type& protection() const;
    const int_type& price() const;

public: // todo make it protected
    void add(const Key& key, const int_type& value);

private:
    const int_type& get(const Key& key) const;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & m_map;
    }

    std::map<Key, int_type> m_map;
}; 

} // namespace descriptor
