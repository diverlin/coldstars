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


#include "GuiTypes.hpp"


std::string getGuiTypeStr(gui::type type_id)
{
    switch(type_id)
    {
        case gui::type::NONE_ID: { return "GUI::NONE_ID"; break; }
            
        case gui::type::MINERALS_ID:         { return "GUI::MINERALS_ID"; break; }
        case gui::type::FOOD_ID:             { return "GUI::FOOD_ID"; break; }
        case gui::type::MEDICINE_ID:         { return "GUI::MEDICINE_ID"; break; }
        case gui::type::MILITARY_ID:         { return "GUI::MILITARY_ID"; break; }
        case gui::type::DRUG_ID:             { return "GUI::DRUG_ID"; break; }
        case gui::type::EXCLUSIVE_ID:         { return "GUI::EXCLUSIVE_ID"; break; }


        case gui::type::GOVERMENT_ID:     { return "GUI::GOVERMENT_ID"; break; }
        case gui::type::STORE_ID:         { return "GUI::STORE_ID"; break; }
        case gui::type::SHOP_ID:         { return "GUI::SHOP_ID"; break; }
        case gui::type::ANGAR_ID:         { return "GUI::ANGAR_ID"; break; }
    
        case gui::type::CARGO_SLOT_ID:         { return "GUI::CARGO_SLOT_ID"; break; }
        case gui::type::GATE_SLOT_ID:         { return "GUI::GATE_SLOT_ID"; break; }

        case gui::type::WEAPON_SLOT_ID:         { return "GUI::WEAPON_SLOT_ID"; break; }
        case gui::type::WEAPON_SLOT1_ID:         { return "GUI::WEAPON_SLOT1_ID"; break; }
        case gui::type::WEAPON_SLOT2_ID:         { return "GUI::WEAPON_SLOT2_ID"; break; }
        case gui::type::WEAPON_SLOT3_ID:         { return "GUI::WEAPON_SLOT3_ID"; break; }
        case gui::type::WEAPON_SLOT4_ID:         { return "GUI::WEAPON_SLOT4_ID"; break; }
        case gui::type::WEAPON_SLOT5_ID:         { return "GUI::WEAPON_SLOT5_ID"; break; }
        case gui::type::WEAPON_SLOT6_ID:         { return "GUI::WEAPON_SLOT6_ID"; break; }
        case gui::type::WEAPON_SLOT7_ID:         { return "GUI::WEAPON_SLOT7_ID"; break; }
        case gui::type::WEAPON_SLOT8_ID:         { return "GUI::WEAPON_SLOT8_ID"; break; }
        case gui::type::WEAPON_SLOT9_ID:         { return "GUI::WEAPON_SLOT9_ID"; break; }
    
        case gui::type::WEAPON_SLOT1_SELECTOR_ID: { return "GUI::WEAPON_SLOT1_SELECTOR_ID"; break; }
        case gui::type::WEAPON_SLOT2_SELECTOR_ID: { return "GUI::WEAPON_SLOT2_SELECTOR_ID"; break; }
        case gui::type::WEAPON_SLOT3_SELECTOR_ID: { return "GUI::WEAPON_SLOT3_SELECTOR_ID"; break; }
        case gui::type::WEAPON_SLOT4_SELECTOR_ID: { return "GUI::WEAPON_SLOT4_SELECTOR_ID"; break; }
        case gui::type::WEAPON_SLOT5_SELECTOR_ID: { return "GUI::WEAPON_SLOT5_SELECTOR_ID"; break; }
        case gui::type::WEAPON_SLOT6_SELECTOR_ID: { return "GUI::WEAPON_SLOT6_SELECTOR_ID"; break; }
        case gui::type::WEAPON_SLOT7_SELECTOR_ID: { return "GUI::WEAPON_SLOT7_SELECTOR_ID"; break; }
        case gui::type::WEAPON_SLOT8_SELECTOR_ID: { return "GUI::WEAPON_SLOT8_SELECTOR_ID"; break; }
        case gui::type::WEAPON_SLOT9_SELECTOR_ID: { return "GUI::WEAPON_SLOT9_SELECTOR_ID"; break; }
         
        case gui::type::DRIVE_SLOT_ID:         { return "GUI::DRIVE_SLOT_ID"; break; }
        case gui::type::RADAR_SLOT_ID:         { return "GUI::RADAR_SLOT_ID"; break; }
        case gui::type::BAK_SLOT_ID:         { return "GUI::BAK_SLOT_ID"; break; }
        case gui::type::ENERGIZER_SLOT_ID:     { return "GUI::ENERGIZER_SLOT_ID"; break; }
        case gui::type::PROTECTOR_SLOT_ID:     { return "GUI::PROTECTOR_SLOT_ID"; break; }
        case gui::type::DROID_SLOT_ID:         { return "GUI::DROID_SLOT_ID"; break; }
        case gui::type::FREEZER_SLOT_ID:     { return "GUI::FREEZER_SLOT_ID"; break; }
        case gui::type::GRAPPLE_SLOT_ID:     { return "GUI::GRAPPLE_SLOT_ID"; break; }
        case gui::type::SCANER_SLOT_ID:     { return "GUI::SCANER_SLOT_ID"; break; }
        case gui::type::ARTEFACT_SLOT_ID:     { return "GUI::ARTEFACT_SLOT_ID"; break; }

        default:     { return "GUI::UNKNOWN id_type"; break; }
    }
}

gui::type getGuiItemSlotType(entity::type val)
{
    switch(val)
    {
        case entity::type::CARGO_SLOT_ID:     { return gui::type::CARGO_SLOT_ID; break; }
        case entity::type::CARGO_SLOT1_ID:    { return gui::type::CARGO_SLOT1_ID; break; }
        case entity::type::CARGO_SLOT2_ID:    { return gui::type::CARGO_SLOT2_ID; break; }
        case entity::type::CARGO_SLOT3_ID:    { return gui::type::CARGO_SLOT3_ID; break; }
        case entity::type::CARGO_SLOT4_ID:    { return gui::type::CARGO_SLOT4_ID; break; }
        case entity::type::CARGO_SLOT5_ID:    { return gui::type::CARGO_SLOT5_ID; break; }
        case entity::type::CARGO_SLOT6_ID:    { return gui::type::CARGO_SLOT6_ID; break; }
        case entity::type::CARGO_SLOT7_ID:    { return gui::type::CARGO_SLOT7_ID; break; }
        case entity::type::CARGO_SLOT8_ID:    { return gui::type::CARGO_SLOT8_ID; break; }
        case entity::type::CARGO_SLOT9_ID:    { return gui::type::CARGO_SLOT9_ID; break; }
        case entity::type::CARGO_SLOT10_ID:   { return gui::type::CARGO_SLOT10_ID; break; }
        case entity::type::CARGO_SLOT11_ID:   { return gui::type::CARGO_SLOT11_ID; break; }
        case entity::type::CARGO_SLOT12_ID:   { return gui::type::CARGO_SLOT12_ID; break; }
        case entity::type::CARGO_SLOT13_ID:   { return gui::type::CARGO_SLOT13_ID; break; }
        case entity::type::CARGO_SLOT14_ID:   { return gui::type::CARGO_SLOT14_ID; break; }
        case entity::type::CARGO_SLOT15_ID:   { return gui::type::CARGO_SLOT15_ID; break; }
        case entity::type::CARGO_SLOT16_ID:   { return gui::type::CARGO_SLOT16_ID; break; }
        case entity::type::CARGO_SLOT17_ID:   { return gui::type::CARGO_SLOT17_ID; break; }
        case entity::type::CARGO_SLOT18_ID:   { return gui::type::CARGO_SLOT18_ID; break; }

        case entity::type::WEAPON_SLOT_ID:    { return gui::type::WEAPON_SLOT_ID; break; }
        case entity::type::WEAPON_SLOT1_ID:   { return gui::type::WEAPON_SLOT1_ID; break; }
        case entity::type::WEAPON_SLOT2_ID:   { return gui::type::WEAPON_SLOT2_ID; break; }
        case entity::type::WEAPON_SLOT3_ID:   { return gui::type::WEAPON_SLOT3_ID; break; }
        case entity::type::WEAPON_SLOT4_ID:   { return gui::type::WEAPON_SLOT4_ID; break; }
        case entity::type::WEAPON_SLOT5_ID:   { return gui::type::WEAPON_SLOT5_ID; break; }
        case entity::type::WEAPON_SLOT6_ID:   { return gui::type::WEAPON_SLOT6_ID; break; }
        case entity::type::WEAPON_SLOT7_ID:   { return gui::type::WEAPON_SLOT7_ID; break; }
        case entity::type::WEAPON_SLOT8_ID:   { return gui::type::WEAPON_SLOT8_ID; break; }
        case entity::type::WEAPON_SLOT9_ID:   { return gui::type::WEAPON_SLOT9_ID; break; }

        case entity::type::DRIVE_SLOT_ID:   { return gui::type::DRIVE_SLOT_ID; break; }
        case entity::type::RADAR_SLOT_ID:   { return gui::type::RADAR_SLOT_ID; break; }
        case entity::type::BAK_SLOT_ID:   { return gui::type::BAK_SLOT_ID; break; }
        case entity::type::ENERGIZER_SLOT_ID:   { return gui::type::ENERGIZER_SLOT_ID; break; }
        case entity::type::PROTECTOR_SLOT_ID:   { return gui::type::PROTECTOR_SLOT_ID; break; }
        case entity::type::DROID_SLOT_ID:   { return gui::type::DROID_SLOT_ID; break; }
        case entity::type::FREEZER_SLOT_ID:   { return gui::type::FREEZER_SLOT_ID; break; }
        case entity::type::GRAPPLE_SLOT_ID:   { return gui::type::GRAPPLE_SLOT_ID; break; }
        case entity::type::SCANER_SLOT_ID:   { return gui::type::SCANER_SLOT_ID; break; }

        case entity::type::ARTEFACT_SLOT_ID:   { return gui::type::ARTEFACT_SLOT_ID; break; }
        case entity::type::ARTEFACT_SLOT1_ID:  { return gui::type::ARTEFACT_SLOT1_ID; break; }
        case entity::type::ARTEFACT_SLOT2_ID:  { return gui::type::ARTEFACT_SLOT2_ID; break; }
        case entity::type::ARTEFACT_SLOT3_ID:  { return gui::type::ARTEFACT_SLOT3_ID; break; }
        case entity::type::ARTEFACT_SLOT4_ID:  { return gui::type::ARTEFACT_SLOT4_ID; break; }

        case entity::type::GATE_SLOT_ID:   { return gui::type::GATE_SLOT_ID; break; }
        //case entity::type::REPAIR_SLOT_ID:   { return gui::type::REPAIR_SLOT_ID; break; }
        //case entity::type::CHARGE_SLOT_ID:   { return gui::type::CHARGE_SLOT_ID; break; }
    }

    return gui::type::NONE_ID;
}

gui::type getGuiItemSlotSelectorType(entity::type val)
{
    switch(val)
    {
        case entity::type::WEAPON_SLOT1_ID:   { return gui::type::WEAPON_SLOT1_SELECTOR_ID; break; }
        case entity::type::WEAPON_SLOT2_ID:   { return gui::type::WEAPON_SLOT2_SELECTOR_ID; break; }
        case entity::type::WEAPON_SLOT3_ID:   { return gui::type::WEAPON_SLOT3_SELECTOR_ID; break; }
        case entity::type::WEAPON_SLOT4_ID:   { return gui::type::WEAPON_SLOT4_SELECTOR_ID; break; }
        case entity::type::WEAPON_SLOT5_ID:   { return gui::type::WEAPON_SLOT5_SELECTOR_ID; break; }
        case entity::type::WEAPON_SLOT6_ID:   { return gui::type::WEAPON_SLOT6_SELECTOR_ID; break; }
        case entity::type::WEAPON_SLOT7_ID:   { return gui::type::WEAPON_SLOT7_SELECTOR_ID; break; }
        case entity::type::WEAPON_SLOT8_ID:   { return gui::type::WEAPON_SLOT8_SELECTOR_ID; break; }
        case entity::type::WEAPON_SLOT9_ID:   { return gui::type::WEAPON_SLOT9_SELECTOR_ID; break; }

        case entity::type::DRIVE_SLOT_ID:   { return gui::type::DRIVE_SLOT_SELECTOR_ID; break; }
        case entity::type::RADAR_SLOT_ID:   { return gui::type::RADAR_SLOT_SELECTOR_ID; break; }
        case entity::type::BAK_SLOT_ID:   { return gui::type::BAK_SLOT_SELECTOR_ID; break; }
        case entity::type::ENERGIZER_SLOT_ID:   { return gui::type::ENERGIZER_SLOT_SELECTOR_ID; break; }
        case entity::type::PROTECTOR_SLOT_ID:   { return gui::type::PROTECTOR_SLOT_SELECTOR_ID; break; }
        case entity::type::DROID_SLOT_ID:   { return gui::type::DROID_SLOT_SELECTOR_ID; break; }
        case entity::type::FREEZER_SLOT_ID:   { return gui::type::FREEZER_SLOT_SELECTOR_ID; break; }
        case entity::type::GRAPPLE_SLOT_ID:   { return gui::type::GRAPPLE_SLOT_SELECTOR_ID; break; }
        case entity::type::SCANER_SLOT_ID:   { return gui::type::SCANER_SLOT_SELECTOR_ID; break; }
    }

    return gui::type::NONE_ID;
}

