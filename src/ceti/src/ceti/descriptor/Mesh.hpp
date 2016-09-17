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

#include "Base.hpp"

#include <ceti/type/IdType.hpp>

#include <meti/VectorUtils.hpp>

#include <string>

namespace ceti {
namespace descriptor {

class Mesh : public Base
{
public:
    Mesh(int type,
         const std::string& model,
         const std::string& texture = "",
         const meti::vec3& orientation = meti::vec3(1.0, 0.0, 0.0));

    Mesh(const std::string& data);
    ~Mesh();

    std::string data() const;

    bool operator==(const Mesh& rhs) const;

    const std::string& model() const { return m_modelPath; }
    const std::string& texture() const { return m_texturePath; }
    const glm::vec3& orientation() const { return m_orientation; }

private:
    std::string m_modelPath = "";
    std::string m_texturePath = "";
    meti::vec3 m_orientation = meti::vec3(1.0, 0.0, 0.0);

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<Base>(*this);
        ar & m_modelPath;
        ar & m_texturePath;
        ar & m_orientation;
    }
};

} // namespace descriptor
} // namespace ceti
