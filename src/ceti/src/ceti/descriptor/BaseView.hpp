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

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

namespace ceti {
namespace descriptor {

class BaseView
{
public:
    BaseView() = default;
    ~BaseView() = default;

    int_t texture() const { return m_texture; }
    int_t mesh() const { return m_mesh; }

    void setTexture(int_t texture) { m_texture = texture; }
    void setMesh(int_t mesh) { m_mesh = mesh; }

    std::string info() const {
        std::string result = "ceti::descriptor::BaseView:\n";
        result += std::string(" texture = ") + std::to_string(m_texture) + "\n";
        result += std::string(" mesh = ") + std::to_string(m_mesh) + "\n";
        return result;
    }

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & m_texture;
        ar & m_mesh;
    }

private:
    int_t m_texture = NONE;
    int_t m_mesh = NONE;
};

} // namespace descriptor
} // namespace ceti
