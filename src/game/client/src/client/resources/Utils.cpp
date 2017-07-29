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

#include "Utils.hpp"

#include <core/manager/DescriptorManager.hpp>

#include <jeti/Material.hpp>
#include <jeti/Mesh.hpp>

namespace utils {

jeti::Mesh*
createMeshByDescriptorId(int_t id) {
    ceti::descriptor::Mesh* descriptor = descriptor::Manager::get().meshes()->get(id);
    assert(descriptor);
    jeti::Mesh* mesh = new jeti::Mesh(descriptor);
    assert(mesh);
    return mesh;
}

jeti::control::Material*
createMaterialByDescriptorId(int_t id) {
    ceti::descriptor::Material* descriptor = descriptor::Manager::get().materials()->get(id);
    assert(descriptor);
    jeti::model::Material* model = new jeti::model::Material(descriptor);
    jeti::control::Material* material = new jeti::control::Material(model);
    assert(material);
    return material;
}

jeti::control::Material*
createMaterialByDescriptorType(texture::Type type) {
    ceti::descriptor::Material* descriptor = descriptor::Manager::get().materials()->random(int(type));
    assert(descriptor);
    jeti::model::Material* model = new jeti::model::Material(descriptor);
    jeti::control::Material* material = new jeti::control::Material(model);
    assert(material);
    return material;
}

} // namespace utils

