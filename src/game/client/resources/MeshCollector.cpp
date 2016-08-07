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
#include <meti/RandUtils.hpp>

#include <iostream>

MeshCollector& MeshCollector::get()
{
    static MeshCollector instance;
    return instance;
}

MeshCollector::~MeshCollector()
{
    for (auto& pair: m_idsMeshes) {
        delete pair.second.second;
    }
}

void MeshCollector::add(jeti::Mesh* mesh, MeshDescriptor descriptor)
{
    if (!isExist(mesh)) {
        m_idsMeshes.insert(std::make_pair(mesh->id(), std::make_pair(descriptor, mesh)));
        m_typesMeshes[descriptor.type_id].push_back(std::make_pair( descriptor, mesh));
    } else {
        std::cout<<"mesh id="<<mesh->id()<<std::endl;
        throw std::runtime_error("mesh id is already exist");
    }
}

bool MeshCollector::isExist(jeti::Mesh* mesh) const
{
    auto it = m_idsMeshes.find(mesh->id());
    if (it != m_idsMeshes.end()) {
        return true;
    } else {
        return false;
    }
}

jeti::Mesh* MeshCollector::get(int id) const
{
    jeti::Mesh* requested = nullptr;

    auto it = m_idsMeshes.find(id);
    if (it != m_idsMeshes.end()) {
        requested = it->second.second;
    }

    assert(requested);
    return requested;
}

jeti::Mesh* MeshCollector::get(type::mesh type_id) const
{
    jeti::Mesh* requested = nullptr;

    auto it = m_typesMeshes.find(type_id);
    if (it != m_typesMeshes.end()) {
        const std::vector<std::pair<MeshDescriptor, jeti::Mesh*>>& vec = it->second;
        requested = meti::getRand(vec).second;
    }

    assert(requested);
    return requested;
}
