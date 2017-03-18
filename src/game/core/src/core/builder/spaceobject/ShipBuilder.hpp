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


#include <core/builder/spaceobject/BaseVehicleBuilder.hpp>

#include <string>

namespace descriptor {
class Ship;
} // namespace model

namespace model {
class Ship;
} // namespace model

namespace builder {

class Ship : public BaseVehicle
{
public:
    static model::Ship* gen();
    static model::Ship* gen(descriptor::Ship*);

private:
    Ship()=delete;
    ~Ship()=delete;

    static model::Ship* __genTemplate(int_t);
    static void __createInternals(model::Ship*, descriptor::Ship*);
}; 

} // namespace builder


