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

#include "TextureManager.hpp"

#include <types/TextureTypes.hpp>
#include <types/RaceTypes.hpp>

#include <math/rand.hpp>
#include <common/Logger.hpp>
#include <common/constants.hpp>

#include <struct/RaceInformationCollector.hpp>

#include <jeti/TextureOb.hpp>


TextureManager& TextureManager::Instance()
{
    static TextureManager instance;
    return instance;
}

void TextureManager::Add(jeti::TextureOb* texOb)
{
    textureOb_total_vec.push_back(texOb);

    switch(texOb->GetAssociation().type_id)
    {
    case TYPE::TEXTURE::SPACESTATION_ID: { spacestation_texOb_vec.push_back(texOb);    break; }
    case TYPE::TEXTURE::SATELLITE_ID:    { satellite_texOb_vec.push_back(texOb);   break; }
        
    case TYPE::TEXTURE::ITEM_SLOT_ID:    { itemslot_texOb_vec.push_back(texOb);        break; }
    case TYPE::TEXTURE::VEHICLE_SLOT_ID: { vehicleslot_texOb_vec.push_back(texOb); break; }
    case TYPE::TEXTURE::TURREL_ID:      { turrel_texOb_vec.push_back(texOb);      break; }
        
    case TYPE::TEXTURE::NEBULA_BACKGROUND_ID:      { nebulaBgEffect_texOb_vec.push_back(texOb); break; }
    case TYPE::TEXTURE::STAR_ID:        { star_texOb_vec.push_back(texOb);           break; }
    case TYPE::TEXTURE::PLANET_ID:      { planet_texOb_vec.push_back(texOb);         break; }
    case TYPE::TEXTURE::ATMOSPHERE_ID:  { atmosphere_texOb_vec.push_back(texOb);     break; }
    case TYPE::TEXTURE::RING_ID:  { ring_texOb_vec.push_back(texOb);     break; }
    case TYPE::TEXTURE::SHIP_ID:
    {
        TYPE::RACE race_id = texOb->GetAssociation().race_id;
        switch(texOb->GetAssociation().subtype_id)
        {
        case TYPE::ENTITY::RANGER_ID:   { ship_ranger_texOb_vec[static_cast<int>(race_id)].push_back(texOb);   break; }
        case TYPE::ENTITY::WARRIOR_ID:  { ship_warrior_texOb_vec[static_cast<int>(race_id)].push_back(texOb);  break; }
        case TYPE::ENTITY::TRADER_ID:   { ship_trader_texOb_vec[static_cast<int>(race_id)].push_back(texOb);   break; }
        case TYPE::ENTITY::PIRAT_ID:    { ship_pirat_texOb_vec[static_cast<int>(race_id)].push_back(texOb);    break; }
        case TYPE::ENTITY::DIPLOMAT_ID: { ship_diplomat_texOb_vec[static_cast<int>(race_id)].push_back(texOb); break; }
        }
    }
    case TYPE::TEXTURE::ROCKET_BULLET_ID: { rocketBullet_texOb_vec.push_back(texOb); break; }
    case TYPE::TEXTURE::LAZER_EFFECT_ID:  { lazerEffect_texOb_vec.push_back(texOb);  break; }
    case TYPE::TEXTURE::SHIELD_EFFECT_ID: { shieldEffect_texOb_vec.push_back(texOb); break; }
    case TYPE::TEXTURE::DISTANTSTAR_ID:   { starBgEffect_texOb_vec.push_back(texOb); break; }
    case TYPE::TEXTURE::PARTICLE_EFFECT_ID:      { particles_texOb_vec.push_back(texOb); break; }

    // ASTEROIDS/MINERALS
    case TYPE::TEXTURE::ASTEROID_ID:  { asteroid_texOb_vec.push_back(texOb);  break; }
    case TYPE::TEXTURE::MINERAL_ID:   { mineral_texOb_vec.push_back(texOb);   break; }
    case TYPE::TEXTURE::CONTAINER_ID: { container_texOb_vec.push_back(texOb); break; }
    case TYPE::TEXTURE::BOMB_ID:      { bomb_texOb_vec.push_back(texOb);      break; }

    case TYPE::TEXTURE::BLACKHOLE_ID: { blackhole_texOb_vec.push_back(texOb); break; }

    // LAND
    case TYPE::TEXTURE::NATURELAND_BACKGROUND_ID: { landBg_texOb_vec.push_back(texOb); break; }

    // IN KOSMOPORT
    case TYPE::TEXTURE::ANGAR_BACKGROUND_ID: { angarBg_texOb_vec.push_back(texOb); break; }
    case TYPE::TEXTURE::STORE_BACKGROUND_ID: { storeBg_texOb_vec.push_back(texOb); break; }
    case TYPE::TEXTURE::SHOP_BACKGROUND_ID:  { shopBg_texOb_vec.push_back(texOb); break; }
    case TYPE::TEXTURE::GOVERMENT_BACKGROUND_ID: { govermentBg_texOb_vec.push_back(texOb); break; }
        
        
    // ITEMS
    case TYPE::TEXTURE::ROCKET_EQUIPMENT_ID:      { rocketEquipment_texOb_vec.push_back(texOb);      break; }
    case TYPE::TEXTURE::LAZER_EQUIPMENT_ID:       { lazerEquipment_texOb_vec.push_back(texOb);       break; }
    case TYPE::TEXTURE::DRIVE_EQUIPMENT_ID:       { driveEquipment_texOb_vec.push_back(texOb);       break; }
    case TYPE::TEXTURE::PROTECTOR_EQUIPMENT_ID:   { protectorEquipment_texOb_vec.push_back(texOb);   break; }
    case TYPE::TEXTURE::DROID_EQUIPMENT_ID:       { droidEquipment_texOb_vec.push_back(texOb);       break; }
    case TYPE::TEXTURE::GRAPPLE_EQUIPMENT_ID:     { grappleEquipment_texOb_vec.push_back(texOb);     break; }
    case TYPE::TEXTURE::BAK_EQUIPMENT_ID:         { bakEquipment_texOb_vec.push_back(texOb);         break; }
    case TYPE::TEXTURE::ENERGIZER_EQUIPMENT_ID: { energyBlockEquipment_texOb_vec.push_back(texOb); break; }
    case TYPE::TEXTURE::FREEZER_EQUIPMENT_ID:     { freezerEquipment_texOb_vec.push_back(texOb);     break; }
    case TYPE::TEXTURE::RADAR_EQUIPMENT_ID:       { radarEquipment_texOb_vec.push_back(texOb);       break; }
    case TYPE::TEXTURE::SCANER_EQUIPMENT_ID:      { scanerEquipment_texOb_vec.push_back(texOb);      break; }

    case TYPE::TEXTURE::MODULE_ID: { module_texOb_vec.push_back(texOb);      break; }

    case TYPE::TEXTURE::FACE_ID:
    {
        switch(texOb->GetAssociation().race_id)
        {
        case TYPE::RACE::R0_ID: { face_race0_texOb_vec.push_back(texOb); break; }
        case TYPE::RACE::R1_ID: { face_race1_texOb_vec.push_back(texOb); break; }
        case TYPE::RACE::R2_ID: { face_race2_texOb_vec.push_back(texOb); break; }
        case TYPE::RACE::R3_ID: { face_race3_texOb_vec.push_back(texOb); break; }
        case TYPE::RACE::R4_ID: { face_race4_texOb_vec.push_back(texOb); break; }

        case TYPE::RACE::R6_ID: { face_race6_texOb_vec.push_back(texOb); break; }
        case TYPE::RACE::R7_ID: { face_race7_texOb_vec.push_back(texOb); break; }
        }
        break;
    }
    }
}


jeti::TextureOb* TextureManager::_GetRandomTextureObFromVec(const std::vector<jeti::TextureOb*>& textureOb_vec)
{
    jeti::TextureOb* requested_texOb = nullptr;

    if (textureOb_vec.size() == 1)
    {
        requested_texOb = textureOb_vec[0];
    }
    if (textureOb_vec.size() > 1)
    {
        requested_texOb = textureOb_vec[getRandInt(0, textureOb_vec.size()-1)];
    }

    return requested_texOb;
}

jeti::TextureOb* TextureManager::_GetShipTexObByClosestSizeFromVec(const std::vector<jeti::TextureOb*>& textureOb_vec, int size_id)
{  
    jeti::TextureOb* requested_texOb = _TryGetShipTexObBySizeFromVec(textureOb_vec, size_id);
    int sign_base = -1;
    int sign = 1;
    int i = 1;

    while (requested_texOb == nullptr)
    {
        sign *= sign_base;
        size_id += sign*i;
        requested_texOb = _TryGetShipTexObBySizeFromVec(textureOb_vec, size_id);
        i++;
        if (size_id > 2*SIZE_10_ID)
        {
            break;
        }
    }

    assert(requested_texOb);
    return requested_texOb;
}


jeti::TextureOb* TextureManager::_TryGetShipTexObBySizeFromVec(const std::vector<jeti::TextureOb*>& textureOb_vec, int size_id)
{  
    jeti::TextureOb* requested_texOb  = nullptr;
    for (unsigned int i=0; i<textureOb_vec.size(); i++)
    {
        if (textureOb_vec[i]->GetData().size_id == size_id)
        {
            requested_texOb = textureOb_vec[i];
            break;
        }
    }
    return requested_texOb;
}

jeti::TextureOb* TextureManager::_GetShipTexObBySizeFromVec(const std::vector<jeti::TextureOb*>& textureOb_vec, int size_id)
{
    jeti::TextureOb* requested_texOb  = _TryGetShipTexObBySizeFromVec(textureOb_vec, size_id);
//    if (FALSE_RESOURCES) {
//        requested_texOb = ship_race0_ranger_texOb_vec[0];
//    }

    return requested_texOb;
}

jeti::TextureOb* TextureManager::GetRandomFaceTexObWithFolloingAttributes(TYPE::RACE race_id)
{
    jeti::TextureOb* requested_texOb = nullptr;
    switch(race_id)
    {
        case TYPE::RACE::R0_ID: { requested_texOb = _GetRandomTextureObFromVec(face_race0_texOb_vec); break; }
        case TYPE::RACE::R1_ID: { requested_texOb = _GetRandomTextureObFromVec(face_race1_texOb_vec); break; }
        case TYPE::RACE::R2_ID: { requested_texOb = _GetRandomTextureObFromVec(face_race2_texOb_vec); break; }
        case TYPE::RACE::R3_ID: { requested_texOb = _GetRandomTextureObFromVec(face_race3_texOb_vec); break; }
        case TYPE::RACE::R4_ID: { requested_texOb = _GetRandomTextureObFromVec(face_race4_texOb_vec); break; }

        case TYPE::RACE::R6_ID: { requested_texOb = _GetRandomTextureObFromVec(face_race6_texOb_vec); break; }
        case TYPE::RACE::R7_ID: { requested_texOb = _GetRandomTextureObFromVec(face_race7_texOb_vec); break; }
    }
    
    assert(requested_texOb);
    return requested_texOb;
}

jeti::TextureOb* TextureManager::GetRandomShipTexObWithFollowingAtrributes(TYPE::RACE race_id, TYPE::ENTITY subtype_id, int size_id)
{
    jeti::TextureOb* requested_texOb  = nullptr;

    switch(subtype_id)
    {
    case TYPE::ENTITY::RANGER_ID:   { requested_texOb = _GetShipTexObByClosestSizeFromVec(ship_ranger_texOb_vec[static_cast<int>(race_id)], size_id);   break; }
    case TYPE::ENTITY::WARRIOR_ID:  { requested_texOb = _GetShipTexObByClosestSizeFromVec(ship_warrior_texOb_vec[static_cast<int>(race_id)], size_id);  break; }
    case TYPE::ENTITY::TRADER_ID:   { requested_texOb = _GetShipTexObByClosestSizeFromVec(ship_trader_texOb_vec[static_cast<int>(race_id)], size_id);   break; }
    case TYPE::ENTITY::PIRAT_ID:    { requested_texOb = _GetShipTexObByClosestSizeFromVec(ship_pirat_texOb_vec[static_cast<int>(race_id)], size_id);    break; }
    case TYPE::ENTITY::DIPLOMAT_ID: { requested_texOb = _GetShipTexObByClosestSizeFromVec(ship_diplomat_texOb_vec[static_cast<int>(race_id)], size_id); break; }
    default:                        { std::cout<<"request wrong="<<getStr(subtype_id)<<std::endl; }
    }

    assert(requested_texOb);
    return requested_texOb;
}

jeti::TextureOb* TextureManager::GetTexObByColorId(TYPE::TEXTURE _type_id, int _color_id)
{
    jeti::TextureOb* requested_texOb = nullptr;
    std::vector<jeti::TextureOb*>* requested_vec = nullptr;
    
    switch(_type_id)
    {
    case TYPE::TEXTURE::PARTICLE_EFFECT_ID:    { requested_vec = &particles_texOb_vec;      break; }
    case TYPE::TEXTURE::DISTANTSTAR_ID:          { requested_vec = &starBgEffect_texOb_vec;   break; }
    case TYPE::TEXTURE::NEBULA_BACKGROUND_ID:  { requested_vec = &nebulaBgEffect_texOb_vec; break; }
    }
    
    for(unsigned int i=0; i<requested_vec->size(); i++)
    {
        if ((*requested_vec)[i]->GetData().color_id == _color_id)
        {
            requested_texOb = (*requested_vec)[i];
        }
    }
    
    assert(requested_texOb);
    return requested_texOb;
}
                
jeti::TextureOb* TextureManager::GetRandomTextureOb(TYPE::TEXTURE texture_type_id)
{
    jeti::TextureOb* requested_texOb = nullptr;
    switch(texture_type_id)
    {
        case TYPE::TEXTURE::SPACESTATION_ID:     { requested_texOb = _GetRandomTextureObFromVec(spacestation_texOb_vec);             break; }
        case TYPE::TEXTURE::SATELLITE_ID:        { requested_texOb = _GetRandomTextureObFromVec(satellite_texOb_vec);            break; }
                    
        case TYPE::TEXTURE::ITEM_SLOT_ID:         { requested_texOb = _GetRandomTextureObFromVec(itemslot_texOb_vec);             break; }
        case TYPE::TEXTURE::VEHICLE_SLOT_ID:      { requested_texOb = _GetRandomTextureObFromVec(vehicleslot_texOb_vec);          break; }
        case TYPE::TEXTURE::CONTAINER_ID:        { requested_texOb = _GetRandomTextureObFromVec(container_texOb_vec);            break; }
        case TYPE::TEXTURE::STAR_ID:             { requested_texOb = _GetRandomTextureObFromVec(star_texOb_vec);                 break; }
        case TYPE::TEXTURE::PLANET_ID:           { requested_texOb = _GetRandomTextureObFromVec(planet_texOb_vec);               break; }
        case TYPE::TEXTURE::ATMOSPHERE_ID:       { requested_texOb = _GetRandomTextureObFromVec(atmosphere_texOb_vec);           break; }
        case TYPE::TEXTURE::RING_ID:       { requested_texOb = _GetRandomTextureObFromVec(ring_texOb_vec);           break; }
        case TYPE::TEXTURE::ASTEROID_ID:         { requested_texOb = _GetRandomTextureObFromVec(asteroid_texOb_vec);             break; }
        case TYPE::TEXTURE::MINERAL_ID:          { requested_texOb = _GetRandomTextureObFromVec(mineral_texOb_vec);              break; }
        case TYPE::TEXTURE::BOMB_ID:             { requested_texOb = _GetRandomTextureObFromVec(bomb_texOb_vec);                 break; }
        case TYPE::TEXTURE::BLACKHOLE_ID:        { requested_texOb = _GetRandomTextureObFromVec(blackhole_texOb_vec);            break; }
        case TYPE::TEXTURE::ROCKET_BULLET_ID:    { requested_texOb = _GetRandomTextureObFromVec(rocketBullet_texOb_vec);         break; }

        case TYPE::TEXTURE::ROCKET_EQUIPMENT_ID:      { requested_texOb = _GetRandomTextureObFromVec(rocketEquipment_texOb_vec);      break; }
        case TYPE::TEXTURE::LAZER_EQUIPMENT_ID:       { requested_texOb = _GetRandomTextureObFromVec(lazerEquipment_texOb_vec);       break; }
        case TYPE::TEXTURE::RADAR_EQUIPMENT_ID:       { requested_texOb = _GetRandomTextureObFromVec(radarEquipment_texOb_vec);       break; }
        case TYPE::TEXTURE::DRIVE_EQUIPMENT_ID:       { requested_texOb = _GetRandomTextureObFromVec(driveEquipment_texOb_vec);       break; }
        case TYPE::TEXTURE::BAK_EQUIPMENT_ID:         { requested_texOb = _GetRandomTextureObFromVec(bakEquipment_texOb_vec);         break; }
        case TYPE::TEXTURE::ENERGIZER_EQUIPMENT_ID: { requested_texOb = _GetRandomTextureObFromVec(energyBlockEquipment_texOb_vec); break; }
        case TYPE::TEXTURE::PROTECTOR_EQUIPMENT_ID:   { requested_texOb = _GetRandomTextureObFromVec(protectorEquipment_texOb_vec);   break; }
        case TYPE::TEXTURE::DROID_EQUIPMENT_ID:       { requested_texOb = _GetRandomTextureObFromVec(droidEquipment_texOb_vec);       break; }
        case TYPE::TEXTURE::FREEZER_EQUIPMENT_ID:     { requested_texOb = _GetRandomTextureObFromVec(freezerEquipment_texOb_vec);     break; }
        case TYPE::TEXTURE::SCANER_EQUIPMENT_ID:      { requested_texOb = _GetRandomTextureObFromVec(scanerEquipment_texOb_vec);      break; }
        case TYPE::TEXTURE::GRAPPLE_EQUIPMENT_ID:     { requested_texOb = _GetRandomTextureObFromVec(grappleEquipment_texOb_vec);     break; }

        case TYPE::TEXTURE::MODULE_ID: { requested_texOb = _GetRandomTextureObFromVec(module_texOb_vec);     break; }
                                                                                
        case TYPE::TEXTURE::TURREL_ID:           { requested_texOb = _GetRandomTextureObFromVec(turrel_texOb_vec);               break; }
        case TYPE::TEXTURE::LAZER_EFFECT_ID:     { requested_texOb = _GetRandomTextureObFromVec(lazerEffect_texOb_vec);          break; }
        
        case TYPE::TEXTURE::NATURELAND_BACKGROUND_ID: { requested_texOb = _GetRandomTextureObFromVec(landBg_texOb_vec); break; }
                            
        case TYPE::TEXTURE::ANGAR_BACKGROUND_ID:         { requested_texOb = _GetRandomTextureObFromVec(angarBg_texOb_vec);              break; }
        case TYPE::TEXTURE::STORE_BACKGROUND_ID:         { requested_texOb = _GetRandomTextureObFromVec(storeBg_texOb_vec);              break; }
        case TYPE::TEXTURE::SHOP_BACKGROUND_ID:          { requested_texOb = _GetRandomTextureObFromVec(shopBg_texOb_vec);               break; }
        case TYPE::TEXTURE::GOVERMENT_BACKGROUND_ID:     { requested_texOb = _GetRandomTextureObFromVec(govermentBg_texOb_vec);          break; }

        case TYPE::TEXTURE::SHIELD_EFFECT_ID:    { requested_texOb = _GetRandomTextureObFromVec(shieldEffect_texOb_vec);         break; }
        case TYPE::TEXTURE::NEBULA_BACKGROUND_ID:           { requested_texOb = _GetRandomTextureObFromVec(nebulaBgEffect_texOb_vec);       break; }
        case TYPE::TEXTURE::DISTANTSTAR_ID:      { requested_texOb = _GetRandomTextureObFromVec(starBgEffect_texOb_vec);         break; }
                
    }

    assert(requested_texOb);
    return requested_texOb;
}
        
void TextureManager::FillShipSubTypeList()
{
    if (ship_ranger_texOb_vec[static_cast<int>(TYPE::RACE::R0_ID)].size() != 0)   RaceInformationCollector::Instance().RACE0_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::RANGER_ID);
    if (ship_warrior_texOb_vec[static_cast<int>(TYPE::RACE::R0_ID)].size() != 0)  RaceInformationCollector::Instance().RACE0_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::WARRIOR_ID);
    if (ship_trader_texOb_vec[static_cast<int>(TYPE::RACE::R0_ID)].size() != 0)   RaceInformationCollector::Instance().RACE0_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::TRADER_ID);
    if (ship_pirat_texOb_vec[static_cast<int>(TYPE::RACE::R0_ID)].size() != 0)    RaceInformationCollector::Instance().RACE0_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::PIRAT_ID);
    if (ship_diplomat_texOb_vec[static_cast<int>(TYPE::RACE::R0_ID)].size() != 0) RaceInformationCollector::Instance().RACE0_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::DIPLOMAT_ID);

    if (ship_ranger_texOb_vec[static_cast<int>(TYPE::RACE::R1_ID)].size() != 0)   RaceInformationCollector::Instance().RACE1_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::RANGER_ID);
    if (ship_warrior_texOb_vec[static_cast<int>(TYPE::RACE::R1_ID)].size() != 0)  RaceInformationCollector::Instance().RACE1_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::WARRIOR_ID);
    if (ship_trader_texOb_vec[static_cast<int>(TYPE::RACE::R1_ID)].size() != 0)   RaceInformationCollector::Instance().RACE1_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::TRADER_ID);
    if (ship_pirat_texOb_vec[static_cast<int>(TYPE::RACE::R1_ID)].size() != 0)    RaceInformationCollector::Instance().RACE1_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::PIRAT_ID);
    if (ship_diplomat_texOb_vec[static_cast<int>(TYPE::RACE::R1_ID)].size() != 0) RaceInformationCollector::Instance().RACE1_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::DIPLOMAT_ID);

    if (ship_ranger_texOb_vec[static_cast<int>(TYPE::RACE::R2_ID)].size() != 0)   RaceInformationCollector::Instance().RACE2_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::RANGER_ID);
    if (ship_warrior_texOb_vec[static_cast<int>(TYPE::RACE::R2_ID)].size() != 0)  RaceInformationCollector::Instance().RACE2_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::WARRIOR_ID);
    if (ship_trader_texOb_vec[static_cast<int>(TYPE::RACE::R2_ID)].size() != 0)   RaceInformationCollector::Instance().RACE2_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::TRADER_ID);
    if (ship_pirat_texOb_vec[static_cast<int>(TYPE::RACE::R2_ID)].size() != 0)    RaceInformationCollector::Instance().RACE2_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::PIRAT_ID);
    if (ship_diplomat_texOb_vec[static_cast<int>(TYPE::RACE::R2_ID)].size() != 0) RaceInformationCollector::Instance().RACE2_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::DIPLOMAT_ID);
 
    if (ship_ranger_texOb_vec[static_cast<int>(TYPE::RACE::R3_ID)].size() != 0)   RaceInformationCollector::Instance().RACE3_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::RANGER_ID);
    if (ship_warrior_texOb_vec[static_cast<int>(TYPE::RACE::R3_ID)].size() != 0)  RaceInformationCollector::Instance().RACE3_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::WARRIOR_ID);
    if (ship_trader_texOb_vec[static_cast<int>(TYPE::RACE::R3_ID)].size() != 0)   RaceInformationCollector::Instance().RACE3_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::TRADER_ID);
    if (ship_pirat_texOb_vec[static_cast<int>(TYPE::RACE::R3_ID)].size() != 0)    RaceInformationCollector::Instance().RACE3_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::PIRAT_ID);
    if (ship_diplomat_texOb_vec[static_cast<int>(TYPE::RACE::R3_ID)].size() != 0) RaceInformationCollector::Instance().RACE3_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::DIPLOMAT_ID);

    if (ship_ranger_texOb_vec[static_cast<int>(TYPE::RACE::R4_ID)].size() != 0)   RaceInformationCollector::Instance().RACE4_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::RANGER_ID);
    if (ship_warrior_texOb_vec[static_cast<int>(TYPE::RACE::R4_ID)].size() != 0)  RaceInformationCollector::Instance().RACE4_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::WARRIOR_ID);
    if (ship_trader_texOb_vec[static_cast<int>(TYPE::RACE::R4_ID)].size() != 0)   RaceInformationCollector::Instance().RACE4_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::TRADER_ID);
    if (ship_pirat_texOb_vec[static_cast<int>(TYPE::RACE::R4_ID)].size() != 0)    RaceInformationCollector::Instance().RACE4_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::PIRAT_ID);
    if (ship_diplomat_texOb_vec[static_cast<int>(TYPE::RACE::R4_ID)].size() != 0) RaceInformationCollector::Instance().RACE4_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::DIPLOMAT_ID);

    if (ship_ranger_texOb_vec[static_cast<int>(TYPE::RACE::R6_ID)].size() != 0)   RaceInformationCollector::Instance().RACE6_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::RANGER_ID);
    if (ship_warrior_texOb_vec[static_cast<int>(TYPE::RACE::R6_ID)].size() != 0)  RaceInformationCollector::Instance().RACE6_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::WARRIOR_ID);
    if (ship_trader_texOb_vec[static_cast<int>(TYPE::RACE::R6_ID)].size() != 0)   RaceInformationCollector::Instance().RACE6_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::TRADER_ID);
    if (ship_pirat_texOb_vec[static_cast<int>(TYPE::RACE::R6_ID)].size() != 0)    RaceInformationCollector::Instance().RACE6_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::PIRAT_ID);
    if (ship_diplomat_texOb_vec[static_cast<int>(TYPE::RACE::R6_ID)].size() != 0) RaceInformationCollector::Instance().RACE6_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::DIPLOMAT_ID);

    if (ship_ranger_texOb_vec[static_cast<int>(TYPE::RACE::R7_ID)].size() != 0)   RaceInformationCollector::Instance().RACE7_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::RANGER_ID);
    if (ship_warrior_texOb_vec[static_cast<int>(TYPE::RACE::R7_ID)].size() != 0)  RaceInformationCollector::Instance().RACE7_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::WARRIOR_ID);
    if (ship_trader_texOb_vec[static_cast<int>(TYPE::RACE::R7_ID)].size() != 0)   RaceInformationCollector::Instance().RACE7_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::TRADER_ID);
    if (ship_pirat_texOb_vec[static_cast<int>(TYPE::RACE::R7_ID)].size() != 0)    RaceInformationCollector::Instance().RACE7_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::PIRAT_ID);
    if (ship_diplomat_texOb_vec[static_cast<int>(TYPE::RACE::R7_ID)].size() != 0) RaceInformationCollector::Instance().RACE7_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::DIPLOMAT_ID);
}

jeti::TextureOb* TextureManager::GetTextureObByPath(const std::string& path)
{
    jeti::TextureOb* requested_texOb = nullptr;
    for (unsigned int i = 0; i<textureOb_total_vec.size(); i++)
    {
        if (textureOb_total_vec[i]->GetData().texture_path == path)
        {
            requested_texOb = textureOb_total_vec[i];
            break;
        }
    }
    
    assert(requested_texOb);
    return requested_texOb;
}
        
