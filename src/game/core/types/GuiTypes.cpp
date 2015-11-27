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


std::string getGuiTypeStr(TYPE::GUI type_id)
{
    switch(type_id)
    {
        case TYPE::GUI::NONE_ID: { return "GUI::NONE_ID"; break; }
            
        case TYPE::GUI::MINERALS_ID:         { return "GUI::MINERALS_ID"; break; }
        case TYPE::GUI::FOOD_ID:             { return "GUI::FOOD_ID"; break; }
        case TYPE::GUI::MEDICINE_ID:         { return "GUI::MEDICINE_ID"; break; }
        case TYPE::GUI::MILITARY_ID:         { return "GUI::MILITARY_ID"; break; }
        case TYPE::GUI::DRUG_ID:             { return "GUI::DRUG_ID"; break; }
        case TYPE::GUI::EXCLUSIVE_ID:         { return "GUI::EXCLUSIVE_ID"; break; }


        case TYPE::GUI::GOVERMENT_ID:     { return "GUI::GOVERMENT_ID"; break; }
        case TYPE::GUI::STORE_ID:         { return "GUI::STORE_ID"; break; }
        case TYPE::GUI::SHOP_ID:         { return "GUI::SHOP_ID"; break; }
        case TYPE::GUI::ANGAR_ID:         { return "GUI::ANGAR_ID"; break; }          
    
        case TYPE::GUI::CARGO_SLOT_ID:         { return "GUI::CARGO_SLOT_ID"; break; }    
        case TYPE::GUI::GATE_SLOT_ID:         { return "GUI::GATE_SLOT_ID"; break; }        

        case TYPE::GUI::WEAPON_SLOT_ID:         { return "GUI::WEAPON_SLOT_ID"; break; }
        case TYPE::GUI::WEAPON_SLOT1_ID:         { return "GUI::WEAPON_SLOT1_ID"; break; }
        case TYPE::GUI::WEAPON_SLOT2_ID:         { return "GUI::WEAPON_SLOT2_ID"; break; }
        case TYPE::GUI::WEAPON_SLOT3_ID:         { return "GUI::WEAPON_SLOT3_ID"; break; }
        case TYPE::GUI::WEAPON_SLOT4_ID:         { return "GUI::WEAPON_SLOT4_ID"; break; }
        case TYPE::GUI::WEAPON_SLOT5_ID:         { return "GUI::WEAPON_SLOT5_ID"; break; }
        case TYPE::GUI::WEAPON_SLOT6_ID:         { return "GUI::WEAPON_SLOT6_ID"; break; }
        case TYPE::GUI::WEAPON_SLOT7_ID:         { return "GUI::WEAPON_SLOT7_ID"; break; }
        case TYPE::GUI::WEAPON_SLOT8_ID:         { return "GUI::WEAPON_SLOT8_ID"; break; }
        case TYPE::GUI::WEAPON_SLOT9_ID:         { return "GUI::WEAPON_SLOT9_ID"; break; }
    
        case TYPE::GUI::WEAPON_SLOT1_SELECTOR_ID: { return "GUI::WEAPON_SLOT1_SELECTOR_ID"; break; }
        case TYPE::GUI::WEAPON_SLOT2_SELECTOR_ID: { return "GUI::WEAPON_SLOT2_SELECTOR_ID"; break; }
        case TYPE::GUI::WEAPON_SLOT3_SELECTOR_ID: { return "GUI::WEAPON_SLOT3_SELECTOR_ID"; break; }
        case TYPE::GUI::WEAPON_SLOT4_SELECTOR_ID: { return "GUI::WEAPON_SLOT4_SELECTOR_ID"; break; }
        case TYPE::GUI::WEAPON_SLOT5_SELECTOR_ID: { return "GUI::WEAPON_SLOT5_SELECTOR_ID"; break; }
        case TYPE::GUI::WEAPON_SLOT6_SELECTOR_ID: { return "GUI::WEAPON_SLOT6_SELECTOR_ID"; break; }
        case TYPE::GUI::WEAPON_SLOT7_SELECTOR_ID: { return "GUI::WEAPON_SLOT7_SELECTOR_ID"; break; }
        case TYPE::GUI::WEAPON_SLOT8_SELECTOR_ID: { return "GUI::WEAPON_SLOT8_SELECTOR_ID"; break; }
        case TYPE::GUI::WEAPON_SLOT9_SELECTOR_ID: { return "GUI::WEAPON_SLOT9_SELECTOR_ID"; break; }
         
        case TYPE::GUI::DRIVE_SLOT_ID:         { return "GUI::DRIVE_SLOT_ID"; break; }
        case TYPE::GUI::RADAR_SLOT_ID:         { return "GUI::RADAR_SLOT_ID"; break; }
        case TYPE::GUI::BAK_SLOT_ID:         { return "GUI::BAK_SLOT_ID"; break; }
        case TYPE::GUI::ENERGIZER_SLOT_ID:     { return "GUI::ENERGIZER_SLOT_ID"; break; }
        case TYPE::GUI::PROTECTOR_SLOT_ID:     { return "GUI::PROTECTOR_SLOT_ID"; break; }
        case TYPE::GUI::DROID_SLOT_ID:         { return "GUI::DROID_SLOT_ID"; break; }
        case TYPE::GUI::FREEZER_SLOT_ID:     { return "GUI::FREEZER_SLOT_ID"; break; }
        case TYPE::GUI::GRAPPLE_SLOT_ID:     { return "GUI::GRAPPLE_SLOT_ID"; break; }
        case TYPE::GUI::SCANER_SLOT_ID:     { return "GUI::SCANER_SLOT_ID"; break; }
        case TYPE::GUI::ARTEFACT_SLOT_ID:     { return "GUI::ARTEFACT_SLOT_ID"; break; }

        default:     { return "GUI::UNKNOWN id_type"; break; }
    }
}

TYPE::GUI getGuiItemSlotType(TYPE::ENTITY val)
{
    switch(val)
    {
        case TYPE::ENTITY::CARGO_SLOT_ID:     { return TYPE::GUI::CARGO_SLOT_ID; break; }
        case TYPE::ENTITY::CARGO_SLOT1_ID:    { return TYPE::GUI::CARGO_SLOT1_ID; break; }
        case TYPE::ENTITY::CARGO_SLOT2_ID:    { return TYPE::GUI::CARGO_SLOT2_ID; break; }
        case TYPE::ENTITY::CARGO_SLOT3_ID:    { return TYPE::GUI::CARGO_SLOT3_ID; break; }
        case TYPE::ENTITY::CARGO_SLOT4_ID:    { return TYPE::GUI::CARGO_SLOT4_ID; break; }
        case TYPE::ENTITY::CARGO_SLOT5_ID:    { return TYPE::GUI::CARGO_SLOT5_ID; break; }
        case TYPE::ENTITY::CARGO_SLOT6_ID:    { return TYPE::GUI::CARGO_SLOT6_ID; break; }
        case TYPE::ENTITY::CARGO_SLOT7_ID:    { return TYPE::GUI::CARGO_SLOT7_ID; break; }
        case TYPE::ENTITY::CARGO_SLOT8_ID:    { return TYPE::GUI::CARGO_SLOT8_ID; break; }
        case TYPE::ENTITY::CARGO_SLOT9_ID:    { return TYPE::GUI::CARGO_SLOT9_ID; break; }
        case TYPE::ENTITY::CARGO_SLOT10_ID:   { return TYPE::GUI::CARGO_SLOT10_ID; break; }
        case TYPE::ENTITY::CARGO_SLOT11_ID:   { return TYPE::GUI::CARGO_SLOT11_ID; break; }
        case TYPE::ENTITY::CARGO_SLOT12_ID:   { return TYPE::GUI::CARGO_SLOT12_ID; break; }
        case TYPE::ENTITY::CARGO_SLOT13_ID:   { return TYPE::GUI::CARGO_SLOT13_ID; break; }
        case TYPE::ENTITY::CARGO_SLOT14_ID:   { return TYPE::GUI::CARGO_SLOT14_ID; break; }
        case TYPE::ENTITY::CARGO_SLOT15_ID:   { return TYPE::GUI::CARGO_SLOT15_ID; break; }
        case TYPE::ENTITY::CARGO_SLOT16_ID:   { return TYPE::GUI::CARGO_SLOT16_ID; break; }
        case TYPE::ENTITY::CARGO_SLOT17_ID:   { return TYPE::GUI::CARGO_SLOT17_ID; break; }
        case TYPE::ENTITY::CARGO_SLOT18_ID:   { return TYPE::GUI::CARGO_SLOT18_ID; break; }

        case TYPE::ENTITY::WEAPON_SLOT_ID:    { return TYPE::GUI::WEAPON_SLOT_ID; break; }
        case TYPE::ENTITY::WEAPON_SLOT1_ID:   { return TYPE::GUI::WEAPON_SLOT1_ID; break; }
        case TYPE::ENTITY::WEAPON_SLOT2_ID:   { return TYPE::GUI::WEAPON_SLOT2_ID; break; }
        case TYPE::ENTITY::WEAPON_SLOT3_ID:   { return TYPE::GUI::WEAPON_SLOT3_ID; break; }
        case TYPE::ENTITY::WEAPON_SLOT4_ID:   { return TYPE::GUI::WEAPON_SLOT4_ID; break; }
        case TYPE::ENTITY::WEAPON_SLOT5_ID:   { return TYPE::GUI::WEAPON_SLOT5_ID; break; }
        case TYPE::ENTITY::WEAPON_SLOT6_ID:   { return TYPE::GUI::WEAPON_SLOT6_ID; break; }
        case TYPE::ENTITY::WEAPON_SLOT7_ID:   { return TYPE::GUI::WEAPON_SLOT7_ID; break; }
        case TYPE::ENTITY::WEAPON_SLOT8_ID:   { return TYPE::GUI::WEAPON_SLOT8_ID; break; }
        case TYPE::ENTITY::WEAPON_SLOT9_ID:   { return TYPE::GUI::WEAPON_SLOT9_ID; break; }

        case TYPE::ENTITY::DRIVE_SLOT_ID:   { return TYPE::GUI::DRIVE_SLOT_ID; break; }
        case TYPE::ENTITY::RADAR_SLOT_ID:   { return TYPE::GUI::RADAR_SLOT_ID; break; }
        case TYPE::ENTITY::BAK_SLOT_ID:   { return TYPE::GUI::BAK_SLOT_ID; break; }
        case TYPE::ENTITY::ENERGIZER_SLOT_ID:   { return TYPE::GUI::ENERGIZER_SLOT_ID; break; }
        case TYPE::ENTITY::PROTECTOR_SLOT_ID:   { return TYPE::GUI::PROTECTOR_SLOT_ID; break; }
        case TYPE::ENTITY::DROID_SLOT_ID:   { return TYPE::GUI::DROID_SLOT_ID; break; }
        case TYPE::ENTITY::FREEZER_SLOT_ID:   { return TYPE::GUI::FREEZER_SLOT_ID; break; }
        case TYPE::ENTITY::GRAPPLE_SLOT_ID:   { return TYPE::GUI::GRAPPLE_SLOT_ID; break; }
        case TYPE::ENTITY::SCANER_SLOT_ID:   { return TYPE::GUI::SCANER_SLOT_ID; break; }

        case TYPE::ENTITY::ARTEFACT_SLOT_ID:   { return TYPE::GUI::ARTEFACT_SLOT_ID; break; }
        case TYPE::ENTITY::ARTEFACT_SLOT1_ID:  { return TYPE::GUI::ARTEFACT_SLOT1_ID; break; }
        case TYPE::ENTITY::ARTEFACT_SLOT2_ID:  { return TYPE::GUI::ARTEFACT_SLOT2_ID; break; }
        case TYPE::ENTITY::ARTEFACT_SLOT3_ID:  { return TYPE::GUI::ARTEFACT_SLOT3_ID; break; }
        case TYPE::ENTITY::ARTEFACT_SLOT4_ID:  { return TYPE::GUI::ARTEFACT_SLOT4_ID; break; }

        case TYPE::ENTITY::GATE_SLOT_ID:   { return TYPE::GUI::GATE_SLOT_ID; break; }
        //case TYPE::ENTITY::REPAIR_SLOT_ID:   { return TYPE::GUI::REPAIR_SLOT_ID; break; }
        //case TYPE::ENTITY::CHARGE_SLOT_ID:   { return TYPE::GUI::CHARGE_SLOT_ID; break; }
    }

    return TYPE::GUI::NONE_ID;
}

TYPE::GUI getGuiItemSlotSelectorType(TYPE::ENTITY val)
{
    switch(val)
    {
        case TYPE::ENTITY::WEAPON_SLOT1_ID:   { return TYPE::GUI::WEAPON_SLOT1_SELECTOR_ID; break; }
        case TYPE::ENTITY::WEAPON_SLOT2_ID:   { return TYPE::GUI::WEAPON_SLOT2_SELECTOR_ID; break; }
        case TYPE::ENTITY::WEAPON_SLOT3_ID:   { return TYPE::GUI::WEAPON_SLOT3_SELECTOR_ID; break; }
        case TYPE::ENTITY::WEAPON_SLOT4_ID:   { return TYPE::GUI::WEAPON_SLOT4_SELECTOR_ID; break; }
        case TYPE::ENTITY::WEAPON_SLOT5_ID:   { return TYPE::GUI::WEAPON_SLOT5_SELECTOR_ID; break; }
        case TYPE::ENTITY::WEAPON_SLOT6_ID:   { return TYPE::GUI::WEAPON_SLOT6_SELECTOR_ID; break; }
        case TYPE::ENTITY::WEAPON_SLOT7_ID:   { return TYPE::GUI::WEAPON_SLOT7_SELECTOR_ID; break; }
        case TYPE::ENTITY::WEAPON_SLOT8_ID:   { return TYPE::GUI::WEAPON_SLOT8_SELECTOR_ID; break; }
        case TYPE::ENTITY::WEAPON_SLOT9_ID:   { return TYPE::GUI::WEAPON_SLOT9_SELECTOR_ID; break; }

        case TYPE::ENTITY::DRIVE_SLOT_ID:   { return TYPE::GUI::DRIVE_SLOT_SELECTOR_ID; break; }
        case TYPE::ENTITY::RADAR_SLOT_ID:   { return TYPE::GUI::RADAR_SLOT_SELECTOR_ID; break; }
        case TYPE::ENTITY::BAK_SLOT_ID:   { return TYPE::GUI::BAK_SLOT_SELECTOR_ID; break; }
        case TYPE::ENTITY::ENERGIZER_SLOT_ID:   { return TYPE::GUI::ENERGIZER_SLOT_SELECTOR_ID; break; }
        case TYPE::ENTITY::PROTECTOR_SLOT_ID:   { return TYPE::GUI::PROTECTOR_SLOT_SELECTOR_ID; break; }
        case TYPE::ENTITY::DROID_SLOT_ID:   { return TYPE::GUI::DROID_SLOT_SELECTOR_ID; break; }
        case TYPE::ENTITY::FREEZER_SLOT_ID:   { return TYPE::GUI::FREEZER_SLOT_SELECTOR_ID; break; }
        case TYPE::ENTITY::GRAPPLE_SLOT_ID:   { return TYPE::GUI::GRAPPLE_SLOT_SELECTOR_ID; break; }
        case TYPE::ENTITY::SCANER_SLOT_ID:   { return TYPE::GUI::SCANER_SLOT_SELECTOR_ID; break; }
    }

    return TYPE::GUI::NONE_ID;
}

