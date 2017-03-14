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

#include "MeshTypes.hpp"

std::string getTypeStr(mesh::type type)
{
    switch(type)
    {
        case mesh::type::FAILBACK:            { return "FAILBACK"; break; }

        case mesh::type::PLANE:            { return "PLANE"; break; }
        case mesh::type::SPHERE:           { return "SPHERE"; break; }
        case mesh::type::SPHERE_DEFORMED:  { return "SPHERE_DEFORMED"; break; }
        case mesh::type::SPACESTATION:     { return "SPACESTATION"; break; }

        default: { return "UKNOWN MESH TYPE"; break; }
    }
}

