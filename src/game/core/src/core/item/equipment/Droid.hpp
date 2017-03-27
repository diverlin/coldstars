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
class Droid;
} // namespace item
} // namespace descriptor

namespace model {
namespace item {
class Droid;
} // namespace item
} // namespace model

namespace control {
namespace item {

class Droid : public Equipment
{
public:
    Droid(model::item::Droid*, descriptor::item::Droid*);
    virtual ~Droid() = default;

    model::item::Droid* model() const { return m_model_droid; }
    descriptor::item::Droid* descriptor() const { return m_descriptor_droid; }

private:
    virtual void updateProperties();
    virtual void updateInStatic();

private:
    int m_repair_add = 0;

    model::item::Droid* m_model_droid = nullptr;
    descriptor::item::Droid* m_descriptor_droid = nullptr;

    void virtual addUniqueInfo();
    std::string GetRepairStr();
};

} // namespace item
} // namespace control
