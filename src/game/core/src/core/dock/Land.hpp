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

#include <vector>
#include <string>

namespace descriptor {
class Land;
} // namespace descriptor

namespace model {
class Land;
} // namespace model

namespace control {

class SpaceObject;
class Vehicle;

class Land : public Base
{
public:
    Land(descriptor::Land*, model::Land*);
    virtual ~Land();

    void setOwner(SpaceObject* owner)  { m_owner = owner; }

    SpaceObject* owner() const { return m_owner; }
    virtual bool isAllowedToLand() const = 0;

    virtual bool add(Vehicle*) = 0;
    virtual bool remove(Vehicle*) = 0;
    virtual int shipsNum() const = 0;

    virtual void updateInStatic() = 0;

    virtual std::string vehiclesStr() const = 0;

    descriptor::Land* descriptor() const { return m_descriptor_land; }
    model::Land* model() const { return m_model_land; }

private:
    SpaceObject* m_owner = nullptr;

    descriptor::Land* m_descriptor_land = nullptr;
    model::Land* m_model_land = nullptr;

//    UnresolvedDataLand data_unresolved_Land;
//    void SaveData(boost::property_tree::ptree&, const std::string&) const;
//    void LoadData(const boost::property_tree::ptree&);
//    void ResolveData();
};

} // namespace control
