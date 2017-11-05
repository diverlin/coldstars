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


#include "GuiType.hpp"

#include <cassert>

namespace gui {

std::string to_string(Type type_id)
{
    switch(type_id)
    {
        case gui::Type::NONE: { return "GUI::NONE"; }

        case gui::Type::MINERALS: { return "GUI::MINERALS"; }
    case gui::Type::FOOD:         { return "GUI::FOOD"; }
        case gui::Type::MEDICINE: { return "GUI::MEDICINE"; }
        case gui::Type::MILITARY: { return "GUI::MILITARY"; }
        case gui::Type::DRUG:     { return "GUI::DRUG"; }
        case gui::Type::EXCLUSIVE: { return "GUI::EXCLUSIVE"; }


        case gui::Type::GOVERMENT: { return "GUI::GOVERMENT"; }
        case gui::Type::STORE:     { return "GUI::STORE"; }
        case gui::Type::SHOP:      { return "GUI::SHOP"; }
        case gui::Type::ANGAR:     { return "GUI::ANGAR"; }
    
        case gui::Type::CARGO_SLOT: { return "GUI::CARGO_SLOT"; }
        case gui::Type::GATE_SLOT:  { return "GUI::GATE_SLOT"; }

        case gui::Type::WEAPON_SLOT:  { return "GUI::WEAPON_SLOT"; }
        case gui::Type::WEAPON_SLOT1: { return "GUI::WEAPON_SLOT1"; }
        case gui::Type::WEAPON_SLOT2: { return "GUI::WEAPON_SLOT2"; }
        case gui::Type::WEAPON_SLOT3: { return "GUI::WEAPON_SLOT3"; }
        case gui::Type::WEAPON_SLOT4: { return "GUI::WEAPON_SLOT4"; }
        case gui::Type::WEAPON_SLOT5: { return "GUI::WEAPON_SLOT5"; }
        case gui::Type::WEAPON_SLOT6: { return "GUI::WEAPON_SLOT6"; }
        case gui::Type::WEAPON_SLOT7: { return "GUI::WEAPON_SLOT7"; }
        case gui::Type::WEAPON_SLOT8: { return "GUI::WEAPON_SLOT8"; }
        case gui::Type::WEAPON_SLOT9: { return "GUI::WEAPON_SLOT9"; }
    
        case gui::Type::WEAPON_SLOT1_SELECTOR: { return "GUI::WEAPON_SLOT1_SELECTOR"; }
        case gui::Type::WEAPON_SLOT2_SELECTOR: { return "GUI::WEAPON_SLOT2_SELECTOR"; }
        case gui::Type::WEAPON_SLOT3_SELECTOR: { return "GUI::WEAPON_SLOT3_SELECTOR"; }
        case gui::Type::WEAPON_SLOT4_SELECTOR: { return "GUI::WEAPON_SLOT4_SELECTOR"; }
        case gui::Type::WEAPON_SLOT5_SELECTOR: { return "GUI::WEAPON_SLOT5_SELECTOR"; }
        case gui::Type::WEAPON_SLOT6_SELECTOR: { return "GUI::WEAPON_SLOT6_SELECTOR"; }
        case gui::Type::WEAPON_SLOT7_SELECTOR: { return "GUI::WEAPON_SLOT7_SELECTOR"; }
        case gui::Type::WEAPON_SLOT8_SELECTOR: { return "GUI::WEAPON_SLOT8_SELECTOR"; }
        case gui::Type::WEAPON_SLOT9_SELECTOR: { return "GUI::WEAPON_SLOT9_SELECTOR"; }
         
        case gui::Type::DRIVE_SLOT:     { return "GUI::DRIVE_SLOT"; }
        case gui::Type::RADAR_SLOT:     { return "GUI::RADAR_SLOT"; }
        case gui::Type::BAK_SLOT:       { return "GUI::BAK_SLOT"; }
        case gui::Type::ENERGIZER_SLOT: { return "GUI::ENERGIZER_SLOT"; }
        case gui::Type::PROTECTOR_SLOT: { return "GUI::PROTECTOR_SLOT"; }
        case gui::Type::DROID_SLOT:     { return "GUI::DROID_SLOT"; }
        case gui::Type::FREEZER_SLOT:   { return "GUI::FREEZER_SLOT"; }
        case gui::Type::GRAPPLE_SLOT:   { return "GUI::GRAPPLE_SLOT"; }
        case gui::Type::SCANER_SLOT:    { return "GUI::SCANER_SLOT"; }
        case gui::Type::ARTEFACT_SLOT:  { return "GUI::ARTEFACT_SLOT"; }
    }
     assert(false);
     return "";
}

Type getGuiItemSlotType(entity::Type val)
{
    switch(val)
    {
        case entity::Type::CARGO_SLOT:     { return gui::Type::CARGO_SLOT; }
        case entity::Type::CARGO_SLOT1:    { return gui::Type::CARGO_SLOT1; }
        case entity::Type::CARGO_SLOT2:    { return gui::Type::CARGO_SLOT2; }
        case entity::Type::CARGO_SLOT3:    { return gui::Type::CARGO_SLOT3; }
        case entity::Type::CARGO_SLOT4:    { return gui::Type::CARGO_SLOT4; }
        case entity::Type::CARGO_SLOT5:    { return gui::Type::CARGO_SLOT5; }
        case entity::Type::CARGO_SLOT6:    { return gui::Type::CARGO_SLOT6; }
        case entity::Type::CARGO_SLOT7:    { return gui::Type::CARGO_SLOT7; }
        case entity::Type::CARGO_SLOT8:    { return gui::Type::CARGO_SLOT8; }
        case entity::Type::CARGO_SLOT9:    { return gui::Type::CARGO_SLOT9; }
        case entity::Type::CARGO_SLOT10:   { return gui::Type::CARGO_SLOT10; }
        case entity::Type::CARGO_SLOT11:   { return gui::Type::CARGO_SLOT11; }
        case entity::Type::CARGO_SLOT12:   { return gui::Type::CARGO_SLOT12; }
        case entity::Type::CARGO_SLOT13:   { return gui::Type::CARGO_SLOT13; }
        case entity::Type::CARGO_SLOT14:   { return gui::Type::CARGO_SLOT14; }
        case entity::Type::CARGO_SLOT15:   { return gui::Type::CARGO_SLOT15; }
        case entity::Type::CARGO_SLOT16:   { return gui::Type::CARGO_SLOT16; }
        case entity::Type::CARGO_SLOT17:   { return gui::Type::CARGO_SLOT17; }
        case entity::Type::CARGO_SLOT18:   { return gui::Type::CARGO_SLOT18; }

        case entity::Type::WEAPON_SLOT:    { return gui::Type::WEAPON_SLOT; }
        case entity::Type::WEAPON1_SLOT:   { return gui::Type::WEAPON_SLOT1; }
        case entity::Type::WEAPON2_SLOT:   { return gui::Type::WEAPON_SLOT2; }
        case entity::Type::WEAPON3_SLOT:   { return gui::Type::WEAPON_SLOT3; }
        case entity::Type::WEAPON4_SLOT:   { return gui::Type::WEAPON_SLOT4; }
        case entity::Type::WEAPON5_SLOT:   { return gui::Type::WEAPON_SLOT5; }
        case entity::Type::WEAPON6_SLOT:   { return gui::Type::WEAPON_SLOT6; }
        case entity::Type::WEAPON7_SLOT:   { return gui::Type::WEAPON_SLOT7; }
        case entity::Type::WEAPON8_SLOT:   { return gui::Type::WEAPON_SLOT8; }
        case entity::Type::WEAPON9_SLOT:   { return gui::Type::WEAPON_SLOT9; }

        case entity::Type::DRIVE_SLOT:   { return gui::Type::DRIVE_SLOT; }
        case entity::Type::RADAR_SLOT:   { return gui::Type::RADAR_SLOT; }
        case entity::Type::BAK_SLOT:   { return gui::Type::BAK_SLOT; }
        case entity::Type::ENERGIZER_SLOT:   { return gui::Type::ENERGIZER_SLOT; }
        case entity::Type::PROTECTOR_SLOT:   { return gui::Type::PROTECTOR_SLOT; }
        case entity::Type::DROID_SLOT:   { return gui::Type::DROID_SLOT; }
        case entity::Type::FREEZER_SLOT:   { return gui::Type::FREEZER_SLOT; }
        case entity::Type::GRAPPLE_SLOT:   { return gui::Type::GRAPPLE_SLOT; }
        case entity::Type::SCANER_SLOT:   { return gui::Type::SCANER_SLOT; }

        case entity::Type::ARTEFACT_SLOT:   { return gui::Type::ARTEFACT_SLOT; }
        case entity::Type::ARTEFACT_SLOT1:  { return gui::Type::ARTEFACT_SLOT1; }
        case entity::Type::ARTEFACT_SLOT2:  { return gui::Type::ARTEFACT_SLOT2; }
        case entity::Type::ARTEFACT_SLOT3:  { return gui::Type::ARTEFACT_SLOT3; }
        case entity::Type::ARTEFACT_SLOT4:  { return gui::Type::ARTEFACT_SLOT4; }

        case entity::Type::GATE_SLOT:   { return gui::Type::GATE_SLOT; }
        //case entity::Type::REPAIR_SLOT:   { return gui::type::REPAIR_SLOT; }
        //case entity::Type::CHARGE_SLOT:   { return gui::type::CHARGE_SLOT; }
    }

    assert(false);
    return gui::Type::NONE;
}

Type getGuiItemSlotSelectorType(entity::Type id)
{
    switch(id)
    {
        case entity::Type::WEAPON1_SLOT:   { return gui::Type::WEAPON_SLOT1_SELECTOR; }
        case entity::Type::WEAPON2_SLOT:   { return gui::Type::WEAPON_SLOT2_SELECTOR; }
        case entity::Type::WEAPON3_SLOT:   { return gui::Type::WEAPON_SLOT3_SELECTOR; }
        case entity::Type::WEAPON4_SLOT:   { return gui::Type::WEAPON_SLOT4_SELECTOR; }
        case entity::Type::WEAPON5_SLOT:   { return gui::Type::WEAPON_SLOT5_SELECTOR; }
        case entity::Type::WEAPON6_SLOT:   { return gui::Type::WEAPON_SLOT6_SELECTOR; }
        case entity::Type::WEAPON7_SLOT:   { return gui::Type::WEAPON_SLOT7_SELECTOR; }
        case entity::Type::WEAPON8_SLOT:   { return gui::Type::WEAPON_SLOT8_SELECTOR; }
        case entity::Type::WEAPON9_SLOT:   { return gui::Type::WEAPON_SLOT9_SELECTOR; }

        case entity::Type::DRIVE_SLOT:   { return gui::Type::DRIVE_SLOT_SELECTOR; }
        case entity::Type::RADAR_SLOT:   { return gui::Type::RADAR_SLOT_SELECTOR; }
        case entity::Type::BAK_SLOT:   { return gui::Type::BAK_SLOT_SELECTOR; }
        case entity::Type::ENERGIZER_SLOT:   { return gui::Type::ENERGIZER_SLOT_SELECTOR; }
        case entity::Type::PROTECTOR_SLOT:   { return gui::Type::PROTECTOR_SLOT_SELECTOR; }
        case entity::Type::DROID_SLOT:   { return gui::Type::DROID_SLOT_SELECTOR; }
        case entity::Type::FREEZER_SLOT:   { return gui::Type::FREEZER_SLOT_SELECTOR; }
        case entity::Type::GRAPPLE_SLOT:   { return gui::Type::GRAPPLE_SLOT_SELECTOR; }
        case entity::Type::SCANER_SLOT:   { return gui::Type::SCANER_SLOT_SELECTOR; }
    }
    //assert(false);
    return gui::Type::NONE;
}

} // namespace gui
