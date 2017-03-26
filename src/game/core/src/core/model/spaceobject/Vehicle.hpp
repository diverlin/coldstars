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

#include <core/spaceobject/SpaceObject.hpp>

namespace model {

class Vehicle : public SpaceObject {
public:
    Vehicle()=default;
    ~Vehicle() = default;

    int_t npc() const { return m_npc; }
    int_t dock() const { return m_dock; }
    [[warning("do we need this? using dock will be sufficient probably")]]
    int_t land() const { return m_land; }

    void addItem(int_t id) { if (_isWritable()) m_items.push_back(id); }
    std::vector<int_t> items() const { return m_items; }

private:
    int_t m_npc = NONE;
    int_t m_dock = NONE;
    int_t m_land = NONE;

    std::vector<int_t> m_items;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<SpaceObject>(*this);
        ar & m_npc;
        ar & m_dock;
        ar & m_land;
        ar & m_items;
    }
};

} // namespace model

