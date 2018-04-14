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

#include "Equipment.hpp"


namespace descriptor {
namespace item {
class Bak;
} // namespace item
} // namespace descriptor

namespace model {
namespace item {
class Bak;
} // namespace item
} // namespace model

namespace core {
namespace control {
namespace item {

class Bak : public Equipment
{
public:
    Bak(descriptor::item::Bak*, model::item::Bak*);
    virtual ~Bak() = default;

    void increaseFuel(int fuel);
    int fuelMiss() const;

public:
    descriptor::item::Bak* descriptor() const { return m_descriptor_bak; }
    model::item::Bak* model() const { return m_model_bak; }

private:
    void updateProperties() override final;

private:
    int m_fuelMax_add = 0;
    int m_fuelMax = 0;

    descriptor::item::Bak* m_descriptor_bak = nullptr;
    model::item::Bak* m_model_bak = nullptr;

    void virtual addUniqueInfo();
    std::string fuelStr();
};

} // namespace item
} // namespace control
} // namespace core

