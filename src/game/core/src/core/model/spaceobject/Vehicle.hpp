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

#include <ceti/Pack.hpp>

namespace core {

class VehicleModel : public SpaceObjectModel {
public:
    VehicleModel() = default;
    VehicleModel(int_t, int_t);
    VehicleModel(const std::string& data);
    ~VehicleModel() override = default;
    std::string data() const override;

    int_t npc() const { return m_npc; }
    int_t dock() const { return m_dock; }
    [[warning("do we need this? using dock will be sufficient probably")]]
    int_t land() const { return m_land; }

    void addItem(int_t id) { if (_isWritable()) m_items.add(id); }
    void removeItem(int_t id) { if (_isWritable()) m_items.remove(id); }

    const ceti::pack<int_t>& items() const { return m_items; }

    ceti::InfoTable info() const override {
        ceti::InfoTable result = SpaceObjectModel::info();
        result.add("Vehicle");
        result.add("npc", m_npc);
        result.add("dock", m_dock);
        result.add("land", m_land);
        result.add("items", m_items);
        return result;
    }

private:
    int_t m_npc = NONE;
    int_t m_dock = NONE;
    int_t m_land = NONE;

    ceti::pack<int_t> m_items;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        UNUSED(version)
        ar & boost::serialization::base_object<SpaceObjectModel>(*this);
        ar & m_npc;
        ar & m_dock;
        ar & m_land;
        ar & m_items;
    }
};

} // namespace core

