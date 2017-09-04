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
class Galaxy;
} // namespace descriptor

namespace control {
class Galaxy;
} // namespace control

namespace builder {

class Galaxy
{
public:
    static control::Galaxy* gen();
    static control::Galaxy* gen(int_t, int_t object = NONE);
    static control::Galaxy* gen(descriptor::Galaxy*);

private:
    Galaxy() = delete;
    ~Galaxy() = delete;

    static void __createInternals(control::Galaxy*, descriptor::Galaxy*);
    static control::Galaxy* __genTemplate(descriptor::Galaxy*, int_t object = NONE);
}; 

} // namespace builder





