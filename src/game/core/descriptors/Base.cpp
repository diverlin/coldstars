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

#include <sstream>

namespace descriptor {

// const
std::string Base::KEY_TYPE = "type";
std::string Base::KEY_RACE = "race";
std::string Base::KEY_DAMAGE = "damage";
std::string Base::KEY_RADIUS = "radius";
std::string Base::KEY_TECH = "tech";
std::string Base::KEY_MODULES_NUM = "modules_num";
std::string Base::KEY_MASS = "mass";
std::string Base::KEY_CONDITION_MAX = "condition_max";
std::string Base::KEY_DETERIORATION = "deterioration";
std::string Base::KEY_FUEL_MAX = "fuel_max";
std::string Base::KEY_SPEED = "speed";
std::string Base::KEY_HYPER = "hyper";
std::string Base::KEY_REPAIR = "repair";
std::string Base::KEY_STRENGTH = "strength";
std::string Base::KEY_SCAN = "scan";
std::string Base::KEY_PROTECTION = "protection";
std::string Base::KEY_PRICE = "price";
// dynamic
std::string Base::KEY_ID = "id";
std::string Base::KEY_OWNER = "owner";
std::string Base::KEY_CHILD = "child";
std::string Base::KEY_TARGET = "target";

std::string keyStr(const Key& key) {
    switch(key) {
    // const
    case Key::TYPE: return Base::KEY_TYPE; break;
    case Key::RACE: return Base::KEY_RACE; break;
    case Key::DAMAGE: return Base::KEY_DAMAGE; break;
    case Key::RADIUS: return Base::KEY_RADIUS; break;
    case Key::TECH: return Base::KEY_TECH; break;
    case Key::MODULES_NUM: return Base::KEY_MODULES_NUM; break;
    case Key::MASS: return Base::KEY_MASS; break;
    case Key::CONDITION_MAX: return Base::KEY_CONDITION_MAX; break;
    case Key::DETERIORATION: return Base::KEY_DETERIORATION; break;
    case Key::FUEL_MAX: return Base::KEY_FUEL_MAX; break;
    case Key::SPEED: return Base::KEY_SPEED; break;
    case Key::HYPER: return Base::KEY_HYPER; break;
    case Key::REPAIR: return Base::KEY_REPAIR; break;
    case Key::STRENGTH: return Base::KEY_STRENGTH; break;
    case Key::SCAN: return Base::KEY_SCAN; break;
    case Key::PROTECTION: return Base::KEY_PROTECTION; break;
    case Key::PRICE: return Base::KEY_PRICE; break;
// dynamic
    case Key::ID: return Base::KEY_ID; break;
    case Key::OWNER: return Base::KEY_OWNER; break;
    case Key::CHILD: return Base::KEY_CHILD; break;
    case Key::TARGET: return Base::KEY_TARGET; break;

    default: throw std::runtime_error("ERROR: fixme: unknown descriptor key"); break;
    }
}

std::string typeStr(const Type& type) {
    switch(type) {
    case Type::HIT: return "Type::HIT"; break;
    case Type::CONTAINER: return "Type::CONTAINER"; break;
    case Type::BOMB: return "Type::BOMB"; break;
    case Type::STARSYSTEM: return "Type::STARSYSTEM"; break;
    case Type::BAK: return "Type::BAK"; break;
    case Type::DRIVE: return "Type::DRIVE"; break;
    case Type::DROID: return "Type::DROID"; break;
    case Type::GRAPPLE: return "Type::GRAPPLE"; break;
    case Type::SCANER: return "Type::SCANER"; break;
    case Type::RADAR: return "Type::RADAR"; break;
    case Type::PROTECTOR: return "Type::PROTECTOR"; break;
    default: throw std::runtime_error("ERROR: fixme: unknown descriptor key"); break;
    }
}

Base::Base()
{
}

Base::Base(const std::map<Key, int_type>& map)
    : m_map(map)
{
}

Base::Base(const std::string& data)
{
    std::stringstream ss;
    ss << data;
    boost::archive::text_iarchive ia(ss);
    ia >> *this;
}

Base::~Base()
{
}

std::string
Base::data() const
{
    std::stringstream ss;
    boost::archive::text_oarchive oa(ss);
    oa << *this;
    return ss.str();
}

void
Base::add(const Key& key, const int_type& value)
{
    auto f = m_map.find(key);
    if (f == m_map.end()) {
        m_map.insert(std::make_pair(key, value));
    } else {
        throw std::runtime_error("CODE ERROR: " + keyStr(key) + " is already existed in descriptor");
    }
}

const int_type&
Base::id() const
{
    return get(Key::ID);
}

const int_type&
Base::type() const
{
    return get(Key::TYPE);
}

const int_type&
Base::race() const
{
    return get(Key::RACE);
}

const int_type&
Base::owner() const
{
    return get(Key::OWNER);
}

const int_type&
Base::child() const
{
    return get(Key::CHILD);
}

const int_type&
Base::target() const
{
    return get(Key::TARGET);
}

const int_type&
Base::damage() const
{
    return get(Key::DAMAGE);
}

const int_type&
Base::radius() const
{
    return get(Key::RADIUS);
}

const int_type&
Base::tech() const
{
    return get(Key::TECH);
}

const int_type&
Base::modulesNum() const
{
    return get(Key::MODULES_NUM);
}

const int_type&
Base::mass() const
{
    return get(Key::MASS);
}

const int_type&
Base::conditionMax() const
{
    return get(Key::CONDITION_MAX);
}

const int_type&
Base::deterioration() const
{
    return get(Key::DETERIORATION);
}

const int_type&
Base::fuelMax() const
{
    return get(Key::FUEL_MAX);
}

const int_type&
Base::speed() const
{
    return get(Key::SPEED);
}

const int_type&
Base::hyper() const
{
    return get(Key::HYPER);
}

const int_type&
Base::repair() const
{
    return get(Key::REPAIR);
}

const int_type&
Base::strength() const
{
    return get(Key::STRENGTH);
}

const int_type&
Base::scan() const
{
    return get(Key::SCAN);
}

const int_type&
Base::protection() const
{
    return get(Key::PROTECTION);
}

const int_type&
Base::price() const
{
    return get(Key::PRICE);
}


bool
Base::operator==(const Base& rhs) const
{
    return data() == rhs.data();
}

const int_type&
Base::get(const Key& key) const
{
    auto f = m_map.find(key);
    if (f != m_map.end()) {
        return f->second;
    }
    throw std::runtime_error("CODE ERROR: " + keyStr(key) + " is not found in descriptor");
}

} // namespace descriptor

