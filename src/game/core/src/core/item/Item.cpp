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


#include "Item.hpp"
#include <common/constants.hpp>

#include <core/common/Global.hpp>

#include <core/slot/ItemSlot.hpp>

#include <core/descriptor/item/Item.hpp>
#include <core/model/item/Item.hpp>

#include <ceti/Logger.hpp>

namespace core {
namespace control {

Item::Item(ItemDescr* descr, model::Item* model)
    :
      Base(descr, model)
    , m_descriptor_item(descr)
    , m_model_item(model)
{
}

bool Item::isDamaged() const { return (model()->condition() <= 0); }
bool Item::isLocked() const { return (model()->lockedTurns() > 0); }
int Item::isFunctioning() const { return ( !isDamaged() && !isLocked() ); }

void Item::lock(int lock)
{
    bool was_working = false;
    if (!model()->lockedTurns()) {
        was_working = true;
    }
    
    model()->setLockedTurns(model()->lockedTurns() + lock);
    if (was_working) {
        m_slot->updateVehiclePropetries();
    }
}

void Item::unlock()
{
    model()->setLockedTurns(0);
    m_slot->updateVehiclePropetries();
}
                
void Item::useNormalDeterioration()
{
    assert(false);
    //m_deterioration = m_data.deterioration;
}
                                
void Item::useOverloadDeterioration()
{
    assert(false);
    //m_deterioration = m_data.deterioration * m_data.deterioration_overload_rate;
}
 
void Item::corrupt()
{
    //LOG("Base::broken");
    model()->setCondition(0);
    m_slot->updateVehiclePropetries();
}
                
void Item::deteriorate()
{
    model()->setCondition(model()->condition() - descriptor()->deterioration());
    if (model()->condition() <= 0) {
        corrupt();
    }
}         
                
bool Item::repair()
{
    model()->setCondition(descriptor()->condition());
    m_slot->updateVehiclePropetries();
    
    return true;
}

void Item::_updateLock()
{
    if (model()->lockedTurns() > 0) {
        model()->setLockedTurns(model()->lockedTurns() - 1);
        if (!model()->lockedTurns()) {
            m_slot->updateVehiclePropetries();
        }
    }
}     

} // namespace control
} // namespace core
