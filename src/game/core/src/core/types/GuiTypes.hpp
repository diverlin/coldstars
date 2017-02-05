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
        NONE_ID = 0,
        
        BUTTON_ID, 
        BUTTON_SINGLE_ID, BUTTON_TRIGGER_ID,
        BUTTON_ITEMSLOT_ID, BUTTON_ITEMSLOT2_ID,
        BUTTON_GALAXYMAP_ID,
        
        SLIDER_ID,
        SLIDE_ID, ACCEPT_ID, DECLINE_ID,
                
        BUYARMOR_ID, BUYFUEL_ID, GETLAUNCH_ID,        
        WEAPON1_ACTIVATOR_ID, WEAPON2_ACTIVATOR_ID, WEAPON3_ACTIVATOR_ID, WEAPON4_ACTIVATOR_ID, WEAPON5_ACTIVATOR_ID, 
        WEAPON6_ACTIVATOR_ID, WEAPON7_ACTIVATOR_ID, WEAPON8_ACTIVATOR_ID, WEAPON9_ACTIVATOR_ID,
          
        CARGO_SLOT_ID, 
        CARGO_SLOT1_ID, CARGO_SLOT2_ID, CARGO_SLOT3_ID, CARGO_SLOT4_ID, CARGO_SLOT5_ID, CARGO_SLOT6_ID, CARGO_SLOT7_ID, CARGO_SLOT8_ID, CARGO_SLOT9_ID,  
        CARGO_SLOT10_ID, CARGO_SLOT11_ID, CARGO_SLOT12_ID, CARGO_SLOT13_ID, CARGO_SLOT14_ID, CARGO_SLOT15_ID, CARGO_SLOT16_ID, CARGO_SLOT17_ID, CARGO_SLOT18_ID,
                
        WEAPON_SLOT_ID, 
        WEAPON_SLOT1_ID, WEAPON_SLOT2_ID, WEAPON_SLOT3_ID, WEAPON_SLOT4_ID, WEAPON_SLOT5_ID, WEAPON_SLOT6_ID, WEAPON_SLOT7_ID, WEAPON_SLOT8_ID, WEAPON_SLOT9_ID,
        WEAPON_SLOT1_SELECTOR_ID, WEAPON_SLOT2_SELECTOR_ID, WEAPON_SLOT3_SELECTOR_ID, WEAPON_SLOT4_SELECTOR_ID, WEAPON_SLOT5_SELECTOR_ID, WEAPON_SLOT6_SELECTOR_ID, WEAPON_SLOT7_SELECTOR_ID, WEAPON_SLOT8_SELECTOR_ID, WEAPON_SLOT9_SELECTOR_ID,
         
            
        GATE_SLOT_ID, //REPAIR_SLOT_ID, CHARGE_SLOT_ID,
        
        DRIVE_SLOT_ID, RADAR_SLOT_ID, BAK_SLOT_ID, ENERGIZER_SLOT_ID, PROTECTOR_SLOT_ID, DROID_SLOT_ID, FREEZER_SLOT_ID, GRAPPLE_SLOT_ID, SCANER_SLOT_ID, 
        DRIVE_SLOT_SELECTOR_ID, RADAR_SLOT_SELECTOR_ID, BAK_SLOT_SELECTOR_ID, ENERGIZER_SLOT_SELECTOR_ID, PROTECTOR_SLOT_SELECTOR_ID, DROID_SLOT_SELECTOR_ID, FREEZER_SLOT_SELECTOR_ID, GRAPPLE_SLOT_SELECTOR_ID, SCANER_SLOT_SELECTOR_ID, 
        
        ARTEFACT_SLOT_ID, 
        ARTEFACT_SLOT1_ID, ARTEFACT_SLOT2_ID, ARTEFACT_SLOT3_ID, ARTEFACT_SLOT4_ID,
           
        ANGAR_ID, STORE_ID, SHOP_ID, GALAXYMAP_ID, GOVERMENT_ID,
                
        INCREMENT_ATTACK_ID, DECREMENT_ATTACK_ID, INCREMENT_DEFENCE_ID, DECREMENT_DEFENCE_ID, INCREMENT_LEADER_ID,
        DECREMENT_LEADER_ID, INCREMENT_TRADER_ID, DECREMENT_TRADER_ID, INCREMENT_TECHNIC_ID, DECREMENT_TECHNIC_ID,
        INCREMENT_DIPLOMAT_ID, DECREMENT_DIPLOMAT_ID,
                
        SAVE_ID, LOAD_ID,
                
        MINERALS_ID, FOOD_ID, MEDICINE_ID, MILITARY_ID, DRUG_ID, EXCLUSIVE_ID,
                
        ACTION_ATTACK_ID, ACTION_PRECISEATTACK_ID, ACTION_SCAN_ID, ACTION_GRAB_ID, ACTION_FOLLOW_ID,
                
        GUI_RADAR_ID,
        PLAYER_VEHICLE_ID,
        SCAN_VEHICLE_ID
    };
}

std::string getGuiTypeStr(gui::type);

gui::type getGuiItemSlotType(entity::type);
gui::type getGuiItemSlotSelectorType(entity::type);

#endif

