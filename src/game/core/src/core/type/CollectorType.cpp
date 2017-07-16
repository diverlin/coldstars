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

#include "CollectorType.hpp"

#include <core/type/TextureType.hpp>
#include <core/type/MeshType.hpp>

#include <cassert>

namespace type {

Collector::Collector() {
    __registerType(int_t(texture::Type::STAR), "texture::star");
    __registerType(int_t(texture::Type::PLANET), "texture::planet");
    __registerType(int_t(texture::Type::ASTEROID), "texture::asteroid");
    __registerType(int_t(texture::Type::SHIP), "texture::ship");
    __registerType(int_t(texture::Type::TURREL), "texture::turrel");
    __registerType(int_t(mesh::Type::SPHERE), "mesh::sphere");
    __registerType(int_t(mesh::Type::SPHERE_DEFORMED), "mesh::sphere_deformed");
    __registerType(int_t(mesh::Type::PLANE), "mesh::plane");
}

Collector::~Collector() {}

void
Collector::__registerType(int_t id, const std::string& info) {
    m_typesTextureString.insert(std::make_pair(id, info));
    m_typesStringTexture.insert(std::make_pair(info, id));
}

int_t
Collector::toInt(const std::string& info) const {
    const auto& it = m_typesStringTexture.find(info);
    if (it != m_typesStringTexture.end()) {
        return it->second;
    }
    assert(false);
    return -1;
}

} // namespace type
