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

#include "StringUtils.hpp"

#include <sstream>

namespace ceti {

std::string to_string(const glm::vec3& v) {
    std::string result;
    result += "(";
    result += to_string(v.x);
    result += ",";
    result += to_string(v.y);
    result += ",";
    result += to_string(v.z);
    result += ")";
    return result;
}

std::string to_string(float val)
{
    std::ostringstream stream;
    stream<<val;
    return stream.str();
}

std::string str(long int val)
{
    return str((long long int)val);
}

std::string str(long long int val)
{
    std::ostringstream stm;
    if (val >= 0) {
        stm<<val;
        return stm.str();
    } else {
        stm<<abs(val);
        return "-"+stm.str();
    }
}

std::string str(int val)
{
    return str((long long int)val);
}


std::string str(bool var)
{
    std::ostringstream stm;
    if (var == true) {
        stm << "true";
    } else {
        stm << "false";
    }
    return stm.str() ;
}

std::vector<std::string> split(const std::string& str, const std::string& delim) {
    std::vector<std::string> v;
    std::string::size_type start = 0;
    auto pos = str.find_first_of(delim, start);
    while(pos != std::string::npos) {
        if(pos != start) // ignore empty tokens
            v.emplace_back(str, start, pos - start);
        start = pos + 1;
        pos = str.find_first_of(delim, start);
    }
    if(start < str.length()) // ignore trailing delimiter
        v.emplace_back(str, start, str.length() - start); // add what's left of the string
    return v;
}

std::string join(const std::vector<std::string>& v, const std::string& delim) {
    std::string str = "";
    for(auto& seg: v) {
        str += seg;
        if (seg != v.back()) {
            str += delim;
        }
    }
    return str;
}

} // namespace ceti
