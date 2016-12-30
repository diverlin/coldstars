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

#include "type.hpp"

namespace ceti {

    Type::Type(int id, const std::string& string)
        :
          m_id(id)
        , m_string(string)
    {}

} // namespace ceti


//TYPE::GUI getGuiItemSlotType(type::entity val)
//{
//    switch(val)
//    {
//        case type::entity::CARGO_SLOT_ID:     { return TYPE::GUI::CARGO_SLOT_ID; break; }
//        case type::entity::CARGO_SLOT1_ID:    { return TYPE::GUI::CARGO_SLOT1_ID; break; }
//        case type::entity::CARGO_SLOT2_ID:    { return TYPE::GUI::CARGO_SLOT2_ID; break; }
//        case type::entity::CARGO_SLOT3_ID:    { return TYPE::GUI::CARGO_SLOT3_ID; break; }
//        case type::entity::CARGO_SLOT4_ID:    { return TYPE::GUI::CARGO_SLOT4_ID; break; }
//        case type::entity::CARGO_SLOT5_ID:    { return TYPE::GUI::CARGO_SLOT5_ID; break; }
//        case type::entity::CARGO_SLOT6_ID:    { return TYPE::GUI::CARGO_SLOT6_ID; break; }
//        case type::entity::CARGO_SLOT7_ID:    { return TYPE::GUI::CARGO_SLOT7_ID; break; }
//        case type::entity::CARGO_SLOT8_ID:    { return TYPE::GUI::CARGO_SLOT8_ID; break; }
//        case type::entity::CARGO_SLOT9_ID:    { return TYPE::GUI::CARGO_SLOT9_ID; break; }
//        case type::entity::CARGO_SLOT10_ID:   { return TYPE::GUI::CARGO_SLOT10_ID; break; }
//        case type::entity::CARGO_SLOT11_ID:   { return TYPE::GUI::CARGO_SLOT11_ID; break; }
//        case type::entity::CARGO_SLOT12_ID:   { return TYPE::GUI::CARGO_SLOT12_ID; break; }
//        case type::entity::CARGO_SLOT13_ID:   { return TYPE::GUI::CARGO_SLOT13_ID; break; }
//        case type::entity::CARGO_SLOT14_ID:   { return TYPE::GUI::CARGO_SLOT14_ID; break; }
//        case type::entity::CARGO_SLOT15_ID:   { return TYPE::GUI::CARGO_SLOT15_ID; break; }
//        case type::entity::CARGO_SLOT16_ID:   { return TYPE::GUI::CARGO_SLOT16_ID; break; }
//        case type::entity::CARGO_SLOT17_ID:   { return TYPE::GUI::CARGO_SLOT17_ID; break; }
//        case type::entity::CARGO_SLOT18_ID:   { return TYPE::GUI::CARGO_SLOT18_ID; break; }
                                
//        case type::entity::WEAPON_SLOT_ID:    { return TYPE::GUI::WEAPON_SLOT_ID; break; }
//        case type::entity::WEAPON_SLOT1_ID:   { return TYPE::GUI::WEAPON_SLOT1_ID; break; }
//        case type::entity::WEAPON_SLOT2_ID:   { return TYPE::GUI::WEAPON_SLOT2_ID; break; }
//        case type::entity::WEAPON_SLOT3_ID:   { return TYPE::GUI::WEAPON_SLOT3_ID; break; }
//        case type::entity::WEAPON_SLOT4_ID:   { return TYPE::GUI::WEAPON_SLOT4_ID; break; }
//        case type::entity::WEAPON_SLOT5_ID:   { return TYPE::GUI::WEAPON_SLOT5_ID; break; }
//        case type::entity::WEAPON_SLOT6_ID:   { return TYPE::GUI::WEAPON_SLOT6_ID; break; }
//        case type::entity::WEAPON_SLOT7_ID:   { return TYPE::GUI::WEAPON_SLOT7_ID; break; }
//        case type::entity::WEAPON_SLOT8_ID:   { return TYPE::GUI::WEAPON_SLOT8_ID; break; }
//        case type::entity::WEAPON_SLOT9_ID:   { return TYPE::GUI::WEAPON_SLOT9_ID; break; }
        
//        case type::entity::DRIVE_SLOT_ID:   { return TYPE::GUI::DRIVE_SLOT_ID; break; }
//        case type::entity::RADAR_SLOT_ID:   { return TYPE::GUI::RADAR_SLOT_ID; break; }
//        case type::entity::BAK_SLOT_ID:   { return TYPE::GUI::BAK_SLOT_ID; break; }
//        case type::entity::ENERGIZER_SLOT_ID:   { return TYPE::GUI::ENERGIZER_SLOT_ID; break; }
//        case type::entity::PROTECTOR_SLOT_ID:   { return TYPE::GUI::PROTECTOR_SLOT_ID; break; }
//        case type::entity::DROID_SLOT_ID:   { return TYPE::GUI::DROID_SLOT_ID; break; }
//        case type::entity::FREEZER_SLOT_ID:   { return TYPE::GUI::FREEZER_SLOT_ID; break; }
//        case type::entity::GRAPPLE_SLOT_ID:   { return TYPE::GUI::GRAPPLE_SLOT_ID; break; }
//        case type::entity::SCANER_SLOT_ID:   { return TYPE::GUI::SCANER_SLOT_ID; break; }

//        case type::entity::ARTEFACT_SLOT_ID:   { return TYPE::GUI::ARTEFACT_SLOT_ID; break; }
//        case type::entity::ARTEFACT_SLOT1_ID:  { return TYPE::GUI::ARTEFACT_SLOT1_ID; break; }
//        case type::entity::ARTEFACT_SLOT2_ID:  { return TYPE::GUI::ARTEFACT_SLOT2_ID; break; }
//        case type::entity::ARTEFACT_SLOT3_ID:  { return TYPE::GUI::ARTEFACT_SLOT3_ID; break; }
//        case type::entity::ARTEFACT_SLOT4_ID:  { return TYPE::GUI::ARTEFACT_SLOT4_ID; break; }
                                            
//        case type::entity::GATE_SLOT_ID:   { return TYPE::GUI::GATE_SLOT_ID; break; }
//        //case type::entity::REPAIR_SLOT_ID:   { return TYPE::GUI::REPAIR_SLOT_ID; break; }
//        //case type::entity::CHARGE_SLOT_ID:   { return TYPE::GUI::CHARGE_SLOT_ID; break; }
//    }
    
//    return TYPE::GUI::NONE_ID;
//}

//TYPE::GUI getGuiItemSlotSelectorType(type::entity val)
//{
//    switch(val)
//    {
//        case type::entity::WEAPON_SLOT1_ID:   { return TYPE::GUI::WEAPON_SLOT1_SELECTOR_ID; break; }
//        case type::entity::WEAPON_SLOT2_ID:   { return TYPE::GUI::WEAPON_SLOT2_SELECTOR_ID; break; }
//        case type::entity::WEAPON_SLOT3_ID:   { return TYPE::GUI::WEAPON_SLOT3_SELECTOR_ID; break; }
//        case type::entity::WEAPON_SLOT4_ID:   { return TYPE::GUI::WEAPON_SLOT4_SELECTOR_ID; break; }
//        case type::entity::WEAPON_SLOT5_ID:   { return TYPE::GUI::WEAPON_SLOT5_SELECTOR_ID; break; }
//        case type::entity::WEAPON_SLOT6_ID:   { return TYPE::GUI::WEAPON_SLOT6_SELECTOR_ID; break; }
//        case type::entity::WEAPON_SLOT7_ID:   { return TYPE::GUI::WEAPON_SLOT7_SELECTOR_ID; break; }
//        case type::entity::WEAPON_SLOT8_ID:   { return TYPE::GUI::WEAPON_SLOT8_SELECTOR_ID; break; }
//        case type::entity::WEAPON_SLOT9_ID:   { return TYPE::GUI::WEAPON_SLOT9_SELECTOR_ID; break; }
        
//        case type::entity::DRIVE_SLOT_ID:   { return TYPE::GUI::DRIVE_SLOT_SELECTOR_ID; break; }
//        case type::entity::RADAR_SLOT_ID:   { return TYPE::GUI::RADAR_SLOT_SELECTOR_ID; break; }
//        case type::entity::BAK_SLOT_ID:   { return TYPE::GUI::BAK_SLOT_SELECTOR_ID; break; }
//        case type::entity::ENERGIZER_SLOT_ID:   { return TYPE::GUI::ENERGIZER_SLOT_SELECTOR_ID; break; }
//        case type::entity::PROTECTOR_SLOT_ID:   { return TYPE::GUI::PROTECTOR_SLOT_SELECTOR_ID; break; }
//        case type::entity::DROID_SLOT_ID:   { return TYPE::GUI::DROID_SLOT_SELECTOR_ID; break; }
//        case type::entity::FREEZER_SLOT_ID:   { return TYPE::GUI::FREEZER_SLOT_SELECTOR_ID; break; }
//        case type::entity::GRAPPLE_SLOT_ID:   { return TYPE::GUI::GRAPPLE_SLOT_SELECTOR_ID; break; }
//        case type::entity::SCANER_SLOT_ID:   { return TYPE::GUI::SCANER_SLOT_SELECTOR_ID; break; }
//    }
    
//    return TYPE::GUI::NONE_ID;
//}
 
