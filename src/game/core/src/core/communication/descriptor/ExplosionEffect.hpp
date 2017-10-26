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
#include <ceti/StringUtils.hpp>

#include <meti/VectorUtils.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

namespace descriptor {
namespace comm {
namespace effect {

class Explosion
{
public:
    Explosion(float, const glm::vec3&);
    Explosion(const std::string& data);
    ~Explosion() = default;
    std::string data() const;

    float size() const { return m_size; }
    const meti::vec3& position() const { return m_position; }

    std::string info() const {
        std::string result = "descriptor::comm::effect::Explosion:\n";
        result += std::string(" size = ") + std::to_string(m_size) + "\n";
        result += std::string(" position = ") + ceti::to_string(m_position) + "\n";
        return result;
    }

private:
    float m_size = 0.0f;
    meti::vec3 m_position;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & m_size;
        ar & m_position;
    }
};

} // namespace effect
} // namespace comm
} // namespace descriptor


