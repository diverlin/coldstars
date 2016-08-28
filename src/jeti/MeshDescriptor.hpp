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

#include <ceti/descriptor/Base.hpp>

#include <glm/glm.hpp>

#include <string>

namespace jeti {

namespace descriptor {

class Mesh /*: public ceti::descriptor::Base*/
{
public:
    Mesh(int type, const std::string& model, const std::string& texture = "", const glm::vec3& orientation = glm::vec3(1.0, 0.0, 0.0)):
        m_type(type)
      , m_model(model)
      , m_texture(texture)
      , m_orientation(orientation)
    {
        m_id = -1;
    }
    virtual ~Mesh() {}

    int id() const { return m_id; }
    const std::string& fname() const { return m_model; }
    int type() const { return m_type; }
    const glm::vec3& orientation() const { return m_orientation; }

private:
    int m_id = -1;
    int m_type = -1;
    std::string m_model = "";
    std::string m_texture = "";
    glm::vec3 m_orientation = glm::vec3(1.0, 0.0, 0.0);

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        //ar & boost::serialization::base_object<Base>(*this);
        ar & m_id;
        ar & m_type;
        ar & m_model;
        ar & m_texture;
        ar & m_orientation.x;
        ar & m_orientation.y;
        ar & m_orientation.z;
    }
};

} // namespace descriptor

} // namespace jeti
