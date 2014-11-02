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


#include "MeshCollector.hpp"
#include <jeti/Mesh.hpp>
#include <math/rand.hpp>

MeshCollector& MeshCollector::Instance()
{
    static MeshCollector instance;
    return instance;
}

MeshCollector::~MeshCollector()
{
    for (auto& pair: meshes_map) {
        delete pair.second;
    }
    meshes_map.clear();
    descri_map.clear();
}

void MeshCollector::addMesh(const MeshDescriptor& descriptor, jeti::Mesh* mesh)
{
    auto it = meshes_map.find(mesh->id());
    if (it != meshes_map.end()) {
        throw std::runtime_error("mesh type is already exist");
    }
    meshes_map.insert(std::make_pair(mesh->id(), mesh));
    descri_map.insert(std::make_pair(mesh->id(), descriptor));
}

jeti::Mesh* MeshCollector::getMesh(int id) const
{
    auto it = meshes_map.find(id);
    if (it != meshes_map.end()) {
        return it->second;
    }
    throw std::runtime_error("mesh type not found");
}

jeti::Mesh* MeshCollector::getMesh(TYPE::MESH type) const
{
    std::vector<jeti::Mesh*> result;
    for (auto& pair: descri_map) {
        if (pair.second.type == type) {
            auto p = meshes_map.find(pair.first);
            result.push_back(p->second);
        }
    }

    if (result.empty()) {
        throw "mesh with request type is not found";
        return nullptr;
    } else {
        return result[getRandInt(0, result.size()-1)];
    }
}

