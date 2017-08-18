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
#include <jeti/Material.hpp>

#include <ceti/Logger.hpp>

TextureCollector& TextureCollector::get()
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

void TextureCollector::setTextureBlank(jeti::control::Material* texture)
{
    m_textureBlank = texture;
}

void TextureCollector::add(jeti::control::Material* texture, const TextureDescriptor& descriptor)
{
    if (!isExist(texture)) {
        m_idsTextures.insert(std::make_pair(texture->id(), std::make_pair(descriptor, texture)));
        m_typesTextures[descriptor.type_id].push_back(std::make_pair( descriptor, texture));
    } else {
        //Logger::Instance().error("texture id=" + std::to_string(texture->id()) + "already exist");
    }
}

bool TextureCollector::isExist(jeti::control::Material* texture) const
{
    auto it = m_idsTextures.find(texture->id());
    if (it != m_idsTextures.end()) {
        return true;
    } else {
        return false;
    }
}

jeti::control::Material* TextureCollector::get(int id)
{
    jeti::control::Material* requested = nullptr;
    if (hasId(id)) {
        requested = m_idsTextures[id].second;
    }

    _validate(requested);
    return requested;
}

jeti::control::Material* TextureCollector::getTextureByTypeId(texture::Type type_id)
{
    jeti::control::Material* requested = nullptr;
    if (hasTypeId(type_id)) {
        requested = meti::rand::get_element(m_typesTextures[type_id]).second;
    }

    _validate(requested);
    return requested;
}

jeti::control::Material* TextureCollector::getTextureByColorId(texture::Type type_id, int color_id)
{
    jeti::control::Material* requested = nullptr;
    if (hasTypeId(type_id)) {
        const std::vector<std::pair<TextureDescriptor, jeti::control::Material*>>& vec = m_typesTextures[type_id];
        for(std::pair<TextureDescriptor, jeti::control::Material*> pair: vec) {
            if (pair.second->model()->color_id == color_id) {
                requested = pair.second;
            }
        }
    }

    _validate(requested);
    return requested;
}

jeti::control::Material* TextureCollector::getTextureByRaceId(texture::Type type_id, race::Type race_id)
{
    jeti::control::Material* requested = nullptr;
    if (hasTypeId(type_id)) {
        const std::vector<std::pair<TextureDescriptor, jeti::control::Material*>>& vec = m_typesTextures[type_id];
        for(std::pair<TextureDescriptor, jeti::control::Material*> pair: vec) {
            if (pair.first.race_id == race_id) {
                requested = pair.second;
                break;
            }
        }
    }

    _validate(requested);
    return requested;
}

jeti::control::Material* TextureCollector::getTextureByDescriptor(const TextureDescriptor& descriptor)
{
    jeti::control::Material* requested = nullptr;
    std::vector<int> ids;
    std::map<int, std::pair<TextureDescriptor, jeti::control::Material*>>::const_iterator it = m_idsTextures.begin();
    for (; it != m_idsTextures.end(); ++it) {
        if (it->second.first == descriptor) {
            ids.push_back(it->first);
        }
    }

    if (!ids.empty()) {
        int id = meti::rand::get_element(ids);
        requested = get(id);
    }

    _validate(requested);
    return requested;
}

void TextureCollector::_validate(jeti::control::Material* requested)
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
        //Logger::Instance().warn("TextureCollector has no id="+std::to_string(id));
        return false;
    }
}

bool TextureCollector::hasTypeId(texture::Type type_id) const
{
    if (m_typesTextures.find(type_id) != m_typesTextures.end()) {
        return true;
    } else {
        //Logger::Instance().warn("TextureCollector has no type_id="+getStr(type_id));
        return false;
    }
}

jeti::control::Material* TextureCollector::_getTextureByClosestSizeId(const std::vector<jeti::control::Material*>& textures, int size_id)
{  
    jeti::control::Material* requested = _tryGetTextureBySizeId(textures, size_id);
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

jeti::control::Material* TextureCollector::_getTextureBySizeId(const std::vector<jeti::control::Material*>& textures, int size_id)
{
    jeti::control::Material* requested = _tryGetTextureBySizeId(textures, size_id);
    return requested;
}

jeti::control::Material* TextureCollector::_tryGetTextureBySizeId(const std::vector<jeti::control::Material*>& textures, int size_id)
{
    jeti::control::Material* requested = nullptr;
    for (jeti::control::Material* texture: textures) {
        if (texture->model()->size_id == size_id) {
            requested = texture;
            break;
        }
    }
    return requested;
}

