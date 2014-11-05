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

#include <map>
#include <resources/MeshDescriptor.hpp>
#include <types/MeshTypes.hpp>
#include <vector>

namespace jeti {
    class Mesh;
}

class MeshCollector
{
    public:
        static MeshCollector& Instance();
        
        void add(jeti::Mesh*, const MeshDescriptor&);
        jeti::Mesh* getMesh(int) const;
        jeti::Mesh* getMesh(TYPE::MESH) const;

        ~MeshCollector();

    private:
        std::map<int, jeti::Mesh*> m_Meshes_map;
        std::map<TYPE::MESH, std::vector<jeti::Mesh*>> m_MeshesGroup_map;
        std::map<int, MeshDescriptor> m_Descriptors_map;

        MeshCollector() = default;

        MeshCollector(const MeshCollector&) = delete;
        MeshCollector& operator=(const MeshCollector&) = delete;

        bool isAbsent(jeti::Mesh* mesh) const;
};



