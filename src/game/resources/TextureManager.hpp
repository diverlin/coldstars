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


#pragma once

#include <string>
#include <vector>
#include <map>

#include <resources/TextureDescriptor.hpp>
#include <types/TextureTypes.hpp>
#include <types/RaceTypes.hpp>
#include <types/EntityTypes.hpp>


namespace jeti {
class TextureOb;
}

class TextureManager
{   
    public:
        static TextureManager& Instance();
        
        void add(TYPE::TEXTURE, jeti::TextureOb*);
        
        jeti::TextureOb* GetRandomFaceTexObWithFolloingAttributes(TYPE::RACE);
        jeti::TextureOb* GetRandomShipTexObWithFollowingAtrributes(TYPE::RACE, TYPE::ENTITY, int _size_id);
        
        jeti::TextureOb* GetTexObByColorId(TYPE::TEXTURE, int color_id);
        
        jeti::TextureOb* GetRandomTextureOb(TYPE::TEXTURE);
        
        jeti::TextureOb* GetTextureObByPath(const std::string&);
        
        void FillShipSubTypeList();

    private:
        TextureManager() {};
        ~TextureManager() {};
        
        TextureManager(TextureManager&) = delete;
        TextureManager& operator=(TextureManager&) = delete;
        
        std::map<TYPE::TEXTURE, std::vector<jeti::TextureOb*>> m_TexturesGroup_map;
        std::map<int, jeti::TextureOb*> m_Textures_map;
        std::map<int, TextureDescriptor> m_Descriptors_map;

//        std::vector<jeti::TextureOb*> textureOb_total_vec;
        
//        std::vector<jeti::TextureOb*> itemslot_texOb_vec;
//        std::vector<jeti::TextureOb*> vehicleslot_texOb_vec;
//        std::vector<jeti::TextureOb*> turrel_texOb_vec;
            
//        std::vector<jeti::TextureOb*> particles_texOb_vec;

        // BACKGROUND 
//        std::vector<jeti::TextureOb*> nebulaBgEffect_texOb_vec;
//        std::vector<jeti::TextureOb*> starBgEffect_texOb_vec;

        // BACKGROUND AT PLANET 
//        std::vector<jeti::TextureOb*> angarBg_texOb_vec;
//        std::vector<jeti::TextureOb*> storeBg_texOb_vec;
//        std::vector<jeti::TextureOb*> shopBg_texOb_vec;
//        std::vector<jeti::TextureOb*> govermentBg_texOb_vec;
//        std::vector<jeti::TextureOb*> landBg_texOb_vec;

        // EFFECTS
//        std::vector<jeti::TextureOb*> rocketBullet_texOb_vec;
//        std::vector<jeti::TextureOb*> lazerEffect_texOb_vec;
//        std::vector<jeti::TextureOb*> shieldEffect_texOb_vec;


        // SPACE OBJECTS
//        std::vector<jeti::TextureOb*> spacestation_texOb_vec;
//        std::vector<jeti::TextureOb*> satellite_texOb_vec;
//        std::vector<jeti::TextureOb*> star_texOb_vec;
//        std::vector<jeti::TextureOb*> planet_texOb_vec;
//        std::vector<jeti::TextureOb*> atmosphere_texOb_vec;
//        std::vector<jeti::TextureOb*> ring_texOb_vec;
//        std::vector<jeti::TextureOb*> asteroid_texOb_vec;
//        std::vector<jeti::TextureOb*> mineral_texOb_vec;
//        std::vector<jeti::TextureOb*> container_texOb_vec;
//        std::vector<jeti::TextureOb*> bomb_texOb_vec;
//        std::vector<jeti::TextureOb*> blackhole_texOb_vec;
        
        // SHIPS
//        std::vector<jeti::TextureOb*> ship_ranger_texOb_vec[static_cast<int>(TYPE::RACE::LAST_ID)];
//        std::vector<jeti::TextureOb*> ship_warrior_texOb_vec[static_cast<int>(TYPE::RACE::LAST_ID)];
//        std::vector<jeti::TextureOb*> ship_trader_texOb_vec[static_cast<int>(TYPE::RACE::LAST_ID)];
//        std::vector<jeti::TextureOb*> ship_pirat_texOb_vec[static_cast<int>(TYPE::RACE::LAST_ID)];
//        std::vector<jeti::TextureOb*> ship_diplomat_texOb_vec[static_cast<int>(TYPE::RACE::LAST_ID)];

        // ITEMS
//        std::vector<jeti::TextureOb*> lazerEquipment_texOb_vec;
//        std::vector<jeti::TextureOb*> rocketEquipment_texOb_vec;
//        std::vector<jeti::TextureOb*> driveEquipment_texOb_vec;
//        std::vector<jeti::TextureOb*> protectorEquipment_texOb_vec;
//        std::vector<jeti::TextureOb*> droidEquipment_texOb_vec;
//        std::vector<jeti::TextureOb*> grappleEquipment_texOb_vec;
//        std::vector<jeti::TextureOb*> bakEquipment_texOb_vec;
//        std::vector<jeti::TextureOb*> energyBlockEquipment_texOb_vec;
//        std::vector<jeti::TextureOb*> freezerEquipment_texOb_vec;
//        std::vector<jeti::TextureOb*> radarEquipment_texOb_vec;
//        std::vector<jeti::TextureOb*> scanerEquipment_texOb_vec;
        
//        std::vector<jeti::TextureOb*> module_texOb_vec;

        // FACE
//        std::vector<jeti::TextureOb*> face_race0_texOb_vec;
//        std::vector<jeti::TextureOb*> face_race1_texOb_vec;
//        std::vector<jeti::TextureOb*> face_race2_texOb_vec;
//        std::vector<jeti::TextureOb*> face_race3_texOb_vec;
//        std::vector<jeti::TextureOb*> face_race4_texOb_vec;
//        std::vector<jeti::TextureOb*> face_race6_texOb_vec;
//        std::vector<jeti::TextureOb*> face_race7_texOb_vec;
    
        jeti::TextureOb* _GetRandomTextureObFromVec(const std::vector<jeti::TextureOb*>&);
        jeti::TextureOb* _TryGetRandomTextureObFromVec(const std::vector<jeti::TextureOb*>&);
        jeti::TextureOb* _GetShipTexObByClosestSizeFromVec(const std::vector<jeti::TextureOb*>&, int);
        jeti::TextureOb* _GetShipTexObBySizeFromVec(const std::vector<jeti::TextureOb*>&, int);
        jeti::TextureOb* _TryGetShipTexObBySizeFromVec(const std::vector<jeti::TextureOb*>&, int);
};

