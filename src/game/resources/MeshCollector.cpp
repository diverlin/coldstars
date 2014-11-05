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
    for (auto& pair: m_Meshes_map) {
        delete pair.second;
    }
}

void MeshCollector::add(jeti::Mesh* mesh, const MeshDescriptor& descriptor)
{
    if (isAbsent(mesh)) {
        m_Textures_map.insert(std::make_pair(mesh->id(), mesh));
    } else {
        std::cout<<"mesh id="<<mesh->id()<<std::endl;
        throw std::runtime_error("mesh id is already exist");
    }

    auto it = m_MeshesGroup_map.find(descriptor.type_id);
    if (it != m_MeshesGroup_map.end()) {
        m_MeshesGroup_map.insert(std::make_pair(descriptor.type_id, std::vector<jeti::Mesh*> { mesh }));
    } else {
        it->second.push_back(mesh);
    }

    m_Descriptors_map.insert(std::make_pair(mesh->id(), descriptor));
}

bool MeshCollector::isAbsent(jeti::Mesh* mesh) const
{
    auto it = m_Meshes_map.find(mesh->id());
    if (it != m_Meshes_map.end()) {
        return false;
    } else {
        return true;
    }
}

jeti::Mesh* MeshCollector::getMesh(int id) const
{
    auto it = m_Meshes_map.find(id);
    if (it != m_Meshes_map.end()) {
        return it->second;
    } else {
        throw std::runtime_error("mesh id not found");
    }
}

jeti::Mesh* MeshCollector::getMesh(TYPE::MESH type) const
{
    std::vector<jeti::Mesh*> result;
    for (auto& pair: m_Descriptors_map) {
        if (pair.second.type == type) {
            auto p = m_Meshes_map.find(pair.first);
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

