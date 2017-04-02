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

//#include "Base.hpp"
#include <core/type/TelegramType.hpp>

#include <ceti/type/IdType.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

namespace descriptor {
namespace comm {

class Dock
{
public:
    Dock(int_t, int_t);
    Dock(const std::string& data);
    ~Dock() = default;
    std::string data() const;

    int_t object() const { return m_object; }
    int_t dock() const { return m_dock; }

    std::string info() const {
        std::string result = "descriptor::comm::DockShip:\n";
        result += std::string(" object = ") + std::to_string(m_object) + "\n";
        result += std::string(" dock = ") + std::to_string(m_dock) + "\n";
        return result;
    }

private:
    int_t m_object = NONE;
    int_t m_dock = NONE;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & m_object;
        ar & m_dock;
    }
};

} // namespace comm
} // namespace descriptor


