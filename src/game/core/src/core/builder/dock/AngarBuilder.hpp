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

#include <ceti/type/IdType.hpp>

namespace descriptor {
class AngarDescr;
} // namespace descriptor

namespace core {
namespace control {
class Angar;
} // namespace control
}

const unsigned int ANGAR_ITEM_SLOTS_NUM = 10;
const unsigned int ANGAR_VEHICLE_SLOTS_FOR_MILITARY_NUM = 6;
const unsigned int ANGAR_VEHICLE_SLOTS_FOR_VISITORS_NUM = 6;
const unsigned int ANGAR_VEHICLE_SLOTS_NUM = ANGAR_VEHICLE_SLOTS_FOR_MILITARY_NUM + ANGAR_VEHICLE_SLOTS_FOR_VISITORS_NUM;

namespace core {

class AngarBuilder
{
public:
    static core::control::Angar* gen();
    static core::control::Angar* gen(descriptor::AngarDescr*);

private:
    AngarBuilder() = delete;
    ~AngarBuilder() = delete;

    static void __createInternals(core::control::Angar*);
    static core::control::Angar* __createTemplate(descriptor::AngarDescr*);
}; 

} // namespace core






