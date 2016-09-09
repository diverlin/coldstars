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

#include <glm/glm.hpp>

#include <string>
#include <vector>

namespace ceti {

std::string to_string(const glm::vec3&);
std::string to_string(float);
std::string str(long long int);
std::string str(long int);
std::string str(int);
std::string str(bool);

std::vector<std::string> split(const std::string& str, const std::string& delim);
std::string join(const std::vector<std::string>& v, const std::string& delim);

} // namespace ceti
