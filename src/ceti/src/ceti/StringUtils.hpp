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

#include <ceti/type/IdType.hpp>
#include <ceti/Pack.hpp>

#include <glm/glm.hpp>

#include <string>
#include <vector>

namespace {
const int STRING_FLOAT_PRECISION = 2;
}

namespace ceti {

std::string to_string(const glm::vec2&, int digits = STRING_FLOAT_PRECISION);
std::string to_string(const glm::vec3&, int digits = STRING_FLOAT_PRECISION);
std::string to_string(float, int digits = STRING_FLOAT_PRECISION);
std::string to_string(const std::vector<int_t>&);
std::string to_string(const pack<int>&);
std::string to_string(const std::string& label, const std::vector<int_t>& ids);

int to_int(const std::string&);
bool to_bool(const std::string&);

std::vector<std::string> split(const std::string& to_string, const std::string& delim);
std::string join(const std::vector<std::string>& v, const std::string& delim);
std::string replace(const std::string&, const std::string&, const std::string&);
void strip(std::string&);
void superstrip(std::string&, const char&);
void strip(std::vector<std::string>&);

std::string get_nested(const std::string& str, const char* open="{", const char* close="}");

} // namespace ceti
