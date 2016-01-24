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

#include "Descriptor.hpp"

#include <sstream>

std::string Descriptor::KEY_ID = "id";
std::string Descriptor::KEY_OWNER = "owner";
std::string Descriptor::KEY_TARGET = "target";
std::string Descriptor::KEY_DAMAGE = "damage";
std::string Descriptor::KEY_RADIUS = "radius";

Descriptor::Descriptor(const std::map<std::string, std::string>& map)
    : map(map)
{

}

Descriptor::Descriptor(const std::string& data)
{
    std::stringstream ss;
    ss << data;
    boost::archive::text_iarchive ia(ss);
    ia >> *this;
}

std::string
Descriptor::data() const
{
    std::stringstream ss;
    boost::archive::text_oarchive oa(ss);
    oa << *this;
    return ss.str();
}

id_type
Descriptor::id() const
{
    return get<id_type>(KEY_ID);
}

id_type
Descriptor::owner() const
{
    return get<id_type>(KEY_OWNER);
}

id_type
Descriptor::target() const
{
    return get<id_type>(KEY_TARGET);
}

int
Descriptor::damage() const
{
    return get<int>(KEY_DAMAGE);
}

int
Descriptor::radius() const
{
    return get<int>(KEY_RADIUS);
}

bool
Descriptor::operator==(const Descriptor& rhs) const
{
    return data() == rhs.data();
}

const std::string&
Descriptor::get_raw(const std::string& key) const
{
    auto f = map.find(key);
    if (f != map.end()) {
        return f->second;
    }
    throw std::runtime_error("CODE ERROR: " + key + " is not found in descriptor");
}
    



