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

#include "BaseComplex.hpp"

#include <vector>

namespace core {
namespace control {
class Vehicle;
} // namespace control
} // namespace core

namespace slot {
class ItemSlot;
} // namespace slot

namespace core {
namespace complex {

class Protector : public Base
{
public:
    Protector(core::control::Vehicle*);
    ~Protector();

    void addProtectorSlot(slot::ItemSlot* slot) { m_protectorSlots.push_back(slot); }

    std::vector<slot::ItemSlot*> protectorSlots() const { return m_protectorSlots; }

private:
    std::vector<slot::ItemSlot*> m_protectorSlots;
};

} // namepsace complex
} // namespace core
