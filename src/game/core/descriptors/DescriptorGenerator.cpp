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


#include "DescriptorGenerator.hpp"

#include <meti/RandUtils.hpp>
#include <common/Global.hpp>
#include <common/IdGenerator.hpp>

Descriptor generateHitDescriptor(const id_type& owner, const id_type& target, int damage)
{
    id_type id = global::get().idGenerator().nextId();
    std::map<std::string, std::string> map = {
        {Descriptor::KEY_ID, std::to_string(id)},
        {Descriptor::KEY_OWNER, std::to_string(owner)},
        {Descriptor::KEY_TARGET, std::to_string(target)},
        {Descriptor::KEY_DAMAGE, std::to_string(damage)}
    };

    Descriptor descriptor(map);
    return descriptor;
}

Descriptor generateBombDescriptor()
{
    id_type id = global::get().idGenerator().nextId();
    int damage = meti::getRandInt(10, 100);
    int radius = meti::getRandInt(100, 300);
    std::map<std::string, std::string> map = {
        {Descriptor::KEY_ID, std::to_string(id)},
        {Descriptor::KEY_DAMAGE, std::to_string(damage)},
        {Descriptor::KEY_RADIUS, std::to_string(radius)}
    };

    Descriptor descriptor(map);
    return descriptor;
}
