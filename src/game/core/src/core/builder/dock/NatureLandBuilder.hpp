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
class NatureLandDescr;
} // namespace descriptor

namespace core {
namespace control {
class NatureLand;
} // namespace control
}

namespace core {

class NatureLandBuilder
{
public:
    static core::control::NatureLand* gen();
    static core::control::NatureLand* gen(descriptor::NatureLandDescr*);

private:
    NatureLandBuilder() = delete;
    ~NatureLandBuilder() = delete;

    static core::control::NatureLand* __createTemplate(descriptor::NatureLandDescr*);
    static void __createInternals(core::control::NatureLand*);
}; 

} // namespace core




