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

#include <iomanip>
#include <algorithm>
#include <sstream>

namespace ceti {

std::string to_string(float val, int digits)
{
    std::ostringstream out;
    out << std::setprecision(digits) << std::fixed << val;
    return out.str();
}

std::string
to_string(const glm::vec2& v, int digits)
{
    std::ostringstream out;
    out << std::setprecision(digits) << std::fixed;
    out << "(" << v.x << ", " << v.y << ")";
    return out.str();
}

std::string
to_string(const glm::vec3& v, int digits)
{
    std::ostringstream out;
    out << std::setprecision(digits) << std::fixed;
    out << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return out.str();
}

std::string to_string(const std::vector<int_t>& ids)
{
    std::string result;
    for (int_t id: ids) {
        result += std::to_string(id) + ",";
    }
    return result;
}

std::string to_string(const pack<int>& data)
{
    std::string result;
    for (int id: data) {
        result += std::to_string(id) + ",";
    }
    return result;
}

std::string to_string(const std::string& label, const std::vector<int_t>& ids)
{
    std::string result = label;
    for (int_t id: ids) {
        result += std::to_string(id) + ",";
    }
    return result;
}

int to_int(const std::string& val)
{
    return std::atoi(val.c_str());
}

bool to_bool(const std::string& val)
{
    return bool(std::atoi(val.c_str()));
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

std::string replace(const std::string& src, const std::string& from, const std::string& to)
{
    std::string result(src);

    const auto it = result.find(from);
    if (it != result.npos) {
        result.replace(it, from.size(), to);
    }
    return result;
}

void remove_whitespaces(std::string& str) {
    if (str.empty()) {
        return;
    }
    str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
}

void trim_char(std::string& str, const char& dirty) {
    if (str.empty()) {
        return;
    }
    if (str[0] == dirty) {
        str = str.substr(1, str.size()-1);
    }
    if (str[str.size()-1] == dirty) {
        str.erase(str.end()-1);
    }
}

void remove_whitespaces(std::vector<std::string>& v) {
    for(std::string& element: v) {
        remove_whitespaces(element);
    }
}

std::string get_nested(const std::string& str, const char& open, const char& close) {
    unsigned long begin = str.find_first_of(open);
    unsigned long end = str.find_last_of(close);
    if ((begin == str.npos) && (end != str.npos)) {
        std::cout<<"corrupted fragment=["<<str<<"] , the "<<open<<" not found"<<std::endl;
        assert(false);
    }
    if ((begin != str.npos) && (end == str.npos)) {
        std::cout<<"corrupted fragment=["<<str<<"] , the "<<close<<" not found"<<std::endl;
        assert(false);
    }
    if ((begin == str.npos) && (end == str.npos)) {
        return "";
    }
    begin++;
    unsigned long size = end - begin;
    return str.substr(begin, size);
}


} // namespace ceti
