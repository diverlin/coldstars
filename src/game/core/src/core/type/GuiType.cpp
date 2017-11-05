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
    
//        case gui::Type::CARGO_SLOT: { return "GUI::CARGO_SLOT"; }
        case gui::Type::GATE_SLOT:  { return "GUI::GATE_SLOT"; }

//        case gui::Type::WEAPON_SLOT:  { return "GUI::WEAPON_SLOT"; }
//        case gui::Type::WEAPON_SLOT1: { return "GUI::WEAPON_SLOT1"; }
//        case gui::Type::WEAPON_SLOT2: { return "GUI::WEAPON_SLOT2"; }
//        case gui::Type::WEAPON_SLOT3: { return "GUI::WEAPON_SLOT3"; }
//        case gui::Type::WEAPON_SLOT4: { return "GUI::WEAPON_SLOT4"; }
//        case gui::Type::WEAPON_SLOT5: { return "GUI::WEAPON_SLOT5"; }
//        case gui::Type::WEAPON_SLOT6: { return "GUI::WEAPON_SLOT6"; }
//        case gui::Type::WEAPON_SLOT7: { return "GUI::WEAPON_SLOT7"; }
//        case gui::Type::WEAPON_SLOT8: { return "GUI::WEAPON_SLOT8"; }
//        case gui::Type::WEAPON_SLOT9: { return "GUI::WEAPON_SLOT9"; }
    
//        case gui::Type::WEAPON_SLOT1_SELECTOR: { return "GUI::WEAPON_SLOT1_SELECTOR"; }
//        case gui::Type::WEAPON_SLOT2_SELECTOR: { return "GUI::WEAPON_SLOT2_SELECTOR"; }
//        case gui::Type::WEAPON_SLOT3_SELECTOR: { return "GUI::WEAPON_SLOT3_SELECTOR"; }
//        case gui::Type::WEAPON_SLOT4_SELECTOR: { return "GUI::WEAPON_SLOT4_SELECTOR"; }
//        case gui::Type::WEAPON_SLOT5_SELECTOR: { return "GUI::WEAPON_SLOT5_SELECTOR"; }
//        case gui::Type::WEAPON_SLOT6_SELECTOR: { return "GUI::WEAPON_SLOT6_SELECTOR"; }
//        case gui::Type::WEAPON_SLOT7_SELECTOR: { return "GUI::WEAPON_SLOT7_SELECTOR"; }
//        case gui::Type::WEAPON_SLOT8_SELECTOR: { return "GUI::WEAPON_SLOT8_SELECTOR"; }
//        case gui::Type::WEAPON_SLOT9_SELECTOR: { return "GUI::WEAPON_SLOT9_SELECTOR"; }
         
//        case gui::Type::DRIVE_SLOT:     { return "GUI::DRIVE_SLOT"; }
//        case gui::Type::RADAR_SLOT:     { return "GUI::RADAR_SLOT"; }
//        case gui::Type::BAK_SLOT:       { return "GUI::BAK_SLOT"; }
//        case gui::Type::ENERGIZER_SLOT: { return "GUI::ENERGIZER_SLOT"; }
//        case gui::Type::PROTECTOR_SLOT: { return "GUI::PROTECTOR_SLOT"; }
//        case gui::Type::DROID_SLOT:     { return "GUI::DROID_SLOT"; }
//        case gui::Type::FREEZER_SLOT:   { return "GUI::FREEZER_SLOT"; }
//        case gui::Type::GRAPPLE_SLOT:   { return "GUI::GRAPPLE_SLOT"; }
//        case gui::Type::SCANER_SLOT:    { return "GUI::SCANER_SLOT"; }
//        case gui::Type::ARTEFACT_SLOT:  { return "GUI::ARTEFACT_SLOT"; }
    }
     assert(false);
     return "";
}

//Type getGuiItemSlotType(slot::Type type)
//{
//    switch(type)
//    {
//        case slot::Type::CARGO:     { return gui::Type::CARGO_SLOT; }
//        case slot::Type::WEAPON:    { return gui::Type::WEAPON_SLOT; }

//        case slot::Type::DRIVE:   { return gui::Type::DRIVE_SLOT; }
//        case slot::Type::RADAR:   { return gui::Type::RADAR_SLOT; }
//        case slot::Type::BAK:   { return gui::Type::BAK_SLOT; }
//        case slot::Type::ENERGIZER:   { return gui::Type::ENERGIZER_SLOT; }
//        case slot::Type::PROTECTOR:   { return gui::Type::PROTECTOR_SLOT; }
//        case slot::Type::DROID:   { return gui::Type::DROID_SLOT; }
//        case slot::Type::FREEZER:   { return gui::Type::FREEZER_SLOT; }
//        case slot::Type::GRAPPLE:   { return gui::Type::GRAPPLE_SLOT; }
//        case slot::Type::SCANER:   { return gui::Type::SCANER_SLOT; }

//        case slot::Type::ARTEFACT:   { return gui::Type::ARTEFACT_SLOT; }

//        //case slot::Type::GATE_SLOT:   { return gui::Type::GATE_SLOT; }
//        //case entity::Type::REPAIR_SLOT:   { return gui::type::REPAIR_SLOT; }
//        //case entity::Type::CHARGE_SLOT:   { return gui::type::CHARGE_SLOT; }
//    }

//    assert(false);
//    return gui::Type::NONE;
//}

//Type getGuiItemSlotSelectorType(slot::Type type)
//{
//    switch(type)
//    {
////        case entity::Type::WEAPON1_SLOT:   { return gui::Type::WEAPON_SLOT1_SELECTOR; }
////        case entity::Type::WEAPON2_SLOT:   { return gui::Type::WEAPON_SLOT2_SELECTOR; }
////        case entity::Type::WEAPON3_SLOT:   { return gui::Type::WEAPON_SLOT3_SELECTOR; }
////        case entity::Type::WEAPON4_SLOT:   { return gui::Type::WEAPON_SLOT4_SELECTOR; }
////        case entity::Type::WEAPON5_SLOT:   { return gui::Type::WEAPON_SLOT5_SELECTOR; }
////        case entity::Type::WEAPON6_SLOT:   { return gui::Type::WEAPON_SLOT6_SELECTOR; }
////        case entity::Type::WEAPON7_SLOT:   { return gui::Type::WEAPON_SLOT7_SELECTOR; }
////        case entity::Type::WEAPON8_SLOT:   { return gui::Type::WEAPON_SLOT8_SELECTOR; }
////        case entity::Type::WEAPON9_SLOT:   { return gui::Type::WEAPON_SLOT9_SELECTOR; }

//        case slot::Type::DRIVE:   { return gui::Type::DRIVE_SLOT_SELECTOR; }
//        case slot::Type::RADAR:   { return gui::Type::RADAR_SLOT_SELECTOR; }
//        case slot::Type::BAK:   { return gui::Type::BAK_SLOT_SELECTOR; }
//        case slot::Type::ENERGIZER:   { return gui::Type::ENERGIZER_SLOT_SELECTOR; }
//        case slot::Type::PROTECTOR:   { return gui::Type::PROTECTOR_SLOT_SELECTOR; }
//        case slot::Type::DROID:   { return gui::Type::DROID_SLOT_SELECTOR; }
//        case slot::Type::FREEZER:   { return gui::Type::FREEZER_SLOT_SELECTOR; }
//        case slot::Type::GRAPPLE:   { return gui::Type::GRAPPLE_SLOT_SELECTOR; }
//        case slot::Type::SCANER:   { return gui::Type::SCANER_SLOT_SELECTOR; }
//    }
//    assert(false);
//    return gui::Type::NONE;
//}

} // namespace gui
