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

#include <string>

namespace descriptor {
class StarSystem;
} // namespace descriptor

namespace control {
class StarSystem;
} // namespace control

namespace builder {

class StarSystem
{
public:
    static control::StarSystem* gen(descriptor::StarSystem*);
    static control::StarSystem* gen(int_t, int_t ob_id = NONE);
    static control::StarSystem* gen();

private:
    StarSystem()=delete;
    ~StarSystem()=delete;

    static void __createInternals(control::StarSystem*, descriptor::StarSystem*);

    static void __createBackground(control::StarSystem&, int, int, int);
    static void __createStar(control::StarSystem&);
    static void __createPlanets(control::StarSystem&, int);

    static control::StarSystem* __genTemplate(descriptor::StarSystem*, int_t ob_id = NONE);
}; 

} // namespace builder
