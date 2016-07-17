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
#include <vector>

#include <resources/MeshDescriptor.hpp>
#include <types/MeshTypes.hpp>


namespace jeti {
class Mesh;
}

class MeshCollector
{
    public:
        static MeshCollector& Instance();
        
        void add(jeti::Mesh*, MeshDescriptor);
        jeti::Mesh* getMesh(int) const;
        jeti::Mesh* getMesh(type::MESH) const;

        ~MeshCollector();

    private:
        std::map<int, std::pair<MeshDescriptor, jeti::Mesh*>> m_idsMeshes;
        std::map<type::MESH, std::vector<std::pair<MeshDescriptor, jeti::Mesh*>>> m_typesMeshes;

        MeshCollector() = default;

        MeshCollector(const MeshCollector&) = delete;
        MeshCollector& operator=(const MeshCollector&) = delete;

        bool isExist(jeti::Mesh* mesh) const;
};



