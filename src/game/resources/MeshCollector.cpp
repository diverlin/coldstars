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
}

void MeshCollector::addMesh(TYPE::MESH type, jeti::Mesh* mesh)
{
    auto it = meshes_map.find(type);
    if (it != meshes_map.end()) {
        throw std::runtime_error("mesh type is already exist");
    }
    meshes_map.insert(std::make_pair(type, mesh));
}

jeti::Mesh* MeshCollector::getMesh(TYPE::MESH type_id) const
{
//    std::vector<jeti::Mesh*> result;
//    for (unsigned int i=0; i<mesh_vec.size(); i++)
//    {
//        if (mesh_vec[i]->GetTypeId() == type_id)
//        {
//            result.push_back(mesh_vec[i]);
//        }
//    }
    
//    if (result.size() == 0)
//    {
//        throw "mesh with request type is not found";
//        return nullptr;
//    }
//    else
//    {
//        return result[getRandInt(0, result.size()-1)];
//    }
    auto it = meshes_map.find(type_id);
    if (it != meshes_map.end()) {
        return it->second;
    }
    throw std::runtime_error("mesh type not found");
}

        
