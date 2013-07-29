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


std::string getGuiTypeStr(GUI::TYPE type_id)
{
	switch(type_id)
	{
		case GUI::TYPE::NONE_ID: { return "GUI::NONE_ID"; break; }
			
		case GUI::TYPE::MINERALS_ID: 		{ return "GUI::MINERALS_ID"; break; }
		case GUI::TYPE::FOOD_ID: 			{ return "GUI::FOOD_ID"; break; }
		case GUI::TYPE::MEDICINE_ID: 		{ return "GUI::MEDICINE_ID"; break; }
		case GUI::TYPE::MILITARY_ID: 		{ return "GUI::MILITARY_ID"; break; }
		case GUI::TYPE::DRUG_ID: 			{ return "GUI::DRUG_ID"; break; }
		case GUI::TYPE::EXCLUSIVE_ID: 		{ return "GUI::EXCLUSIVE_ID"; break; }


		case GUI::TYPE::GOVERMENT_ID: 	{ return "GUI::GOVERMENT_ID"; break; }
		case GUI::TYPE::STORE_ID: 		{ return "GUI::STORE_ID"; break; }
		case GUI::TYPE::SHOP_ID: 		{ return "GUI::SHOP_ID"; break; }
		case GUI::TYPE::ANGAR_ID: 		{ return "GUI::ANGAR_ID"; break; }  		
	
		case GUI::TYPE::CARGO_SLOT_ID: 		{ return "GUI::CARGO_SLOT_ID"; break; }	
		case GUI::TYPE::GATE_SLOT_ID: 		{ return "GUI::GATE_SLOT_ID"; break; }		

		case GUI::TYPE::WEAPON_SLOT_ID: 		{ return "GUI::WEAPON_SLOT_ID"; break; }
		case GUI::TYPE::WEAPON_SLOT1_ID: 		{ return "GUI::WEAPON_SLOT1_ID"; break; }
		case GUI::TYPE::WEAPON_SLOT2_ID: 		{ return "GUI::WEAPON_SLOT2_ID"; break; }
		case GUI::TYPE::WEAPON_SLOT3_ID: 		{ return "GUI::WEAPON_SLOT3_ID"; break; }
		case GUI::TYPE::WEAPON_SLOT4_ID: 		{ return "GUI::WEAPON_SLOT4_ID"; break; }
		case GUI::TYPE::WEAPON_SLOT5_ID: 		{ return "GUI::WEAPON_SLOT5_ID"; break; }
		case GUI::TYPE::WEAPON_SLOT6_ID: 		{ return "GUI::WEAPON_SLOT6_ID"; break; }
		case GUI::TYPE::WEAPON_SLOT7_ID: 		{ return "GUI::WEAPON_SLOT7_ID"; break; }
		case GUI::TYPE::WEAPON_SLOT8_ID: 		{ return "GUI::WEAPON_SLOT8_ID"; break; }
		case GUI::TYPE::WEAPON_SLOT9_ID: 		{ return "GUI::WEAPON_SLOT9_ID"; break; }
	
        case GUI::TYPE::WEAPON_SLOT1_SELECTOR_ID: { return "GUI::WEAPON_SLOT1_SELECTOR_ID"; break; }
        case GUI::TYPE::WEAPON_SLOT2_SELECTOR_ID: { return "GUI::WEAPON_SLOT2_SELECTOR_ID"; break; }
        case GUI::TYPE::WEAPON_SLOT3_SELECTOR_ID: { return "GUI::WEAPON_SLOT3_SELECTOR_ID"; break; }
        case GUI::TYPE::WEAPON_SLOT4_SELECTOR_ID: { return "GUI::WEAPON_SLOT4_SELECTOR_ID"; break; }
        case GUI::TYPE::WEAPON_SLOT5_SELECTOR_ID: { return "GUI::WEAPON_SLOT5_SELECTOR_ID"; break; }
        case GUI::TYPE::WEAPON_SLOT6_SELECTOR_ID: { return "GUI::WEAPON_SLOT6_SELECTOR_ID"; break; }
        case GUI::TYPE::WEAPON_SLOT7_SELECTOR_ID: { return "GUI::WEAPON_SLOT7_SELECTOR_ID"; break; }
        case GUI::TYPE::WEAPON_SLOT8_SELECTOR_ID: { return "GUI::WEAPON_SLOT8_SELECTOR_ID"; break; }
        case GUI::TYPE::WEAPON_SLOT9_SELECTOR_ID: { return "GUI::WEAPON_SLOT9_SELECTOR_ID"; break; }
         
        case GUI::TYPE::DRIVE_SLOT_ID: 		{ return "GUI::DRIVE_SLOT_ID"; break; }
		case GUI::TYPE::RADAR_SLOT_ID: 		{ return "GUI::RADAR_SLOT_ID"; break; }
		case GUI::TYPE::BAK_SLOT_ID: 		{ return "GUI::BAK_SLOT_ID"; break; }
		case GUI::TYPE::ENERGIZER_SLOT_ID: 	{ return "GUI::ENERGIZER_SLOT_ID"; break; }
		case GUI::TYPE::PROTECTOR_SLOT_ID: 	{ return "GUI::PROTECTOR_SLOT_ID"; break; }
		case GUI::TYPE::DROID_SLOT_ID: 		{ return "GUI::DROID_SLOT_ID"; break; }
		case GUI::TYPE::FREEZER_SLOT_ID: 	{ return "GUI::FREEZER_SLOT_ID"; break; }
		case GUI::TYPE::GRAPPLE_SLOT_ID: 	{ return "GUI::GRAPPLE_SLOT_ID"; break; }
		case GUI::TYPE::SCANER_SLOT_ID: 	{ return "GUI::SCANER_SLOT_ID"; break; }
		case GUI::TYPE::ARTEFACT_SLOT_ID: 	{ return "GUI::ARTEFACT_SLOT_ID"; break; }

		default: 	{ return "GUI::UNKNOWN ID"; break; }
	}
}
