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

#include <core/type/EntityType.hpp>

#include <string>

namespace gui
{ 
    enum class Type
    {
        NONE = 0,
        
        BUTTON, 
        BUTTON_SINGLE, BUTTON_TRIGGER,
        BUTTON_ITEMSLOT, BUTTON_ITEMSLOT2,
        BUTTON_GALAXYMAP,
        
        SLIDER,
        SLIDE, ACCEPT, DECLINE,
                
        BUYARMOR, BUYFUEL, GETLAUNCH,        

//        CARGO_SLOT,

        // SLOT_SELECTOR
        WEAPON_SLOT_SELECTOR,
        CARGO_SLOT_SELECTOR,
        DRIVE_SLOT_SELECTOR, RADAR_SLOT_SELECTOR, BAK_SLOT_SELECTOR, ENERGIZER_SLOT_SELECTOR, PROTECTOR_SLOT_SELECTOR, DROID_SLOT_SELECTOR, FREEZER_SLOT_SELECTOR, GRAPPLE_SLOT_SELECTOR, SCANER_SLOT_SELECTOR,

        GATE_SLOT, //REPAIR_SLOT, CHARGE_SLOT,
        
//        ARTEFACT_SLOT,
           
        ANGAR, STORE, SHOP, GALAXYMAP, GOVERMENT,
                
        INCREMENT_ATTACK, DECREMENT_ATTACK, INCREMENT_DEFENCE, DECREMENT_DEFENCE, INCREMENT_LEADER,
        DECREMENT_LEADER, INCREMENT_TRADER, DECREMENT_TRADER, INCREMENT_TECHNIC, DECREMENT_TECHNIC,
        INCREMENT_DIPLOMAT, DECREMENT_DIPLOMAT,
                
        SAVE, LOAD,
                
        MINERALS, FOOD, MEDICINE, MILITARY, DRUG, EXCLUSIVE,
                
        ACTION_ATTACK, ACTION_PRECISEATTACK, ACTION_SCAN, ACTION_GRAB, ACTION_FOLLOW,
                
        GUI_RADAR,
        PLAYER_VEHICLE,
        SCAN_VEHICLE
    };

std::string to_string(Type);
//Type getGuiItemSlotType(entity::Type);
//Type getGuiItemSlotSelectorType(entity::Type);

} // namespace gui





