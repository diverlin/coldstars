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
#include "../render/Mesh.hpp"
#include "../common/rand.hpp"

MeshCollector& MeshCollector::Instance()
{
	static MeshCollector instance;
	return instance;
}
		
void MeshCollector::RegisterMesh(Mesh* mesh)
{
	mesh_vec.push_back(mesh);
}

Mesh* MeshCollector::GetMeshByTypeId(int type_id) const
{
	std::vector<Mesh*> result;
	for (unsigned int i=0; i<mesh_vec.size(); i++)
	{
		if (mesh_vec[i]->GetTypeId() == type_id)
		{
			result.push_back(mesh_vec[i]);
		}
	}
	
	if (result.size() == 0) 
	{
		throw "mesh with request type is not found";
		return NULL;
	}
	else
	{
		return result[getRandInt(0, result.size()-1)];
	}
}

		
