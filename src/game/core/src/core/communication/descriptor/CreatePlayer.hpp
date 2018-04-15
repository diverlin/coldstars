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

namespace core {

class CreatePlayerComDescr
{
public:
    CreatePlayerComDescr(int_t, int_t);
    CreatePlayerComDescr(const std::string& data);
    CreatePlayerComDescr() = default;
    ~CreatePlayerComDescr() = default;
    std::string data() const;

    int_t player() const { return m_player; }
    int_t npc() const { return m_npc; }

    std::string info() const {
        std::string result = "CreatePlayer:\n";
        result += std::string(" player = ") + std::to_string(m_player) + "\n";
        result += std::string(" npc = ") + std::to_string(m_npc) + "\n";
        return result;
    }

private:
    int_t m_player = NONE;
    int_t m_npc = NONE;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & m_player;
        ar & m_npc;
    }
};

} // namespace descriptor


