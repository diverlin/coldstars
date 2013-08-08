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

#include <cmath>

#include "common.hpp"
#include "constants.hpp"
#include "Logger.hpp"

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
    
int getObjectSize(int w, int h)
{
    int area = w*h;
    if(area < SIZE_1_AREA) return SIZE_1_ID;
    if(area < SIZE_2_AREA) return SIZE_2_ID;
    if(area < SIZE_3_AREA) return SIZE_3_ID;
    if(area < SIZE_4_AREA) return SIZE_4_ID;
    if(area < SIZE_5_AREA) return SIZE_5_ID;
    if(area < SIZE_6_AREA) return SIZE_6_ID;
    if(area < SIZE_7_AREA) return SIZE_7_ID;
    if(area < SIZE_8_AREA) return SIZE_8_ID;
    if(area < SIZE_9_AREA) return SIZE_9_ID;
    if(area >= SIZE_9_AREA) return SIZE_10_ID;
    
    return SIZE_10_ID;
}



bool get_dPos_ToPoint(const Vec3<float>& p1, const Vec3<float>& p2, float velocity, Vec3<float>& d_pos)
{           
    Vec3<float> dir(p2-p1);

    if (!dir.IsNull())
    {
        dir.Normalize();
        d_pos.Set(dir * velocity);               
        return true;
    }
    else
    {
        d_pos.Set(0.0, 0.0, 0.0);               
        return false;
    }
}


bool get_dPos_ToPoint(const Vec3<float>& p1, const Vec3<float>& p2, float velocity, Vec3<float>& d_pos, float& rTo_angle_inD)
{
    Vec3<float> dir(p2-p1);

    if (!dir.IsNull())
    {             
        dir.Normalize();
        d_pos.Set(dir * velocity);   
        rTo_angle_inD = atan2(dir.y, dir.x) * RADIAN_TO_DEGREE_RATE;
        
        return true;
    }
    else
    {
        d_pos.Set(0.0, 0.0, 0.0); 
        rTo_angle_inD = atan2(0.0, 0.0) * RADIAN_TO_DEGREE_RATE;
        
        return false;
    }        
}

Color4<float> getColor4fById(int color_id)
{
    Color4<float> color;
    switch(color_id)
    {
        case COLOR::YELLOW_ID:
        {
            color.r = 255/255.0;
            color.g = 255/255.0;
            color.b = 235/255.0; // 235
            color.a = 1.0;
            
            break;
        }

        case COLOR::BLUE_ID:
        {
            color.r = 220/255.0; // 220
            color.g = 255/255.0;
            color.b = 255/255.0;
            color.a = 1.0;
            
            break;
        }
    }
    
    return color;
}
