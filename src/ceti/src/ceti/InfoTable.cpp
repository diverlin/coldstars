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

#include "InfoTable.hpp"

#include <ceti/StringUtils.hpp>
#include <ceti/Pack.hpp>


namespace ceti {

void InfoTable::add(const std::string& label)
{
    push_back(std::make_pair(label, ""));
}

void InfoTable::add(const std::string& label, const std::string& value)
{
    push_back(std::make_pair(label, value));
}

void InfoTable::add(const std::string& label, int value)
{
    add(label, std::to_string(value));
}

void InfoTable::add(const std::string& label, int_t value)
{
    add(label, std::to_string(value));
}

void InfoTable::add(const std::string& label, float value)
{
    add(label, ceti::to_string(value));
}

void InfoTable::add(const std::string& label, const glm::vec3& value)
{
    add(label, ceti::to_string(value));
}

void InfoTable::add(const std::string& label, const std::vector<int_t>& value)
{
    add(label, ceti::to_string(value));
}

std::string InfoTable::toString() const {
    std::string result;
    for (const auto& p: *this) {
        result += p.first + ":" + p.second + ";";
    }
    return result;
}

std::string
InfoTable::__getValue(const std::string& key) const {
    assert(key.size()>0);
    for (const auto& p: *this) {
        if (p.first == key) {
            return p.second;
        }
    }
    return "key absent";
}

ceti::pack<std::string> InfoTable::__keys() const
{
    ceti::pack<std::string> keys;
    for (const auto& p: *this) {
        keys.add(p.first);
    }
    return keys;
}

std::string InfoTable::diff(const InfoTable& other) const {
    std::string result = "";
    ceti::pack<std::string> keys = __keys().unite(other.__keys());

    for (const std::string& key: keys) {
        std::string value1 = __getValue(key);
        std::string value2 = other.__getValue(key);
        if (value1 != value2) {
            result += "key="+ key + ": value1=" + value1 + " vs value2=" + value2 +"\n";
        }
    }

    return result;
}

} // namespace ceti
