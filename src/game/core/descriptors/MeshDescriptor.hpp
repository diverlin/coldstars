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

#include <descriptors/Base.hpp>

#include <types/IdType.hpp>
#include <types/MeshTypes.hpp>

#include <glm/glm.hpp>

#include <string>

namespace descriptor {

class Mesh : public BBase
{
public:
    Mesh(const std::string fname, const type::mesh& type, const glm::vec3& orientation = glm::vec3(1.0, 0.0, 0.0), const id_type& texture = -1):
        m_fname(fname)
      , m_type(type)
      , m_orientation(orientation)
      , m_texture(texture)
    {}
    ~Mesh() {}

    const std::string& fname() const { return m_fname; }
    const type::mesh& type() const { return m_type; }
    const glm::vec3& orientation() const { return m_orientation; }

private:
    std::string m_fname = "";
    glm::vec3 m_orientation = glm::vec3(1.0, 0.0, 0.0);
    type::mesh m_type;
    id_type m_texture = -1;
};

} // namespace descriptor


