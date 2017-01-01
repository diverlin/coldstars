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

#include <client/resources/TextureDescriptor.hpp>
#include <types/TextureTypes.hpp>
#include <types/RaceTypes.hpp>
#include <types/EntityTypes.hpp>


namespace jeti {
namespace control {
class Material;
} // namespace control
}

class TextureCollector
{   
public:
    static TextureCollector& get();

    void setTextureBlank(jeti::control::Material*);
    void add(jeti::control::Material*, const TextureDescriptor&);

    jeti::control::Material* get(int);
    jeti::control::Material* getTextureByTypeId(type::texture);
    jeti::control::Material* getTextureByColorId(type::texture, int);
    jeti::control::Material* getTextureByRaceId(type::texture, type::race);
    jeti::control::Material* getTextureByDescriptor(const TextureDescriptor& descriptior);

private:
    TextureCollector();
    ~TextureCollector();

    TextureCollector(TextureCollector&) = delete;
    TextureCollector& operator=(TextureCollector&) = delete;

    jeti::control::Material* m_textureBlank;

    std::map<int, std::pair<TextureDescriptor, jeti::control::Material*>> m_idsTextures;
    std::map<type::texture, std::vector<std::pair<TextureDescriptor, jeti::control::Material*>>> m_typesTextures;

    bool isExist(jeti::control::Material*) const;
    
    jeti::control::Material* _getTextureByClosestSizeId(const std::vector<jeti::control::Material*>&, int);
    jeti::control::Material* _getTextureBySizeId(const std::vector<jeti::control::Material*>&, int);
    jeti::control::Material* _tryGetTextureBySizeId(const std::vector<jeti::control::Material*>&, int);

    void _validate(jeti::control::Material*);

    bool hasId(int) const;
    bool hasTypeId(type::texture) const;
};

