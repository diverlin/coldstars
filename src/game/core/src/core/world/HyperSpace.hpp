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

#include <core/Base.hpp>

#include <ceti/Pack.hpp>

namespace core {
class HyperSpaceDescr;
} // naemspace descriptor

namespace model {
class HyperSpaceModel;
} // naemspace model

namespace core {
namespace control {

class Vehicle;
//class Starsystem;

class HyperSpace : public Base
{
public:
    HyperSpace(HyperSpaceDescr*, model::HyperSpaceModel*);
    ~HyperSpace() = default;

    void add(Vehicle*);
    void remove(Vehicle*);

    const ceti::pack<Vehicle*>& vehicles() const { return m_vehicles; }

//    bool isHere(int) const;
//    void postHyperJumpEvent(Starsystem*);

//    int queueSize() const { return m_vehicles.size(); }

private:
    HyperSpaceDescr* m_descriptor_hyperspace = nullptr;
    model::HyperSpaceModel* m_model_hyperspace = nullptr;

    HyperSpaceDescr* descriptor() const { return m_descriptor_hyperspace; }
    model::HyperSpaceModel* model() const { return m_model_hyperspace; }

    ceti::pack<Vehicle*> m_vehicles;
};

} // namespace control
} // namespace core



