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

namespace ceti {

class InfoTable : public std::vector<std::pair<std::string, std::string>>
{
public:
    InfoTable() = default;
    ~InfoTable() = default;

    void add(const std::string&);
    void add(const std::string&, const std::string&);
    void add(const std::string&, int);
    void add(const std::string&, int_t);
    void add(const std::string&, float);
    void add(const std::string&, const glm::vec3&);
    void add(const std::string&, const std::vector<int_t>&);

    std::string str() const;
    std::string diff(const InfoTable&) const;

private:
    ceti::pack<std::string> __keys() const;
    std::string __getValue(const std::string& key) const;
};

} // namespace ceti

