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

#include "TextureCollector.hpp"

#include <types/TextureTypes.hpp>
#include <types/RaceTypes.hpp>

#include <math/rand.hpp>
#include <common/Logger.hpp>
#include <common/constants.hpp>

#include <struct/RaceInformationCollector.hpp>

#include <jeti/TextureOb.hpp>


TextureCollector& TextureCollector::Instance()
{
    static TextureCollector instance;
    return instance;
}

void TextureCollector::add(jeti::TextureOb* texture, const TextureDescriptor& descriptor)
{
    if (isAbsent(texture)) {
        m_idsTextures.insert(std::make_pair(texture->id(), std::make_pair(descriptor, texture)));
    } else {
        std::cout<<"texture id="<<texture->id()<<std::endl;
        throw std::runtime_error("texture id is already exist");
    }

    m_typesTextures[descriptor.type_id].push_back(std::make_pair( descriptor, texture));
}

bool TextureCollector::isAbsent(jeti::TextureOb* texOb) const
{
    auto it = m_idsTextures.find(texOb->id());
    if (it != m_idsTextures.end()) {
        return false;
    } else {
        return true;
    }
}

jeti::TextureOb* TextureCollector::getTextureById(int id)
{
    jeti::TextureOb* requested = m_idsTextures[id].second;

    assert(requested);
    return requested;
}

jeti::TextureOb* TextureCollector::getTextureByTypeId(TYPE::TEXTURE type_id)
{
    jeti::TextureOb* requested = getRandomElement(m_typesTextures[type_id]).second;

    assert(requested);
    return requested;
}

jeti::TextureOb* TextureCollector::getTextureByColorId(TYPE::TEXTURE type_id, int color_id)
{
    jeti::TextureOb* requested = nullptr;
    const std::vector<std::pair<TextureDescriptor, jeti::TextureOb*>>& vec = m_typesTextures[type_id];
    for(std::pair<TextureDescriptor, jeti::TextureOb*> pair: vec) {
        if (pair.second->GetMaterial().color_id == color_id) {
            requested = pair.second;
        }
    }

    assert(requested);
    return requested;
}

jeti::TextureOb* TextureCollector::getTextureByRaceId(TYPE::TEXTURE type_id, TYPE::RACE race_id)
{
    jeti::TextureOb* requested = nullptr;
    const std::vector<std::pair<TextureDescriptor, jeti::TextureOb*>>& vec = m_typesTextures[type_id];
    for(std::pair<TextureDescriptor, jeti::TextureOb*> pair: vec) {
        if (pair.first.race_id == race_id) {
            requested = pair.second;
        }
    }

    assert(requested);
    return requested;
}
jeti::TextureOb* TextureCollector::getTextureByDescriptor(const TextureDescriptor& descriptor)
{
    std::vector<int> ids;
    std::map<int, std::pair<TextureDescriptor, jeti::TextureOb*>>::const_iterator it = m_idsTextures.begin();
    for (; it != m_idsTextures.end(); ++it) {
        if (it->second.first == descriptor) {
            ids.push_back(it->first);
        }
    }

    int id = getRandomElement(ids);
    jeti::TextureOb* requested = getTextureById(id);

    assert(requested);
    return requested;
}

jeti::TextureOb* TextureCollector::_GetShipTexObByClosestSizeFromVec(const std::vector<jeti::TextureOb*>& textureOb_vec, int size_id)
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


jeti::TextureOb* TextureCollector::_TryGetShipTexObBySizeFromVec(const std::vector<jeti::TextureOb*>& textures, int size_id)
{  
    jeti::TextureOb* requested = nullptr;
    for (jeti::TextureOb* texture: textures) {
        if (texture->GetMaterial().size_id == size_id) {
            requested = texture;
            break;
        }
    }
    return requested;
}

jeti::TextureOb* TextureCollector::_GetShipTexObBySizeFromVec(const std::vector<jeti::TextureOb*>& textures, int size_id)
{
    jeti::TextureOb* requested  = _TryGetShipTexObBySizeFromVec(textures, size_id);
    return requested;
}

void TextureCollector::FillShipSubTypeList()
{
//    if (ship_ranger_texOb_vec[static_cast<int>(TYPE::RACE::R0_ID)].size() != 0)   RaceInformationCollector::Instance().RACE0_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::RANGER_ID);
//    if (ship_warrior_texOb_vec[static_cast<int>(TYPE::RACE::R0_ID)].size() != 0)  RaceInformationCollector::Instance().RACE0_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::WARRIOR_ID);
//    if (ship_trader_texOb_vec[static_cast<int>(TYPE::RACE::R0_ID)].size() != 0)   RaceInformationCollector::Instance().RACE0_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::TRADER_ID);
//    if (ship_pirat_texOb_vec[static_cast<int>(TYPE::RACE::R0_ID)].size() != 0)    RaceInformationCollector::Instance().RACE0_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::PIRAT_ID);
//    if (ship_diplomat_texOb_vec[static_cast<int>(TYPE::RACE::R0_ID)].size() != 0) RaceInformationCollector::Instance().RACE0_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::DIPLOMAT_ID);

//    if (ship_ranger_texOb_vec[static_cast<int>(TYPE::RACE::R1_ID)].size() != 0)   RaceInformationCollector::Instance().RACE1_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::RANGER_ID);
//    if (ship_warrior_texOb_vec[static_cast<int>(TYPE::RACE::R1_ID)].size() != 0)  RaceInformationCollector::Instance().RACE1_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::WARRIOR_ID);
//    if (ship_trader_texOb_vec[static_cast<int>(TYPE::RACE::R1_ID)].size() != 0)   RaceInformationCollector::Instance().RACE1_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::TRADER_ID);
//    if (ship_pirat_texOb_vec[static_cast<int>(TYPE::RACE::R1_ID)].size() != 0)    RaceInformationCollector::Instance().RACE1_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::PIRAT_ID);
//    if (ship_diplomat_texOb_vec[static_cast<int>(TYPE::RACE::R1_ID)].size() != 0) RaceInformationCollector::Instance().RACE1_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::DIPLOMAT_ID);

//    if (ship_ranger_texOb_vec[static_cast<int>(TYPE::RACE::R2_ID)].size() != 0)   RaceInformationCollector::Instance().RACE2_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::RANGER_ID);
//    if (ship_warrior_texOb_vec[static_cast<int>(TYPE::RACE::R2_ID)].size() != 0)  RaceInformationCollector::Instance().RACE2_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::WARRIOR_ID);
//    if (ship_trader_texOb_vec[static_cast<int>(TYPE::RACE::R2_ID)].size() != 0)   RaceInformationCollector::Instance().RACE2_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::TRADER_ID);
//    if (ship_pirat_texOb_vec[static_cast<int>(TYPE::RACE::R2_ID)].size() != 0)    RaceInformationCollector::Instance().RACE2_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::PIRAT_ID);
//    if (ship_diplomat_texOb_vec[static_cast<int>(TYPE::RACE::R2_ID)].size() != 0) RaceInformationCollector::Instance().RACE2_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::DIPLOMAT_ID);

//    if (ship_ranger_texOb_vec[static_cast<int>(TYPE::RACE::R3_ID)].size() != 0)   RaceInformationCollector::Instance().RACE3_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::RANGER_ID);
//    if (ship_warrior_texOb_vec[static_cast<int>(TYPE::RACE::R3_ID)].size() != 0)  RaceInformationCollector::Instance().RACE3_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::WARRIOR_ID);
//    if (ship_trader_texOb_vec[static_cast<int>(TYPE::RACE::R3_ID)].size() != 0)   RaceInformationCollector::Instance().RACE3_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::TRADER_ID);
//    if (ship_pirat_texOb_vec[static_cast<int>(TYPE::RACE::R3_ID)].size() != 0)    RaceInformationCollector::Instance().RACE3_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::PIRAT_ID);
//    if (ship_diplomat_texOb_vec[static_cast<int>(TYPE::RACE::R3_ID)].size() != 0) RaceInformationCollector::Instance().RACE3_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::DIPLOMAT_ID);

//    if (ship_ranger_texOb_vec[static_cast<int>(TYPE::RACE::R4_ID)].size() != 0)   RaceInformationCollector::Instance().RACE4_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::RANGER_ID);
//    if (ship_warrior_texOb_vec[static_cast<int>(TYPE::RACE::R4_ID)].size() != 0)  RaceInformationCollector::Instance().RACE4_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::WARRIOR_ID);
//    if (ship_trader_texOb_vec[static_cast<int>(TYPE::RACE::R4_ID)].size() != 0)   RaceInformationCollector::Instance().RACE4_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::TRADER_ID);
//    if (ship_pirat_texOb_vec[static_cast<int>(TYPE::RACE::R4_ID)].size() != 0)    RaceInformationCollector::Instance().RACE4_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::PIRAT_ID);
//    if (ship_diplomat_texOb_vec[static_cast<int>(TYPE::RACE::R4_ID)].size() != 0) RaceInformationCollector::Instance().RACE4_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::DIPLOMAT_ID);

//    if (ship_ranger_texOb_vec[static_cast<int>(TYPE::RACE::R6_ID)].size() != 0)   RaceInformationCollector::Instance().RACE6_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::RANGER_ID);
//    if (ship_warrior_texOb_vec[static_cast<int>(TYPE::RACE::R6_ID)].size() != 0)  RaceInformationCollector::Instance().RACE6_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::WARRIOR_ID);
//    if (ship_trader_texOb_vec[static_cast<int>(TYPE::RACE::R6_ID)].size() != 0)   RaceInformationCollector::Instance().RACE6_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::TRADER_ID);
//    if (ship_pirat_texOb_vec[static_cast<int>(TYPE::RACE::R6_ID)].size() != 0)    RaceInformationCollector::Instance().RACE6_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::PIRAT_ID);
//    if (ship_diplomat_texOb_vec[static_cast<int>(TYPE::RACE::R6_ID)].size() != 0) RaceInformationCollector::Instance().RACE6_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::DIPLOMAT_ID);

//    if (ship_ranger_texOb_vec[static_cast<int>(TYPE::RACE::R7_ID)].size() != 0)   RaceInformationCollector::Instance().RACE7_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::RANGER_ID);
//    if (ship_warrior_texOb_vec[static_cast<int>(TYPE::RACE::R7_ID)].size() != 0)  RaceInformationCollector::Instance().RACE7_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::WARRIOR_ID);
//    if (ship_trader_texOb_vec[static_cast<int>(TYPE::RACE::R7_ID)].size() != 0)   RaceInformationCollector::Instance().RACE7_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::TRADER_ID);
//    if (ship_pirat_texOb_vec[static_cast<int>(TYPE::RACE::R7_ID)].size() != 0)    RaceInformationCollector::Instance().RACE7_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::PIRAT_ID);
//    if (ship_diplomat_texOb_vec[static_cast<int>(TYPE::RACE::R7_ID)].size() != 0) RaceInformationCollector::Instance().RACE7_ALLOWED_SUBTYPE_vec.push_back(TYPE::ENTITY::DIPLOMAT_ID);
}
