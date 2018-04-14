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
             
#include "ButtonItemSlot2.hpp"

#include <core/slot/ItemSlot.hpp>
#include <core/type/EntityType.hpp>

namespace {

gui::Type guiTypeFromSlotType(core::slot::Type slot) {
    switch(slot)
    {
    case core::slot::Type::CARGO:     { return gui::Type::CARGO_SLOT_SELECTOR; break; }
    case core::slot::Type::WEAPON:    { return gui::Type::WEAPON_SLOT_SELECTOR; break; }
    case core::slot::Type::DRIVE:     { return gui::Type::DRIVE_SLOT_SELECTOR; break; }
    case core::slot::Type::RADAR:     { return gui::Type::RADAR_SLOT_SELECTOR; break; }
    case core::slot::Type::BAK:       { return gui::Type::BAK_SLOT_SELECTOR; break; }
        //case slot::Type::ENERGIZER:   { return gui::Type::ENERGIZER_SLOT_SELECTOR; break; }
        //case slot::Type::PROTECTOR:   { return gui::Type::PROTECTOR_SLOT_SELECTOR; break; }
    case core::slot::Type::DROID:     { return gui::Type::DROID_SLOT_SELECTOR; break; }
    case core::slot::Type::FREEZER:   { return gui::Type::FREEZER_SLOT_SELECTOR; break; }
    case core::slot::Type::GRAPPLE:   { return gui::Type::GRAPPLE_SLOT_SELECTOR; break; }
    case core::slot::Type::SCANER:    { return gui::Type::SCANER_SLOT_SELECTOR; break; }
        //            case entity::Type::ARTEFACT_SLOT:   { return gui::type::ARTEFACT_SLOT; break; }
        //            case entity::Type::GATE_SLOT:   { return gui::type::GATE_SLOT; break; }
    }

    return gui::Type::NONE;
}

} // namespace

namespace gui {

ButtonItemSlot2::ButtonItemSlot2(core::slot::Item* slot)
    :
      BaseButtonItemSlot(slot)
{
    _setType(guiTypeFromSlotType(slot->type()));
}

ButtonItemSlot2::~ButtonItemSlot2()
{
}

void ButtonItemSlot2::onPressEventMBL(client::Player* player)
{
    if (!isLocked()) {
        _setIsPressed(!isPressed());
    } else {
        _setIsPressed(false);
    }
        
    if (itemSlot()) // !!!
    {        
//        if (GetPressed() == true)
//        {
//            if (GetItemSlot()->isSelected() == false)
//            {
//                GetItemSlot()->SelectEvent();
//            }
//        }
//        else
//        {
//            if (GetItemSlot()->isSelected() == true)
//            {
//                GetItemSlot()->DeselectEvent();
//            }
//        }
    }
}

/* virtual override final */
void ButtonItemSlot2::resetState()
{
    _setIsPressed(false);
    if (itemSlot()) {
//        if (GetItemSlot()->isSelected() == true)
//        {
//            GetItemSlot()->DeselectEvent();
//        }
    }
}
        
/* virtual override final */    
void ButtonItemSlot2::_updateUnique(client::Player* player)
{
    _invalidateItemView();
    _updateAnimation();
            
    if (!hasAnimation()) {
        if (itemSlot()) {
            if (isPressed()) {
                box().setScale(1.5f);
            } else {
                box().setScale(1.0f);
            }
        }
    } else {
        if (isPressed()){
            resetState();
        }
    }
}

/*virtual override final*/
void ButtonItemSlot2::_renderUnique(const jeti::Render& render, client::Player*) const
{
    _drawSlot(render);
    _drawItem(render);
}        

} // namespace gui
