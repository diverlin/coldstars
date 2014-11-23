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
#include <iostream>

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

void MeshCollector::add(jeti::Mesh* mesh, MeshDescriptor descriptor)
{
    if (isAbsent(mesh)) {
        m_Meshes_map.insert(std::make_pair(mesh->id(), mesh));
    } else {
        std::cout<<"mesh id="<<mesh->id()<<std::endl;
        throw std::runtime_error("mesh id is already exist");
    }

    auto it = m_MeshesGroup_map.find(descriptor.type);
    if (it == m_MeshesGroup_map.end()) {
        m_MeshesGroup_map.insert(std::make_pair(descriptor.type, std::vector<jeti::Mesh*> { mesh }));
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
        std::cout<<"id="<<id<<std::endl;
        throw std::runtime_error("mesh id not found");
    }
}

jeti::Mesh* MeshCollector::getMesh(TYPE::MESH type) const
{
    auto it = m_MeshesGroup_map.find(type);
    if (it != m_MeshesGroup_map.end()) {
        const std::vector<jeti::Mesh*> group = it->second;
        return group[getRandInt(0, group.size()-1)];
    } else {
        std::cout<<"mesh type="<<getTypeStr(type)<<std::endl;
        throw std::runtime_error("mesh type doesn't exist");
    }
}
