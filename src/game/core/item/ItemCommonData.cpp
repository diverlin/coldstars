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


#include "ItemCommonData.hpp"

#include <descriptors/Base.hpp>

ItemCommonData extractCommonData(const descriptor::Base& descriptor)
{
    ItemCommonData data;
    data.id          = descriptor.id();
    data.race        = (TYPE::RACE)descriptor.race();
    data.tech        = (TYPE::TECH)descriptor.tech();
    data.modules_num = descriptor.modulesNum();
    data.mass        = descriptor.mass();
    data.condition_max = descriptor.conditionMax();
    data.deterioration = descriptor.deterioration();
    data.price         = descriptor.price();
    data.descriptor_type = descriptor.type();
    return data;
}