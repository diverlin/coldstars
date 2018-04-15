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

namespace core {
class ItemDescr;
} // namespace core

namespace model {
class ItemModel;
} // namespace model

namespace core {

class ItemSlot;

namespace control {

class Item : public Base
{
public:
    Item(ItemDescr*, model::ItemModel*);
    virtual ~Item() = default;

    ItemDescr* descriptor() const { return m_descriptor_item; }
    model::ItemModel* model() const { return m_model_item; }
    ItemSlot* slot() const { return m_slot; }

    void setSlot(ItemSlot* slot)  { m_slot = slot; }

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
    ItemDescr* m_descriptor_item = nullptr;
    model::ItemModel* m_model_item = nullptr;

    ItemSlot* m_slot = nullptr;
};

} // namespace control
} // namespace core
