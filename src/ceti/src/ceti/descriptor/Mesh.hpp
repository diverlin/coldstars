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

#include <ceti/descriptor/Association.hpp>
#include <ceti/type/IdType.hpp>

#include <meti/VectorUtils.hpp>

#include <string>

namespace ceti {
namespace descriptor {

const meti::vec3 DEFAULT_DIRECTION = meti::vec3(0.0, 1.0, 0.0);

class Mesh : public Base
{
public:
    Mesh(int_t type = -1);

    Mesh(int_t type,
         const std::string& path,
         const std::string& materialPath = "",
         const meti::vec3& orientation = DEFAULT_DIRECTION);

    Mesh(const std::string& data);
    ~Mesh();

    std::string data() const;

    bool operator==(const Mesh& rhs) const;

    void setModelPath(const std::string& model_path) { m_modelPath = model_path; }
    void setMaterialPath(const std::string& material_path) { m_materialPath = material_path; }
    void setAssociation(const Association& association) { m_association = association; }

    const std::string& modelPath() const { return m_modelPath; }
    const std::string& materialPath() const { return m_materialPath; }
    const glm::vec3& orientation() const { return m_orientation; }

    const Association& association() const { return m_association; }

private:
    std::string m_modelPath = "";
    std::string m_materialPath = "";
    meti::vec3 m_orientation = DEFAULT_DIRECTION;

    Association m_association;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<Base>(*this);
        ar & m_modelPath;
        ar & m_materialPath;
        ar & m_orientation;
        ar & m_association;
    }
};

} // namespace descriptor
} // namespace ceti
