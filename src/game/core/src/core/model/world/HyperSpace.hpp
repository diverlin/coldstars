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

#include <core/model/Base.hpp>

#include <ceti/Pack.hpp>

namespace model {

class HyperSpaceModel : public BaseModel
{
public:
    HyperSpaceModel(int_t, int_t ob_id = NONE);
    ~HyperSpaceModel() = default;
    HyperSpaceModel(const std::string& data);
    std::string data() const;

    void addVehicle(int_t ship) { if (_isWritable()) m_vehicles.add(ship); }

    void removeVehicle(int_t id) { m_vehicles.remove(id); }

    ceti::pack<int_t> vehicles() const { return m_vehicles; }

    ceti::InfoTable info() const override final {
        ceti::InfoTable result;
        result.add("model::HyperSpace");
        result.add("vehicles", m_vehicles);
        return result;
    }

private:
    ceti::pack<int_t> m_vehicles;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<BaseModel>(*this);
        ar & m_vehicles;
    }
};

} // namespace model

