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

class CreateBullet
{
public:
    CreateBullet(int_t, int_t, int_t);
    CreateBullet(const std::string& data);
    ~CreateBullet() = default;
    std::string data() const;

    int_t owner() const { return m_owner; }
    int_t weapon() const { return m_item; }
    int_t target() const { return m_target; }

    std::string info() const {
        std::string result = "descriptor::comm::BulletShoot:\n";
        result += std::string(" owner = ") + std::to_string(m_owner) + "\n";
        result += std::string(" item = ") + std::to_string(m_item) + "\n";
        result += std::string(" target = ") + std::to_string(m_target) + "\n";
        return result;
    }

private:
    int_t m_owner = 0;
    int_t m_item = 0;
    int_t m_target = 0;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & m_owner;
        ar & m_item;
        ar & m_target;
    }
};

} // namespace comm
} // namespace descriptor


