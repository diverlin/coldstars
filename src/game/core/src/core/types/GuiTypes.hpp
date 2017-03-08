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


#ifndef GUITYPES_HPP
#define GUITYPES_HPP

#include <string>
#include <types/EntityTypes.hpp>


namespace gui
{ 
    enum class type
    {
        NONE = 0,
        
        BUTTON, 
        BUTTON_SINGLE, BUTTON_TRIGGER,
        BUTTON_ITEMSLOT, BUTTON_ITEMSLOT2,
        BUTTON_GALAXYMAP,
        
        SLIDER,
        SLIDE, ACCEPT, DECLINE,
                
        BUYARMOR, BUYFUEL, GETLAUNCH,        
        WEAPON1_ACTIVATOR, WEAPON2_ACTIVATOR, WEAPON3_ACTIVATOR, WEAPON4_ACTIVATOR, WEAPON5_ACTIVATOR, 
        WEAPON6_ACTIVATOR, WEAPON7_ACTIVATOR, WEAPON8_ACTIVATOR, WEAPON9_ACTIVATOR,
          
        CARGO_SLOT, 
        CARGO_SLOT1, CARGO_SLOT2, CARGO_SLOT3, CARGO_SLOT4, CARGO_SLOT5, CARGO_SLOT6, CARGO_SLOT7, CARGO_SLOT8, CARGO_SLOT9,  
        CARGO_SLOT10, CARGO_SLOT11, CARGO_SLOT12, CARGO_SLOT13, CARGO_SLOT14, CARGO_SLOT15, CARGO_SLOT16, CARGO_SLOT17, CARGO_SLOT18,
                
        WEAPON_SLOT, 
        WEAPON_SLOT1, WEAPON_SLOT2, WEAPON_SLOT3, WEAPON_SLOT4, WEAPON_SLOT5, WEAPON_SLOT6, WEAPON_SLOT7, WEAPON_SLOT8, WEAPON_SLOT9,
        WEAPON_SLOT1_SELECTOR, WEAPON_SLOT2_SELECTOR, WEAPON_SLOT3_SELECTOR, WEAPON_SLOT4_SELECTOR, WEAPON_SLOT5_SELECTOR, WEAPON_SLOT6_SELECTOR, WEAPON_SLOT7_SELECTOR, WEAPON_SLOT8_SELECTOR, WEAPON_SLOT9_SELECTOR,
         
            
        GATE_SLOT, //REPAIR_SLOT, CHARGE_SLOT,
        
        DRIVE_SLOT, RADAR_SLOT, BAK_SLOT, ENERGIZER_SLOT, PROTECTOR_SLOT, DROID_SLOT, FREEZER_SLOT, GRAPPLE_SLOT, SCANER_SLOT, 
        DRIVE_SLOT_SELECTOR, RADAR_SLOT_SELECTOR, BAK_SLOT_SELECTOR, ENERGIZER_SLOT_SELECTOR, PROTECTOR_SLOT_SELECTOR, DROID_SLOT_SELECTOR, FREEZER_SLOT_SELECTOR, GRAPPLE_SLOT_SELECTOR, SCANER_SLOT_SELECTOR, 
        
        ARTEFACT_SLOT, 
        ARTEFACT_SLOT1, ARTEFACT_SLOT2, ARTEFACT_SLOT3, ARTEFACT_SLOT4,
           
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
}

std::string getGuiTypeStr(gui::type);

gui::type getGuiItemSlotType(entity::Type);
gui::type getGuiItemSlotSelectorType(entity::Type);

#endif

