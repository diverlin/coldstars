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


#include "ContainerDescriptorGenerator.hpp"

//#include <types/RaceTypes.hpp>
//#include <types/EntityTypes.hpp>

//#include <descriptors/RaceDescriptors.hpp>
//#include <meti/RandUtils.hpp>

#include <common/Global.hpp>
#include <common/IdGenerator.hpp>


ContainerDescriptor generateContainerDescriptor(const id_type& child_id)
{
    ContainerDescriptor descriptor;
    descriptor.id = global::get().idGenerator().nextId();
    descriptor.child_id = child_id;

    return descriptor;
}
