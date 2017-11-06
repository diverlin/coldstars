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

namespace descriptor {
class Item;
} // namespace descriptor

namespace model {
class Item;
} // namespace model

namespace slot {
class Item;
} // namespace slot


namespace control {

class Item : public Base
{
public:
    Item(descriptor::Item*, model::Item*);
    virtual ~Item() = default;

    descriptor::Item* descriptor() const { return m_descriptor_item; }
    model::Item* model() const { return m_model_item; }
    slot::Item* slot() const { return m_slot; }

    void setSlot(slot::Item* slot)  { m_slot = slot; }

    bool isDamaged() const;
    bool isLocked() const;
    int isFunctioning() const;

    void useNormalDeterioration();
    void useOverloadDeterioration();

    void corrupt();
    void deteriorate();
    void lock(int lock = 1);
    void unlock();
    bool repair();

    virtual void updateProperties() {}
    virtual void updateInStatic() { _updateLock(); }

protected:
    void _updateLock();

private:
    descriptor::Item* m_descriptor_item = nullptr;
    model::Item* m_model_item = nullptr;

    slot::Item* m_slot = nullptr;
};

} // namespace control
