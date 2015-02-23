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

#include <math/rand.hpp>
#include <meti/RandUtils.hpp>
#include <jeti/TextureOb.hpp>

#include <common/Logger.hpp>

TextureCollector& TextureCollector::Instance()
{
    static TextureCollector instance;
    return instance;
}

TextureCollector::TextureCollector()
    :m_textureBlank(nullptr)
{}

TextureCollector::~TextureCollector()
{
    for (auto& pair: m_idsTextures) {
        delete pair.second.second;
    }
}

void TextureCollector::setTextureBlank(jeti::TextureOb* texture)
{
    m_textureBlank = texture;
}

void TextureCollector::add(jeti::TextureOb* texture, const TextureDescriptor& descriptor)
{
    if (!isExist(texture)) {
        m_idsTextures.insert(std::make_pair(texture->id(), std::make_pair(descriptor, texture)));
        m_typesTextures[descriptor.type_id].push_back(std::make_pair( descriptor, texture));
    } else {
        Logger::Instance().error("texture id=" + std::to_string(texture->id()) + "already exist");
    }
}

bool TextureCollector::isExist(jeti::TextureOb* texture) const
{
    auto it = m_idsTextures.find(texture->id());
    if (it != m_idsTextures.end()) {
        return true;
    } else {
        return false;
    }
}

jeti::TextureOb* TextureCollector::getTextureById(int id)
{
    jeti::TextureOb* requested = nullptr;
    if (hasId(id)) {
        requested = m_idsTextures[id].second;
    }

    _validate(requested);
    return requested;
}

jeti::TextureOb* TextureCollector::getTextureByTypeId(TYPE::TEXTURE type_id)
{
    jeti::TextureOb* requested = nullptr;
    if (hasTypeId(type_id)) {
        requested = meti::getRandomElement(m_typesTextures[type_id]).second;
    }

    _validate(requested);
    return requested;
}

jeti::TextureOb* TextureCollector::getTextureByColorId(TYPE::TEXTURE type_id, int color_id)
{
    jeti::TextureOb* requested = nullptr;
    if (hasTypeId(type_id)) {
        const std::vector<std::pair<TextureDescriptor, jeti::TextureOb*>>& vec = m_typesTextures[type_id];
        for(std::pair<TextureDescriptor, jeti::TextureOb*> pair: vec) {
            if (pair.second->GetMaterial().color_id == color_id) {
                requested = pair.second;
            }
        }
    }

    _validate(requested);
    return requested;
}

jeti::TextureOb* TextureCollector::getTextureByRaceId(TYPE::TEXTURE type_id, TYPE::RACE race_id)
{
    jeti::TextureOb* requested = nullptr;
    if (hasTypeId(type_id)) {
        const std::vector<std::pair<TextureDescriptor, jeti::TextureOb*>>& vec = m_typesTextures[type_id];
        for(std::pair<TextureDescriptor, jeti::TextureOb*> pair: vec) {
            if (pair.first.race_id == race_id) {
                requested = pair.second;
                break;
            }
        }
    }

    _validate(requested);
    return requested;
}

jeti::TextureOb* TextureCollector::getTextureByDescriptor(const TextureDescriptor& descriptor)
{
    jeti::TextureOb* requested = nullptr;
    std::vector<int> ids;
    std::map<int, std::pair<TextureDescriptor, jeti::TextureOb*>>::const_iterator it = m_idsTextures.begin();
    for (; it != m_idsTextures.end(); ++it) {
        if (it->second.first == descriptor) {
            ids.push_back(it->first);
        }
    }

    if (!ids.empty()) {
        int id = meti::getRandomElement(ids);
        requested = getTextureById(id);
    }

    _validate(requested);
    return requested;
}

void TextureCollector::_validate(jeti::TextureOb* requested)
{
    if (!requested) {
        requested = m_textureBlank;
    }
}

bool TextureCollector::hasId(int id) const
{
    if (m_idsTextures.find(id) != m_idsTextures.end()) {
        return true;
    } else {
        Logger::Instance().warn("TextureCollector has no id="+std::to_string(id));
        return false;
    }
}

bool TextureCollector::hasTypeId(TYPE::TEXTURE type_id) const
{
    if (m_typesTextures.find(type_id) != m_typesTextures.end()) {
        return true;
    } else {
        Logger::Instance().warn("TextureCollector has no type_id="+getStr(type_id));
        return false;
    }
}

jeti::TextureOb* TextureCollector::_getTextureByClosestSizeId(const std::vector<jeti::TextureOb*>& textures, int size_id)
{  
    jeti::TextureOb* requested = _tryGetTextureBySizeId(textures, size_id);
    int sign = 1;
    int i = 1;

    for (int i=1; i<11; i++) {
        sign *= -1;
        size_id += sign*i;
        requested = _tryGetTextureBySizeId(textures, size_id);
        if (requested) {
            break;
        }
    }

    return requested;
}

jeti::TextureOb* TextureCollector::_getTextureBySizeId(const std::vector<jeti::TextureOb*>& textures, int size_id)
{
    jeti::TextureOb* requested = _tryGetTextureBySizeId(textures, size_id);
    return requested;
}

jeti::TextureOb* TextureCollector::_tryGetTextureBySizeId(const std::vector<jeti::TextureOb*>& textures, int size_id)
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

