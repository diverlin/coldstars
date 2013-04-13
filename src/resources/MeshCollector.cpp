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
#include "ObjMesh.hpp"

MeshCollector& MeshCollector::Instance()
{
	static MeshCollector instance;
	return instance;
}
		
void MeshCollector::RegisterMesh(ObjMesh* mesh)
{
	mesh_map.insert(std::make_pair(mesh->GetTypeId(), mesh));
}

ObjMesh* MeshCollector::GetMeshByTypeId(int type_id) const
{
	std::map<int, ObjMesh*>::const_iterator slice = mesh_map.find(type_id);
	return slice->second;
}

		
