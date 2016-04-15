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

std::string Base::KEY_ID = "id";
std::string Base::KEY_TYPE = "type";
std::string Base::KEY_RACE = "race";
std::string Base::KEY_OWNER = "owner";
std::string Base::KEY_CHILD = "child";
std::string Base::KEY_TARGET = "target";
std::string Base::KEY_DAMAGE = "damage";
std::string Base::KEY_RADIUS = "radius";
std::string Base::KEY_TECH = "tech";
std::string Base::KEY_MODULES_NUM = "modules";
std::string Base::KEY_MASS = "mass";
std::string Base::KEY_CONDITION = "condition";
std::string Base::KEY_DETEORATION = "deteoration";
std::string Base::KEY_FUEL = "fuel";
std::string Base::KEY_SPEED = "speed";
std::string Base::KEY_HYPER = "hyper";
std::string Base::KEY_REPAIR = "repair";
std::string Base::KEY_STRENGTH = "strength";
std::string Base::KEY_SCAN = "scan";
std::string Base::KEY_PROTECTION = "protection";

Base::Base()
{
}

Base::Base(const std::map<std::string, int_type>& map)
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
Base::add(const std::string& key, const int_type& value)
{
    auto f = m_map.find(key);
    if (f == m_map.end()) {
        m_map.insert(std::make_pair(key, value));
    } else {
        throw std::runtime_error("CODE ERROR: " + key + " is already existed in descriptor");
    }
}

const int_type&
Base::id() const
{
    return get(KEY_ID);
}

const int_type&
Base::type() const
{
    return get(KEY_TYPE);
}

const int_type&
Base::race() const
{
    return get(KEY_RACE);
}

const int_type&
Base::owner() const
{
    return get(KEY_OWNER);
}

const int_type&
Base::child() const
{
    return get(KEY_CHILD);
}

const int_type&
Base::target() const
{
    return get(KEY_TARGET);
}

const int_type&
Base::damage() const
{
    return get(KEY_DAMAGE);
}

const int_type&
Base::radius() const
{
    return get(KEY_RADIUS);
}

const int_type&
Base::tech() const
{
    return get(KEY_TECH);
}

const int_type&
Base::modules() const
{
    return get(KEY_MODULES_NUM);
}

const int_type&
Base::mass() const
{
    return get(KEY_MASS);
}

const int_type&
Base::condition() const
{
    return get(KEY_CONDITION);
}

const int_type&
Base::deteoration() const
{
    return get(KEY_DETEORATION);
}

const int_type&
Base::fuel() const
{
    return get(KEY_FUEL);
}

const int_type&
Base::speed() const
{
    return get(KEY_SPEED);
}

const int_type&
Base::hyper() const
{
    return get(KEY_HYPER);
}

const int_type&
Base::repair() const
{
    return get(KEY_REPAIR);
}

const int_type&
Base::strength() const
{
    return get(KEY_STRENGTH);
}

const int_type&
Base::scan() const
{
    return get(KEY_SCAN);
}

const int_type&
Base::protection() const
{
    return get(KEY_PROTECTION);
}

bool
Base::operator==(const Base& rhs) const
{
    return data() == rhs.data();
}

const int_type&
Base::get(const std::string& key) const
{
    auto f = m_map.find(key);
    if (f != m_map.end()) {
        return f->second;
    }
    throw std::runtime_error("CODE ERROR: " + key + " is not found in descriptor");
}

} // namespace descriptor

