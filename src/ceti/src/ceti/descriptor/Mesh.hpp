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
    Mesh()=default;

//    Mesh(int_t type,
//         const std::string& path,
//         const std::string& materialPath = "",
//         const meti::vec3& orientation = DEFAULT_DIRECTION);

    ~Mesh()=default;

    void setModelPath(const std::string& model_path) { m_modelPath = model_path; }
    void setMaterialPath(const std::string& material_path) { m_materialPath = material_path; }
    void setOrientation(const meti::vec3& orientation) { m_orientation = orientation; }

    const std::string& modelPath() const { return m_modelPath; }
    const std::string& materialPath() const { return m_materialPath; }
    const glm::vec3& orientation() const { return m_orientation; }

private:
    std::string m_modelPath = "";
    std::string m_materialPath = "";
    meti::vec3 m_orientation = meti::OY;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<Base>(*this);
        ar & m_modelPath;
        ar & m_materialPath;
        ar & m_orientation;
    }
};

} // namespace descriptor
} // namespace ceti
