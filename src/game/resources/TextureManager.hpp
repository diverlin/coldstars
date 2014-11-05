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
        
        void add(jeti::TextureOb*, const TextureDescriptor&);
        
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

        bool isAbsent(jeti::TextureOb*) const;
    
        jeti::TextureOb* _GetRandomTextureObFromVec(const std::vector<jeti::TextureOb*>&);
        jeti::TextureOb* _TryGetRandomTextureObFromVec(const std::vector<jeti::TextureOb*>&);
        jeti::TextureOb* _GetShipTexObByClosestSizeFromVec(const std::vector<jeti::TextureOb*>&, int);
        jeti::TextureOb* _GetShipTexObBySizeFromVec(const std::vector<jeti::TextureOb*>&, int);
        jeti::TextureOb* _TryGetShipTexObBySizeFromVec(const std::vector<jeti::TextureOb*>&, int);
};

