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


#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include <string>
#include <vector>

#include <types/TextureTypes.hpp>
#include <types/EntityTypes.hpp>

class TextureOb;

class TextureManager
{   
    public:
        static TextureManager& Instance();
        
        void Add(TextureOb*);
               
        TextureOb* GetTexObByColorId(TYPE::TEXTURE, int color_id);
        
        TextureOb* GetRandomTextureOb(TYPE::TEXTURE);
        
        TextureOb* GetTextureObByPath(const std::string&);

    private:
        TextureManager() {};
        ~TextureManager() {};
        
        TextureManager(TextureManager&) = delete;
        TextureManager& operator=(TextureManager&) = delete;
        
        std::vector<TextureOb*> textureOb_total_vec;
        
        std::vector<TextureOb*> itemslot_texOb_vec;
        std::vector<TextureOb*> vehicleslot_texOb_vec;
        std::vector<TextureOb*> turrel_texOb_vec;
            
        std::vector<TextureOb*> particles_texOb_vec;

        // BACKGROUND 
        std::vector<TextureOb*> nebulaBgEffect_texOb_vec;
        std::vector<TextureOb*> starBgEffect_texOb_vec;

        // BACKGROUND AT PLANET 
        std::vector<TextureOb*> angarBg_texOb_vec;
        std::vector<TextureOb*> storeBg_texOb_vec;
        std::vector<TextureOb*> shopBg_texOb_vec;
        std::vector<TextureOb*> govermentBg_texOb_vec;
        std::vector<TextureOb*> landBg_texOb_vec;

        // EFFECTS
        std::vector<TextureOb*> rocketBullet_texOb_vec;
        std::vector<TextureOb*> lazerEffect_texOb_vec;
        std::vector<TextureOb*> shieldEffect_texOb_vec;


        // SPACE OBJECTS
        std::vector<TextureOb*> spacestation_texOb_vec;
        std::vector<TextureOb*> satellite_texOb_vec;
        std::vector<TextureOb*> star_texOb_vec;
        std::vector<TextureOb*> planet_texOb_vec;
        std::vector<TextureOb*> atmosphere_texOb_vec;
        std::vector<TextureOb*> ring_texOb_vec;
        std::vector<TextureOb*> asteroid_texOb_vec;  
        std::vector<TextureOb*> mineral_texOb_vec;   
        std::vector<TextureOb*> container_texOb_vec;  
        std::vector<TextureOb*> bomb_texOb_vec;   
        std::vector<TextureOb*> blackhole_texOb_vec;  
        
        // ITEMS
        std::vector<TextureOb*> lazerEquipment_texOb_vec;
        std::vector<TextureOb*> rocketEquipment_texOb_vec;
        std::vector<TextureOb*> driveEquipment_texOb_vec;
        std::vector<TextureOb*> protectorEquipment_texOb_vec;
        std::vector<TextureOb*> droidEquipment_texOb_vec;
        std::vector<TextureOb*> grappleEquipment_texOb_vec;
        std::vector<TextureOb*> bakEquipment_texOb_vec;
        std::vector<TextureOb*> energyBlockEquipment_texOb_vec;
        std::vector<TextureOb*> freezerEquipment_texOb_vec;
        std::vector<TextureOb*> radarEquipment_texOb_vec;
        std::vector<TextureOb*> scanerEquipment_texOb_vec;
        
        std::vector<TextureOb*> module_texOb_vec;            

        // FACE
        std::vector<TextureOb*> face_race0_texOb_vec;
        std::vector<TextureOb*> face_race1_texOb_vec;
        std::vector<TextureOb*> face_race2_texOb_vec;
        std::vector<TextureOb*> face_race3_texOb_vec;
        std::vector<TextureOb*> face_race4_texOb_vec;
        std::vector<TextureOb*> face_race6_texOb_vec;
        std::vector<TextureOb*> face_race7_texOb_vec;
    
        TextureOb* _GetRandomTextureObFromVec(const std::vector<TextureOb*>&);
        TextureOb* _TryGetRandomTextureObFromVec(const std::vector<TextureOb*>&);
};

#endif 
