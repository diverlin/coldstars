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

#include "Land.hpp"

#include <ceti/Pack.hpp>

namespace model {

class NatureLandModel : public LandModel
{
public:
    NatureLandModel(int_t);
    ~NatureLandModel() = default;
    NatureLandModel(const std::string& data);
    std::string data() const;

    const ceti::pack<int_t>& items() const { return m_items; }
    const ceti::pack<int_t>& vehicles() const { return m_vehicles; }

    void addItem(int_t id) { m_items.add(id); }
    void addVehicle(int_t id) { m_vehicles.add(id); }

    void removeItem(int_t id) { m_items.remove(id); }
    void removeVehicle(int_t id) { m_vehicles.remove(id); }

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<LandModel>(*this);
        ar & m_items;
        ar & m_vehicles;
    }

private:
    ceti::pack<int_t> m_items;
    ceti::pack<int_t> m_vehicles;
};

} // namespace model
