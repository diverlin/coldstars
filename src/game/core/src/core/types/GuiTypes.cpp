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
        case gui::type::NONE: { return "GUI::NONE"; break; }
            
        case gui::type::MINERALS:         { return "GUI::MINERALS"; break; }
        case gui::type::FOOD:             { return "GUI::FOOD"; break; }
        case gui::type::MEDICINE:         { return "GUI::MEDICINE"; break; }
        case gui::type::MILITARY:         { return "GUI::MILITARY"; break; }
        case gui::type::DRUG:             { return "GUI::DRUG"; break; }
        case gui::type::EXCLUSIVE:         { return "GUI::EXCLUSIVE"; break; }


        case gui::type::GOVERMENT:     { return "GUI::GOVERMENT"; break; }
        case gui::type::STORE:         { return "GUI::STORE"; break; }
        case gui::type::SHOP:         { return "GUI::SHOP"; break; }
        case gui::type::ANGAR:         { return "GUI::ANGAR"; break; }
    
        case gui::type::CARGO_SLOT:         { return "GUI::CARGO_SLOT"; break; }
        case gui::type::GATE_SLOT:         { return "GUI::GATE_SLOT"; break; }

        case gui::type::WEAPON_SLOT:         { return "GUI::WEAPON_SLOT"; break; }
        case gui::type::WEAPON_SLOT1:         { return "GUI::WEAPON_SLOT1"; break; }
        case gui::type::WEAPON_SLOT2:         { return "GUI::WEAPON_SLOT2"; break; }
        case gui::type::WEAPON_SLOT3:         { return "GUI::WEAPON_SLOT3"; break; }
        case gui::type::WEAPON_SLOT4:         { return "GUI::WEAPON_SLOT4"; break; }
        case gui::type::WEAPON_SLOT5:         { return "GUI::WEAPON_SLOT5"; break; }
        case gui::type::WEAPON_SLOT6:         { return "GUI::WEAPON_SLOT6"; break; }
        case gui::type::WEAPON_SLOT7:         { return "GUI::WEAPON_SLOT7"; break; }
        case gui::type::WEAPON_SLOT8:         { return "GUI::WEAPON_SLOT8"; break; }
        case gui::type::WEAPON_SLOT9:         { return "GUI::WEAPON_SLOT9"; break; }
    
        case gui::type::WEAPON_SLOT1_SELECTOR: { return "GUI::WEAPON_SLOT1_SELECTOR"; break; }
        case gui::type::WEAPON_SLOT2_SELECTOR: { return "GUI::WEAPON_SLOT2_SELECTOR"; break; }
        case gui::type::WEAPON_SLOT3_SELECTOR: { return "GUI::WEAPON_SLOT3_SELECTOR"; break; }
        case gui::type::WEAPON_SLOT4_SELECTOR: { return "GUI::WEAPON_SLOT4_SELECTOR"; break; }
        case gui::type::WEAPON_SLOT5_SELECTOR: { return "GUI::WEAPON_SLOT5_SELECTOR"; break; }
        case gui::type::WEAPON_SLOT6_SELECTOR: { return "GUI::WEAPON_SLOT6_SELECTOR"; break; }
        case gui::type::WEAPON_SLOT7_SELECTOR: { return "GUI::WEAPON_SLOT7_SELECTOR"; break; }
        case gui::type::WEAPON_SLOT8_SELECTOR: { return "GUI::WEAPON_SLOT8_SELECTOR"; break; }
        case gui::type::WEAPON_SLOT9_SELECTOR: { return "GUI::WEAPON_SLOT9_SELECTOR"; break; }
         
        case gui::type::DRIVE_SLOT:         { return "GUI::DRIVE_SLOT"; break; }
        case gui::type::RADAR_SLOT:         { return "GUI::RADAR_SLOT"; break; }
        case gui::type::BAK_SLOT:         { return "GUI::BAK_SLOT"; break; }
        case gui::type::ENERGIZER_SLOT:     { return "GUI::ENERGIZER_SLOT"; break; }
        case gui::type::PROTECTOR_SLOT:     { return "GUI::PROTECTOR_SLOT"; break; }
        case gui::type::DROID_SLOT:         { return "GUI::DROID_SLOT"; break; }
        case gui::type::FREEZER_SLOT:     { return "GUI::FREEZER_SLOT"; break; }
        case gui::type::GRAPPLE_SLOT:     { return "GUI::GRAPPLE_SLOT"; break; }
        case gui::type::SCANER_SLOT:     { return "GUI::SCANER_SLOT"; break; }
        case gui::type::ARTEFACT_SLOT:     { return "GUI::ARTEFACT_SLOT"; break; }

        default:     { return "GUI::UNKNOWN id_type"; break; }
    }
}

gui::type getGuiItemSlotType(entity::Type val)
{
    switch(val)
    {
        case entity::Type::CARGO_SLOT:     { return gui::type::CARGO_SLOT; break; }
        case entity::Type::CARGO_SLOT1:    { return gui::type::CARGO_SLOT1; break; }
        case entity::Type::CARGO_SLOT2:    { return gui::type::CARGO_SLOT2; break; }
        case entity::Type::CARGO_SLOT3:    { return gui::type::CARGO_SLOT3; break; }
        case entity::Type::CARGO_SLOT4:    { return gui::type::CARGO_SLOT4; break; }
        case entity::Type::CARGO_SLOT5:    { return gui::type::CARGO_SLOT5; break; }
        case entity::Type::CARGO_SLOT6:    { return gui::type::CARGO_SLOT6; break; }
        case entity::Type::CARGO_SLOT7:    { return gui::type::CARGO_SLOT7; break; }
        case entity::Type::CARGO_SLOT8:    { return gui::type::CARGO_SLOT8; break; }
        case entity::Type::CARGO_SLOT9:    { return gui::type::CARGO_SLOT9; break; }
        case entity::Type::CARGO_SLOT10:   { return gui::type::CARGO_SLOT10; break; }
        case entity::Type::CARGO_SLOT11:   { return gui::type::CARGO_SLOT11; break; }
        case entity::Type::CARGO_SLOT12:   { return gui::type::CARGO_SLOT12; break; }
        case entity::Type::CARGO_SLOT13:   { return gui::type::CARGO_SLOT13; break; }
        case entity::Type::CARGO_SLOT14:   { return gui::type::CARGO_SLOT14; break; }
        case entity::Type::CARGO_SLOT15:   { return gui::type::CARGO_SLOT15; break; }
        case entity::Type::CARGO_SLOT16:   { return gui::type::CARGO_SLOT16; break; }
        case entity::Type::CARGO_SLOT17:   { return gui::type::CARGO_SLOT17; break; }
        case entity::Type::CARGO_SLOT18:   { return gui::type::CARGO_SLOT18; break; }

        case entity::Type::WEAPON_SLOT:    { return gui::type::WEAPON_SLOT; break; }
        case entity::Type::WEAPON_SLOT1:   { return gui::type::WEAPON_SLOT1; break; }
        case entity::Type::WEAPON_SLOT2:   { return gui::type::WEAPON_SLOT2; break; }
        case entity::Type::WEAPON_SLOT3:   { return gui::type::WEAPON_SLOT3; break; }
        case entity::Type::WEAPON_SLOT4:   { return gui::type::WEAPON_SLOT4; break; }
        case entity::Type::WEAPON_SLOT5:   { return gui::type::WEAPON_SLOT5; break; }
        case entity::Type::WEAPON_SLOT6:   { return gui::type::WEAPON_SLOT6; break; }
        case entity::Type::WEAPON_SLOT7:   { return gui::type::WEAPON_SLOT7; break; }
        case entity::Type::WEAPON_SLOT8:   { return gui::type::WEAPON_SLOT8; break; }
        case entity::Type::WEAPON_SLOT9:   { return gui::type::WEAPON_SLOT9; break; }

        case entity::Type::DRIVE_SLOT:   { return gui::type::DRIVE_SLOT; break; }
        case entity::Type::RADAR_SLOT:   { return gui::type::RADAR_SLOT; break; }
        case entity::Type::BAK_SLOT:   { return gui::type::BAK_SLOT; break; }
        case entity::Type::ENERGIZER_SLOT:   { return gui::type::ENERGIZER_SLOT; break; }
        case entity::Type::PROTECTOR_SLOT:   { return gui::type::PROTECTOR_SLOT; break; }
        case entity::Type::DROID_SLOT:   { return gui::type::DROID_SLOT; break; }
        case entity::Type::FREEZER_SLOT:   { return gui::type::FREEZER_SLOT; break; }
        case entity::Type::GRAPPLE_SLOT:   { return gui::type::GRAPPLE_SLOT; break; }
        case entity::Type::SCANER_SLOT:   { return gui::type::SCANER_SLOT; break; }

        case entity::Type::ARTEFACT_SLOT:   { return gui::type::ARTEFACT_SLOT; break; }
        case entity::Type::ARTEFACT_SLOT1:  { return gui::type::ARTEFACT_SLOT1; break; }
        case entity::Type::ARTEFACT_SLOT2:  { return gui::type::ARTEFACT_SLOT2; break; }
        case entity::Type::ARTEFACT_SLOT3:  { return gui::type::ARTEFACT_SLOT3; break; }
        case entity::Type::ARTEFACT_SLOT4:  { return gui::type::ARTEFACT_SLOT4; break; }

        case entity::Type::GATE_SLOT:   { return gui::type::GATE_SLOT; break; }
        //case entity::type::REPAIR_SLOT:   { return gui::type::REPAIR_SLOT; break; }
        //case entity::type::CHARGE_SLOT:   { return gui::type::CHARGE_SLOT; break; }
    }

    return gui::type::NONE;
}

gui::type getGuiItemSlotSelectorType(entity::Type val)
{
    switch(val)
    {
        case entity::Type::WEAPON_SLOT1:   { return gui::type::WEAPON_SLOT1_SELECTOR; break; }
        case entity::Type::WEAPON_SLOT2:   { return gui::type::WEAPON_SLOT2_SELECTOR; break; }
        case entity::Type::WEAPON_SLOT3:   { return gui::type::WEAPON_SLOT3_SELECTOR; break; }
        case entity::Type::WEAPON_SLOT4:   { return gui::type::WEAPON_SLOT4_SELECTOR; break; }
        case entity::Type::WEAPON_SLOT5:   { return gui::type::WEAPON_SLOT5_SELECTOR; break; }
        case entity::Type::WEAPON_SLOT6:   { return gui::type::WEAPON_SLOT6_SELECTOR; break; }
        case entity::Type::WEAPON_SLOT7:   { return gui::type::WEAPON_SLOT7_SELECTOR; break; }
        case entity::Type::WEAPON_SLOT8:   { return gui::type::WEAPON_SLOT8_SELECTOR; break; }
        case entity::Type::WEAPON_SLOT9:   { return gui::type::WEAPON_SLOT9_SELECTOR; break; }

        case entity::Type::DRIVE_SLOT:   { return gui::type::DRIVE_SLOT_SELECTOR; break; }
        case entity::Type::RADAR_SLOT:   { return gui::type::RADAR_SLOT_SELECTOR; break; }
        case entity::Type::BAK_SLOT:   { return gui::type::BAK_SLOT_SELECTOR; break; }
        case entity::Type::ENERGIZER_SLOT:   { return gui::type::ENERGIZER_SLOT_SELECTOR; break; }
        case entity::Type::PROTECTOR_SLOT:   { return gui::type::PROTECTOR_SLOT_SELECTOR; break; }
        case entity::Type::DROID_SLOT:   { return gui::type::DROID_SLOT_SELECTOR; break; }
        case entity::Type::FREEZER_SLOT:   { return gui::type::FREEZER_SLOT_SELECTOR; break; }
        case entity::Type::GRAPPLE_SLOT:   { return gui::type::GRAPPLE_SLOT_SELECTOR; break; }
        case entity::Type::SCANER_SLOT:   { return gui::type::SCANER_SLOT_SELECTOR; break; }
    }

    return gui::type::NONE;
}

