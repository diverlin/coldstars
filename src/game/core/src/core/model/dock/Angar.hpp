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

#include "Room.hpp"

#include <ceti/Pack.hpp>

namespace core {

class AngarModel : public RoomModel {
public:
    AngarModel(int_t);
    ~AngarModel() = default;
    AngarModel(const std::string& data);
    std::string data() const;

    void setFuelprice(int fuelPrice) { m_fuelPrice = fuelPrice; }

    void addWarrior(int_t id) { m_warriors.add(id); }
    void addGuest(int_t id) { m_guests.add(id); }
    void addItem(int_t id) { m_items.add(id); }

    void removeWarrior(int_t id) { m_warriors.remove(id); }
    void removeGuest(int_t id) { m_guests.remove(id); }
    void removeItem(int_t id) { m_items.remove(id); }

    int fuelprice() { return m_fuelPrice; }

    const ceti::pack<int_t>& warriors() const { return m_warriors; }
    const ceti::pack<int_t>& guests() const { return m_guests; }
    const ceti::pack<int_t>& items() const { return m_items; }

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<RoomModel>(*this);
    }

private:
    ceti::pack<int_t> m_warriors;
    ceti::pack<int_t> m_guests;
    ceti::pack<int_t> m_items;

    int m_fuelPrice = 0;
};

} // namespace model

